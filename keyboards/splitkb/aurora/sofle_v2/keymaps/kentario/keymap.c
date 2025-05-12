#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layers {
  DEF,
  NUM,
  SYM,
  EXT,
};

#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_LGUI OSM(MOD_LGUI) // LGUI and RGUI one shot keys are not used.
#define OS_RGUI OSM(MOD_RGUI)

#define OS_SYM OSL(SYM)
#define OS_EXT OSL(EXT)
#define MO_EXT MO(EXT)
#define OS_NUM OSL(NUM)

enum my_keycodes {
  // Will also clear caps word, I just can't think of a better name yet.
  CLEAR_OS = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT(
		   _______   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , CLEAR_OS  ,
		   KC_ESC    , KC_Q      , KC_W      , KC_F      , KC_P      , KC_B      ,                         KC_J      , KC_L      , KC_U      , KC_Y      , KC_SCLN   , KC_BSPC   ,
		   KC_TAB    , KC_A      , KC_R      , KC_S      , KC_T      , KC_G      ,                         KC_M      , KC_N      , KC_E      , KC_I      , KC_O      , KC_QUOT   ,
		   KC_LGUI   , KC_Z      , KC_X      , KC_C      , KC_D      , KC_V      , _______   , _______   , KC_K      , KC_H      , KC_COMM   , KC_DOT    , KC_SLSH   , OS_RGUI   ,
		                           _______   , QK_REP    , OS_LSFT   , KC_SPC    , OS_NUM    , OS_SYM    , KC_ENT    , OS_RSFT   , QK_AREP   , _______

		   ),

    [NUM] = LAYOUT(
		   KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     ,                         KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
		   KC_GRV    , KC_UNDS   , KC_LCBR   , KC_LPRN   , KC_LBRC   , KC_MINS   ,                         KC_PLUS   , KC_RBRC   , KC_RPRN   , KC_RCBR   , KC_SCLN   , KC_BSPC   ,
		   KC_TILD   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_BSLS   ,
		   _______   , KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , _______   , _______   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_DOT    , KC_SLSH   , KC_PIPE   ,
		                           _______   , _______   , _______   , _______   , _______   , MO_EXT    , _______   , _______   , _______   , _______
 		 ),

    [SYM] = LAYOUT(
		   _______   , _______   , _______   , _______   , _______   , _______   ,                         _______   , _______   , _______   , _______   , _______   , _______   ,
		   KC_GRV    , KC_UNDS   , KC_LCBR   , KC_LPRN   , KC_LBRC   , KC_MINS   ,                         KC_PLUS   , KC_RBRC   , KC_RPRN   , KC_RCBR   , KC_SCLN   , KC_BSPC   ,
		   KC_TAB    , KC_UNDS   , KC_EQUAL  , KC_PLUS   , KC_MINUS  , KC_LABK   ,                         KC_RABK   , KC_ASTR   , KC_8      , KC_9      , KC_PIPE   , KC_BSLS   ,
		   _______   , KC_EXLM   , KC_AT     , KC_PLUS   , KC_DLR    , KC_PERC   , _______   , _______   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_EQL    , KC_RPRN   , KC_PIPE   ,
		                           _______   , _______   , _______   , _______   , MO_EXT    , _______   , _______   , _______   , _______   , _______
		   ),

    [EXT] = LAYOUT(
		   KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     ,                         KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
		   _______   , KC_INS    , KC_PSCR   , KC_APP    , XXXXXXX   , XXXXXXX   ,                         KC_PGUP   , C(KC_LEFT), KC_UP     , C(KC_RGHT), C(KC_BSPC), KC_DEL   ,
		   _______   , KC_LGUI   , KC_LALT   , KC_LCTL   , KC_LSFT   , KC_CAPS   ,                         KC_PGDN   , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_RGUI   , KC_DEL    ,
		   _______   , C(KC_Z)   , C(KC_X)   , C(KC_C)   , C(KC_V)   , XXXXXXX   , _______   , _______   , XXXXXXX   , KC_HOME   , XXXXXXX   , KC_END    , XXXXXXX   , _______   ,
		                           _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______
		   )

    /* [SYM] = LAYOUT( */
    /* 		   KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     ,                         KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    , */
    /* 		   KC_GRV    , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_BSPC   , */
    /* 		   _______   , KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                         KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_LPRN   , KC_RPRN   , KC_PIPE   , */
    /* 		   _______   , KC_EQL    , KC_MINS   , KC_PLUS   , KC_LCBR   , KC_RCBR   , _______   , _______   , KC_LBRC   , KC_RBRC   , KC_SCLN   , KC_COLN   , KC_BSLS   , _______   , */
    /* 		                           _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______ */
    /* 		 ), */

    /* [2] = LAYOUT( */
    /* 		 _______   , _______   , _______   , _______   , _______   , _______   ,                         _______   , _______   , _______   , _______   , _______   , _______   , */
    /* 		 _______   , KC_INS    , KC_PSCR   , KC_APP    , XXXXXXX   , XXXXXXX   ,                         KC_PGUP   , C(KC_LEFT), KC_UP     , C(KC_RGHT), C(KC_BSPC), KC_BSPC   , */
    /* 		 _______   , KC_LALT   , KC_LCTL   , KC_LSFT   , XXXXXXX   , KC_CAPS   ,                         KC_PGDN   , KC_LEFT   , KC_DOWN   , KC_RGHT   , KC_DEL    , KC_BSPC   , */
    /* 		 _______   , C(KC_Z)   , C(KC_X)   , C(KC_C)   , C(KC_V)   , XXXXXXX   , _______   , _______   , XXXXXXX   , KC_HOME   , XXXXXXX   , KC_END    , XXXXXXX   , _______   , */
    /* 		                         _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______ */
    /* 		 ), */
    
     /* [3] = LAYOUT( */
    /* 		 XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                         XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , */
    /* 		 XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                         XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , */
    /* 		 XXXXXXX   , RGB_TOG   , RGB_HUI   , RGB_SAI   , RGB_VAI   , XXXXXXX   ,                         XXXXXXX   , KC_VOLD   , KC_MUTE   , KC_VOLU   , XXXXXXX   , XXXXXXX   , */
    /* 		 XXXXXXX   , RGB_MOD   , RGB_HUD   , RGB_SAD   , RGB_VAD   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_MPRV   , KC_MPLY   , KC_MNXT   , XXXXXXX   , XXXXXXX   , */
    /* 		                         _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______ */
    /* 		 ) */
};

//const uint16_t PROGMEM os_lctl_combo[] = {KC_S, KC_F, COMBO_END};
//const uint16_t PROGMEM os_rctl_combo[] = {KC_E, KC_U, COMBO_END};
//const uint16_t PROGMEM os_lalt_combo[] = {KC_R, KC_W, COMBO_END};
//const uint16_t PROGMEM os_ralt_combo[] = {KC_I, KC_Y, COMBO_END};
const uint16_t PROGMEM os_lctl_combo[] = {KC_SPC, OS_SYM, COMBO_END};
const uint16_t PROGMEM os_lalt_combo[] = {KC_ENT, OS_NUM, COMBO_END};

combo_t key_combos[] = {
  COMBO(os_lctl_combo, OS_LCTL),
  //  COMBO(os_rctl_combo, OS_RCTL),
  COMBO(os_lalt_combo, OS_LALT),
  //  COMBO(os_ralt_combo, OS_RALT),
  
};

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR_OS:
    if (record->event.pressed) {
    }
    return false;
  default:
    return true;
  }
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
