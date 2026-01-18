/* This project is compatible with all microcontrollers in the Arduino series.
   Tools needed are:
1. LED (Most Arduino boards have built-in LED). If you don't want a separate LED, check the board; if it has an LED with an (L) next to it, then you don't need a separate LED.
2. Resistors (220 ohms, or 330 ohms). If you are using built-in LED, skip this.
3. A microcontroller (Arduino).
4. Breadboard
5. 2 male-to-male jumping wires 

Remember to paste this straight into Arduino IDE, connect the Arduino, and hit upload for the project to run on your Arduino.
*/

int led = 13; 

void setup() {
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);   // turn the LED off (LOW is the voltage level)
  delay(1000);               // wait for a second
}
