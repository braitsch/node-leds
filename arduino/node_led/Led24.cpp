/*
	Led24.cpp - Library for Controlling 24 Led's via 3x74HC595 Shift Registers
	Created by Stephen Braitsch, February 22, 2013
	Released into the public domain.
*/

#include "Led24.h"

Led24::Led24(int sd, int rc, int sc){
	_serialDataPin = sd;
	_registerClockPin = rc;
	_serialClockPin = sc;
// initialize counter variables //
	_index = 0;
	_sequence_count = 0;
	_state = 1;
// set data & clock pins on the arduino //
	pinMode(_serialDataPin, OUTPUT);
	pinMode(_registerClockPin, OUTPUT);
	pinMode(_serialClockPin, OUTPUT);
// ensure nothing is in the shift registers to start //
	for(int i = 0; i < TOTAL_LEDS; i++) _registers[i] = LOW;
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

void Led24::update(){
	if (_sequence_count == 0){
		slow_step_left_to_right();
	}  else if (_sequence_count < 6){
		quick_pulse();
	}  else if (_sequence_count < 26){
		knight_rider();
	}  else if (_sequence_count < 31){
		quick_pulse();
	}  else if (_sequence_count < 50){
		every_other_one();
	}  else if (_sequence_count < 60){
		out_from_center();
	}  else{
		_sequence_count = 0;
	};
	int data =  pollSensor();
	int result = fancyAlgorithm(data);
}

void Led24::slow_step_left_to_right(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		_registers[i] = (i == _index) ? HIGH : LOW;
	}
	_index++;
	if (_index == TOTAL_LEDS) {
		_index = 0;
		_sequence_count++;
	}
	writeRegisters(); delay(PULSE);
}

void Led24::quick_pulse(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		_registers[i] = (_state == 1) ? HIGH : LOW;
	}
	_state = !_state;
	if (_state == 1) _sequence_count++;
	writeRegisters(); delay(PULSE);
}

void Led24::knight_rider(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		if (_state == 1){
			_registers[i] = (i == _index) ? HIGH : LOW;
		}  else if (_state == 0){
			_registers[i] = (i == TOTAL_LEDS - _index) ? HIGH : LOW;
		}
	}
	_index++;
	if (_index == TOTAL_LEDS) {
		_index = 0;
	// flip to the other direction //
		_state = !_state;
		_sequence_count++;
	}
	writeRegisters(); delay(10);
}

void Led24::every_other_one(){
	for(int i = TOTAL_LEDS - 1; i >=  0; i--){
		_registers[i] = (i % 2 == _state) ? HIGH : LOW;
	}
// flip to the other direction //
	_state = !_state;
	if (_state == 1) _sequence_count++;
	writeRegisters(); delay(PULSE);
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
		if (l <= TOTAL_LEDS) _registers[l] = HIGH;
		if (r >= 0) _registers[r] = HIGH;
	}
	_index++;
	if (_index == CENTER_LED + CHAIN_LENGTH) {
		_index = 0;
		_sequence_count++;
	}
	writeRegisters(); delay(35);
}

