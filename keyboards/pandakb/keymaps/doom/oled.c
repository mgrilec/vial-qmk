oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

static const char PROGMEM IMP_SPRITE0[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 32, 160, 224, 224, 160, 32, 64, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 156, 227, 4, 199, 23, 140, 200, 200, 140, 23, 199, 6, 227, 92, 128, 128, 0, 0, 0, 128, 128, 192, 192, 199, 207, 63, 14, 2, 5, 31, 31, 27, 65, 64, 0, 3, 0, 24, 24, 24, 24, 0, 3, 0, 0, 97, 123, 62, 31, 15, 7, 3, 7, 31, 99, 0, 0, 0, 128, 96, 16, 16, 32, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 32, 16, 16, 32, 192, 0, 0, 0, 120, 134, 1, 0, 0, 192, 60, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 28, 96, 192, 32, 31, 0, 0, 8, 4, 3, 0, 0, 0, 127, 128, 0, 0, 0, 0, 0, 0, 0, 0, 252, 252, 0, 0, 0, 0, 0, 0, 0, 0, 224, 31, 2, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 1, 6, 120, 128, 0, 24, 0, 0, 0, 15, 240, 255, 0, 0, 0, 14, 0, 192, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 144, 201, 134, 128, 96, 128, 192, 135, 152, 111, 16, 24, 16, 12, 24, 17, 14, 0, 0, 0, 0, 0, 0,
};

static const char PROGMEM IMP_SPRITE1[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 64, 192, 192, 64, 64, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 128, 128, 0, 0, 128, 128, 128, 64, 248, 198, 9, 14, 44, 25, 145, 145, 25, 44, 14, 13, 6, 248, 128, 128, 0, 0, 0, 0, 128, 192, 192, 163, 63, 7, 3, 5, 6, 14, 11, 73, 64, 0, 0, 0, 0, 25, 25, 25, 25, 0, 0, 0, 0, 64, 64, 10, 31, 13, 1, 3, 3, 3, 29, 0, 0, 0, 0, 224, 16, 16, 32, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 32, 16, 16, 224, 0, 128, 0, 0, 0, 28, 227, 0, 0, 192, 56, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 3, 1, 1, 193, 64, 34, 17, 16, 2, 2, 1, 0, 0, 0, 63, 192, 0, 0, 0, 0, 0, 0, 0, 192, 60, 240, 0, 0, 0, 0, 7, 7, 0, 0, 240, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 14, 48, 192, 0, 56, 0, 0, 1, 194, 63, 252, 0, 0, 0, 6, 0, 0, 134, 121, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 51, 32, 24, 32, 48, 32, 31, 96, 145, 142, 192, 128, 96, 128, 134, 217, 144, 96, 0, 0, 0, 0,
};

static const char PROGMEM IMP_SPRITE2[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 96, 144, 232, 196, 148, 28, 28, 148, 196, 232, 208, 96, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 224, 224, 192, 192, 160, 224, 160, 32, 19, 28, 0, 0, 2, 17, 25, 25, 17, 2, 0, 0, 12, 19, 16, 96, 160, 32, 32, 112, 112, 248, 56, 24, 25, 7, 0, 0, 0, 1, 0, 8, 8, 8, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 8, 10, 1, 1, 0, 0, 0, 0, 3, 12, 0, 0, 0, 56, 68, 130, 2, 196, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 4, 2, 4, 120, 128, 0, 0, 8, 16, 16, 16, 8, 7, 248, 7, 0, 0, 32, 0, 0, 0, 0, 192, 192, 0, 0, 0, 0, 0, 0, 0, 1, 14, 240, 0, 30, 33, 32, 32, 0, 0, 0, 0, 0, 0, 15, 112, 128, 0, 0, 0, 0, 0, 0, 31, 239, 240, 0, 0, 0, 128, 0, 0, 128, 124, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 15, 16, 224, 6, 0, 0, 0, 0, 255, 224, 0, 0, 1, 0, 128, 97, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 16, 12, 16, 24, 112, 159, 135, 192, 128, 96, 128, 135, 200, 144, 96, 0, 0, 0, 0, 0,
};

static const char PROGMEM IMP_SPRITE3[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 32, 160, 224, 224, 160, 32, 64, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 128, 128, 0, 128, 192, 128, 128, 92, 99, 4, 7, 30, 140, 200, 200, 140, 30, 7, 6, 99, 92, 64, 64, 96, 64, 64, 192, 224, 224, 240, 32, 115, 115, 15, 7, 1, 2, 7, 10, 32, 32, 0, 0, 0, 12, 12, 12, 12, 0, 0, 0, 0, 32, 32, 12, 5, 7, 6, 1, 1, 7, 8, 48, 16, 0, 0, 0, 0, 28, 40, 208, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 24, 6, 4, 248, 0, 0, 0, 0, 1, 2, 2, 4, 4, 4, 194, 58, 7, 0, 192, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 12, 112, 224, 17, 14, 0, 0, 128, 0, 0, 0, 0, 0, 0, 31, 224, 0, 0, 3, 3, 0, 0, 0, 192, 63, 240, 0, 0, 0, 0, 0, 0, 192, 56, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 62, 195, 2, 0, 0, 0, 7, 8, 255, 176, 64, 0, 6, 0, 0, 113, 142, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 216, 135, 128, 96, 128, 192, 135, 158, 105, 12, 8, 6, 8, 12, 8, 7, 0, 0, 0, 0, 0, 0,
};

