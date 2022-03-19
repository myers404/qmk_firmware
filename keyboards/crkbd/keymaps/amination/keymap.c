#include QMK_KEYBOARD_H
#include <stdio.h>
#include "animation.h"

enum custom_keycodes {
    JM_PWD = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        LALT_T(KC_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T,				KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,				KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B,				        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
        KC_LGUI, LSFT_T(KC_SPC), MO(2),							    MO(1), KC_SPC, KC_BSPC
        ),

    [1] = LAYOUT_split_3x6_3(
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,			KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_TILD, KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN, KC_EQL,		KC_MINS, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, KC_NO,
        KC_TRNS, KC_QUES, KC_NO, KC_NO, KC_NO, KC_PLUS,			    KC_UNDS, KC_NO, KC_NO, KC_NO, KC_PIPE, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,								    KC_TRNS, KC_TRNS, KC_TRNS
        ),

    [2] = LAYOUT_split_3x6_3(
        KC_MUTE, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5,				    KC_P6, KC_P7, KC_P8, KC_P9, KC_0, LCTL_T(KC_BSPC),
        KC_VOLU, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_NO,			KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PEQL,
        KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,				    KC_PSLS, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,								    KC_TRNS, KC_DOT, KC_0
        )

#include "crkbd.h"
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

static int c_frame = 0;
bool first_render = true;

static void render_anim(void) {
    if (first_render) {
        oled_write_raw_P( frame, ANIM_SIZE);
        first_render = 0;
    } else {
        change_frame_bytewise(c_frame);
    }
    c_frame = c_frame+1 > IDLE_FRAMES ? 0 : c_frame+1;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_anim();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
