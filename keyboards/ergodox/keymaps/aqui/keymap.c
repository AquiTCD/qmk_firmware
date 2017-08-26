// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
// make clean && make keyboard=ergodox subproject=ez keymap=my-keymap
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define MOVE 1 // Cursol keys and Mouse Keys
#define CALC 2 // Keys like a calculator
/* period of tapping(ms) */
#ifndef TAPPING_TERM
/* #define TAPPING_TERM    200 */
#define TAPPING_TERM    75
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------------------.     ,-----------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |    4    |   5  |  `~  |     |  '"  |   6  |    7    |   8  |   9  |   0  |  \|    |
 * |--------+------+------+------+---------+-------------|     |------+------+---------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |    R    |   T  |  [   |     |  ]   |   Y  |    U    |   I  |   O  |   P  |  '"    |
 * |--------+------+------+------+---------+------|  {   |     |  }   |------+---------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |    F    |   G  |------|     |------|   H  |    J    |   K  |   L  |  ;:  |  -_    |
 * |--------+------+------+------+---------+------|  <   |     |  >   |------+---------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |    V    |   B  |  (   |     |  )   |   N  |    M    |  ,<  |  .>  |  /?  |  +=    |
 * `--------+------+------+------+---------+-------------'     `-------------+---------+------+------+------+--------'
 *   |  ~L2 |  ~L1 | Left | Right|LGui/Eisu|                                 |RGui/Kana|  Up  | Down |  ~L1 | ~L2  |
 *   `-------------------------------------'                                 `-------------------------------------'
 *                                        ,-----------------.    ,-----------------.
 *                                        |LCtrl   | LAlt   |    | RAlt   |  RCtrl |
 *                                 ,------|--------|--------|    |--------+--------+------.
 *                                 |      |        | Tab    |    | Tab    |        |      |
 *                                 | Space| Del    |--------|    |--------| BKspc  |Enter |
 *                                 |LShift| LCtrl  |LAlt/TAB|    |RAlt/ESC|        |      |
 *                                 `------------------------'    `------------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,  KC_1,    KC_2,      KC_3,    KC_4,    KC_5,                 KC_GRV,
        KC_TAB,  KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,                KC_LBRC,
        KC_LCTL, KC_A,    KC_S,      KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,      KC_C,    KC_V,    KC_B,                KC_JYEN,
                      // MO(CALC),  MO(MOVE), KC_LEFT, KC_RGHT, MT(MOD_LGUI, KC_LANG2),
                      MO(CALC),  KC_LALT, KC_LEFT, KC_RGHT, KC_LGUI,
                                                      KC_LCTL,              KC_LALT,
                                                                             KC_TAB,
                  //  MT(MOD_LSFT, KC_SPC), MT(MOD_LCTL, KC_DEL), MT(MOD_LALT, KC_TAB),
                                                            KC_SPC, KC_DEL, KC_RALT,
        // right hand
        KC_QUOTE,  KC_6,                   KC_7,    KC_8,    KC_9,     KC_0,  KC_BSLS,
        KC_RBRC,   KC_Y,                   KC_U,    KC_I,    KC_O,     KC_P,  KC_QUOT,
                   KC_H,                   KC_J,    KC_K,    KC_L,  KC_SCLN,  KC_MINS,
        KC_RO,     KC_N,                   KC_M, KC_COMM,  KC_DOT,  KC_SLSH,   KC_EQL,
                        //  MT(MOD_RGUI, KC_LANG1),   KC_UP, KC_DOWN, MO(MOVE), MO(CALC),
                   KC_RGUI,               KC_UP, KC_DOWN, KC_RALT, MO(MOVE),
             KC_RALT, KC_RCTL,
             KC_TAB,
            //  MT(MOD_RALT, KC_ESC), KC_BSPC, KC_ENT
             KC_RALT, KC_BSPC, KC_ENT
    ),
