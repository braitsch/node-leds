
#include "Led24.h"
#include "SevenSegment.h"

Led24 led24Controller(8, 9, 10);
SevenSegment sevenSegController(11, 12, 13, 14);

void setup(){ }

void loop(){
	led24Controller.update();
	sevenSegController.update();
}