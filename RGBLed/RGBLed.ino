/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int PIN_RED = 10;
int PIN_GREEN = 9;
int PIN_BLUE = 11;
int PIN_IN = A4;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.write("Starting");
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  Serial.write("Whoop loop");
  reset();
  loopLed(PIN_RED);
  loopLed(PIN_GREEN);
  loopLed(PIN_BLUE);

  reset();

  loopLed(PIN_RED);
  reset();
  loopLed(PIN_GREEN);
  reset();
  loopLed(PIN_BLUE);


  delay(1000);                       // wait for a second
}

void reset()
{
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);

}

void loopLed(int led)
{  
  int status = 0;
  while (status <= 255)
  {
    Serial.write("Setting ");
    Serial.write(led);
    Serial.write(" @ ");
    Serial.write(status);

    analogWrite(led, status);
    status++;
    delay(2);
  }
}
