#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "hd44780/hd44780.h"
#include "dht11/dht11.h"
#include "buttons/buttons.h"

#define DDR_LED DDRB
#define PORT_LED PORTB
#define PIN_LED PB0 

static void clearCursor() {
	lcdGoto(8, 2);
	lcdWriteChar(' ');
	lcdGoto(12, 2);
	lcdWriteChar(' ');
	lcdGoto(8, 3);
	lcdWriteChar(' ');
	lcdGoto(12, 3);
	lcdWriteChar(' ');
}

int main() {
	_delay_ms(1000);
	lcdInit();
	buttonsInit();
	
	DDR_LED |= _BV(PIN_LED);

	char buffer[80];
	int8_t temperature = 0;
	int8_t humidity = 0;
	int range_temp_from = 20;
	int range_temp_to = 20;
	int range_hum_from = 30;
	int range_hum_to = 30;
	lcdGoto(0, 0);
	lcdWriteString("Temperature: ");
	lcdGoto(15, 0);
	lcdWriteString("C");
	lcdGoto(0, 1);
	lcdWriteString("Humidity: ");
	lcdGoto(12, 1);
	lcdWriteString("%");
	lcdGoto(0, 2);
	lcdWriteString("T  from: ");
	lcdGoto(11, 2);
	lcdWriteString("C");
	lcdGoto(13, 2);
	lcdWriteString("to: ");
	lcdGoto(18, 2);
	lcdWriteString("C");
	lcdGoto(0, 3);
	lcdWriteString("H  from: ");
	lcdGoto(11, 3);
	lcdWriteString("%");
	lcdGoto(13, 3);
	lcdWriteString("to: ");
	lcdGoto(18, 3);
	lcdWriteString("%");
	//int x = 0;
	int reading_amount = 0;
	// active: 1=temp-top, 2=temp-bottom, 3=hum-top, 4=hum-bottom, 0=wait-for-ok
	int active = 0;
	sei();

	while(1) {
		if (reading_amount == 0) {
			cli();
			humidity = sensorGetHumidity();
			temperature = sensorGetTemperature();
			sei();
			reading_amount = 50;
		}
		reading_amount--;
		itoa(temperature, buffer, 10);
		lcdGoto(13, 0);
		lcdWriteString(buffer);

		itoa(humidity, buffer, 10);
		lcdGoto(10, 1);
		lcdWriteString(buffer);

		_delay_ms(80);
		/*
		if (isPressed(BUTTON_OK) == 1) {
			lcdGoto(0, 3);
			itoa(x, buffer, 10);
			lcdWriteString(buffer);
			x++;
		}
		*/
		if (isPressed(BUTTON_OK) == 1) {
			clearCursor();
			if (active == 0) {
				active = 1;
			}
			else if (active == 1) {
				active = 2;
			}
			else if (active == 2) {
				active = 3;
			}
			else if (active == 3) {
				active = 4;
			}
			else if (active == 4) {
				active = 0;
			}
		}

		if (isPressed(BUTTON_EXIT) == 1) {
			active = 0;
			clearCursor();
		}

		if (active == 1) {
			lcdGoto(8, 2);
			lcdWriteChar(0x7E);
			if (isPressed(BUTTON_NEXT) == 1) {
				++range_temp_from;
			} else if (isPressed(BUTTON_PREV) == 1) {
				--range_temp_from;
			}
		} else if (active == 2) {
			lcdGoto(12, 2);
			lcdWriteChar(0x7E);
			if (isPressed(BUTTON_NEXT) == 1) {
				++range_temp_to;
			} else if (isPressed(BUTTON_PREV) == 1) {
				--range_temp_to;
			}
		} else if (active == 3) {
			lcdGoto(8, 3);
			lcdWriteChar(0x7E);
			if (isPressed(BUTTON_NEXT) == 1) {
				++range_hum_from;
			} else if (isPressed(BUTTON_PREV) == 1) {
				--range_hum_from;
			}
		} else if (active == 4) {
			lcdGoto(12, 3);
			lcdWriteChar(0x7E);
			if (isPressed(BUTTON_NEXT) == 1) {
				++range_hum_to;
			} else if (isPressed(BUTTON_PREV) == 1) {
				--range_hum_to;
			}
		}
		
		
		itoa(range_temp_from, buffer, 10);
		lcdGoto(9, 2);
		lcdWriteString(buffer);

		itoa(range_temp_to, buffer, 10);
		lcdGoto(16, 2);
		lcdWriteString(buffer);

		itoa(range_hum_from, buffer, 10);
		lcdGoto(9, 3);
		lcdWriteString(buffer);

		itoa(range_hum_to, buffer, 10);
		lcdGoto(16, 3);
		lcdWriteString(buffer);

		if((temperature >= range_temp_from) && (temperature <= range_temp_to) && (humidity >= range_hum_from) && (humidity <= range_hum_to)) {
			PORT_LED |= _BV(PIN_LED);
		} else {
			PORT_LED &= ~(_BV(PIN_LED));
		}
	}
}
