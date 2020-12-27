#ifndef RGBLIGHT_LAYERS
  #error "RGBLIGHT_LAYERS need to be defined on ymd09/config.h"
#endif
#include QMK_KEYBOARD_H

/*            HSV COLORS            */
#define HSV_WHITE_L 0, 0, 127
#define HSV_RED_L 0, 255, 127
#define HSV_CORAL_L 11, 176, 127
#define HSV_ORANGE_L 28, 255, 127
#define HSV_GOLDENROD_L 30, 218, 109
#define HSV_GOLD_L 36, 255, 127
#define HSV_YELLOW_L 43, 255, 127
#define HSV_CHARTREUSE_L 64, 255, 127
#define HSV_GREEN_L 85, 255, 127
#define HSV_SPRINGGREEN_L 106, 255, 127
#define HSV_TURQUOISE_L 123, 90, 56
#define HSV_TEAL_L 128, 255, 64
#define HSV_CYAN_L 128, 255, 127
#define HSV_AZURE_L 132, 102, 127
#define HSV_BLUE_L 170, 255, 127
#define HSV_PURPLE_L 191, 255, 127
#define HSV_MAGENTA_L 213, 255, 127
#define HSV_PINK_L 234, 128, 127


// startfrom and numleds not endto
const rgblight_segment_t PROGMEM ship_combat_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_RED_L}
);
const rgblight_segment_t PROGMEM ship_combat_layer2_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_PURPLE_L}
);

// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM power_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_GREEN_L}
);

const rgblight_segment_t PROGMEM travel_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_SPRINGGREEN_L}
);

const rgblight_segment_t PROGMEM xx_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_PINK_L}
);


const rgblight_segment_t PROGMEM mb_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_CYAN_L},
    {0, 1, HSV_RED},
    {2, 1, HSV_GREEN},
    {3, 1, HSV_RED},
    {5, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM debug_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_WHITE},
    {4, 1, HSV_RED},
    {7, 1, HSV_RED}
);

#define DEBUG_LAYER 6
#define CYCLE_LAST_LAYER 4
#define MG_LAYER 5

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    power_layer_colors,
    ship_combat_layer_colors,
    ship_combat_layer2_colors,
    xx_layer_colors,
    travel_layer_colors,
    mb_layer_colors,
    debug_layer_colors
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /**
   * "power" layer
   *
   * cycle layer back, mobiglass layer(hold), cycle layer forward
   * engines on/off, landing mode, vtol mode
   * power on/off, flight ready, wpns on/off
   */
  [0] = LAYOUT(TO(CYCLE_LAST_LAYER), MO(MG_LAYER), TO(1),
               KC_I, KC_N , KC_K,
               KC_U, KC_R, KC_P),

   /**
    * "ship combat" layer
    *
    * cycle layer back, mobiglass layer(hold), cycle layer forward
    * pin idx 1, pin idx 2, pin idx 3
    * shift (setting pins), gimbal mode, ai-turrets
    *
    */
  [1] = LAYOUT(TO(0), KC_TRNS, TO(2),
               KC_1, KC_2, KC_3,
               KC_LSHIFT, KC_G, KC_SLASH),

   /**
    * "ship combat" layer 2
    *
    * cycle layer back, mobiglass layer(hold), cycle layer forward
    * xx,xx,xx
    * remove pins, unlock target, xx
    */
  [2] = LAYOUT(TO(1), KC_TRNS, TO(3),
               KC_COMMA, KC_DOT, KC_BSLASH,
               KC_0, LSFT(KC_T), KC_SCOLON),

   /**
    * "XX" layer
    *
    * cycle layer back, mobiglass layer(hold), cycle layer forward
    */
  [3] = LAYOUT(TO(2), KC_TRNS, TO(4),
               KC_F3, KC_MINUS, KC_EQUAL,
               LSFT(KC_F3), LSFT(KC_MINUS), LSFT(KC_EQUAL)),

   /**
    * "travel" layer
    *
    * cycle layer back, mobiglass layer(hold), cycle layer forward
    * starmap, quantum drive, landing gear
    * exit seat, flight ready, ship lights
    */
  [4] = LAYOUT(TO(3), KC_TRNS, TO(0),
               KC_F2, KC_B, KC_N,
               KC_Y, KC_R, KC_L),

   /**
    * "mobiglass" layer
    *
    * accept, stay in mobiglass layer(hold), decline
    * chat, starmap, mobiglass
    * exit seat (y), go to debug layer, emergency exit seat (shift-u)
    */
  [5] = LAYOUT(KC_LBRACKET, KC_TRNS, KC_RBRACKET,
               KC_F12, KC_F2, KC_F1,
               KC_Y, TO(DEBUG_LAYER), LSFT(KC_U)),


  // debugs (and resets)
  [6] = LAYOUT(DEBUG, EEPROM_RESET, DEBUG,
               DEBUG, RESET, DEBUG,
               DEBUG, DEBUG, TO(0)),


};
