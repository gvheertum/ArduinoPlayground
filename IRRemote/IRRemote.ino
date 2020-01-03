#include <IRremote.h>

// Using the remote to toggle leds on the breadboard
// Map the buttons to a command that puts the port for the led on high

// HX1838 IR receiver 38kHz
// http://dalincom.ru/datasheet/AX-1838HS.pdf

// Wiring from FRONT (with receiver part): LEFT = OUT, CENTER = GND, RIGHT = VCC 
int irPort = 2;
int led_1_port = 8;
int led_2_port = 7;
IRrecv irrecv(irPort);
//1: 16724175
//2: 16718055
//3: 16743045
// Reset: 4294967295

const long IR_BUTTON_1 = 16724175;
const long IR_BUTTON_2 = 16718055;
const long IR_BUTTON_3 = 16743045;
const long IR_RESET = 4294967295;
int led_1_Status = LOW;
int led_2_Status = LOW;

void setup() 
{
  Serial.begin(9600);
  pinMode(irPort, INPUT);
  pinMode(led_1_port, OUTPUT);
  pinMode(led_2_port, OUTPUT);
  irrecv.enableIRIn();
}

decode_results results;
void loop() 
{
  
  if (irrecv.decode(&results)) 
  {
    
    Serial.println(results.value); //prints the value a a button press
    Serial.println(" ");
    irrecv.resume();              // Receive the next value
    delay(100); //Wait for the nex element to prevent button being hold toggling too much
    handleButton(results.value);
  }
}

void handleButton(long btnCode)
{
  Serial.print("Handling: ");
  Serial.print(btnCode);
  Serial.println();
  switch(btnCode)
  {
    case IR_BUTTON_1: led_1_Status = led_1_Status == LOW ? HIGH : LOW; toggleLed(led_1_port, led_1_Status); break;
    case IR_BUTTON_2: led_2_Status = led_2_Status == LOW ? HIGH : LOW; toggleLed(led_2_port, led_2_Status); break;
    case IR_RESET: Serial.println("Reset"); break;
    default: Serial.println("Unknown code"); break; 
  }
}

void toggleLed(int port, int currVal) //Having this toggling the mode would be very nice!! Look into pointers again
{
  digitalWrite(port, currVal);
}
