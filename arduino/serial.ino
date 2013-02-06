const int outputPin = 13;
 
void setup()
{
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if (incomingByte == 1) {
      digitalWrite(outputPin, HIGH);
    } else if (incomingByte == 0) {
      digitalWrite(outputPin, LOW);
    }
  }
}
