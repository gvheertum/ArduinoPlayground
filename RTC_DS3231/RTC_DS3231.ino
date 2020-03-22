#include <Wire.h>
#include <DS3231.h>

RTClib RTC;
DS3231 Clock;

// Connect 
// SDA -> A4
// SCL -> A5

void setup () 
{
  Wire.begin();
  Serial.begin(9600);
  
  //setupTime();   
  
}

void setupTime()
{
  Clock.setClockMode(false);  
  Clock.setYear(20);
  Clock.setMonth(3);
  Clock.setDate(20);
  Clock.setHour(16);
  Clock.setMinute(55);
}

void loop () 
{  
  delay(1000);
  DateTime now = RTC.now();
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");
}
