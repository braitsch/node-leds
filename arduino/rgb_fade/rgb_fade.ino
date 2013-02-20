int pins[] = { 3, 5, 6 };
int index = 0;
int speed = 10;  // higher number equals slower speed //

void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 
  // fade in from min to max in increments of 5 points:
  for(int i = 0 ; i <= 255; i++) { 
    // sets the value (range from 0 to 255):
    analogWrite(pins[index], i);
    delay(speed);
  }

  // fade out from max to min in increments of 5 points:
  for(int i = 255 ; i >= 0; i--) { 
    // sets the value (range from 0 to 255):
    analogWrite(pins[index], i);
    delay(speed);                            
  }

  index++;
  if (index > 2) index = 0;
}

