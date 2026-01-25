/*Including Library*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
/*Creating Instance*/
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 LCD
void setup() {

/*Initiating*/
Wire.begin();
lcd.init();
rtc.begin();
 lcd.backlight();
/* Getting Ready*/
lcd.clear();
lcd.setCursor(0,0);

/*Start Up*/
lcd.print("Time Module");
lcd.setCursor(0,1);
lcd.print("Starting...");
delay(700);
lcd.clear();
/*Format Mentioning*/
lcd.setCursor(0,0);
lcd.print("(Hr:Min:Sec)");
lcd.setCursor(0,1);
lcd.print("(MM/DD/YYYY)");
delay(1000);
lcd.clear();
   
}

void loop() {

    DateTime now = rtc.now();

/*Time Printing*/
lcd.setCursor(0,0);
lcd.print(now.hour(), DEC);
lcd.print(':');
lcd.print(now.minute(), DEC);
lcd.print(':');
lcd.print(now.second(), DEC);
lcd.print("            ");
/*Date Printing*/
lcd.setCursor(0,1);
lcd.print(now.month(), DEC);
lcd.print('/');
lcd.print(now.day(), DEC);
lcd.print('/');
lcd.print(now.year(), DEC);



}
