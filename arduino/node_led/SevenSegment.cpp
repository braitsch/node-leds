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

/*
	Constructor takes four pins that map to each of the four digits.
	Shift Register pins (0, 1, 2) are hard coded as constants for now...
*/

SevenSegment::SevenSegment(int d1, int d2, int d3, int d4){
	_digitPins[0] = d1;
	_digitPins[1] = d2;
	_digitPins[2] = d3;
	_digitPins[3] = d4;
	pinMode(SERIAL_DATA, OUTPUT);
	pinMode(REGISTER_CLOCK, OUTPUT);
	pinMode(SERIAL_CLOCK, OUTPUT);
	for(int i = 0; i < 4; i++) pinMode(_digitPins[i], OUTPUT);
}

void SevenSegment::update()
{
	for(int i = 0; i < 4; i++) {
		writeNumber(_displayNumber[i]);
		digitalWrite(_digitPins[i], HIGH);
		delay(1);
		digitalWrite(_digitPins[i], LOW);
	}
}

void SevenSegment::setNumber(int n)
{
// break the incoming number into four _digitPins //
	_displayNumber[0] = n / 1000;
	_displayNumber[1] = (n / 100) % 10;
	_displayNumber[2] = (n / 10) % 10;
	_displayNumber[3] = n % 10;
	Serial.println(String(_displayNumber[0])+':'+String(_displayNumber[1])+':'+String(_displayNumber[2])+':'+String(_displayNumber[3]));
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