#ifndef SevenSegment_H
#define SevenSegment_H

#include "Arduino.h"

class SevenSegment{

public:
	SevenSegment(int d1, int d2, int d3, int d4);
	void update();
	void countFrom(int n, int speed);

private:
	
	static const int SERIAL_DATA = 0;
	static const int REGISTER_CLOCK = 1;
	static const int SERIAL_CLOCK = 2;
	static const int NUM_DIGITS = 4;
	static const int NUM_SEGMENTS = 8;
	static byte const SEGMENTS[10][7];

	static const int MODE_COUNT_UP = 1;
	
	int _mode;
	int _time;
	int _delay;
	int _displayNumber;
	int _digits[NUM_DIGITS];
	int _digitPins[NUM_DIGITS];
	bool _registers[NUM_SEGMENTS];
	
	void increment();
	void parseNumber(int n);
	void writeNumber(int n);
	void write_registers();
};

#endif