// Copyright 2022 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Declare & Define Super-Alt-Tab Timer Var
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    RGB_SPUP,
    RGB_SPDN,
    CX_EDITING,
    CX_PROGRAM,
    CX_ALTTAB,
    CX_ALTGRV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_65_with_macro( /* MacOS Layer */
    LGUI(KC_C), LGUI(KC_V),     KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                       KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,                                 KC_HOME,
    LGUI(KC_Z), LSG(KC_Z),      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                                  KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(6, KC_BSPC), LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT, KC_ENT,         KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT), KC_UP,                               KC_END,
    DM_PLY1, DM_PLY2,           OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), OSL(5), LT(7, KC_SPC),               KC_SPC, KC_SPC, OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), KC_LEFT, LT(8, KC_DOWN),             KC_RGHT
  ),

  [1] = LAYOUT_65_with_macro( /* Win Layer */
    LCTL(KC_C), LCTL(KC_V),     KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                       KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,                                 KC_HOME,
    LCTL(KC_Z), LCTL(KC_Y),     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                                  KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     LT(6, KC_BSPC), LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT, KC_ENT,         KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,                                     KC_END,
    DM_PLY1, DM_PLY2,           OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LALT), OSL(5), LT(7, KC_SPC),               KC_SPC, KC_SPC, OSM(MOD_RALT), OSM(MOD_RGUI), OSM(MOD_RCTL), KC_LEFT, LT(8, KC_DOWN),             KC_RGHT
  ),

  [2] = LAYOUT_65_with_macro( /* Dev and Speedtyping Layer or when you are annoyed by the lag from the home row modifier */
    KC_TRNS, KC_TRNS,           KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,            KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,              KC_HOME,
    KC_TRNS, KC_TRNS,           KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                KC_PGUP,
    MEH(KC_F5), MEH(KC_F6),     OSL(6), KC_A, KC_S, KC_D, KC_F, KC_G,                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,                       KC_PGDN,
    MEH(KC_F7), MEH(KC_F8),     KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, KC_UP,                   KC_END,
    DM_PLY1, DM_PLY2,           KC_TRNS, KC_TRNS, KC_TRNS, OSL(5), KC_SPC,             KC_SPC, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, LT(8, KC_DOWN),             KC_RGHT
  ),

  [3] = LAYOUT_65_with_macro( /* Photoshop Layer WIP */
    KC_NO, KC_NO,         HYPR(KC_GRV), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6),           HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), HYPR(KC_MINS), HYPR(KC_EQL), HYPR(KC_BSPC), HYPR(KC_BSPC),     HYPR(KC_HOME),
    KC_NO, KC_NO,         HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),                       HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), HYPR(KC_LBRC), HYPR(KC_RBRC), HYPR(KC_BSLS),       HYPR(KC_PGUP),
    KC_NO, KC_NO,         HYPR(KC_CAPS), HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G),                      HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), HYPR(KC_SCLN), HYPR(KC_QUOT), HYPR(KC_ENT),                    HYPR(KC_PGDN),
    KC_NO, KC_NO,         KC_NO, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B),                              HYPR(KC_N), HYPR(KC_M), HYPR(KC_COMM), HYPR(KC_DOT), HYPR(KC_SLSH), KC_NO, HYPR(KC_UP),                        HYPR(KC_END),
    DM_REC1, DM_REC2,     KC_NO, KC_NO, KC_NO, OSL(5), HYPR(KC_SPC),                                                      HYPR(KC_SPC), HYPR(KC_SPC), KC_NO, KC_NO, KC_NO, HYPR(KC_LEFT), LT(8, KC_DOWN),                               HYPR(KC_RGHT)
  ),

  [4] = LAYOUT_65_with_macro( /* Data Entry Layer */
    KC_TRNS, KC_TRNS,     KC_GRV,  KC_NO, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_HOME,
    KC_TRNS, KC_TRNS,     KC_TAB,  KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_PGUP,
    KC_NO, KC_NO,         KC_BSPC, KC_KP_6, KC_KP_5, KC_KP_4, KC_KP_ENTER, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, TG(4), OSL(8), KC_ENT,          KC_PGDN,
    KC_NO, KC_NO,         KC_SPC,  KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_EQUAL, KC_NO,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP,            KC_END,
    DM_PLY1, DM_PLY2,     KC_NO,   KC_NO, KC_KP_0, KC_KP_0, KC_KP_DOT,                                KC_SPC, KC_SPC, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN,      KC_RGHT
  ),

  [5] = LAYOUT_65_with_macro( /* Function 1 Layer access by Left Special Mod Button */
    KC_NO, KC_NO,         TG(8), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6),     HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), HYPR(KC_MINS), HYPR(KC_EQL), HYPR(KC_BSPC), HYPR(KC_BSPC),     HYPR(KC_HOME),
    KC_NO, KC_NO,         HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),          HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), HYPR(KC_LBRC), HYPR(KC_RBRC), HYPR(KC_BSLS),       HYPR(KC_PGUP),
    KC_NO, KC_NO,         HYPR(KC_CAPS), HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G),         HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), HYPR(KC_SCLN), HYPR(KC_QUOT), HYPR(KC_ENT),                    HYPR(KC_PGDN),
    KC_NO, KC_NO,         KC_NO, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B),                 HYPR(KC_N), HYPR(KC_M), HYPR(KC_COMM), HYPR(KC_DOT), HYPR(KC_SLSH), KC_NO, HYPR(KC_UP),                        HYPR(KC_END),
    DM_REC1, DM_REC2,     KC_NO, KC_NO, KC_NO, KC_NO, HYPR(KC_SPC),                                          HYPR(KC_SPC), HYPR(KC_SPC), KC_NO, KC_NO, KC_NO, HYPR(KC_LEFT), HYPR(KC_DOWN),                                 HYPR(KC_RGHT)
  ),

  [6] = LAYOUT_65_with_macro( /* Function 2 Layer access by Caps Lock */
    KC_NO, KC_NO,     MEH(KC_GRV), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6),           MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_MINS), MEH(KC_EQL), MEH(KC_BSPC), MEH(KC_BSPC),     MEH(KC_HOME),
    KC_NO, KC_NO,     MEH(KC_TAB),  MEH(KC_Q), KC_UP, MEH(KC_E), MEH(KC_R), MEH(KC_T),                         MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_BSLS),       MEH(KC_PGUP),
    KC_NO, KC_NO,     KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, MEH(KC_F), MEH(KC_G),                                  MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), MEH(KC_QUOT), MEH(KC_ENT),                   MEH(KC_PGDN),
    KC_NO, KC_NO,     KC_LSFT, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                          MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT),  MEH(KC_SLSH), KC_NO, MEH(KC_UP),                     MEH(KC_END),
    KC_NO, KC_NO,     KC_LCTL, KC_TRNS, KC_TRNS, KC_NO, MEH(KC_SPC),                                           MEH(KC_SPC), MEH(KC_SPC), KC_NO, KC_NO, KC_NO, MEH(KC_LEFT), MEH(KC_DOWN),                             MEH(KC_RGHT)
  ),

  [7] = LAYOUT_65_with_macro( /* Function 3 Layer access by Left Space Bar using Layer-Tap */
    KC_NO, KC_NO,     KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7,                                         KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, MEH(KC_EQL), MEH(KC_BSPC), MEH(KC_BSPC),     MEH(KC_HOME),
    KC_NO, KC_NO,     MEH(KC_TAB),  MEH(KC_Q), KC_UP, MEH(KC_E), MEH(KC_R), MEH(KC_T),                         MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_BSLS),       MEH(KC_PGUP),
    KC_NO, KC_NO,     KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, MEH(KC_F), MEH(KC_G),                                  MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), MEH(KC_QUOT), MEH(KC_ENT),                   MEH(KC_PGDN),
    KC_NO, KC_NO,     KC_LSFT, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                          MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT),  MEH(KC_SLSH), KC_NO, MEH(KC_UP),                     MEH(KC_END),
    KC_NO, KC_NO,     KC_LCTL, KC_TRNS, KC_TRNS, KC_NO, MEH(KC_SPC),                                           MEH(KC_SPC), MEH(KC_SPC), KC_NO, KC_NO, KC_NO, MEH(KC_LEFT), MEH(KC_DOWN),                             MEH(KC_RGHT)
  ),

  [8] = LAYOUT_65_with_macro( /* Menu Layer */
    RGB_MOD, RGB_RMOD,      TG(8), TG(4), CX_PROGRAM, CX_EDITING, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,
    RGB_VAD, RGB_VAI,       KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,
    RGB_SPDN, RGB_SPUP,     KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO,              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO,
    NK_OFF, NK_ON,          KC_NO, KC_BRID, KC_NO, KC_BRIU, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_LOCK,          KC_NO,
    OS_OFF, OS_ON,          KC_NO, DF(1), DF(0), KC_NO, KC_NO,                             KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_NO, KC_NO,      KC_NO
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
};

