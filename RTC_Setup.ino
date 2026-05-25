/* 
 *  ======================================================================
 *  COPYRIGHT NOTICE
 *  ======================================================================
 *  Copyright (C) 2026 Sohan Krishna Golkonda. All Rights Reserved.
 *  
 *  Project Name: RTC_Setup
 *  Creation Date: 03/25/26
 *  Author: Sohan Krishna Golkonda
 *  
 *  LEGAL TERMS AND CONDITIONS:
 *  This software and its source code are the exclusive intellectual 
 *  property of the author. 
 *  
 *  1. PLAGIARISM IS STRICTLY PROHIBITED. You may not copy, re-upload, 
 *     or distribute this code under your own name or claim authorship.
 *  2. You may use and modify this code solely for your own personal, 
 *     private, and non-commercial educational use.
 *  3. Any public exhibition or sharing of this project must explicitly 
 *     credit Sohan Krishna Golkonda as the original author.
 *  ======================================================================
 */

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting the time!");

    // Set the time: RTC_DS1307(hour, minute, second, day, month, year)
    rtc.adjust(DateTime(2026, 1, 19, 12, 17, 40)); // Example: 19 Jan 2026, 11:30:00
  }
}

void loop () {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  delay(1000);
}

