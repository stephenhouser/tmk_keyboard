/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "unimap_trans.h"
#include "hook.h"
#include "timer.h"
#include "host.h"
#include "led.h"

/* === Macros === */
enum macro_id {
    EMAIL,
    ALT_TAB,
};

#define AC_EMAIL    ACTION_MACRO(EMAIL)
#define AC_FN0      ACTION_MACRO(ALT_TAB)
#define AC_LAY_1    ACTION_LAYER_MOMENTARY(1)

/* === Functions === */
enum function_id {
    SCROLL_MUTE,
    SYS_REQUEST,
};

#define AC_SMUTE    ACTION_FUNCTION(SCROLL_MUTE)
#define AC_SYSRQ    ACTION_FUNCTION(SYS_REQUEST)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    // Layer 0
    UNIMAP_PS2(F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    ESC,       F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,            PSCR,SLCK,PAUS,    VOLD,VOLU, MUTE,
    GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,     DEL, END ,PGDN,    P7,  P8,  P9,  PPLS,
    CAPS,  A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,          ENT,                         P4,  P5,  P6,  PCMM,
    LSFT,NUBS,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,          UP,           P1,  P2,  P3,  PENT,
    LCTL,LALT,LGUI,MHEN,          SPC,             HENK,KANA,RALT,RGUI,FN0, RCTL,     LEFT,DOWN,RGHT,    NUHS,P0,  PDOT,PEQL
    ),

    // Layer 1
    UNIMAP(   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
    GRV,      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,                        TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,          TRNS,         TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,          TRNS,          TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS
    ),

    // Layer 2
    UNIMAP(   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
    GRV,      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,                        TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,          TRNS,         TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,          TRNS,          TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS
    ),

    // Layer 3
    UNIMAP(   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
    GRV,      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,                        TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,          TRNS,         TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,          TRNS,          TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS
    ),

    // Layer 4
    UNIMAP(   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
    GRV,      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS,
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,                        TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,          TRNS,         TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,          TRNS,          TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS
    ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case EMAIL:
            return (record->event.pressed ?
                    MACRO( T(S), T(T), T(E), T(P), T(H), T(E), T(N), T(H), T(O), T(U), T(S), T(E), T(R), D(LSFT), T(2), U(LSFT), T(G), T(M), T(A), T(I), T(L), T(DOT), T(C), T(O), T(M), END ) :
                    MACRO_NONE );
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }

    return MACRO_NONE;
}

#define LED_DURATION    100
static uint16_t last_ms = 0;

#define LED_ON(led)     led_set(host_keyboard_leds() | (1<<led))
#define LED_OFF(led)    led_set(host_keyboard_leds() & ~(1<<led))

// void hook_matrix_change(keyevent_t event) {
//     if (event.pressed) {
// 	    LED_ON(USB_LED_SCROLL_LOCK);
// 		last_ms = timer_read();		
// 	}
// }

// void hook_keyboard_loop(void) {
// 	if (last_ms && TIMER_DIFF_16(last_ms, timer_read()) > LED_DURATION) {
// 		LED_OFF(USB_LED_SCROLL_LOCK);
//         last_ms = 0;
// 	}
// }

void hook_layer_change(uint32_t layer_state) {
    // lights LED on Insert when layer 1 is enabled
    unsigned layer = 1;
    if (layer_state & (1UL<<layer)) {
	    LED_ON(USB_LED_CAPS_LOCK);        
    } else {
        LED_OFF(USB_LED_CAPS_LOCK);
    }
}

/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case SCROLL_MUTE:
            if (record->event.pressed) {
                LED_ON(USB_LED_SCROLL_LOCK);
                register_code(KC_MUTE);
                if (record->tap.count > 0 && !record->tap.interrupted) {
                }
            } else {
                LED_OFF(USB_LED_SCROLL_LOCK);
                unregister_code(KC_MUTE);
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    record->tap.count = 0;  // ad hoc: cancel tap
                }
            }

            break;

        case SYS_REQUEST:

            break;
    }
}
