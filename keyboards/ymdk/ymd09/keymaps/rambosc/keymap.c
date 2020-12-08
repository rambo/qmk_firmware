#ifndef RGBLIGHT_LAYERS
  #error "RGBLIGHT_LAYERS need to be defined on ymd09/config.h"
#endif
#include QMK_KEYBOARD_H

// startfrom and numleds not endto
const rgblight_segment_t PROGMEM combat_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_RED}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM power_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_GREEN}
);

const rgblight_segment_t PROGMEM mb_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_CYAN}
);

const rgblight_segment_t PROGMEM debug_layer_colors[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_WHITE}
);

#define DEBUG_LAYER 6
#define CYCLE_LAST_LAYER 4
#define MG_LAYER 5

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    power_layer_colors,
    combat_layer_colors,
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
    rgblight_set_layer_state(2, layer_state_cmp(state, MG_LAYER));
    rgblight_set_layer_state(3, layer_state_cmp(state, DEBUG_LAYER));
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_F13, KC_F14, KC_F15,
               KC_F16, KC_F17, KC_F18,
               TO(CYCLE_LAST_LAYER), MO(MG_LAYER), TO(1)),

  [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               TO(0), KC_TRNS, TO(2)),

  [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               TO(1), KC_TRNS, TO(3)),

  [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               TO(2), KC_TRNS, TO(4)),

  [4] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               TO(3), KC_TRNS, TO(0)),

  [5] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               TO(DEBUG_LAYER), KC_TRNS, TO(DEBUG_LAYER)),


  [6] = LAYOUT(DEBUG, EEPROM_RESET, DEBUG,
               DEBUG, RESET, DEBUG,
               DEBUG, DEBUG, TO(0)),


};
