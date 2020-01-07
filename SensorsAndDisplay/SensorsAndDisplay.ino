#include <LiquidCrystal.h>

// Playing with sensors and display
int LCD_port_RS = 12; 
int LCD_port_Enable = 11;
int LCD_port_D4 = 5;
int LCD_port_D5 = 4;
int LCD_port_D6 = 3;
int LCD_port_D7 = 2;

int SENSOR_Pot_Input = A0;
int SENSOR_Temp_Input = A5;
int SENSOR_Tilt_Input = 8;
int SENSOR_Light_Input = A3;
 
//LiquidCrystal lcd;
LiquidCrystal lcd(LCD_port_RS, LCD_port_Enable, LCD_port_D4, LCD_port_D5, LCD_port_D6, LCD_port_D7);

void setup() 
{
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();

  pinMode(SENSOR_Pot_Input, INPUT);
  pinMode(SENSOR_Temp_Input, INPUT);
  pinMode(SENSOR_Tilt_Input, INPUT);
  pinMode(SENSOR_Light_Input, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:

  int secSinceBoot = millis() / 1000;
  float potVal = analogRead(SENSOR_Pot_Input);
  int tiltVal = digitalRead(SENSOR_Tilt_Input);
  float tempVal = getTemp(SENSOR_Temp_Input);
  float lightVal = analogRead(SENSOR_Light_Input);

  displayInfo(0, "Run(sec)", secSinceBoot);
  displayInfo(1, "Tilt", tiltVal);
  delay(1000);
  
  lcd.clear();
  displayInfo(0, "Temp", tempVal);
  displayInfo(1, "Pot", potVal);
  delay(1000);
  
  lcd.clear();
  displayInfo(0, "Light", lightVal);
  delay(1000);

  //TODO: Auto cycle
  
  
  lcd.clear();
}
float getTemp(int pin)
{
  float sensorValue = analogRead(pin);
  Serial.print(sensorValue);
  Serial.print("   ");
  float outVoltage = (sensorValue * 5000.0) / 1024.0; //This is the mv from the port
  Serial.print(outVoltage);
  float tempC = outVoltage / 10.0; // Convert the mv to C, each 10 mv is 1 C
  return tempC;
}

void displayInfo(int line, char* label, float value)
{
  lcd.setCursor(0, line);
  lcd.print(label);
  lcd.setCursor(8, line);
  lcd.print(value);
}
