/* This project is compatable with all microcontrollers in the Arduino series.
  Tools needed are
1. LED (Most Arduino boards have builtin led) If you don't want an separate LED, check the board, if it has an LED with an (L) next to it, then you don't need a separate LED.
2. Resistors(220ohms, or 330 ohms). IF you are using builtin led, Skip this
3. A microcontroller (Arduino).
4. Breadboard
5. 2 male to male juming wiries 
Remeber to paste this straight into arduino ide, connect the arduino and Hit upload for the prject to be on your arduino.
*\

int led = 13; 
void setup() {

  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
