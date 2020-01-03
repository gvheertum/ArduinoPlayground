int PORT_POT = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PORT_POT, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogVal = analogRead(PORT_POT);
  Serial.print("Val: ");
  Serial.print(analogVal);
  Serial.println("");
  delay(10);
}
