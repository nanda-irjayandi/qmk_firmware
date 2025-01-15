// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_encoder_switcher_active = false;
int led_index = 0;

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    CX_ENCTOGG,
    CX_LEDUP,
    CX_LEDDN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_80_with_macro( /* MacOS Layer */
    CX_ENCTOGG,                 KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                 KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,                                         KC_INS,
    LGUI(KC_C), LGUI(KC_V),     KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                       KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,                                   KC_HOME,
    LGUI(KC_Z), LSG(KC_Z),      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                                     KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(7, KC_BSPC), LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT, LT(5, KC_ENT),     KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT), KC_UP,                                  KC_END,
    DM_PLY1, DM_PLY2,           OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), KC_SPC, KC_SPC, OSL(8),              KC_SPC, KC_SPC, OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), KC_LEFT, LT(10, KC_DOWN),       KC_RGHT
  ),

  [1] = LAYOUT_80_with_macro( /* WIN Linux BSD Layer */
    CX_ENCTOGG,                 KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                 KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,                                       KC_INS,
    LCTL(KC_C), LCTL(KC_V),     KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                       KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,                                 KC_HOME,
    LCTL(KC_Z), LCTL(KC_Y),     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                                   KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(7, KC_BSPC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT, KC_ENT,          KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT), KC_UP,                                KC_END,
    DM_PLY1, DM_PLY2,           OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LALT), KC_SPC, KC_SPC, OSL(8),              KC_SPC, KC_SPC, OSM(MOD_RALT), OSM(MOD_RGUI), OSM(MOD_RCTL), KC_LEFT, LT(10, KC_DOWN),     KC_RGHT
  ),

  [3] = LAYOUT_80_with_macro( /* Game Layer Completed 20230909 */
    CX_ENCTOGG,            KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,      KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,              KC_INS,
    KC_NO, KC_NO,          KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,            KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,         KC_HOME,
    KC_P2, KC_P3,          KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
    KC_P4, KC_P5,          KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                 KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,                 KC_PGDN,
    KC_P6, KC_P7,          KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,             KC_END,
    KC_P8, KC_P9,          KC_LCTL, KC_BSLS, KC_LALT, KC_SPC, KC_SPC, OSL(8),     KC_SPC, KC_SPC, KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN,      KC_RGHT
  ),

  [4] = LAYOUT_80_with_macro( /* Speedtyping Layer or when you are annoyed by the lag from the home row modifier TODO separate game speedype layer with dev layer the latter use space cadet */
    CX_ENCTOGG,                 KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,      KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,                     KC_INS,
    KC_TRNS, KC_TRNS,           KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,            KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,               KC_HOME,
    KC_TRNS, KC_TRNS,           KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                 KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(7, KC_BSPC), KC_A, KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, LT(5, KC_ENT),                 KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, KC_UP,                    KC_END,
    DM_PLY1, DM_PLY2,           KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_SPC, OSL(8),     KC_SPC, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, LT(10, KC_DOWN),     KC_RGHT
  ),

  [5] = LAYOUT_80_with_macro( /* Data Entry Layer WIP 90percent Felt incomplete */
    CX_ENCTOGG,           KC_ESC,      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                          KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,               KC_INS,
    KC_TRNS, KC_TRNS,     KC_GRV,      KC_NO, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_HOME,
    KC_TRNS, KC_TRNS,     KC_TAB,      KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_PGUP,
    KC_TRNS, KC_TRNS,     KC_BSPC,     KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ENTER, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSL(10), TG(5),                 KC_PGDN,
    KC_TRNS, KC_TRNS,     KC_SPC,      KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_EQUAL, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP,                   KC_END,
    DM_PLY1, DM_PLY2,     KC_NO,       KC_NO, KC_KP_0, KC_KP_DOT, KC_KP_DOT, OSL(6),                      KC_SPC, KC_SPC, KC_NO, KC_NO, KC_NO, KC_LEFT, LT(10, KC_DOWN),     KC_RGHT
  ),

  [7] = LAYOUT_80_with_macro( /* Function 1 Layer QUICK and SPECIAL Access ACS Caps Lock WIP */
    KC_NO,                           MEH(KC_ESC), MEH(KC_F1), MEH(KC_F2), MEH(KC_F3), MEH(KC_F4), MEH(KC_F5), MEH(KC_F6),     MEH(KC_F7), MEH(KC_F8), MEH(KC_F9), MEH(KC_F10), MEH(KC_F11), MEH(KC_F12), MEH(KC_DEL),                MEH(KC_INS),
    MEH(KC_KP_1), MEH(KC_KP_2),      MEH(KC_GRV), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6),           MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_MINS), MEH(KC_EQL), MEH(KC_BSPC), MEH(KC_BSPC),     MEH(KC_HOME),
    MEH(KC_KP_3), MEH(KC_KP_4),      MEH(KC_TAB), MEH(KC_Q), KC_UP, MEH(KC_E), MEH(KC_R), MEH(KC_T),                          MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_BSLS),       MEH(KC_PGUP),
    MEH(KC_KP_5), MEH(KC_KP_6),      KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, MEH(KC_F), MEH(KC_G),                                  MEH(KC_H), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_QUOT), MEH(KC_ENT),                              MEH(KC_PGDN),
    MEH(KC_KP_7), MEH(KC_KP_8),      KC_TRNS, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                          MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT),  MEH(KC_SLSH), KC_TRNS, MEH(KC_UP),                   MEH(KC_END),
    MEH(KC_KP_9), MEH(KC_KP_0),      KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_SPC), MEH(KC_SPC), OSL(8),                             MEH(KC_SPC), MEH(KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_LEFT), MEH(KC_DOWN),                       MEH(KC_RGHT)
  ),

  [8] = LAYOUT_80_with_macro( /* Function 2 MEH Layer OSL and MacroPad ACS Left Special Mod Button TOGGLE from layer 7 9 10 */
    KC_NO,                           MEH(KC_ESC), MEH(KC_F1), MEH(KC_F2), MEH(KC_F3), MEH(KC_F4), MEH(KC_F5), MEH(KC_F6),     MEH(KC_F7), MEH(KC_F8), MEH(KC_F9), MEH(KC_F10), MEH(KC_F11), MEH(KC_F12), MEH(KC_DEL),                MEH(KC_INS),
    MEH(KC_KP_1), MEH(KC_KP_2),      MEH(KC_GRV), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6),     MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_MINS), MEH(KC_EQL), MEH(KC_BSPC), MEH(KC_BSPC),     MEH(KC_HOME),
    MEH(KC_KP_3), MEH(KC_KP_4),      MEH(KC_TAB),  MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T),     MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_BSLS),     MEH(KC_PGUP),
    MEH(KC_KP_5), MEH(KC_KP_6),      MEH(KC_CAPS), MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G),     MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), MEH(KC_QUOT), MEH(KC_ENT),                 MEH(KC_PGDN),
    MEH(KC_KP_7), MEH(KC_KP_8),      KC_TRNS, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),          MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT), MEH(KC_SLSH), KC_TRNS, MEH(KC_UP),                  MEH(KC_END),
    MEH(KC_KP_9), MEH(KC_KP_0),      KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_SPC), MEH(KC_SPC), OSL(8),                           MEH(KC_SPC), MEH(KC_SPC), KC_NO, KC_NO, KC_NO, MEH(KC_LEFT), MEH(KC_DOWN),                           MEH(KC_RGHT)
  ),

  [9] = LAYOUT_80_with_macro( /* Function 3 HYPR Layer ACS Left Space Bar using Layer-Tap WIP */
    KC_NO,                            HYPR(KC_ESC), HYPR(KC_F1), HYPR(KC_F2), HYPR(KC_F3), HYPR(KC_F4), HYPR(KC_F5), HYPR(KC_F6),     HYPR(KC_F7), HYPR(KC_F8), HYPR(KC_F9), HYPR(KC_F10), HYPR(KC_F11), HYPR(KC_F12), HYPR(KC_DEL),                HYPR(KC_INS),
    HYPR(KC_KP_1), HYPR(KC_KP_2),     HYPR(KC_GRV), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6),     HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), HYPR(KC_MINS), HYPR(KC_EQL), HYPR(KC_BSPC), HYPR(KC_BSPC),     HYPR(KC_HOME),
    HYPR(KC_KP_3), HYPR(KC_KP_4),     HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),                 HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), HYPR(KC_LBRC), HYPR(KC_RBRC), HYPR(KC_BSLS),       HYPR(KC_PGUP),
    HYPR(KC_KP_5), HYPR(KC_KP_6),     KC_NO, HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G),                        HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), HYPR(KC_SCLN), HYPR(KC_QUOT), HYPR(KC_ENT),                    HYPR(KC_PGDN),
    HYPR(KC_KP_7), HYPR(KC_KP_8),     KC_NO, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B),                        HYPR(KC_N), HYPR(KC_M), HYPR(KC_COMM), HYPR(KC_DOT),  HYPR(KC_SLSH), KC_NO, HYPR(KC_UP),                       HYPR(KC_END),
    HYPR(KC_KP_9), HYPR(KC_KP_0),     KC_TRNS, KC_TRNS, KC_TRNS, MEH(KC_SPC), MEH(KC_SPC), OSL(8),                                                        HYPR(KC_SPC), HYPR(KC_SPC), KC_NO, KC_NO, KC_NO, HYPR(KC_LEFT), HYPR(KC_DOWN),                                 HYPR(KC_RGHT)
  ),

  [10] = LAYOUT_80_with_macro( /* Menu Layer NOTE the Right Mod is there for Shiroyama Encoder RGB */
    CX_ENCTOGG,             KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,       KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, CX_LEDDN,        CX_LEDUP,
    RGB_MOD, RGB_RMOD,      TG(6), TG(5), TG(4), KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_RBT,      RGB_SPI,
    KC_NO, KC_NO,           KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,     RGB_VAI,
    OS_OFF, OS_ON,          KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, QK_LOCK, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(5),              RGB_VAD,
    NK_OFF, NK_ON,          KC_NO, KC_BRID, KC_F15, KC_BRIU, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,              RGB_SPD,
    DM_REC1, DM_REC2,       KC_NO, DF(1), DF(0), TG(10), TG(10), TG(8),             KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, RGB_HUD, KC_NO,      RGB_HUI
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case CX_ENCTOGG:
            if (record->event.pressed) {
                is_encoder_switcher_active = !is_encoder_switcher_active;
            }
        case CX_LEDUP:
            led_index = led_index + 1;
            rgb_matrix_set_color(led_index, 255, 255, 255);
        case CX_LEDDN:
            led_index = led_index - 1;
            rgb_matrix_set_color(led_index, 255, 255, 255);
    }
    return true; // process all keycodes normally
};

