
//Keypad
#include <Keypad.h> // add this library
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
int nonIntegerKeys[]={35,42,65,66,67,68};
byte rowPins[ROWS] = {3,9,10,11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A3,A2,13,12}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    Serial.println(int(key));
  }
}
