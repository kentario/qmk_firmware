#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_LGUI OSM(MOD_LGUI) // LGUI and RGUI one shot keys are not used.
#define OS_RGUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
		 _______   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , _______   ,
		 KC_ESC    , KC_Q      , KC_W      , KC_F      , KC_P      , KC_B      ,                         KC_J      , KC_L      , KC_U      , KC_Y      , KC_SCLN   , KC_BSPC   ,
		 KC_TAB    , KC_A      , KC_R      , KC_S      , KC_T      , KC_G      ,                         KC_M      , KC_N      , KC_E      , KC_I      , KC_O      , KC_QUOT   ,
		 MO(1)     , KC_Z      , KC_X      , KC_C      , KC_D      , KC_V      , _______   , _______   , KC_K      , KC_H      , KC_COMM   , KC_DOT    , KC_SLSH   , MO(2)     ,
		                         KC_LGUI   , OS_LALT   , OS_LSFT   , KC_SPC    , OS_LCTL   , OS_RCTL   , KC_ENT    , OS_RSFT   , OS_RALT   , KC_RGUI
		 ),


    [1] = LAYOUT(
		 _______   , KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     ,                         KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    ,
		 KC_GRV    , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_F12    ,
		 _______   , KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                         KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_LPRN   , KC_RPRN   , KC_PIPE   ,
		 _______   , KC_EQL    , KC_MINS   , KC_PLUS   , KC_LCBR   , KC_RCBR   , _______   , _______   , KC_LBRC   , KC_RBRC   , KC_SCLN   , KC_COLN   , KC_BSLS   , MO(3)     ,
		                         _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______
 		 ),

    [2] = LAYOUT(
		 _______   , _______   , _______   , _______   , _______   , _______   ,                         _______   , _______   , _______   , _______   , _______   , _______   ,
		 _______   , KC_INS    , KC_PSCR   , KC_APP    , XXXXXXX   , XXXXXXX   ,                         KC_PGUP   , C(KC_LEFT), KC_UP     , C(KC_RGHT), C(KC_BSPC), KC_BSPC   ,
		 _______   , KC_LALT   , KC_LCTL   , KC_LSFT   , XXXXXXX   , KC_CAPS   ,                         KC_PGDN   , KC_LEFT   , KC_DOWN   , KC_RGHT   , KC_DEL    , KC_BSPC   ,
		 MO(3)     , C(KC_Z)   , C(KC_X)   , C(KC_C)   , C(KC_V)   , XXXXXXX   , _______   , _______   , XXXXXXX   , KC_HOME   , XXXXXXX   , KC_END    , XXXXXXX   , _______   ,
		                         _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______
		 ),
    
    [3] = LAYOUT(
		 XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                         XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,
		 XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                         XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,
		 XXXXXXX   , RGB_TOG   , RGB_HUI   , RGB_SAI   , RGB_VAI   , XXXXXXX   ,                         XXXXXXX   , KC_VOLD   , KC_MUTE   , KC_VOLU   , XXXXXXX   , XXXXXXX   ,
		 XXXXXXX   , RGB_MOD   , RGB_HUD   , RGB_SAD   , RGB_VAD   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_MPRV   , KC_MPLY   , KC_MNXT   , XXXXXXX   , XXXXXXX   ,
		                         _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______
		 )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

/*
  I am working on configuring my aurora sofle v2 which I just built. On qmk, it has a keymap.json file. What should I do in order to add more configuration? Should i convert it to a .c? are there ways to add more functionality to it? What is the current best practice?
*/
