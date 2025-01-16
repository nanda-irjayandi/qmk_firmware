// Copyright 2022 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Super Alt Tab currently disabled due to persistent button press Bug and performance cost

bool is_recording = false;

// enum custom_keycodes {
//     TD_RSFT
// };



// void dance_egg(tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         set_oneshot_mods(MOD_BIT(KC_RSFT));
//     } else if (state->count == 2) {
//         register_code(KC_LBRC);
//         unregister_code(KC_LBRC);
//     } else if (state->count == 3) {
//         register_code(KC_RBRC);
//         unregister_code(KC_RBRC);
//     }
// };

// void dance_egg(tap_dance_state_t *state, void *user_data){
//     switch (state->count) {
//         case 1:
//             set_oneshot_mods(MOD_BIT(KC_RSFT));
//             break;
//         case 2:
//             register_code(KC_LBRC);
//             unregister_code(KC_LBRC);
//             break;
//         case 3:
//             register_code(KC_RBRC);
//             unregister_code(KC_RBRC);
//             break;
//     }
// }

// tap_dance_action_t tap_dance_actions[] = {
//     [TD_RSFT] = ACTION_TAP_DANCE_FN(dance_egg),
// };


const rgblight_segment_t PROGMEM DEV_LAYER[]          = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_GREEN});
const rgblight_segment_t PROGMEM DATA_LAYER[]         = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_BLUE});
const rgblight_segment_t PROGMEM MOD_LAYER[]          = RGBLIGHT_LAYER_SEGMENTS({0, 16, HSV_RED});
const rgblight_segment_t PROGMEM FUNCTION_LAYER[]     = RGBLIGHT_LAYER_SEGMENTS({8, 1, HSV_RED});
const rgblight_segment_t PROGMEM MENU_LAYER[]         = RGBLIGHT_LAYER_SEGMENTS({8, 1, HSV_WHITE});

/* the right-most or bottom-most from above lime blocks overrides other lightning layer */
const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(DEV_LAYER, DATA_LAYER, MOD_LAYER, FUNCTION_LAYER, MENU_LAYER);