static const char* const PROGMEM imp_sprite_frames[] = {
    IMP_SPRITE0,
    IMP_SPRITE1,
    IMP_SPRITE2,
    IMP_SPRITE3
};

#define IMP_SPRITE_FRAMES_COUNT (sizeof(imp_sprite_frames) / sizeof(imp_sprite_frames[0]))

/* KEYBOARD PET START */

/* advanced settings */
#define ANIM_FRAME_DURATION 100 // how long each frame lasts in ms

/* timers */
// static uint16_t key_timer; // timer to track the last keyboard activity
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
char  current_wpm_str[3];
led_t led_usb_state;

bool isSneaking = false;
bool isBarking  = false;
bool isJumping  = false;
bool showedJump = true;

/* KEYBOARD PET END */

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[]   = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[]   = {0x20, 0x9a, 0x9b, 0x9c, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[]  = {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if (layer_state_is(3)) {
        oled_write_P(adjust_layer, false);
    } else if (layer_state_is(2)) {
        oled_write_P(lower_layer, false);
    } else if (layer_state_is(1)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

static void render_imp(void) {

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        current_frame++;
        if (current_frame >= IMP_SPRITE_FRAMES_COUNT) {
            current_frame = 0;
        }
    }

    oled_write_raw_P(imp_sprite_frames[current_frame], sizeof(IMP_SPRITE0));
}

static void render_logo(void) {
    // logo图像，在https://joric.github.io/qle/生成，需要做成32*128大小的，然后把“static const unsigned char”改成“static const char”
    static const char PROGMEM raw_logo[] = {
        0,   128, 64,  64,  0,   64,  64,  128, 0,  0,  0,   128, 64,  32,  16,  8,   4,   2,   2,  2,   2,  2,   2,   2,   4,   12,  24,  224, 0,   0,  0,   0,   31,  32,  32,  224, 0,   192, 224, 249, 250, 253, 253, 254, 252, 240, 224, 192, 128, 128, 0, 0,  0,   0,   0,   0,   0,   0,  0,  159, 0,  0,  0,   0,   0,  0,  254, 1,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 127, 127, 63, 63, 63, 31, 31, 31,  14,  14,  6,   2,   0,   3,   2,   4,   56,  0,   128, 64,  33, 22, 25,  7,   15,  15,  15, 195, 225, 225, 240, 240, 240, 240, 248, 248, 248, 248, 248, 248, 248, 240, 240, 224, 192, 128, 0,  240, 14, 0,  3,   204, 48, 192, 224, 240, 248, 254, 255, 255, 255, 255, 255, 255, 63, 31, 15, 15, 15, 7,  15, 31,  255, 255, 255, 255, 255, 255, 254, 225, 252, 0, 0,  15,  224, 63,  255, 255, 255, 255, 255, 255, 255,
        255, 255, 252, 240, 246, 246, 240, 240, 56, 28, 127, 255, 127, 255, 255, 255, 255, 255, 51, 255, 0,  0,   0,   253, 2,   1,   3,   15,  31,  63, 127, 127, 127, 255, 255, 225, 197, 133, 129, 131, 134, 252, 255, 255, 254, 255, 255, 255, 63,  3,   0, 31, 192, 0,   0,   0,   1,   1,  2,  2,   2,  2,  193, 225, 96, 98, 194, 226, 98,  98,  227, 199, 13,  11,  19,  35,  67,  65,  65,  64,  64, 64, 32, 60, 3,  0,   0,   0,   0,   0,   0,   0,   0,   0,   207, 207, 140, 140, 13, 13, 140, 140, 207, 207, 0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   56, 57, 59,  63,  63, 63,  63,  187, 185, 184, 128, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 62, 127, 255, 227, 3,   3,   3,   3,   113, 120, 56,
        56,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   12, 30,  30, 126, 254, 254, 142, 128, 128, 128, 128, 28, 60,  56,  56,  0,   3,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0,   224, 241, 251, 251, 59, 59, 59,  57, 56, 0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  193, 227, 231, 103, 103, 119, 247, 247, 247, 0,   0,   60,  42,  42, 42, 42,  0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 128, 199, 207, 223, 156, 24,  24,  31,  15, 7,   0,  0,  142, 17,  17, 17,  142, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  14, 63, 59, 113, 113, 113, 127, 127, 112, 112, 112, 112, 0,   0, 3,  4,   4,   100, 99,  0,   0,   0,   0,   0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    // Renders the current keyboard state (layers and mods)
    /* KEYBOARD PET VARIABLES START */

    if (is_keyboard_master()) {
        render_imp(); // Renders the keyboard pet
    } else {
        render_logo(); // Renders a static logo
    }
    return false;
}
