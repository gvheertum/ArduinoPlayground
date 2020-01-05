
// LED DOT MATRIX - 1088BS
// ROWS = POS
// COLS = NEG

// SENT RMA -> Pins seem to be shorted and P16 lights R0 and 2

// BOTTOM LEFT -> RIGHT (text is on the bottom half)
// R4 R6 C1 C2 R7 C4 R5 C7

// TOP LEFT -> RIGHT 
// (R0+2/C6) C6 R1 C0 R3 C5 C3 (C7?)

const int PIN_R0;
const int PIN_R1;
const int PIN_R2;
const int PIN_R3;
const int PIN_R4;
const int PIN_R5;



void setup() 
{
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
