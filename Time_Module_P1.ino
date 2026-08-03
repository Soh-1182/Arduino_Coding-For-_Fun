/* 
 *  ======================================================================
 *  COPYRIGHT NOTICE
 *  ======================================================================
 *  Copyright (C) 2026 Sohan Krishna Golkonda. All Rights Reserved.
 *  
 *  Project Name: Time_Module_P1
 *  Creation Date: 02/13/26
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
    while(1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting the time!");

    // Set the time: RTC_DS1307(YR, MON, DAY, HOUR, MIN, SEC)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  else {
    Serial.println("RTC is already RUNNING. Could be either right or wrong time. Please pull out battery and replace it"); 
    while(1);
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