// Custom Keycodes
bool process_record_user(uint16_t keycode, keyrecord_t * record) {
// Get current mod and one-shot mod states.
const uint8_t mods = get_mods();
const uint8_t oneshot_mods = get_oneshot_mods();

  switch (keycode) {

  case RGB_SPUP:
    if (record -> event.pressed) {
      rgblight_increase_speed_noeeprom();
    }
    break;

  case RGB_SPDN:
    if (record -> event.pressed) {
      rgblight_decrease_speed_noeeprom(); // selects all and copies
    }
    break;

  case CX_EDITING:
    if (record -> event.pressed) {
      if (IS_LAYER_OFF(4)) {
        layer_on(4);
        layer_off(3);
        layer_off(5);
      } else {
        layer_off(4);
      }
    }
    break;

  case CX_PROGRAM:
    if (record -> event.pressed) {
      if (IS_LAYER_OFF(3)) {
        layer_on(3);
        layer_off(4);
        layer_off(5);
      } else {
        layer_off(3);
      }
    }
    break;

  case CX_ALTTAB:
    if (record -> event.pressed) {
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_RGUI);
      }
      alt_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
    break;

  case CX_ALTGRV:
    if (record -> event.pressed) {
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_RGUI);
      }
      alt_tab_timer = timer_read();
      register_code(KC_GRV);
    } else {
      unregister_code(KC_GRV);
    }
    break;

  case KC_TAB:  // Arrow macro, types -> or =>.
    if (record->event.pressed) {
      if ((mods | oneshot_mods) & MOD_MASK_GUI) {  // Is GUI held?
        // Temporarily delete GUI.
//        del_oneshot_mods(MOD_MASK_GUI);
//        unregister_mods(MOD_MASK_GUI);  
                if (!is_alt_tab_active) {
                  is_alt_tab_active = true;
                  register_code(KC_RGUI);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
                } else {
                  unregister_code(KC_TAB);
                }
      } 
      break;

  };

  return false;
};

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_RGUI);
      is_alt_tab_active = false;
    }
  }
}

