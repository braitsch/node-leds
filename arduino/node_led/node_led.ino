
#include "Led24.h"
#include "SevenSegment.h"

/*
	Define Pin Connections From Arduino Board
*/

static const int LED_24_SERIAL_DATA_PIN = 9;
static const int LED_24_REGISTER_CLOCK_PIN = 10;
static const int LED_24_SERIAL_CLOCK_PIN = 11;

static const int SEVEN_SEG_SERIAL_DATA = 0;
static const int SEVEN_SEG_REGISTER_CLOCK = 1;
static const int SEVEN_SEG_SERIAL_CLOCK = 2;

static const int SEVEN_SEG_DIGIT_1_PIN = 4;
static const int SEVEN_SEG_DIGIT_2_PIN = 5;
static const int SEVEN_SEG_DIGIT_3_PIN = 6;
static const int SEVEN_SEG_DIGIT_4_PIN = 7;

static const int LED_24_PINS[3] = {
	LED_24_SERIAL_DATA_PIN,
	LED_24_REGISTER_CLOCK_PIN,
	LED_24_SERIAL_CLOCK_PIN
};

static const int SEVEN_SEG_PINS[7] = {
	SEVEN_SEG_SERIAL_DATA,
	SEVEN_SEG_REGISTER_CLOCK,
	SEVEN_SEG_SERIAL_CLOCK,
	SEVEN_SEG_DIGIT_1_PIN,
	SEVEN_SEG_DIGIT_2_PIN,
	SEVEN_SEG_DIGIT_3_PIN,
	SEVEN_SEG_DIGIT_4_PIN
};

Led24 led24Controller(LED_24_PINS);
SevenSegment sevSegController(SEVEN_SEG_PINS);

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
