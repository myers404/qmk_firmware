#include QMK_KEYBOARD_H
#include <stdio.h>

enum custom_keycodes {
    JM_PWD = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
	  LALT_T(KC_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T,				KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
      LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,				KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
	  LT(3,KC_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B,				KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, 
	  KC_LGUI, LSFT_T(KC_SPC), MO(2),							MO(1), KC_SPC, KC_BSPC
  ),

  [1] = LAYOUT_split_3x6_3(
	  KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,			KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
	  KC_TILD, KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN, KC_EQL,		KC_MINS, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, KC_NO,
	  KC_TRNS, KC_QUES, KC_NO, KC_NO, KC_NO, KC_PLUS,			KC_UNDS, KC_NO, KC_NO, KC_NO, KC_PIPE, KC_TRNS,
	  KC_TRNS, KC_TRNS, KC_TRNS,								KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_split_3x6_3(
	  KC_MUTE, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5,				KC_P6, KC_P7, KC_P8, KC_P9, KC_0, LCTL_T(KC_BSPC),
	  KC_VOLU, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_NO,			KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PEQL,
	  KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,				KC_PSLS, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_TRNS,
	  KC_TRNS, KC_TRNS, KC_TRNS,								KC_TRNS, KC_DOT, KC_0
  ),
	  
  [3] = LAYOUT_split_3x6_3(
	  JM_PWD, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,		SGUI_T(KC_4), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
	  KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,		SGUI_T(KC_5), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
	  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,					KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
	  RGB_TOG, KC_NO, KC_NO,									KC_NO, KC_NO, KC_NO
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

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  switch(keycode) {
	case JM_PWD:
      if (record->event.pressed) {
        SEND_STRING("drink your ovaltine");
      }
	  break;
  }
  return true;
}
#endif // OLED_ENABLE
