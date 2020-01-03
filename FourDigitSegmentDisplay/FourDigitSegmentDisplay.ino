//SEGMENT DISPLAY (4x7)
// MR-3461SRB-2 13 24


// TOP: D1 (5v) | TOP | TOP LEFT | D2 (5v) | D3 (5v) | TOP RIGHT
// BOTTOM: BOTTOM LEFT | BOTTOM | DOT | BOTTOM RIGHT | MIDDLE | D4 (5v)

// Working: Put 5v on the digit to show and negative the segments


// DIGIT SETUP
int D1 = 2;
int D2 = 3;
int D3 = 4;
int D4 = 13;
int digits[] = { D1,D2,D3,D4};

// SEGMENT SETUP
int S_TOP = 6;
int S_TOP_LEFT = 8 ;
int S_TOP_RIGHT = 7;
int S_BOTTOM_LEFT = 11;
int S_BOTTOM = 10;
int S_BOTTOM_RIGHT = 12;
int S_MIDDLE = 9;
int segments[] = { S_TOP, S_TOP_LEFT, S_TOP_RIGHT, S_BOTTOM, S_BOTTOM_LEFT, S_BOTTOM_RIGHT, S_MIDDLE };

// NUMBER LAYOUTS
int layout_0[7] = { S_TOP, S_TOP_LEFT, S_TOP_RIGHT, S_BOTTOM, S_BOTTOM_LEFT, S_BOTTOM_RIGHT };
int layout_1[7] = { S_TOP_RIGHT, S_BOTTOM_RIGHT };
int layout_2[7] = { S_TOP, S_TOP_RIGHT, S_BOTTOM, S_BOTTOM_LEFT, S_MIDDLE };
int layout_3[7] = { S_TOP, S_TOP_RIGHT, S_BOTTOM, S_BOTTOM_RIGHT, S_MIDDLE };
int layout_4[7] = { S_TOP_LEFT, S_TOP_RIGHT, S_BOTTOM_RIGHT, S_MIDDLE };
int layout_5[7] = { S_TOP, S_TOP_LEFT, S_BOTTOM, S_BOTTOM_RIGHT, S_MIDDLE };
int layout_6[7] = { S_TOP, S_TOP_LEFT, S_BOTTOM, S_BOTTOM_LEFT, S_BOTTOM_RIGHT, S_MIDDLE };
int layout_7[7] = { S_TOP, S_TOP_RIGHT, S_BOTTOM_RIGHT };
int layout_8[7] = { S_TOP, S_TOP_LEFT, S_TOP_RIGHT, S_BOTTOM, S_BOTTOM_LEFT, S_BOTTOM_RIGHT, S_MIDDLE };
int layout_9[7] = { S_TOP, S_TOP_LEFT, S_TOP_RIGHT, S_BOTTOM,  S_BOTTOM_RIGHT, S_MIDDLE };
int layout_fail[7] = { S_MIDDLE };

#define len(x)       (sizeof(x) / sizeof(x[0]))

void setup() {
  
  Serial.begin(9600);
  
  // Setup the digits and segments to be output elements
  for(int i = 0; i < len(digits); i++)
  {
    if(digits[i] == 0) { continue; }
    pinMode(digits[i], OUTPUT);
  }

  for(int i = 0; i < len(segments); i++)
  {
    if(segments[i] == 0) { continue; }  
    pinMode(segments[i], OUTPUT);
  }
}

struct SegmentData
{
  int segments[7];
};


struct SegmentData getSegmentForNumber(int number)
{
  SegmentData sd;
  switch(number)
  {
    case 0: arrayCopy(layout_0, sd.segments); break;
    case 1: arrayCopy(layout_1, sd.segments); break;
    case 2: arrayCopy(layout_2, sd.segments); break;
    case 3: arrayCopy(layout_3, sd.segments); break;
    case 4: arrayCopy(layout_4, sd.segments); break;
    case 5: arrayCopy(layout_5, sd.segments); break;
    case 6: arrayCopy(layout_6, sd.segments); break;
    case 7: arrayCopy(layout_7, sd.segments); break;
    case 8: arrayCopy(layout_8, sd.segments); break;
    case 9: arrayCopy(layout_9, sd.segments); break;
    default: arrayCopy(layout_fail, sd.segments); break;
  }
  return sd;
}

void loop()
{
  /*for(int i = 0; i < 10; i++)
  {
    reset();
    delay(200);
    showDigitNumber(0, getSegmentForNumber(i), 0);
    delay(200);
    showDigitNumber(1, getSegmentForNumber(i), 0);
    delay(200);
    showDigitNumber(2, getSegmentForNumber(i), 0);
    delay(200);
    showDigitNumber(3, getSegmentForNumber(i), 1000); //Should keep it for at least 1000;
    delay(1000);
  }*/

  showMultiDigitNumber(1,2,3,4,1000);
  showMultiDigitNumber(8,8,8,8,1000);
  showMultiDigitNumber(2,5,7,11,1000);
  /*for(int i = 1; i < 1000000; i++)
  {
    reset();
    lightSegments(i % 4, segments, len(segments));
    //delayMicroseconds(20);
  }*/
  
}

void reset()
{
  setSerie(segments, len(segments), HIGH);
  setSerie(digits, len(digits), LOW);
}

void showMultiDigitNumber(int nrIdx0, int nrIdx1, int nrIdx2, int nrIdx3, int durationMs)
{
  Serial.println("Showing multi");
  long durationUs = (long)1000 * (long)durationMs;
  Serial.print(durationUs);
  int sleep = 100;
  
  int idxLoop = 0;
  int nrs[] = { nrIdx0, nrIdx1, nrIdx2, nrIdx3 };
  for(long i = 0; i < durationUs; i += sleep) 
  {
    showDigitNumber(idxLoop, getSegmentForNumber(nrs[idxLoop]), sleep);
    idxLoop = idxLoop > 3 ? 0 : idxLoop + 1;
  }  
}

void showDigitNumber(int digitIdx, struct SegmentData segmentData, int durationUs) // Duration will set a minumum length for display and then reset it. If no time is set the number will be kept on 
{
  int digitPin = digits[digitIdx];

  // Put HIGH on all segments "breaking" the flow and stopping the lighting
  setSerie(segments, len(segments), HIGH);

  // Put High on the input of the digit
  digitalWrite(digitPin, HIGH);

  // For all segements to be lit set LOW to have a current (lighting the element), assume length of 7
  setSerie(segmentData.segments, 7, LOW);

  // Do we need to wait? (applicable for multi number situations)
  if(durationUs > 0)
  {
    delayMicroseconds(durationUs);    
    reset();
  }
}




// HELPERS



void setSerie(int elements[], int count, int value) // :( Cannot get the length working right.... stupid C
{
  for(int i = 0; i < count; i++)
  {
    if(elements[i] == 0) { continue; }  
    digitalWrite(elements[i], value);
  }
}

void arrayCopy(int origin[7], int destination[7])
{
  for(int i = 0; i < 7; i++)
  {
    destination[i] = origin[i];
  }
}
