/*
	SevenSegment.cpp - Library for Controlling a 7-Segment Display via a 74HC595 Shift Register
	Created by Stephen Braitsch, February 22, 2013
	Released into the public domain.
*/

#include "SevenSegment.h"

SevenSegment::SevenSegment(int d1, int d2, int d3, int d4){
	static const byte numbers[10] = {
		B11000000, // 0
		B11111001, // 1
		B10100100, // 2
		B10110000, // 3
		B10011001, // 4
		B10010010, // 5
		B10000010, // 6
		B11111000, // 7
		B10000000, // 8
		B10010000  // 9
	};
	digit1 = d1;
	digit2 = d2;
	digit3 = d3;
	digit4 = d4;
	pinMode(digit1,OUTPUT);
	pinMode(digit2,OUTPUT);
	pinMode(digit3,OUTPUT);
	pinMode(digit4,OUTPUT);
	pinMode(segA,OUTPUT);
	pinMode(segB,OUTPUT);
	pinMode(segC,OUTPUT);
	pinMode(segD,OUTPUT);
	pinMode(segE,OUTPUT);
	pinMode(segF,OUTPUT);
	pinMode(segG,OUTPUT);
	pinMode(segP,OUTPUT);
}

void SevenSegment::update()
{
	for (int digitPosition=0; digitPosition < 4; digitPosition++){
		digitalWrite(digit1 + digitPosition,HIGH);
		for (int numIndex=0; numIndex <= 9; numIndex++){
			int number = numbers[numIndex];
			// digitalWrite(segA, bitRead(number, 0));
			// digitalWrite(segB, bitRead(number, 1));
			// digitalWrite(segC, bitRead(number, 2));
			// digitalWrite(segD, bitRead(number, 3));
			// digitalWrite(segE, bitRead(number, 4));
			// digitalWrite(segF, bitRead(number, 5));
			// digitalWrite(segG, bitRead(number, 6));
			// digitalWrite(segP, bitRead(number, 7));
			// delay(200);
		}
		digitalWrite(digit1 + digitPosition,LOW);
	}
}