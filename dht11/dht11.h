#ifndef _DHT11_H_
#define _DHT11_H_

#include <stdio.h>
#include <avr/io.h>

// setup parameters
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN PINC
#define DHT11_INPUTPIN PC5

int8_t sensorGetTemperature();
int8_t sensorGetHumidity();

#endif
