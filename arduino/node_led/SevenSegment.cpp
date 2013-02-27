/*
	SevenSegment.cpp - Library for Controlling a 7-Segment Display via a 74HC595 Shift Register
	Created by Stephen Braitsch, February 22, 2013
	Released into the public domain.
*/

#include "SevenSegment.h"

byte const SevenSegment::SEGMENTS[10][7] = { 
	{ 1,1,1,1,1,1,0 },  // = 0
	{ 0,1,1,0,0,0,0 },  // = 1
	{ 1,1,0,1,1,0,1 },  // = 2
	{ 1,1,1,1,0,0,1 },  // = 3
	{ 0,1,1,0,0,1,1 },  // = 4
	{ 1,0,1,1,0,1,1 },  // = 5
	{ 1,0,1,1,1,1,1 },  // = 6
	{ 1,1,1,0,0,0,0 },  // = 7
	{ 1,1,1,1,1,1,1 },  // = 8
	{ 1,1,1,0,0,1,1 }   // = 9
};

byte const SevenSegment::LOOPS[6][7] = { 
	{ 1,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0 },
	{ 0,0,1,0,0,0,0 },
	{ 0,0,0,1,0,0,0 },
	{ 0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,1,0 },
};

/*
	Constructor takes four pins that map to each of the four digits.
	Shift Register pins (0, 1, 2) are hard coded as constants for now...
*/

SevenSegment::SevenSegment(int d1, int d2, int d3, int d4){
	_time = millis();
	_index = 0;
	_digitPins[0] = d1;
	_digitPins[1] = d2;
	_digitPins[2] = d3;
	_digitPins[3] = d4;
	pinMode(SERIAL_DATA, OUTPUT);
	pinMode(REGISTER_CLOCK, OUTPUT);
	pinMode(SERIAL_CLOCK, OUTPUT);
	for(int i = 0; i < 4; i++) pinMode(_digitPins[i], OUTPUT);
}

void SevenSegment::setNumber(int n)
{
	_delay = 100;
	_sequence_count = 0;
	_mode = SevenSegment::MODE_STATIC;
	parseNumber(n);
}

void SevenSegment::countFrom(int n, int speed)
{
	_delay = speed;
	_mode = SevenSegment::MODE_COUNT_UP;
	parseNumber(n);
}

void SevenSegment::update()
{
	if (_mode == SevenSegment::MODE_STATIC) {
		cycle();
	}	else if (_mode == SevenSegment::MODE_COUNT_UP){
		increment();
	}
}

void SevenSegment::cycle()
{
	int t2 = millis();
	if (t2 - _time > _delay){
		_time = t2;
		if (++_index == 6) {
			_index = 0;
			if (_sequence_count++ == 5){
				// stop cycling and show static number //
			}
		}
		const byte* digit = SevenSegment::LOOPS[_index];
	// copy segment values for this digit into the registers array //
		for(int i = 0; i < NUM_SEGMENTS; i++) _registers[i] = digit[i] == 0 ? 1 : 0;
		write_registers();
	// turn each digit on in order //
		for(int i = 0; i < NUM_DIGITS; i++) digitalWrite(_digitPins[i], HIGH);
	}
}

void SevenSegment::increment()
{
	int t2 = millis();
	if (t2 - _time > _delay){
		_time = t2;
		parseNumber(++_displayNumber);
	}
// turn each digit on in order //
	for(int i = 0; i < NUM_DIGITS; i++) {
		writeNumber(_digits[i]);
		digitalWrite(_digitPins[i], HIGH);
		delay(1);
		digitalWrite(_digitPins[i], LOW);
	}
}

void SevenSegment::parseNumber(int n)
{
	_displayNumber = n;
// limit displayNumber to 9999 since we only have four digits //
	if (_displayNumber > 9999) _displayNumber = 0;
// break the incoming number into four _digitPins //
	_digits[0] = _displayNumber / 1000;
	_digits[1] = (_displayNumber / 100) % 10;
	_digits[2] = (_displayNumber / 10) % 10;
	_digits[3] = _displayNumber % 10;
	Serial.println(String(_digits[0])+':'+String(_digits[1])+':'+String(_digits[2])+':'+String(_digits[3]));
}

void SevenSegment::writeNumber(int n)
{
	const byte* digit = SevenSegment::SEGMENTS[n];
// copy segment values for this digit into the registers array //
	for(int i = 0; i < NUM_SEGMENTS; i++) _registers[i] = digit[i] == 0 ? 1 : 0;
// force off the decimal point for now //
	_registers[7] = HIGH;
	write_registers();
}

void SevenSegment::write_registers(){
	digitalWrite(REGISTER_CLOCK, LOW);
	for(int i = NUM_SEGMENTS - 1; i >= 0; i--){
		digitalWrite(SERIAL_CLOCK, LOW);
		digitalWrite(SERIAL_DATA, _registers[i]);
		digitalWrite(SERIAL_CLOCK, HIGH);
	}
	digitalWrite(REGISTER_CLOCK, HIGH);
}
