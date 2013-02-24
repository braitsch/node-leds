
#include "Led24.h"
#include "SevenSegment.h"

Led24 led24Controller(8, 9, 10);
SevenSegment sevSegController(4, 5, 6, 7);

void setup(){ }

int seconds = 0;
int t1 = millis();
void loop(){
	int t2 = millis();
	if (t2 - t1 > 1000){
		t1 = t2;
		seconds++;
		sevSegController.setNumber(seconds);
	}
	if (seconds > 9999) seconds = 1;
//	led24Controller.update();
	sevSegController.update();
}