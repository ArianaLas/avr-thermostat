#ifndef _BUTTONS_H_
#define _BUTTONS_H_

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

// Frequency of reading buttons state: 61Hz

void buttonsInit();


#endif
