// Use ADAFruit SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS3231.h>

RTClib RTC;
DS3231 Clock;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// 0,96" OLED / 0,91 OLED
// vcc -> 5v
// gnd -> gnd
// SCL -> A5
// SDA -> A4

// Link oled and RTC on SDA and SCK/SCL (using wire both can be on the same bus)

void setup() 
{
  Wire.begin(); 
  Serial.begin(9600);

  // Start the screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
}


void loop() 
{   
  display.clearDisplay();  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  DateTime now = RTC.now();
  display.setCursor(0, 0); 
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.print(' ');
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  
  display.display(); //Flush!
  delay(500);
}
