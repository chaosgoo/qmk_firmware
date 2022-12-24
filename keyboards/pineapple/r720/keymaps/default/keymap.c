/* Copyright 2021 QMK
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
#include "r720.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT_pa(
		KC_PMNS, KC_PSLS, KC_P0, KC_LALT, KC_SPC, KC_Z, KC_B, KC_N, KC_DOWN, KC_LSFT, KC_PAST, KC_LCTL, KC_UP, KC_ENT, KC_F8, 
		KC_C, KC_Q, KC_RALT, KC_X, KC_V, KC_M, KC_DOT, KC_RSFT, KC_COMM, KC_RCTL, KC_SLSH, KC_QUOT, 
		KC_PPLS, KC_P9, MO(1), KC_E, KC_F2, KC_G, KC_H, KC_BSLS, KC_F7, KC_P8, KC_MINS, KC_RGHT, 
		KC_P2, KC_LGUI, KC_TAB, KC_F4, KC_F1, KC_T, KC_Y, KC_O, KC_F6, KC_F9, KC_F12, KC_PSLS, 
		KC_P3, KC_P7, KC_GRV, KC_CAPS, KC_S, KC_5, KC_6, KC_F10, KC_F5, KC_0, KC_EQL, KC_DEL, 
		KC_PDOT, KC_1, KC_3, KC_2, KC_4, KC_7, KC_9, KC_8, KC_P, KC_BSPC, KC_P4, 
		KC_P1, KC_F3, KC_W, KC_R, KC_U, KC_F11, KC_I, KC_LEFT, KC_LBRC, KC_RBRC, KC_P5, 
		KC_NUM, KC_A, KC_ESC, KC_F, KC_J, KC_L, KC_K, KC_APP, KC_SCLN, KC_D, KC_P6),

	LAYOUT_pa(
		KC_PAUS, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_MPRV, KC_TRNS, KC_TRNS, KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_END, 
		KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_INS, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     // If console is enabled, it will print the matrix position and status of each key pressed
//     // #ifdef CONSOLE_ENABLE
//     uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
//     // #endif
//     return true;
// }

// void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (record->event.pressed) {
//         uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
//     }
// }