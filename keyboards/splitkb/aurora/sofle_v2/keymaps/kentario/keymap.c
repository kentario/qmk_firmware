// make splitkb/aurora/sofle_v2/rev1:kentario:flash
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layers {
  COL,
  EXT,
  NUM,
  SYM,
  QWT,
};

#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_LGUI OSM(MOD_LGUI) // LGUI and RGUI one shot keys are not used.
#define OS_RGUI OSM(MOD_RGUI)

// For switching layers
#define DF_COL DF(COL)
#define DF_QWT DF(QWT)

#define OS_SYM OSL(SYM)
#define MO_SYM MO(SYM)
#define OS_EXT OSL(EXT)
#define MO_EXT MO(EXT)
#define OS_NUM OSL(NUM)

enum my_keycodes {
  // Will also clear caps word, I just can't think of a better name yet.
  CLEAR_OS = SAFE_RANGE,
};

enum tap_dance_keycodes {
  TD_NUM,
  TD_EXT,
};

typedef enum {
  TD_NONE,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_TRIPLE_TAP,
  TD_TRIPLE_HOLD,
} td_state_t;

static td_state_t td_state = TD_NONE;

typedef struct {
  uint8_t layer;
  uint8_t mod;
} td_layer_mod_t;

td_state_t current_dance (tap_dance_state_t *state) {
  switch (state->count) {
  case 1:
    return state->pressed ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
  case 2:
    return state->pressed ? TD_DOUBLE_HOLD : TD_DOUBLE_TAP;
  case 3:
    return state->pressed ? TD_TRIPLE_HOLD : TD_TRIPLE_TAP;
  default:
    return TD_NONE;
  }
}

void td_oslm_finished (tap_dance_state_t *state, void *user_data) {
  td_layer_mod_t *cfg = (td_layer_mod_t *)user_data;
  td_state = current_dance(state);
  
  switch (td_state) {
  case TD_SINGLE_TAP:
    set_oneshot_layer(cfg->layer, ONESHOT_START);
    break;
    
  case TD_SINGLE_HOLD:
    layer_on(cfg->layer);
    break;
    
  case TD_DOUBLE_TAP:
    set_oneshot_mods(cfg->mod);
    break;

  case TD_DOUBLE_HOLD:
    add_mods(cfg->mod);
    break;

  case TD_TRIPLE_TAP:
    set_oneshot_layer(cfg->layer, ONESHOT_START);
    set_oneshot_mods(cfg->mod);
    break;

  case TD_TRIPLE_HOLD:
    layer_on(cfg->layer);
    add_mods(cfg->mod);
    break;

  default:
    break;
  }
}

void td_oslm_reset (tap_dance_state_t *state, void *user_data) {
  td_layer_mod_t *cfg = (td_layer_mod_t *)user_data;
  
  switch (td_state) {
  case TD_SINGLE_TAP:
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    break;

  case TD_SINGLE_HOLD:
    layer_off(cfg->layer);
    break;

  case TD_DOUBLE_HOLD:
    del_mods(cfg->mod);
    break;

  case TD_TRIPLE_TAP:
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    break;
    
  case TD_TRIPLE_HOLD:
    layer_off(cfg->layer);
    del_mods(cfg->mod);
    break;

  default:
    break;
  }

  td_state = TD_NONE;
}

#define ACTION_TAP_DANCE_OSLM(config)				\
  {								\
    .fn        = {NULL, td_oslm_finished, td_oslm_reset},	\
    .user_data = (void *)&(config),				\
  }

static const td_layer_mod_t td_num_cfg = {NUM, MOD_LCTL};
static const td_layer_mod_t td_ext_cfg = {EXT, MOD_LALT};

