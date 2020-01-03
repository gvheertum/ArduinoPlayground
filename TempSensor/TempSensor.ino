// Temp sensor: LM35 TO-92
// http://www.ti.com/lit/ds/symlink/lm35.pdf

// Flat part on top: left = +3.3, center = Vout, right = gnd
// WARNING: IF PUT ON 5V the board will pull to much energie from the USB
int sensorPin = A0;

/*
 * FeatureDescription
 * 7.3.1LM35TransferFunctionThe accuracyspecifications
 * of the LM35are givenwith respectto a simple
 * linear transfer function: VOUT= 10 mv/°C × T
 * where VOUT is the LM35 outputvoltage and T is the temperaturein °C
 */

// So that's 1024 states, divided in the range 0-5V. 5V / 1024 states = 0,00488V/state (4.88mV/state)
const float ADC_CONVERT = 4.88;

void setup() 
{
   Serial.begin(9600);
   pinMode(sensorPin, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  float sensorValue = analogRead(sensorPin);
  Serial.print(sensorValue);
  Serial.print("   ");
  float outVoltage = (sensorValue * 5000) / 1024; //This is the mv from the port
  Serial.print(outVoltage);
  float tempC = outVoltage / 10; // Convert the mv to C, each 10 mv is 1 C
  Serial.print(" -> Temperature (in C): ");
  Serial.print(tempC);
  Serial.println();
  delay(2000);
}