/* Keymap 1: Media and mouse keys
 *
 * ,--------------------------------------------------------.      ,--------------------------------------------------.
 * | TRANS  |  F1  |   F2   |   F3   |   F4   |  F5  |      |      | Power|  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+--------+--------+--------+-------------|      |------+------+------+------+------+------+--------|
 * | TRANS  |      |        |  MsUp  |        |      | WhUp |      | WhUp |      |      | UP   |      |      |   F12  |
 * |--------+------+--------+--------+--------+------|      |      |      |------+------+------+------+------+--------|
 * | TRANS  |WhLeft| MsLeft | MsDown | MsRght |WhRght|------|      |------|      | Left | Down | Right|      |  VolU  |
 * |--------+------+--------+--------+--------+------|WhDown|      |WhDown|------+------+------+------+------+--------|
 * | TRANS  |      |        |        |        |      |      |      |      |      |      |      |      |      |  VolD  |
 * `--------+------+--------+--------+--------+-------------'      `-------------+------+------+------+------+--------'
 *   | TRANS| TRANS| TRANS  | TRANS  | TRANS  |                                  | TRANS| TRANS|TRANS | TRANS| TRANS  |
 *   `----------------------------------------'                                  `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | TRANS| TRANS|       | TRANS| TRANS|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 | Lclk | Rclk |------|       |------|MsAcl2|MsAcl1|
 *                                 |      |      | WhClk|       |MsAcl0|      |      |
 *                                 `--------------------'       `--------------------'
 */
// Cursor Keys and Mouse Keys
[MOVE] = KEYMAP(
       KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_MUTE,
       KC_TRNS,  KC_NO,   KC_NO,   KC_MS_U, KC_NO,   KC_NO,  KC_WH_D,
       KC_TRNS,  KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,
       KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_WH_U,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_BTN3,
    // right hand
       KC_PWR,  KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10, KC_F11,
       KC_WH_D, KC_NO,    KC_NO,    KC_UP,   KC_NO,   KC_NO,  KC_F12,
                KC_NO,    KC_LEFT,  KC_DOWN, KC_RGHT, KC_NO,  KC_VOLU,
       KC_WH_U, KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_VOLD,
                          KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_ACL0, KC_ACL2, KC_ACL1
     ),


/* Keymap 2: Keys like a Culculator
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | TRANS   |      |      |      |      |      |      |           |      |      |   7  |   8  |   9  |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | TRANS   |      |      |  UP  |      |      |WhDown|           |WhDown|      |   4  |   5  |   6  |   *  |   /    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TRANS   |WhLEFT| LEFT | DOWN | RIGHT|WhRght|------|           |------|      |   1  |   2  |   3  |   +  |   -    |
 * |---------+------+------+------+------+------|WhUp  |           |WhUp  |------+------+------+------+------+--------|
 * | TRANS   |      |      |      |      |      |      |           |      |      |   0  |   0  |   .  |   +  |   =    |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | TRANS | TRANS| TRANS| TRANS| TRANS|                                       | TRANS| TRANS| TRANS| TRANS| TRANS  |
 *   `-----------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | TRANS| TRANS|       | TRANS| TRANS|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 | TRANS|TRANS |------|       |------| TRANS| TRANS|
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 `--------------------'       `--------------------'
 */
// act like ten keys
[CALC] = KEYMAP(
       // left hand
       KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
       KC_TRNS,  KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO,  KC_WH_D,
       KC_TRNS,  KC_WH_L, KC_LEFT, KC_DOWN, KC_RIGHT,KC_WH_R,
       KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_WH_U,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_NO,   KC_P7,  KC_P8,   KC_P9,   KC_NO,   KC_NO,
       KC_WH_D, KC_NO,   KC_P4,  KC_P5,   KC_P6,   KC_PAST, KC_PSLS,
                KC_NO,   KC_P1,  KC_P2,   KC_P3,   KC_PLUS, KC_PMNS,
       KC_WH_U, KC_NO,   KC_P0,  KC_PDOT, KC_PEQL, KC_PLUS, KC_PEQL,
                         KC_TRNS,KC_P0,   KC_PDOT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
     ),


};
enum function_id {
  LEFT_BRACE, RIGHT_BRACE
};
const uint16_t PROGMEM fn_actions[] = {
    // [13] = ACTION_KEY(KC_LPRN),              // FN13 - ( <
    // [14] = ACTION_KEY(KC_RPRN)              // FN14 - ) >
};
// #define MY_FN13 KC_LPRN
// #define MY_FN14 KC_RPRN
// #define S(MY_FN13) KC_LABK
// #define S(MY_FN14) KC_RABK
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
