/*
	SevenSegment.cpp - Library for Controlling a 7-Segment Display via a 74HC595 Shift Register
	Created by Stephen Braitsch, February 22, 2013
	Released into the public domain.
*/

#include "SevenSegment.h"

byte const SevenSegment::NUMBERS[10][7] = { 
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

byte const SevenSegment::SEGMENTS[6][7] = { 
	{ 1,0,0,0,0,0,0 },	// = a
	{ 0,1,0,0,0,0,0 },	// = b
	{ 0,0,1,0,0,0,0 },	// = c
	{ 0,0,0,1,0,0,0 },	// = d
	{ 0,0,0,0,1,0,0 },	// = e
	{ 0,0,0,0,0,1,0 },	// = f
};

/*
	Constructor takes four pins that map to each of the four digits.
	Shift Register pins (0, 1, 2) are hard coded as constants for now...
*/

SevenSegment::SevenSegment(int d1, int d2, int d3, int d4){
	
// initialize some instance variables //
	_time = millis();
	
// bind the four digits to the user specified pins //
	_digitPins[0] = d1;
	_digitPins[1] = d2;
	_digitPins[2] = d3;
	_digitPins[3] = d4;
	for(int i = 0; i < 4; i++) pinMode(_digitPins[i], OUTPUT);
	
// setup the shift register pins, eventually these should be user defined //
	pinMode(SERIAL_DATA, OUTPUT);
	pinMode(REGISTER_CLOCK, OUTPUT);
	pinMode(SERIAL_CLOCK, OUTPUT);
}

void SevenSegment::setNumber(int n)
{
	_delay = 100;
	_displaySegment = 0;
	_sequence_count = 0;
	_mode = SevenSegment::MODE_ANIMATING;
	parseNumber(n);
}

void SevenSegment::countFrom(int n, int speed)
{
	_delay = speed;
	_mode = SevenSegment::MODE_COUNTING;
	parseNumber(n);
}

void SevenSegment::update()
{
	int t2 = millis();
	if (t2 - _time > _delay){
		_time = t2;
		switch(_mode){
			case SevenSegment::MODE_STATIC :
				writeNumber();
			break;
			case SevenSegment::MODE_COUNTING :
				parseNumber(++_displayNumber);
				writeNumber();
			break;
			case SevenSegment::MODE_ANIMATING :
				stepThroughSegments();
			break;
		}
	}
}

void SevenSegment::stepThroughSegments()
{
	if (++_displaySegment == 6) {
		_displaySegment = 0;
		if (_sequence_count++ == 5){
	// stop cycling and show the display number //
			_mode = SevenSegment::MODE_STATIC;
		}
	}
	writeSegment();
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

void SevenSegment::writeSegment()
{
	const byte* digit = SevenSegment::SEGMENTS[_displaySegment];
// copy segment values for this digit into the registers array //
	for(int i = 0; i < NUM_SEGMENTS; i++) _registers[i] = digit[i] == 0 ? 1 : 0;
	write_registers();
// turn all digits on to show the same newly active segment //
	for(int i = 0; i < NUM_DIGITS; i++) digitalWrite(_digitPins[i], HIGH);
}

void SevenSegment::writeNumber()
{
// set each digit one at a time to its corresponding number in the digits array //
	for(int i = 0; i < NUM_DIGITS; i++) {
// get the number for this digit //
		int n = _digits[i];
// get the array of segments that make up the number //
		const byte* digit = SevenSegment::NUMBERS[n];
// copy segment values for this number into the registers array //
		for(int i = 0; i < NUM_SEGMENTS; i++) _registers[i] = digit[i] == 0 ? 1 : 0;
// force off the decimal point for now //
// this might not be necessary .. need to test
		_registers[7] = HIGH;
		write_registers();
		digitalWrite(_digitPins[i], HIGH);
		delay(1);
		digitalWrite(_digitPins[i], LOW);
	}
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
