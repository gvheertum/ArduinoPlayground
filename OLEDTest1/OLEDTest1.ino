// Use ADAFruit SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Start the screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
}

int counter = 0;
void loop() 
{
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("HELLO WORLD"));
  display.setCursor(0,10);
  display.println(counter);
  counter++;
  display.display();      // Show initial text
  delay(100);
}
