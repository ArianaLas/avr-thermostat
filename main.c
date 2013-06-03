#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "hd44780/hd44780.h"
#include "dht11/dht11.h"
// #include "buttons/buttons.h"

int main() {
	_delay_ms(1000);
	lcdInit();
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

	while(1) {
		humidity = sensorGetHumidity();
		temperature = sensorGetTemperature();

		itoa(temperature, buffer, 10);
		lcdGoto(13, 0);
		lcdWriteString(buffer);

		itoa(humidity, buffer, 10);
		lcdGoto(10, 1);
		lcdWriteString(buffer);

		_delay_ms(1000);
	}
}
