#ifndef SevenSegment_H
#define SevenSegment_H

#include "Arduino.h"

class SevenSegment{

public:
	SevenSegment(int d1, int d2, int d3, int d4);
	void update();
	void setNumber(int n);

private:
	
	static const int SERIAL_DATA = 0;
	static const int REGISTER_CLOCK = 1;
	static const int SERIAL_CLOCK = 2;
	static const int NUM_DIGITS = 4;
	static const int NUM_SEGMENTS = 8;
	static byte const SEGMENTS[10][7];
	
	int _displayNumber[4];
	int _digitPins[NUM_DIGITS];
	boolean _registers[NUM_SEGMENTS];
	
	void writeNumber(int n);
	void write_registers();
};

#endif