/* Copyright 2022 DZTECH <moyi4681@live.cn>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum custom_layer {
    _STD,
    _SOCD,
    _UTIL
};
enum custom_keycodes {
  SOCD_W = SAFE_RANGE,
  SOCD_A,
  SOCD_S,
  SOCD_D,
  DTLFT,
  DTRGHT
};

bool w_down = false;
bool a_down = false;
bool s_down = false;
bool d_down = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_STD] = LAYOUT_65_ansi(
        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, MO(2),
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,           KC_RALT, KC_APP, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SOCD] = LAYOUT_65_ansi(
        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, MO(2),
        KC_TAB,   KC_Q,    SOCD_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS,  SOCD_A,    SOCD_S,    SOCD_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,           KC_RALT, KC_APP, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_UTIL] = LAYOUT_65_ansi(
        KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PPLS,  _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_NUM,   KC_PMNS,
        KC_CAPS, RGB_SPI, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______, KC_LNUM,         _______,  TG(1),
        KC_LSFT, _______, _______, _______, _______, QK_BOOT, NK_TOGG, _______, _______, _______, _______, KC_MPLY,          KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,          DTLFT, _______, DTRGHT,          KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [3] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,          _______, _______, _______,          _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_SPLASH);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _STD:
            break;
        case _SOCD:
            rgb_matrix_set_color(17, RGB_RED);
            rgb_matrix_set_color(31, RGB_RED);
            rgb_matrix_set_color(32, RGB_RED);
            rgb_matrix_set_color(33, RGB_RED);
            break;
        case _UTIL:
            rgb_matrix_set_color(49, RGB_RED);
            break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SOCD_W:
        if (record->event.pressed) {
            if (s_down) {
                unregister_code(KC_S);
            }
            register_code(KC_W);
            w_down = true;
        } else {
            unregister_code(KC_W);
            w_down = false;

            if (s_down) {
                register_code(KC_S);
            }

        }
        return false;
        break;
    case SOCD_A:
        if (record->event.pressed) {
            if (d_down) {
                unregister_code(KC_D);
            }
            register_code(KC_A);
            a_down = true;
        } else {
            unregister_code(KC_A);
            a_down = false;

            if (d_down) {
                register_code(KC_D);
            }

        }
        return false;
        break;
    case SOCD_S:
        if (record->event.pressed) {
            if (w_down) {
                unregister_code(KC_W);
            }
            register_code(KC_S);
            s_down = true;
        } else {
            unregister_code(KC_S);
            s_down = false;

            if (w_down) {
                register_code(KC_W);
            }

        }
        return false;
        break;
    case SOCD_D:
        if (record->event.pressed) {
            if (a_down) {
                unregister_code(KC_A);
            }
            register_code(KC_D);
            d_down = true;
        } else {
            unregister_code(KC_D);
            d_down = false;

            if (a_down) {
                register_code(KC_A);
            }
        }
        return false;
        break;
    case DTLFT:
     if (record->event.pressed) {

            register_code(KC_LCTL);
            register_code(KC_LGUI);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_LGUI);
            unregister_code(KC_LEFT);
        }
        break;
    case DTRGHT:
     if (record->event.pressed) {

            register_code(KC_LCTL);
            register_code(KC_LGUI);
            register_code(KC_RGHT);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_LGUI);
            unregister_code(KC_RGHT);
        }
        break;
    }

    return true;
}