/* initialize rgb_layers */
void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 4));  // Dev Layer
    rgblight_set_layer_state(1, layer_state_cmp(state, 6));  // Data Layer
    rgblight_set_layer_state(3,
                                layer_state_cmp(state, 7) ||
                                layer_state_cmp(state, 8) ||
                                layer_state_cmp(state, 9));  // Data Layer
    rgblight_set_layer_state(4, layer_state_cmp(state, 10)); // Menu Layer
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_65_with_macro( /* MacOS Layer */
    LGUI(KC_C), LGUI(KC_V),     QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                      KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,                                   KC_HOME,
    LGUI(KC_Z), LSG(KC_Z),      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                                     KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(7, KC_BSPC), LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT, LT(6, KC_ENT),     KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT), KC_UP,                                  KC_END,
    DM_PLY1, DM_PLY2,           OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), OSL(8), LT(9, KC_SPC),               KC_SPC, KC_SPC, OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), KC_LEFT, LT(10, KC_DOWN),       KC_RGHT
  ),

  [1] = LAYOUT_65_with_macro( /* Win Linux BSD Layer */
    LCTL(KC_C), LCTL(KC_V),     QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                      KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,                                   KC_HOME,
    LCTL(KC_Z), LCTL(KC_Y),     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                                     KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(7, KC_BSPC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT, LT(6, KC_ENT),     KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,                                        KC_END,
    DM_PLY1, DM_PLY2,           OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LALT), OSL(8), LT(9, KC_SPC),               KC_SPC, KC_SPC, OSM(MOD_RALT), OSM(MOD_RGUI), OSM(MOD_RCTL), KC_LEFT, LT(10, KC_DOWN),       KC_RGHT
  ),

  [3] = LAYOUT_65_with_macro( /* Special Fn Layer for Teddie */
    KC_TRNS, KC_TRNS,          KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,         KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,              KC_TRNS,
    KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
    KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,
    KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,
    DM_PLY1, DM_PLY2,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS
  ),

  [4] = LAYOUT_65_with_macro( /* Speedtyping Layer or when you are annoyed by the lag from the home row modifier TODO separate game speedype layer with dev layer the latter use space cadet */
    KC_TRNS, KC_TRNS,           QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,          KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,               KC_HOME,
    KC_TRNS, KC_TRNS,           KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                 KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                 KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(7, KC_BSPC), KC_A, KC_S, KC_D, KC_F, KC_G,         KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, LT(6, KC_ENT),                 KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, KC_UP,                    KC_END,
    DM_PLY1, DM_PLY2,           KC_TRNS, KC_TRNS, KC_TRNS, OSL(8), LT(9, KC_SPC),     KC_SPC, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, LT(10, KC_DOWN),     KC_RGHT
  ),

  [5] = LAYOUT_65_with_macro( /* Data Entry Layer WIP 90percent Felt incomplete */
    KC_TRNS, KC_TRNS,     QK_GESC,     KC_NO, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_HOME,
    KC_TRNS, KC_TRNS,     KC_TAB,      KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_PGUP,
    KC_TRNS, KC_TRNS,     KC_BSPC,     KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ENTER, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSL(10), TG(6),                 KC_PGDN,
    KC_TRNS, KC_TRNS,     KC_SPC,      KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_EQUAL, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP,                   KC_END,
    DM_PLY1, DM_PLY2,     KC_NO,       KC_NO, KC_KP_0, KC_KP_0, KC_KP_DOT,                                KC_SPC, KC_SPC, KC_NO, KC_NO, KC_NO, KC_LEFT, LT(10, KC_DOWN),     KC_RGHT
  ),

  [7] = LAYOUT_65_with_macro( /* Function 1 Layer QUICK and SPECIAL Access ACS Caps Lock WIP */
    MEH(KC_KP_1), MEH(KC_KP_2),      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                    KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_DEL,                                         MEH(KC_HOME),
    MEH(KC_KP_3), MEH(KC_KP_4),      MEH(KC_TAB),  MEH(KC_Q), KC_UP, MEH(KC_E), MEH(KC_R), MEH(KC_T),     MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_BSLS),     MEH(KC_PGUP),
    MEH(KC_KP_5), MEH(KC_KP_6),      KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, MEH(KC_F), MEH(KC_G),              MEH(KC_H), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_QUOT), MEH(KC_ENT),                           MEH(KC_PGDN),
    MEH(KC_KP_7), MEH(KC_KP_8),      KC_TRNS, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),      MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT),  MEH(KC_SLSH), KC_TRNS, MEH(KC_UP),                 MEH(KC_END),
    MEH(KC_KP_9), MEH(KC_KP_0),      KC_TRNS, KC_TRNS, KC_TRNS, TG(8), MEH(KC_SPC),                       MEH(KC_SPC), MEH(KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_LEFT), MEH(KC_DOWN),                     MEH(KC_RGHT)
  ),

  [8] = LAYOUT_65_with_macro( /* Function 2 MEH Layer OSL and MacroPad ACS Left Special Mod Button TOGGLE from layer 7 9 10 */
    MEH(KC_KP_1), MEH(KC_KP_2),      MEH(KC_GRV), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6),     MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_MINS), MEH(KC_EQL), MEH(KC_BSPC), MEH(KC_BSPC),     MEH(KC_HOME),
    MEH(KC_KP_3), MEH(KC_KP_4),      MEH(KC_TAB),  MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T),               MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_BSLS),       MEH(KC_PGUP),
    MEH(KC_KP_5), MEH(KC_KP_6),      MEH(KC_CAPS), MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G),               MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), MEH(KC_QUOT), MEH(KC_ENT),                   MEH(KC_PGDN),
    MEH(KC_KP_7), MEH(KC_KP_8),      KC_TRNS, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                    MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT), MEH(KC_SLSH), KC_TRNS, MEH(KC_UP),                    MEH(KC_END),
    MEH(KC_KP_9), MEH(KC_KP_0),      KC_TRNS, KC_TRNS, KC_TRNS, TG(8), MEH(KC_SPC),                                     MEH(KC_SPC), MEH(KC_SPC), KC_NO, KC_NO, KC_NO, MEH(KC_LEFT), MEH(KC_DOWN),                             MEH(KC_RGHT)
  ),

  [9] = LAYOUT_65_with_macro( /* Function 3 HYPR Layer ACS Left Space Bar using Layer-Tap WIP */
    HYPR(KC_KP_1), HYPR(KC_KP_2),     HYPR(KC_GRV), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6),     HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), HYPR(KC_MINS), HYPR(KC_EQL), HYPR(KC_BSPC), HYPR(KC_BSPC),     HYPR(KC_HOME),
    HYPR(KC_KP_3), HYPR(KC_KP_4),     HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),                 HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), HYPR(KC_LBRC), HYPR(KC_RBRC), HYPR(KC_BSLS),       HYPR(KC_PGUP),
    HYPR(KC_KP_5), HYPR(KC_KP_6),     KC_NO, HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G),                        HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), HYPR(KC_SCLN), HYPR(KC_QUOT), HYPR(KC_ENT),                    HYPR(KC_PGDN),
    HYPR(KC_KP_7), HYPR(KC_KP_8),     KC_NO, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B),                        HYPR(KC_N), HYPR(KC_M), HYPR(KC_COMM), HYPR(KC_DOT),  HYPR(KC_SLSH), KC_NO, HYPR(KC_UP),                       HYPR(KC_END),
    HYPR(KC_KP_9), HYPR(KC_KP_0),     KC_NO, KC_NO, KC_NO, TG(8), KC_NO,                                                        HYPR(KC_SPC), HYPR(KC_SPC), KC_NO, KC_NO, KC_NO, HYPR(KC_LEFT), HYPR(KC_DOWN),                                 HYPR(KC_RGHT)
  ),

  [10] = LAYOUT_65_with_macro( /* Menu Layer NOTE the Right Mod is there for Shiroyama Encoder RGB */
    RGB_MOD, RGB_RMOD,     TG(3), TG(6), TG(4), KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, QK_RBT, QK_MAKE, KC_NO, KC_NO,    RGB_SPI,
    KC_NO, KC_NO,          KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       RGB_VAI,
    OS_OFF, OS_ON,         KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(6),              RGB_VAD,
    NK_OFF, NK_ON,         KC_NO, KC_BRID, KC_F15, KC_BRIU, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,              RGB_SPD,
    DM_REC1, DM_REC2,      KC_NO, DF(1), DF(0), TG(8), TG(10),                   KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, RGB_HUD, KC_NO,      RGB_HUI
  )
};

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(2, get_oneshot_mods() > (0));
};

void caps_word_set_user(bool active) {
        rgblight_set_layer_state(2, is_caps_word_on());
};

// Custom Keycodes
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    return true; // process all keycodes normally
};

void handle_recording_blink(bool is_recording, uint8_t layer, uint16_t duration_ms) {
    if (is_recording) {
        rgblight_blink_layer_repeat(layer, duration_ms, UINT8_MAX / 2); // Simulates indefinite blink
    } else {
        rgblight_unblink_layer(layer);
    }
}

bool dynamic_macro_record_start_kb(int8_t direction) {
    if (!dynamic_macro_record_start_user(direction)) {
        return false;
    }
    handle_recording_blink(true, 2, 1000);
    rgblight_disable_noeeprom();
    return true;
}

bool dynamic_macro_record_end_kb(int8_t direction) {
    if (!dynamic_macro_record_end_user(direction)) {
        return false;
    }
    handle_recording_blink(false, 2, 1000);
    rgblight_enable_noeeprom();
    return true;
}

// note that matrix_scan_user is taxing for the processor and increases lag and I am disabling it
/* void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1250) {
            unregister_code(KC_RGUI);
            is_alt_tab_active = false;
        }
    }
} */
