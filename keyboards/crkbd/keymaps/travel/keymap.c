#include QMK_KEYBOARD_H
#include <stdio.h>

enum custom_keycodes {
    JM_PWD = SAFE_RANGE,
};

// Tap Dance declarations
enum {
	TD_C_COPY,
	TD_V_PASTE,
	TD_SCLN_COLN,
	TD_QUOT_DQUO,
	TD_COMM_LT,
	TD_DOT_GT,
	TD_SLSH_QUES,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_C_COPY] = ACTION_TAP_DANCE_DOUBLE(KC_C, LGUI(KC_C)),
	[TD_V_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),	
	[TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
	[TD_QUOT_DQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
	[TD_COMM_LT] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LT),
	[TD_DOT_GT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_GT),
	[TD_SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
};

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CAPV LGUI(LSFT(KC_5))        // Capture video of portion of screen

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        LALT_T(KC_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T,				KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,				KC_H, KC_J, KC_K, KC_L, TD(TD_SCLN_COLN), TD(TD_QUOT_DQUO),
        KC_LSFT, KC_Z, KC_X, TD(TD_C_COPY), TD(TD_V_PASTE), KC_B,	KC_N, KC_M, TD(TD_COMM_LT), TD(TD_DOT_GT), TD(TD_SLSH_QUES), RSFT_T(KC_ENT),
        KC_LGUI, KC_SPC, MO(2),										MO(1), KC_SPC, KC_BSPC
        ),
		
	[1] = LAYOUT_split_3x6_3(
		LALT_T(KC_ESC), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 	KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
		LCTL_T(KC_TAB), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 			KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
		KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, 
		KC_LGUI, KC_SPC, MO(3),										KC_NO, KC_SPC, KC_BSPC
		),
		
	[2] = LAYOUT_split_3x6_3(
		LALT_T(KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5,				KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
		LCTL_T(KC_TAB), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 			KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,
		KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RSFT_T(KC_ENT),
		KC_LGUI, KC_SPC, KC_NO,										MO(3), KC_SPC, KC_BSPC
		),

    [3] = LAYOUT_split_3x6_3(
        JM_PWD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,					KC_CAPW, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,					KC_CAPP, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLU,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,					KC_CAPV, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD,
        KC_NO, KC_NO, KC_NO,										KC_NO, KC_NO, KC_NO
        )

#include "crkbd.h"
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case JM_PWD:
            if (record->event.pressed) {
                SEND_STRING("drink your ovaltine");
            }
            break;
    }
    return true;
}
