#ifndef RGBLIGHT_LAYERS
  #error "RGBLIGHT_LAYERS need to be defined on ymd09/config.h"
#endif
#include QMK_KEYBOARD_H

// startfrom and numleds not endto
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_RED}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_CYAN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer    // Overrides caps lock layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_KP_7, KC_KP_8, KC_KP_9,
               KC_KP_4, LT(1, KC_KP_5), KC_KP_6,
               KC_KP_1, KC_KP_2, MO(1)),

  [1] = LAYOUT(RGB_RMOD, RGB_VAI, RGB_MOD,
               RGB_HUI, RESET, RGB_SAI,
               RGB_HUD, RGB_VAD, RGB_SAD),

  [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS),

  [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS),
};
