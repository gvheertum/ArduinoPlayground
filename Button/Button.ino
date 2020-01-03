// Test button presses by lighting a traffic light based on the module of the count

// digital pin 2 has a pushbutton attached to it
int pushButton = 2;

// The traffic light is connected to 8,9 and 10
int pinRed = 8;
int pinYellow = 9;
int pinGreen = 10;


int cnt = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("AT");
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinYellow, OUTPUT);
  pinMode(pinGreen, OUTPUT);
}
int oldVal = 0;
void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(pushButton);
  if(value != oldVal)
  {
    //Serial.print("Changed state, cnt: ");
    //Serial.print(cnt);
    //Serial.println("");
    oldVal = value;
    cnt += value;
  }

  digitalWrite(pinRed, LOW);
  digitalWrite(pinYellow, LOW);
  digitalWrite(pinGreen, LOW);
  
  
  
  if(cnt % 2 == 0)
  {
    digitalWrite(pinRed, HIGH);
  }
  if(cnt % 3 == 0)
  {
    digitalWrite(pinYellow, HIGH);
  }
  if(cnt % 4 == 0)
  {
    digitalWrite(pinGreen, HIGH);
  }
  
   
  delay(10);
  
}
