
#include "Led24.h"

Led24 led24Controller(8, 9, 10);

void setup(){ }

void loop(){
	led24Controller.update();
}