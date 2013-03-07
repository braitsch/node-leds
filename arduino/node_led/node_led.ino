
#include "Led24.h"
#include "SevenSegment.h"

Led24 led24Controller(9, 10, 11);
SevenSegment sevSegController(4, 5, 6, 7);

void setup(){
	sevSegController.setNumber(1234);
//	sevSegController.countFrom(0, 10);
}

void loop(){
	// print the id of any new connections //
	if (Serial.available() > 0) {
	// first byte is the multiplier //
		int m = Serial.read() * 255;
	// second byte is the remainder //
		int r = Serial.read();
		sevSegController.setNumber(m + r);
	}
	led24Controller.update();
	sevSegController.update();
}