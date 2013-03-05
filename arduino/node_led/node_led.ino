
#include "Led24.h"
#include "SevenSegment.h"

Led24 led24Controller(9, 10, 11);
SevenSegment sevSegController(4, 5, 6, 7);

int _time = millis();

void setup(){
	sevSegController.setNumber(1234);
//	sevSegController.countFrom(0, 10);
}

void loop(){
	int t2 = millis();
	if (t2 - _time > 6000){
		_time = t2;
		sevSegController.setNumber(random(9999));
	}
	led24Controller.update();
	sevSegController.update();
}