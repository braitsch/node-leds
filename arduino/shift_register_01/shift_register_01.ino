
const int SERIAL_DATA = 8;     // pin 14 on the 75HC595
const int REGISTER_CLOCK = 9;  // pin 12 on the 75HC595
const int SERIAL_CLOCK = 10;   // pin 11 on the 75HC595
const int TOTAL_LEDS = 24;
const int CENTER_LED = 12;
const int PULSE = 250;
const int CHAIN_LENGTH = 3;    // num to keep on when moving out from center //

int index = 0;
boolean state = 1;
int sequence_count = 0;

boolean registers[TOTAL_LEDS];

void setup(){
  Serial.begin(9600);
  pinMode(SERIAL_DATA, OUTPUT);
  pinMode(REGISTER_CLOCK, OUTPUT);
  pinMode(SERIAL_CLOCK, OUTPUT);
// ensure nothing is in the shift registers to start //
  for(int i = 0; i < TOTAL_LEDS; i++) registers[i] = LOW;
  writeRegisters();
}

// call only AFTER all values are set (slow otherwise)
void writeRegisters(){
  digitalWrite(REGISTER_CLOCK, LOW);
  for(int i = TOTAL_LEDS - 1; i >=  0; i--){
    digitalWrite(SERIAL_CLOCK, LOW);
    digitalWrite(SERIAL_DATA, registers[i]);
    digitalWrite(SERIAL_CLOCK, HIGH);

  }
  digitalWrite(REGISTER_CLOCK, HIGH);
}

void loop(){
   if (sequence_count == 0){
      slow_step_left_to_right();
   }  else if (sequence_count < 6){
      quick_pulse();
   }  else if (sequence_count < 26){
      knight_rider();
   }  else if (sequence_count < 31){
      quick_pulse();
   }  else if (sequence_count < 50){
      every_other_one();
   }  else if (sequence_count < 60){
      out_from_center();
   }  else{
      sequence_count = 0;
   };
}

void out_from_center()
{
 // turn everyone off // 
  for(int i = TOTAL_LEDS - 1; i >=  0; i--) registers[i] = LOW;
  for(int k = 0; k < CHAIN_LENGTH; k++){
      int l = CENTER_LED + index - k;
      int r = CENTER_LED - index + k - 1;
  // set constraints //
      if (l < CENTER_LED) l = CENTER_LED;
      if (r > CENTER_LED - 1) r = CENTER_LED - 1;
      if (l <= TOTAL_LEDS) registers[l] = HIGH;
      if (r >= 0) registers[r] = HIGH;
  }
  index++;
  if (index == CENTER_LED + CHAIN_LENGTH) {
    index = 0;
    sequence_count++;
  }
  writeRegisters(); delay(35);
}

void quick_pulse()
{
  for(int i = TOTAL_LEDS - 1; i >=  0; i--){
    registers[i] = (state == 1) ? HIGH : LOW;
  }
  state = !state;
  if (state == 1) sequence_count++;
  writeRegisters(); delay(PULSE);
}

void every_other_one()
{
  for(int i = TOTAL_LEDS - 1; i >=  0; i--){
    registers[i] = (i % 2 == state) ? HIGH : LOW;
  }
  // flip to the other direction //
  state = !state;
  if (state == 1) sequence_count++;
  writeRegisters(); delay(PULSE);
}

void slow_step_left_to_right()
{
  for(int i = TOTAL_LEDS - 1; i >=  0; i--){
    registers[i] = (i == index) ? HIGH : LOW;
  }
  index++;
  if (index == TOTAL_LEDS) {
    index = 0;
    sequence_count++;
  }
  writeRegisters(); delay(PULSE);
}

void knight_rider()
{
  for(int i = TOTAL_LEDS - 1; i >=  0; i--){
    if (state == 1){
        registers[i] = (i == index) ? HIGH : LOW;
    }  else if (state == 0){
        registers[i] = (i == TOTAL_LEDS - index) ? HIGH : LOW;      
    }
  }
  index++;
  if (index == TOTAL_LEDS) {
    index = 0;
  // flip to the other direction //
    state = !state;
    sequence_count++;
  }
  writeRegisters(); delay(10);
}
