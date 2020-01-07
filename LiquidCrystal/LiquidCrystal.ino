#include <LiquidCrystal.h>

// LCD display testing
/*
 *     LCD RS pin to digital pin 12
    LCD Enable pin to digital pin 11
    LCD D4 pin to digital pin 5
    LCD D5 pin to digital pin 4
    LCD D6 pin to digital pin 3
    LCD D7 pin to digital pin 2 

    LCD 1 (VSS) = GND
    LCD 2 (VDD) = 5v
    LCD 5 (RW) = GND -> If not connected the display will not refresh
    LCD 16 (K) = GND
    LCD 15 (A) = 5V

LCD 3 (Vo) -> Contrast POT meter or HIGH resistor
    
 * 
 */

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welkom");
  delay(1000);
  lcd.clear();
}


void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  lcd.setCursor(16-4,0);
  lcd.print(2020);
  delay(500);
  lcd.clear();
}
