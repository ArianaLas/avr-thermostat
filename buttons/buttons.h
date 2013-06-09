#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <avr/io.h>

#define NEXT_PIN PD2
#define NEXT_PIN_REG PIND
#define NEXT_DDR DDRD
#define NEXT_PORT PORTD
#define OK_PIN PD3
#define OK_PIN_REG PIND
#define OK_DDR DDRD
#define OK_PORT PORTD
#define PREV_PIN PD4
#define PREV_PIN_REG PIND
#define PREV_DDR DDRD
#define PREV_PORT PORTD
#define EXIT_PIN PD5
#define EXIT_PIN_REG PIND
#define EXIT_DDR DDRD
#define EXIT_PORT PORTD

#define BUTTONS_DEBOUNCE_MS 20

// Frequency of reading buttons state: 488Hz

#define BUTTON_NEXT 0x01
#define BUTTON_OK 0x02
#define BUTTON_PREV 0x04
#define BUTTON_EXIT 0x08
void buttonsInit();

// return 1 = pressed
uint8_t isPressed(uint8_t button);

#endif
