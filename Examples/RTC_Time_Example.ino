// Code to print the current time with the arduino PCF8523 breakout data logger shield
// Requires RTClib

#include "RTClib.h"

RTC_PCF8523 rtc;

void setup () {
  Serial.begin(57600);

  if (! rtc.begin()) { // Flush serial, this is necessary for the program to work
    Serial.flush();
    abort();
  }
  
  rtc.start();
}

void loop () {
    DateTime now = rtc.now();
    String timestr = String(now.month()) + '/' + String(now.day()) + '/' + String(now.year()) + ' ' + String(now.hour()) + ':' + String(now.minute()) + ':' + String(now.second());
    const char *chartime = timestr.c_str();
    Serial.println(chartime);
}
