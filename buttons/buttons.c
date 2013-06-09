#include "buttons.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void buttonsInit() {

	// timer init
	TIMSK |= _BV(TOIE0); //enable overflow interrupt
	TCCR0 |= (_BV(CS01) | _BV(CS00)); // prescaler 64

	// DDR input
	NEXT_DDR &= ~(_BV(NEXT_PIN));
	OK_DDR &= ~(_BV(OK_PIN));
	PREV_DDR &= ~(_BV(PREV_PIN));
	EXIT_DDR &= ~(_BV(EXIT_PIN));
	// pulling buttons up to VCC
	NEXT_PORT |= _BV(NEXT_PIN);
	OK_PORT |= _BV(OK_PIN);
	PREV_PORT |= _BV(PREV_PIN);
	EXIT_PORT |= _BV(EXIT_PIN);
}

volatile uint8_t real_state;
volatile uint8_t stable_state[4];
volatile uint8_t debounce_timer[4];

ISR(TIMER_OVF_vect) {
	uint8_t current_state[4];

	// reading state of button (BUTTON_PIN = 0 than is pushed) (in buttons[] 1 = pushed)
	if (NEXT_PIN_REG & (1 << NEXT_PIN)) {
		current_state[0] = 0;
	} else {
		current_state[0] = 1;
	}
	if (OK_PIN_REG & (1 << OK_PIN)) {
		current_state[1] = 0;
	} else {
		current_state[1] = 1;
	}
	if (PREV_PIN_REG & (1 << PREV_PIN)) {
		current_state[2] = 0;
	} else {
		current_state[2] = 1;
	}
	if (EXIT_PIN_REG & (1 << EXIT_PIN)) {
		current_state[3] = 0;
	} else {
		current_state[3] = 1;
	}

	uint8_t i;
	for (i = 0; i < 4; ++i) { // each button separately
		if (debounce_timer[i] > 0) { // timing actual delay
			// if end of delay and state changed than update 
			if ((--debounce_state[i] == 0) && (stable_state[i] ^ current_state[i])) {
				stable_state[i] ^= 0x1; // negation 
				real_state ^= (1 << i); // negation
			}
		} else { // scan of buttons
			if (stable_state[i] ^ current_state[i]) { // state changed
				debounce_timer[i] = BUTTONS_DEBOUNCE_MS / 2; // set "delay"
			}
		}
	}
}
