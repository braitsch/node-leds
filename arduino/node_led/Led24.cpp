/*
	Led24.cpp - Library for Controlling 24 Led's via 3x74HC595 Shift Registers
	Created by Stephen Braitsch, February 22, 2013
	Released into the public domain.
*/

#include "Led24.h"

/*
	Animtion Modes { name, pulseDelay, repeatCount }
*/

const Led24::Mode Led24::ANIMATIONS[NUM_ANIMATIONS] = { 
	{ MODE_STEP_LEFT_TO_RIGHT, 150, TOTAL_LEDS},
	{ MODE_PULSE_ALL, 250, 10},
	{ MODE_KNIGHT_RIDER, 25, TOTAL_LEDS * 5},
	{ MODE_TOGGLE_EVEN_ODD, 500, 10},
	{ MODE_OUT_FROM_CENTER, 25, TOTAL_LEDS * 10}
};

Led24::Led24(int sd, int rc, int sc){
	
	_modeIndex = 0;
	_autoMode = true;
	_currentMode = ANIMATIONS[_modeIndex];
// set user defined shift register pins //
	_serialDataPin = sd;
	_registerClockPin = rc;
	_serialClockPin = sc;
	
// initialize counter variables //
	_time = millis();
	_index = 0;
	_state = 1;
	_sequence_count = 0;
	
// set data & clock pins on the arduino //
	pinMode(_serialDataPin, OUTPUT);
	pinMode(_registerClockPin, OUTPUT);
	pinMode(_serialClockPin, OUTPUT);
	
// ensure nothing is in the shift registers to start //
	for(int i = 0; i < TOTAL_LEDS; i++) _registers[i] = LOW;
	writeRegisters();
}

/*
	Public API
*/

void Led24::update(){
	int now = millis();
	if (now - _time > _currentMode.pulseDelay){
		_time = now;
		switch (_currentMode.name){
			case MODE_STEP_LEFT_TO_RIGHT :
				slow_step_left_to_right();
			break;
			case MODE_PULSE_ALL :
				quick_pulse();
			break;
			case MODE_KNIGHT_RIDER :
				knight_rider();
			break;
			case MODE_TOGGLE_EVEN_ODD :
				every_other_one();
			break;
			case MODE_OUT_FROM_CENTER :
				out_from_center();
			break;
		}
		if (_autoMode == true){
			_sequence_count++;
			if (_sequence_count == _currentMode.repeatCount){
				_index = _sequence_count = 0;
				if (++_modeIndex == NUM_ANIMATIONS) _modeIndex = 0;
				_currentMode = ANIMATIONS[_modeIndex];
			}
		}
	}
}

void Led24::setAutoMode(bool n){
	_autoMode = n;
}

void Led24::setAnimation(int n){
// reset timing variables //
	_time = millis();
	_index = 0;
	_state = 1;
	_sequence_count = 0;
// set the animation mode //
	_modeIndex = n - 1;
	_currentMode = ANIMATIONS[_modeIndex];
	Serial.print("Led24::setAnimation received: ");
	Serial.println(n);
}

/*
	Private Methods
*/

void Led24::slow_step_left_to_right(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		_registers[i] = (i == _index) ? HIGH : LOW;
	}
	_index++;
	writeRegisters();
}

void Led24::quick_pulse(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		_registers[i] = (_state == 1) ? HIGH : LOW;
	}
	_state = !_state;
	writeRegisters();
}

void Led24::knight_rider(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		if (_state == 1){
			_registers[i] = (i == _index) ? HIGH : LOW;
		}  else if (_state == 0){
			_registers[i] = (i == TOTAL_LEDS - _index - 1) ? HIGH : LOW;
		}
	}
	_index++;
	if (_index == TOTAL_LEDS) {
		_index = 0;
	// flip to the other direction //
		_state = !_state;
	}
	writeRegisters();
}

void Led24::every_other_one(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		_registers[i] = (i % 2 == _state) ? HIGH : LOW;
	}
// flip to the other direction //
	_state = !_state;
	writeRegisters();
}

void Led24::out_from_center(){
// turn everyone off //
	for(int i = TOTAL_LEDS - 1; i >=  0; i--) _registers[i] = LOW;
	for(int k = 0; k < CHAIN_LENGTH; k++){
		int l = CENTER_LED + _index - k;
		int r = CENTER_LED - _index + k - 1;
	// set constraints //
		if (l < CENTER_LED) l = CENTER_LED;
		if (r > CENTER_LED - 1) r = CENTER_LED - 1;
		if (l >= TOTAL_LEDS) l = TOTAL_LEDS - 1;
		if (r < 0) r = 0;
		if (_index < CENTER_LED + CHAIN_LENGTH - 1){
			_registers[l] = HIGH;
			_registers[r] = HIGH;
		}	else{
			_registers[l] = LOW;
			_registers[r] = LOW;
		}
	}
	_index++;
	if (_index == CENTER_LED + CHAIN_LENGTH) _index = 0;
	writeRegisters();
}

void Led24::writeRegisters(){
	digitalWrite(_registerClockPin, LOW);
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		digitalWrite(_serialClockPin, LOW);
		digitalWrite(_serialDataPin, _registers[i]);
		digitalWrite(_serialClockPin, HIGH);
	}
	digitalWrite(_registerClockPin, HIGH);
}

