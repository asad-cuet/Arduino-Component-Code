#include <Keypad.h> // add this library

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
//    Serial.println(key);
//    int integerVal=getKeypadInteger(key);
    Serial.println(int(key));
  }
}

int getKeypadInteger(int input)
{
  if(input==49)
  {
    return 1;
  }
  if(input==50)
  {
    return 2;
  }
  if(input==51)
  {
    return 3;
  }
  if(input==52)
  {
    return 4;
  }
  if(input==53)
  {
    return 5;
  }
  if(input==54)
  {
    return 6;
  }
  if(input==55)
  {
    return 7;
  }
  if(input==56)
  {
    return 8;
  }
  if(input==57)
  {
    return 9;
  }
  if(input==48)
  {
    return 0;
  }

  // *= 42

  // #= 35

  // D=68

  // C=67

  // B=66

  // A=65
}
