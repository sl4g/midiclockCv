// Declaration of Varialbes
//este funciona con cuatro salidas, dos van a secuenciadores y dos son clock puro

byte midi_start = 0xfa;
byte midi_stop = 0xfc;
byte midi_clock = 0xf8;
byte midi_continue = 0xfb;
int play_flag = 0;
byte data;
int clock_step;
const int switchPin = 8;
const int potPin = 2;
int statusLed0 = 9;
int statusLed1 = 10;
int statusLed2 = 11;
int statusLed3 = 12;
int statusLed4 = 13;
int val = 0;
int switchVal;


// Initialization
void setup() {
  pinMode(statusLed0, OUTPUT);
  pinMode(statusLed1, OUTPUT);
  pinMode(statusLed2, OUTPUT);
  pinMode(statusLed3, OUTPUT);
  pinMode(statusLed4, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(potPin, INPUT);
  Serial.begin(31250);
  clock_step = 0;
}

// Main Programm
void loop() {
  switchVal = digitalRead(switchPin);
  if (switchVal == HIGH) {
    if (Serial.available() > 0) {
      data = Serial.read();
      if (data == midi_start) {
        play_flag = 1;
        clock_step = 0;
      }
      else if (data == midi_continue) {
        play_flag = 1;
      }
      else if (data == midi_stop) {
        play_flag = 0;
        clock_step = 0;
      }
      else if ((data == midi_clock) && (play_flag == 1)) {
        Sync();
      }
    }
  }
  else {

    val = analogRead(potPin); // read the voltage on the pot
    digitalWrite(statusLed0, HIGH); // set the LED on
    digitalWrite(statusLed1, HIGH); // set the LED on
    digitalWrite(statusLed2, HIGH); // set the LED on
    digitalWrite(statusLed3, HIGH); // set the LED on
    digitalWrite(statusLed4, HIGH); // set the LED on
    delay(val); // blink rate set by pot value (in milliseconds)
    digitalWrite(statusLed0, LOW); // set the LED off
    digitalWrite(statusLed1, LOW); // set the LED off
    digitalWrite(statusLed2, LOW); // set the LED off
    digitalWrite(statusLed3, LOW); // set the LED off
    digitalWrite(statusLed4, LOW); // set the LED off
    delay(val); // turn led off for same periodigitalWrite(ledPin, LOW); // turn the ledPin offd as it was turned on

  }
}



// Function

void Sync() { // 1st half of a bar: LED=on, seconds half of a bar: LED=off
  clock_step = clock_step + 1;
  if (clock_step == 1) {
    digitalWrite(statusLed0, HIGH); // set the LED on
    digitalWrite(statusLed1, HIGH); // set the LED on
    digitalWrite(statusLed2, HIGH); // set the LED on
    digitalWrite(statusLed3, HIGH); // set the LED on
    digitalWrite(statusLed4, HIGH); // set the LED on


  }
  else if (clock_step == 24 / 2) {
    digitalWrite(statusLed0, LOW); // set the LED off
    digitalWrite(statusLed1, LOW); // set the LED off
    digitalWrite(statusLed2, LOW); // set the LED off
    digitalWrite(statusLed3, LOW); // set the LED off
    digitalWrite(statusLed4, LOW); // set the LED off

  }
  else if (clock_step == 24) {
    clock_step = 0;
  }
}




/* un codigo para controlar un timmer interno y permitir un timer externo

  void readPots ()
  {
  tempo = (analogRead (AnalogInTempo) * 1.9);
  duration = (analogRead (AnalogInDuration));
  }
   /
*/
