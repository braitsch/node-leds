
#include "Led24.h"
#include "SevenSegment.h"

Led24 led24Controller(9, 10, 11);
SevenSegment sevSegController(4, 5, 6, 7);

void setup(){
	sevSegController.setNumber(1234);
//	sevSegController.countFrom(0, 10);
}

void loop(){
	if (Serial.available() > 0) {
// first byte received represents the command to exec //
		int cmd = Serial.read();
		switch(cmd){
			case 1 :
				onNewUserConnected();
			break;
			case 2 :
				onAnimationSelected();
			break;
			case 3 :
				onAutoModeSelected();
			break;
		}
	}
	led24Controller.update();
	sevSegController.update();
}

void onNewUserConnected()
{
// first byte is the multiplier //
	int m = Serial.read() * 255;
// second byte is the remainder //
	int r = Serial.read();
// print the id of the newest connection //
	sevSegController.setNumber(m + r);
}

void onAnimationSelected()
{
	led24Controller.setAnimation(Serial.read());
}

void onAutoModeSelected()
{
	led24Controller.setAutoMode(Serial.read());
}