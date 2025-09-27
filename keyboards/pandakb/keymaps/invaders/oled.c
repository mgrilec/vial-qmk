#define M_PI 3.14159f
#define M_PI_2 (M_PI/2)  // π/2
#define M_2PI (2*M_PI)   // 2π

#define ENEMY_ROWS 4
#define ENEMY_COLS 3
#define ENEMY_SPACING 8

typedef struct {
    float x;
    float y;
    bool alive;
} Enemy;

Enemy wave[ENEMY_ROWS * ENEMY_COLS];

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

/* timers */
uint32_t last_time_since_startup_ms = 0;
uint32_t time_since_startup_ms = 0;
uint32_t dt_ms;
float dt_seconds;

float rotation = 0.0f;
float rotation_speed = M_PI_2;

float y = 0.0f;
float y_amplitude = 5.0f;
float y_frequency = 1.0f;
float y_phase = 0.0f;

float scale = 1.0f;
float scale_max = 2.0f;

/* status variables */
int   current_wpm = 0;
char  current_wpm_str[3];
led_t led_usb_state;

/* player variables */
float player_x = 16.0f;  // Start at center of 32-pixel wide screen
float player_speed = 20.0f;
int player_direction = 1;  // 1 for right, -1 for left

__attribute__((unused))
static float to_radians(float degrees) {
    return degrees * M_PI / 180.0f;
}

__attribute__((unused))
static float my_sin(float angle) {
    while (angle < 0) angle += M_2PI;
    while (angle >= M_2PI) angle -= M_2PI;

    // Simple lookup table approach with interpolation
    static const float sin_table[] = {
        0.0f, 0.5f, 0.866f, 1.0f, 0.866f, 0.5f, 0.0f,
        -0.5f, -0.866f, -1.0f, -0.866f, -0.5f
    };

    float scaled_angle = (angle * 6.0f) / M_PI;
    int index1 = (int)scaled_angle;
    int index2 = (index1 + 1) % 12;
    float fraction = scaled_angle - index1;

    return sin_table[index1] + (sin_table[index2] - sin_table[index1]) * fraction;
}

__attribute__((unused))
static float my_cos(float angle) {
    return my_sin(angle + M_PI_2);
}

__attribute__((unused))
static float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

static void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        oled_write_pixel(x0, y0, true);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Bresenham's circle drawing algorithm
__attribute__((unused))
static void draw_circle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        // Draw 8 octants
        oled_write_pixel(xc + x, yc + y, true);
        oled_write_pixel(xc - x, yc + y, true);
        oled_write_pixel(xc + x, yc - y, true);
        oled_write_pixel(xc - x, yc - y, true);
        oled_write_pixel(xc + y, yc + x, true);
        oled_write_pixel(xc - y, yc + x, true);
        oled_write_pixel(xc + y, yc - x, true);
        oled_write_pixel(xc - y, yc - x, true);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

static void update_player(float dt) {
    // Move player
    player_x += player_speed * player_direction * dt;

    // Check bounds and reverse direction
    if (player_x >= 28) { // Screen width (32) - player width (4)
        player_direction = -1;
        player_x = 28;  // Prevent overshooting
    } else if (player_x <= 4) { // Player width
        player_direction = 1;
        player_x = 4;  // Prevent overshooting
    }
}

static void draw_player(int x, int y, int size) {
    // Draw the main body (triangle shape)
    draw_line(x - size, y + size, x + size, y + size);     // Base
    draw_line(x - size, y + size, x, y - size);            // Left diagonal
    draw_line(x + size, y + size, x, y - size);            // Right diagonal

    // Draw the cannon (vertical line on top)
    draw_line(x, y - size, x, y - size - size/2);          // Cannon

    // Draw the base extensions
    draw_line(x - size - size/2, y + size, x - size, y + size);   // Left base
    draw_line(x + size, y + size, x + size + size/2, y + size);   // Right base
}

static void draw_enemy(int x, int y) {
    oled_write_pixel(x, y, true);
    oled_write_pixel(x + 5, y, true);

    oled_write_pixel(x + 1, y - 1, true);
    oled_write_pixel(x + 4, y - 1, true);

    oled_write_pixel(x, y - 2, true);
    oled_write_pixel(x + 1, y - 2, true);
    oled_write_pixel(x + 2, y - 2, true);
    oled_write_pixel(x + 3, y - 2, true);
    oled_write_pixel(x + 4, y - 2, true);
    oled_write_pixel(x + 5, y - 2, true);

    oled_write_pixel(x, y - 3, true);
    oled_write_pixel(x + 2, y - 3, true);
    oled_write_pixel(x + 3, y - 3, true);
    oled_write_pixel(x + 5, y - 3, true);

    oled_write_pixel(x + 1, y - 4, true);
    oled_write_pixel(x + 2, y - 4, true);
    oled_write_pixel(x + 3, y - 4, true);
    oled_write_pixel(x + 4, y - 4, true);

    oled_write_pixel(x + 2, y - 5, true);
    oled_write_pixel(x + 3, y - 5, true);
}

static void init_wave(void) {
    // Calculate starting position for first enemy
    int start_x = 0;   // Start from left edge
    int start_y = 12;  // Start from top of screen with some margin

    // Create enemies in a grid formation
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {

            Enemy *e = &wave[row * ENEMY_COLS + col];
            e->x = start_x + (col * ENEMY_SPACING);
            e->y = start_y + (row * ENEMY_SPACING);
            e->alive = true;
        }
    }
}

static void draw_wave(void) {
    for (int i = 0; i < ENEMY_ROWS * ENEMY_COLS; i++) {
        if (wave[i].alive) {
            draw_enemy((int)wave[i].x, (int)wave[i].y);
        }
    }
}

__attribute__((unused))
static void draw_prism(int x, int y, int size) {
    draw_line(x - size, y, x, y + size);
    draw_line(x, y + size, x + size, y);
    draw_line(x + size, y, x, y - size);
    draw_line(x, y - size, x - size, y);
}

static void update_left(float dt) {
    update_player(dt);
}

static void draw_left(float dt) {
    oled_clear();
    draw_wave();
    draw_player((int)player_x, 120, 4);  // Draw player at bottom of 32-pixel screen
}

void keyboard_post_init_user(void) {
    init_wave();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        scale = scale_max;
    }
    return true; // Return true to continue processing the key press
}

bool oled_task_user(void) {
    last_time_since_startup_ms = time_since_startup_ms;
    time_since_startup_ms = timer_read32();
    dt_ms = timer_elapsed32(last_time_since_startup_ms);
    dt_seconds = dt_ms / 1000.0f;

    if (is_keyboard_master()) {
        update_left(dt_seconds);
        draw_left(dt_seconds);
    } else {

    }
    return false;
}
