// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MPLY,        KC_MPLY, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DOWN,        KC_UP,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCTL_T(KC_RGHT),
                                  KC_LALT , TG(_LOWER),  KC_LGUI , LSFT_T(KC_SPC), RSFT_T(KC_ENT),  RGUI_T(KC_BSPC), TG(_RAISE), KC_RALT
    ),

    [_LOWER] = LAYOUT(
         _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX,   XXXXXXX, KC_LPRN, KC_RPRN,                          KC_HASH, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, KC_ASTR,KC_LBRC, KC_RBRC,                          KC_AMPR, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX,
        _______, XXXXXXX, KC_PAST, KC_GRV, KC_NUHS, KC_EQL,  _______,        _______, KC_DLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                   _______, _______, _______, _______,        _______, _______, _______, _______
    ),

    [_RAISE] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,        _______, KC_F6,   KC_KP_7,   KC_KP_8,   KC_KP_9,   KC_F10,  _______,
        _______, _______, _______, _______, _______, _______,                          _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
        _______, _______, _______, _______, _______, _______,                          _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, KC_KP_0, KC_PDOT, KC_COLN, KC_PMNS, _______,
                                            _______, _______, _______,        _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, AC_TOGG, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, UG_NEXT, UG_SATU, UG_TOGG,
        QK_RBT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX,  UG_PREV, UG_SATD, RGB_M_P,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                          XXXXXXX, XXXXXXX, XXXXXXX, UG_HUEU, UG_VALU, RGB_M_B,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UG_HUED, UG_VALD, RGB_M_R,
                                   _______, _______, _______, _______,        _______, _______, _______, _______
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLU, KC_VOLU) },
    [_RAISE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLU, KC_VOLU) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLU, KC_VOLU) }
};

#ifdef OLED_ENABLE
static void print_status_narrow(void) {
    // Create OLED content
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("ツ"), false);
    oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Upper \n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }

    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);

#ifdef AUTO_SHIFT_ENABLE

    bool autoshift = get_autoshift_state();
    oled_advance_page(true);
    oled_write_P(PSTR("Auto-Shift"), autoshift);
    oled_advance_page(true);

#endif


}

bool oled_task_user(void) {
    // Render the OLED
    print_status_narrow();
    return false;
}

#endif
