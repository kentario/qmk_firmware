#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

#define _QWERTY 0
#define _COLEMAK_MOD_DH 1
#define _FL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _QWERTY: QWERTY layer (Default Layer)
   */
    [_QWERTY] = LAYOUT(
        KC_ESC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,         KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,          KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,          KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
        OSM(MOD_LCTL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,          KC_SCLN, KC_QUOT, KC_ENT,
        OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,        KC_SLSH, OSM(MOD_RSFT),                        KC_UP,
        KC_CAPS,       KC_LGUI, OSM(MOD_LALT),             KC_SPC,                             OSM(MOD_RALT), MO(_FL), KC_APP,  OSM(MOD_RCTL),      KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* Keymap _COLEMAK_MOD_DH: Colemak Mod-DH layer
     */
    [_COLEMAK_MOD_DH] = LAYOUT(
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______,            _______, _______, _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,   _______, _______, _______,
        _______,       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,          KC_SCLN, _______, _______, _______,   _______, _______, _______,
        _______,       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,          KC_O,    _______, _______,
        _______,       KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,    KC_K,    KC_H,    _______, _______,       _______, _______,                              _______,
        _______,       _______, _______,                   _______,                            _______,       MO(_FL), _______, _______,            _______, _______, _______
    ),
    /* Keymap _FL: Function Layer
     */
    [_FL] = LAYOUT(
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______,            KC_MUTE, _______, _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU,
        _______,       RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______,       _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD,
        _______,       RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______,       _______, _______, _______,
        _______,       RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______,       _______, _______,                              _______,
        _______,       _______, _______,                   _______,                            _______,       MO(_FL), _______, _______,            _______, _______, _______
    ),
};

// Chord to type the leader key.
const uint16_t PROGMEM leader_combo[] = {KC_L, KC_E, COMBO_END};

combo_t key_combos[] = {
  COMBO(leader_combo, QK_LEAD),
};

/*
  qy to switch to QWERTY layer
  cd to switch to Colemak Mod-DH layer
 */
void leader_end_user (void) {
  if (leader_sequence_two_keys(KC_Q, KC_Y)) {
    tap_code16(DF(_QWERTY));
  } else if (leader_sequence_two_keys(KC_C, KC_D)) {
    tap_code16(DF(_COLEMAK_MOD_DH));
  }
}

#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}
