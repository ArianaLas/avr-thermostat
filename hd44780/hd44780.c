#include <util/delay.h>
#include <avr/io.h>

#include "hd44780.h"

inline static void lcdAccept() {
	E_PORT |= _BV(E_PIN);
	_delay_us(5); // TODO check
	E_PORT &= ~(_BV(E_PIN));
}

static void lcdSendPart(uint8_t part) {
	D4_PORT &= ~(_BV(D4_PIN));
	D5_PORT &= ~(_BV(D5_PIN));
	D6_PORT &= ~(_BV(D6_PIN));
	D7_PORT &= ~(_BV(D7_PIN));
	D4_PORT |= (part & 1) << D4_PIN;
	part >>= 1;
	D5_PORT |= (part & 1) << D5_PIN;
	part >>= 1;
	D6_PORT |= (part & 1) << D6_PIN;
	part >>= 1;
	D7_PORT |= (part & 1) << D7_PIN;
	lcdAccept();
}

static void lcdSendCommand(uint8_t command) {
	_delay_ms(5);
	RS_PORT &= ~(_BV(RS_PIN));
	// higher
	lcdSendPart(command >> 4);
	// lower
	lcdSendPart(command);
}

void lcdInit() {
	_delay_ms(100); // wait for more than 40 ms after VCC rises to 2.7 V
	// output
	D4_DDR |= _BV(D4_PIN);
	D5_DDR |= _BV(D5_PIN);
	D6_DDR |= _BV(D6_PIN);
	D7_DDR |= _BV(D7_PIN);
	RS_DDR |= _BV(RS_PIN);
	E_DDR |= _BV(E_PIN);
	lcdSendPart(0x03); // 8 bit interface
	_delay_ms(6); // wait more than 4.1 ms
	lcdAccept(); // send 0x03 again
	_delay_us(150); // wait more than 100
	lcdAccept(); // send 0x03 again
	_delay_ms(1);
	lcdSendPart(0x02); // 4 bit interface
	// now I can use my defined instructions
	_delay_us(64);
	lcdSendCommand(FUNCTION_SET(MODE_4BIT, LINES_2, FONT_5x8));
	_delay_ms(45);
	lcdSendCommand(DISPLAY_ON_OFF(DISPLAY_OFF, CURSOR_OFF, CURSOR_BLINK_OFF));
	_delay_ms(45);
	lcdSendCommand(CLEAR_DISPLAY);
	_delay_ms(45);
	lcdSendCommand(ENTRY_MODE_SET(INCREMENT, SHIFT_OFF));
	_delay_ms(80);

	lcdSendCommand(DISPLAY_ON_OFF(DISPLAY_ON, CURSOR_OFF, CURSOR_BLINK_OFF));
	_delay_ms(45);
}

void lcdGoto(uint8_t x, uint8_t y) {
	switch(y) {
		case 0:
			lcdSendCommand(DDRAM_SET(LINE_0 + x));
		break;
		case 1:
			lcdSendCommand(DDRAM_SET(LINE_1 + x));
		break;
		case 1:
			lcdSendCommand(DDRAM_SET(LINE_2 + x));
		break;
		case 2:
			lcdSendCommand(DDRAM_SET(LINE_3 + x));
		break;
		case 3:
			lcdSendCommand(DDRAM_SET(LINE_4 + x));
		break;
	}
}

inline void lcdClear() {
	lcdSendCommand(CLEAR_DISPLAY);
}

void lcdWriteChar(char c) {
	RS_PORT |= _BV(RS_PIN);
	lcdSendPart(c >> 4);
	_delay_us(50);
	lcdSendPart(c);
	_delay_us(50);
}

void lcdWriteString(char *s) {
	while(*s != '\0') {
		lcdWriteChar(*s);
		s++;
	}
}
