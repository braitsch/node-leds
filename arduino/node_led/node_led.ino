
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
		int cmd = Serial.read();
		if (cmd == 1){
			onNewUserConnected();
		}	else if (cmd == 2){
			onAnimationSelected();
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
	int n = Serial.read();
	Serial.print("onAnimationSelected received: ");
	Serial.println(n);
}