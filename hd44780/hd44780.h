#ifndef _HD44780_H_
#define _HD44780_H_

#define RS_DDR DDRD
#define RS_PORT PORTD
#define RS_PIN PD6
#define E_DDR DDRC 
#define E_PORT PORTC
#define E_PIN PC0
#define D4_DDR DDRC
#define D4_PORT PORTC
#define D4_PIN PC1
#define D5_DDR DDRC
#define D5_PORT PORTC
#define D5_PIN PC2
#define D6_DDR DDRC
#define D6_PORT PORTC
#define D6_PIN PC3
#define D7_DDR DDRC
#define D7_PORT PORTC
#define D7_PIN PC4

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define DISPLAY_ON_OFF(ON_OFF, CURSOR, BLINK) 0x08 | ON_OFF | CURSOR | BLINK
	#define DISPLAY_ON 0x04
	#define DISPLAY_OFF 0x00
	#define CURSOR_ON 0x02
	#define CURSOR_OFF 0x00
	#define CURSOR_BLINK_ON 0x01
	#define CURSOR_BLINK_OFF 0x00
#define ENTRY_MODE_SET(INC, SHIFT) 0x04 | INC | SHIFT
	#define INCREMENT 0x02
	#define DECREMENT 0x00
	#define SHIFT_ON 0x01
	#define SHIFT_OFF 0x00
#define FUNCTION_SET(MODE, LINES, FONT) 0x20 | MODE | LINES | FONT
	#define MODE_4BIT 0x00
	#define MODE_8BIT 0x10
	#define LINES_1 0x00
	#define LINES_2 0x08
	#define FONT_5x8 0x00
	#define FONT_5x11 0x04
#define DDRAM_SET(ADDR) 0x80 | ((ADDR) & 0x7F)
	#define LINE_0 0x00
	#define LINE_1 0x40
	#define LINE_2 0x14
	#define LINE_3 0x54
#define SHIFT_CURSOR(DIRECTION) 0x10 | (DIRECTION)
	#define CURSOR_RIGHT 0x4
	#define CURSOR_LEFT 0x0
#define SHIFT_DISPLAY(DIRECTION) 0x10 | (DIRECTION)
	#define DISPLAY_RIGHT 0xC
	#define DISPLAY_LEFT 0x8

void lcdInit();
void lcdGoto(uint8_t x, uint8_t y);
void lcdClear();
void lcdWriteChar(char c);
void lcdWriteString(char *s);

#endif
