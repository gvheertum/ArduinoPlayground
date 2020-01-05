/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/
int LED_PINNED = 4;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED_PINNED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED_PINNED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);           
  serial.write("Test!");            // wait for a second
  digitalWrite(LED_PINNED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}