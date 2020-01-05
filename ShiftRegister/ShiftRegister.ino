// TESTING SHIFT REGISTER
// 74HC595
// NOTE: Wire both VCC and SRCLR
const int PIN_CLK = 6; //SRCLK
const int PIN_DATA = 4; // SER
const int PIN_LATCH = 5; //RCLK

void setup() 
{
  Serial.begin(9600);

  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);
}

void loop() 
{

  /*writeSeries(127,1);
  delay(1000);

  writeSeries(127-32-64,1);
  delay(1000);

  writeSeries(0, 1);
  delay(1000);
*/
  for(int i = 1; i < 128; i = i)
  {
    i = i * 2;
    writeSeries(i + (i - 1), 1); //Light this bit and the previous
    delay(1000);
  }
  
  /*writeSeries(0, 1); 
  writeSeries(3, 1);
  delay(3000);
  
  writeSeries(0, 1);
  writeSeries(5, 1);
  delay(3000);
  
  writeSeries(0, 1);
  writeSeries(16, 1);
  delay(3000);
  
  writeSeries(0, 1); 
  writeSeries(1+2+4+8+16+32, 1);
  delay(3000);
  
  writeSeries(0, 1);
  writeSeries(1, 1);
  delay(3000);
  
  writeSeries(0, 1);
  writeSeries(1+8+16+32, 1);
  delay(3000);
  
  writeSeries(0, 1);
  writeSeries(127,1);
  delay(1000);*/
}


void writeSeries(byte data, int iterations)
{
  Serial.print("Writing: ");
  Serial.print(data);
  Serial.print(" for ");
  Serial.print(iterations);
  Serial.print(" iterations");
  Serial.println();
  
  for(int i = 0; i < iterations; i++)
  {
    Serial.print("Iteration: ");
    Serial.print(i);
    Serial.println();
    writeToRegister(data);
  }
}

void writeToRegister(byte data)
{
  Serial.print("Writing and latching: ");
  Serial.print(data);
  Serial.println();
  
  digitalWrite(PIN_LATCH, LOW);
  shiftOut(PIN_DATA, PIN_CLK, MSBFIRST, data);
  digitalWrite(PIN_LATCH, HIGH);
}



/*
 * Serial.println("Before for loop");
  for (int i = 0; i <8; i++)
  {
    // Write bit to dataPin
    if (bit) digitalWrite(dataPin, HIGH);
    else digitalWrite(dataPin, LOW);
    // Take clock pin HIGH
    digitalWrite(clockPin, HIGH);
    // Wait until 74HC595 writes the bit
    delay(20);
    // Take clock pin LOW
    digitalWrite(clockPin, LOW);
    bit != bit;
    // Debug outputs to serial
    Serial.println("For loop");
    Serial.println(i);
  }
  Serial.println("After for loop");
 */
