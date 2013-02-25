#ifndef Led24_H
#define Led24_H

#include "Arduino.h"

class Led24 {

public:
	Led24(int sd, int rc, int sc);
	void update();

private:
	static const int TOTAL_LEDS = 24;
	static const int CENTER_LED = 12;
	static const int CHAIN_LENGTH = 3; // num to keep on when moving out from center //
	
// animation modes //
	static const int MODE_STEP_LEFT_TO_RIGHT = 1;
	static const int MODE_PULSE_ALL = 2;
	static const int MODE_KNIGHT_RIDER = 3;
	static const int MODE_TOGGLE_EVEN_ODD = 4;
	static const int MODE_OUT_FROM_CENTER = 5;

	struct Mode
	{
	    int name;
	    int pulseDelay;
	    int repeatCount;
	};

	Mode _currentMode;
	static const Mode ANIMATIONS[5];

	int _serialDataPin;
	int _registerClockPin;
	int _serialClockPin;

	int _time;
	int _index;
	int _modeIndex;
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