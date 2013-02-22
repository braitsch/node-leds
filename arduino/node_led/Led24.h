#ifndef Led24_H
#define Led24_H

#include "Arduino.h"

class Led24 {
 
public: //everything under here is public, accessible outside of the class the class constructor
	Led24(int sd, int rc, int sc);
	void update();
 
private:
	static const int TOTAL_LEDS = 24;
	static const int CENTER_LED = 12;
	static const int PULSE = 250;
	static const int CHAIN_LENGTH = 3;    // num to keep on when moving out from center //
	
	int _serialDataPin;
	int _registerClockPin;
	int _serialClockPin;

	int _index;
	int _sequence_count;
	boolean _state;
	boolean _registers[TOTAL_LEDS];

	void writeRegisters();
	void slow_step_left_to_right();
	void quick_pulse();
	void knight_rider();
	void every_other_one();
	void out_from_center();
};

#endif