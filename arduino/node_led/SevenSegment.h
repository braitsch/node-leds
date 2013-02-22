#ifndef SevenSegment_H
#define SevenSegment_H

#include "Arduino.h"

class SevenSegment{

public:
	SevenSegment(int d1, int d2, int d3, int d4);
	void update();

private:
	int digit1;
	int digit2;
	int digit3;
	int digit4;
	static const int segA = 0;
	static const int segB = 1;
	static const int segC = 2;
	static const int segD = 3;
	static const int segE = 4;
	static const int segF = 5;
	static const int segG = 6;
	static const int segP = 7;
	static const byte numbers[10];
};

#endif