// Encoder Function
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        uint8_t current_layer = get_highest_layer(default_layer_state | layer_state);
        switch (current_layer) {
            // In Menu Layer, encoder controls RGB Function.
            // Good example of using a function rather than KC as a means to execute
            // Note that in Menu Layer right modifier buttons are non One Shot and must be held
            case 10:
                // Select RGB Mode by holding RGUI Button
                if (get_mods() & MOD_BIT(KC_RGUI)) {
                    if (clockwise) {
                        // unregister_mods(KC_RGUI);
                        rgblight_step_reverse_noeeprom();
                    } else {
                        // unregister_mods(KC_RGUI);
                        rgblight_step_noeeprom();
                    }
                    // Select RGB Hue by holding RAlt Button
                } else if (get_mods() & MOD_BIT(KC_RALT)) {
                    if (clockwise) {
                        // unregister_mods(MOD_MASK_ALT);
                        rgb_matrix_decrease_hue_noeeprom();
                    } else {
                        // unregister_mods(MOD_MASK_ALT);
                        rgb_matrix_increase_hue_noeeprom();
                    }
                    // Select RGB Speed by holding RCtl button
                } else if (get_mods() & MOD_BIT(KC_RCTL)) {
                    if (clockwise) {
                        // unregister_mods(MOD_MASK_CTRL);
                        rgblight_decrease_speed_noeeprom();
                    } else {
                        // unregister_mods(MOD_MASK_CTRL);
                        rgblight_increase_speed_noeeprom();
                    }
                    // Select RGB Brightness without modifier button
                } else {
                    if (clockwise) {
                        rgblight_decrease_val_noeeprom();
                    } else {
                        rgblight_increase_val_noeeprom();
                    }
                }
                break;


            case 3:
                if (!is_encoder_switcher_active) {
                    if (clockwise) {
                        tap_code(KC_BRIU);
                    } else {
                        tap_code(KC_BRID);
                    }
                } else if (is_encoder_switcher_active) {
                    if (clockwise) {
                        tap_code(KC_VOLU);
                    } else {
                        tap_code(KC_VOLD);
                    }
                }
                break;

            default:
                if (!is_encoder_switcher_active) {
                    if (clockwise) {
                        tap_code(KC_LEFT);
                    } else {
                        tap_code(KC_RGHT);
                    }
                } else if (is_encoder_switcher_active) {
                    if (clockwise) {
                        tap_code(KC_UP);
                    } else {
                        tap_code(KC_DOWN);
                    }
                }
                break;

            // default:
            //     // Handle unexpected current_layer values here
            //     break;
        }
    }
    return false;
}

// RGB Matrix Indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(default_layer_state | layer_state)) {
            case 10:
                rgb_matrix_set_color(led_index, 255, 255, 255);
                break;
            case 9:
                rgb_matrix_set_color(0, 255, 255, 255);
                break;
            case 8:
                rgb_matrix_set_color(0, 0, 0, 255);
                break;
            case 7:
                rgb_matrix_set_color(0, 0, 0, 255);
                break;
            case 6:
                rgb_matrix_set_color(0, 0, 0, 255);
                break;
            case 5: // for Data Entry Layer
                rgb_matrix_set_color(0, RGB_CYAN);
                break;
            case 4: // for Photoshop Layer
                rgb_matrix_set_color(0, RGB_PURPLE);
                break;
            case 3: // for Dev Layer
                rgb_matrix_set_color(0, 0, 255, 0);
                break;
            default:
                break;
        }
    };

    {
        if (get_oneshot_mods() > (0)) {
            rgb_matrix_set_color(0, 0, 0, 255);
        };
    };

    {
        if (is_caps_word_on() == true) {
            rgb_matrix_set_color(28, 255, 0, 0);
        };
    }
    return false;
}
