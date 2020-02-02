#include <LedControl.h>

// 4x64 Matrix display
// Enable leds one-by-one for all rows over all screens, and loop to the next row. After all is done, start with wiping the elements
int PIN_DIN = 8;
int PIN_CS = 9;
int PIN_CLK = 10;

LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_CS, 4);
void setup() 
{
  // put your setup code here, to run once:
  for(int i = 0; i < 4; i++)
  {
    lc.shutdown(i, false);
    lc.setIntensity(i,2);
    lc.clearDisplay(i);
  }
}


int globalDisplay = 0;
int globalCol = 0;
int globalRow = 0;
bool setValue = true;
void loop() 
{
  
  lc.setLed(globalDisplay, globalRow, globalCol, setValue);   
  
  
  globalCol = globalCol + 1;
  if(globalCol >= 8) 
  {
    globalCol = 0; //Reset col
    globalRow = globalRow + 1; //Next row
  }

  if(globalRow >= 8) 
  { 
    globalDisplay = globalDisplay + 1;
    globalRow = 0; //Start on row 0
  }

  if(globalDisplay >= 4)
  {
    globalDisplay = 0; //Start on the first screen
    setValue = !setValue; //Reverse the command we are doing  
  }
 
  delay(50);
}