tap_dance_action_t tap_dance_actions[] = {
  [TD_NUM] = ACTION_TAP_DANCE_OSLM(td_num_cfg),
  [TD_EXT] = ACTION_TAP_DANCE_OSLM(td_ext_cfg),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [COL] = LAYOUT(
		   _______   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , DF_QWT    ,
		   KC_ESC    , KC_Q      , KC_W      , KC_F      , KC_P      , KC_B      ,                         KC_J      , KC_L      , KC_U      , KC_Y      , KC_SCLN   , KC_QUOT   ,
		   KC_TAB    , KC_A      , KC_R      , KC_S      , KC_T      , KC_G      ,                         KC_M      , KC_N      , KC_E      , KC_I      , KC_O      , KC_BSPC   ,
		   KC_LGUI   , KC_Z      , KC_X      , KC_C      , KC_D      , KC_V      , _______   , _______   , KC_K      , KC_H      , KC_COMM   , KC_DOT    , KC_SLSH   , OS_RGUI   ,
		                           CLEAR_OS  , QK_REP    , OS_LSFT   , KC_SPC    , TD(TD_NUM), TD(TD_EXT), KC_ENT    , OS_RSFT   , QK_AREP   , _______

		   ),

    [QWT] = LAYOUT(
		   KC_ESC    , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , DF_COL    ,
		   KC_TAB    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      ,                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_QUOT   ,
		   KC_LCTL   , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      ,                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , KC_BSPC   ,
		   KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B      , _______   , _______   , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , OS_RGUI   ,
		                           CLEAR_OS  , MO(SYM)   , KC_LALT   , KC_SPC    , KC_SPC    , KC_ENT    , KC_ENT    , _______   , _______   , _______

		   ),
    
    [NUM] = LAYOUT(
		   KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     ,                         KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
		   KC_GRV    , KC_EQUAL  , KC_MINUS  , KC_LPRN   , KC_PLUS   , KC_MINS   ,                         KC_PLUS   , KC_ASTR   , KC_RPRN   , KC_SLSH   , KC_SCLN   , KC_BSLS   ,
		   _______   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , _______   ,
 		   _______   , KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , _______   , _______   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_LPRN   , KC_RPRN   , KC_PIPE   ,
		                           CLEAR_OS  , _______   , _______   , _______   , _______   , MO_SYM    , _______   , _______   , _______   , _______
		   ),

    [EXT] = LAYOUT(
		   KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     ,                         KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
		   _______   , KC_INS    , KC_PSCR   , KC_APP    , XXXXXXX   , XXXXXXX   ,                         KC_PGUP   , C(KC_LEFT), KC_UP     , C(KC_RGHT), C(KC_BSPC), KC_BSPC   ,
		   _______   , KC_LGUI   , KC_LALT   , KC_LCTL   , KC_LSFT   , KC_CAPS   ,                         KC_PGDN   , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_BSPC   , KC_DEL    ,
		   _______   , C(KC_Z)   , C(KC_X)   , C(KC_C)   , C(KC_V)   , XXXXXXX   , _______   , _______   , XXXXXXX   , KC_HOME   , KC_BSPC   , KC_END    , XXXXXXX   , _______   ,
		                           CLEAR_OS  , _______   , _______   , _______   , MO_SYM    , _______   , _______   , _______   , _______   , _______
		   ),

    [SYM] = LAYOUT(
		   _______   , _______   , _______   , _______   , _______   , _______   ,                         _______   , _______   , _______   , _______   , _______   , _______   ,
		   KC_GRV    , KC_UNDS   , KC_LCBR   , KC_LPRN   , KC_LBRC   , KC_MINS   ,                         KC_PLUS   , KC_RBRC   , KC_RPRN   , KC_RCBR   , KC_SCLN   , KC_PIPE   ,
		   _______   , KC_UNDS   , KC_EQUAL  , KC_PLUS   , KC_MINUS  , KC_LABK   ,                         KC_RABK   , KC_ASTR   , KC_8      , KC_9      , KC_PIPE   , _______   ,
		   _______   , KC_EXLM   , KC_AT     , KC_PLUS   , KC_DLR    , KC_PERC   , _______   , _______   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_EQL    , KC_RPRN   , KC_PIPE   ,
		                           CLEAR_OS  , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______   , _______
		   ),

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

const uint16_t PROGMEM os_lctl_combo[] = {KC_SPC, OS_EXT, COMBO_END};
const uint16_t PROGMEM os_lalt_combo[] = {KC_ENT, OS_NUM, COMBO_END};

combo_t key_combos[] = {
  //  COMBO(os_lctl_combo, OS_LCTL),
  //  COMBO(os_lalt_combo, OS_LALT),
};

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR_OS:
    if (record->event.pressed) {
      // Modifiers
      clear_mods();
      clear_oneshot_mods();
      // Layers
      layer_clear();
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      reset_oneshot_layer();
      // Caps word
      caps_word_off();
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
