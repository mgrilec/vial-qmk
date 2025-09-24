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

float circle_radius = 5.0f;
float circle_grow_speed = 30.0f;
float max_circle_radius = OLED_DISPLAY_WIDTH;

/* status variables */
int   current_wpm = 0;
char  current_wpm_str[3];
led_t led_usb_state;

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

static void draw_prism(int x, int y, int size) {
    draw_line(x - size, y, x, y + size);
    draw_line(x, y + size, x + size, y);
    draw_line(x + size, y, x, y - size);
    draw_line(x, y - size, x - size, y);
}

static void update_left(float dt) {
    circle_radius += circle_grow_speed * dt;
    if (circle_radius > max_circle_radius) {
        circle_radius = 5.0f; // Reset radius if it exceeds max
    }
}

static void draw_left(float dt) {
    oled_clear();
    draw_circle(15, OLED_DISPLAY_WIDTH - 1, circle_radius);
    draw_prism(15, 32, 5);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Code here runs when any key is pressed
        circle_radius = 5.0f; // Reset radius on key press
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
