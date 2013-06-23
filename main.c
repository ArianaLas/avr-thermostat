#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "hd44780/hd44780.h"
#include "dht11/dht11.h"
#include "buttons/buttons.h"

int main() {
	_delay_ms(1000);
	lcdInit();
	buttonsInit();
	char buffer[80];
	int8_t temperature = 0;
	int8_t humidity = 0;
	lcdGoto(0, 0);
	lcdWriteString("Temperature: ");
	lcdGoto(15, 0);
	lcdWriteString("C");
	lcdGoto(0, 1);
	lcdWriteString("Humidity: ");
	lcdGoto(12, 1);
	lcdWriteString("%");
	int x = 0;
	int reading_amount = 0;
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

		_delay_ms(100);
		if (isPressed(BUTTON_OK) == 1) {
			lcdGoto(0, 3);
			itoa(x, buffer, 10);
			lcdWriteString(buffer);
			x++;
		}
	}
}
