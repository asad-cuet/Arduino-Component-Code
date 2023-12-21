//logical variable
int resetMode=0;


//pin used
//motor
int motor_pin_arr[]={2,4,7,8};
//logical pin
int bankM=2;  //driver pin->2
int waterM=4;  //driver pin->7
//speed pin
int bankM_waterM_PWM=5;  //driver pin->1

//logical pin
int patientM=7;  //driver pin->10
int wasteM=8;     //driver pin->15
//speed pin
int patientM_wasteM_PWM=6; //driver pin->9


int availablePerc=0;
int space=0;
int inputOption_1_0[]={1,0};
int inputOption_1_2[]={1,2};



//ultrasonic
#include <NewPing.h> // Library for ultrasonic sensors
int trig= 12; // The pin connected to the trigger pin of the ultrasonic sensor
int echo= 13;    // The pin connected to the echo pin of the ultrasonic sensor
int maxDistance=1000;
NewPing sonar(trig, echo, maxDistance); // Create an instance of the NewPing class




//Lcd Display Library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//for store data
#include <EEPROM.h>
int PatienMotorSpeed=0;

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
byte rowPins[ROWS] = {13, 12, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    //lcd Display
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

    //Run this code reset EEPROM
    pinMode(bankM,OUTPUT);
    pinMode(waterM,OUTPUT);
    pinMode(patientM,OUTPUT);
    pinMode(wasteM,OUTPUT);
    pinMode(bankM_waterM_PWM, OUTPUT);
    pinMode(patientM_wasteM_PWM, OUTPUT);
    
}

void loop() {
  reset:
  if(resetMode)
  {
    turnOffAllMotor();

    option1:
      lcdCharDisplay(1,0,"Want to Clean",1);
      lcdCharDisplay(2,1,"1. Yes",0);
      lcdCharDisplay(2,2,"0. No",0);
      char key1 = keypad.getKey();
      if (key1){
        if(searchInArray(nonIntegerKeys,6,key1))
        {
          warnInvalidInput();
          goto option1;
        }
        lcdCharDisplay(8,3,key1,0);
        if(getKeypadInteger(key1)==1)
        {
          clean();
        }
        if(getKeypadInteger(key1)==0)
        {
          goto option2;
        }
      }
      else
      {
        goto option1;
      }


    option2:
      lcdCharDisplay(1,0,"Want to Load?",1);
      lcdCharDisplay(2,1,"1. Yes",0);
      lcdCharDisplay(2,2,"0. No",0);
      char key2 = keypad.getKey();
      if (key2){
        if(!searchInArray(inputOption_1_0,6,getKeypadInteger(key2)))
        {
          warnInvalidInput();
          goto option2;
        }
        if(getKeypadInteger(key2)==1)
        {
          load();
        }
        if(getKeypadInteger(key2)==0)
        {
          goto option3;
        }
      }
      else
      {
        goto option2;
      }


    option3:
      lcdCharDisplay(1,0,"Want to Change Speed?",1);
      lcdCharDisplay(2,1,"1. Yes",0);
      lcdCharDisplay(2,2,"0. No",0);

      char key3 = keypad.getKey();
      if (key3)
      {
        if(!searchInArray(inputOption_1_0,6,getKeypadInteger(key3)))
        {
          warnInvalidInput();
          goto option3;
        }
        if(getKeypadInteger(key3)==1)
        {
          goto option3_digit1;
        }
        if(getKeypadInteger(key3)==0)
        {
          goto option4;
        }
      }
      else
      {
        goto option3;
      }




    option3_digit1:
      lcdCharDisplay(3,0,"Enter Input",1);
      char key4 = keypad.getKey();
      if (key4)
      {
        if(searchInArray(nonIntegerKeys,6,key4))
        {
          warnInvalidInput();
          goto option3_digit1;
        }
        int digit1=key4;



        option3_digit2:
          char key5 = keypad.getKey();
          if (key5)
          {
            if(searchInArray(nonIntegerKeys,6,key5))
            {
              warnInvalidInput();
              goto option3_digit1;
            }
            int digit2=key5;


            option3_digit3:
              char key6 = keypad.getKey();
              if (key6)
              {
                if(searchInArray(nonIntegerKeys,6,key6))
                {
                  warnInvalidInput();
                  goto option3_digit1;
                }
                int digit3=key6;
                int finalSpeed=getKeypadInteger(digit1)*100+getKeypadInteger(digit2)*10 + getKeypadInteger(digit3);
                EEPROM.write(PatienMotorSpeed, finalSpeed);
              }
              else
              {
                goto option3_digit3;
              }
          }
          else
          {
            goto option3_digit2;
          }
      }
      else
      {
        goto option3_digit1;
      }

    option4:
    resetMode=0;
    goto reset;
  }


  initiateDevice:
  lcdCharDisplay(1,0,"Choose a option?",1);
  lcdCharDisplay(2,1,"1. Patient Load",0);
  lcdCharDisplay(2,2,"2. Reset Device",0);
  initiateInput:
    char key7 = keypad.getKey();
    if (key7){
      if(searchInArray(inputOption_1_2,6,getKeypadInteger(key7)))
      {
        if(getKeypadInteger(key7)==1)
        {
          load();
        }
        if(getKeypadInteger(key7)==2)
        {
          resetMode=1;
          goto reset;
        }
      }
      else
      {
        warnInvalidInput();
        goto initiateDevice;
      }
    }
    else
    {
      goto initiateInput;
    }

}

void measureSpace()
{
  digitalWrite(trig, HIGH);
  delay(0.01);
  digitalWrite(trig, LOW);
  space=pulseIn(echo, HIGH)*0.0332/2;  //in cm
}

void mesaureWaterPerc()
{
  measureSpace();
  float available_water=380-space;   //380 is the height of bottle
  availablePerc=(available_water/380)*100;
}

void lcdCharDisplay(int column,int row,char text[],int clear)
{
  if(clear==1)
  {
    lcd.clear();
  }
  lcd.setCursor(column, row);
  lcd.print(text);
}

void warnInvalidInput()
{
  lcdCharDisplay(3,0,"Invalid Input",1);
  lcdCharDisplay(3,2,"Starting Again",0);
  delay(1500);
}

void resetEeprom()
{
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Reseting EEPROM");

    for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 0);
    }
    
}

void turnOnMotor(int motor_pin)
{
  digitalWrite(motor_pin, HIGH);
  //turn all other motor
  for(int i=0; i<4; i++)
  {
      if(motor_pin_arr[i] != motor_pin)
      {
          digitalWrite(motor_pin_arr[i], LOW);
      }
  }
}
void turnOffAllMotor()
{
  for(int i=0; i<4; i++)
  {
    digitalWrite(motor_pin_arr[i], LOW);
  }
}

void load()
{
  mesaureWaterPerc();
  while(availablePerc>5)
  {
    turnOnMotor(bankM);
    mesaureWaterPerc();
  }
}

int clean()
{
  mesaureWaterPerc();
  int waste_removed=0;
  warn:
  if(availablePerc>5)
  {
    lcdCharDisplay(1,0,"Clean At Any Cost?",1);
    lcdCharDisplay(2,1,"1. Yes",0);
      lcdCharDisplay(2,2,"0. No",0);
      inputAgain:
      char key1 = keypad.getKey();
      if (key1){
        if(searchInArray(nonIntegerKeys,6,key1))
        {
          warnInvalidInput();
          goto inputAgain;
        }
        lcdCharDisplay(8,3,key1,0);
        if(getKeypadInteger(key1)==1)
        {
          removeWaste();
          waste_removed=1;
        }
        if(getKeypadInteger(key1)==0)
        {
          goto finish;
        }
      }
      else
      {
        goto warn;
      }
  }
  else
  {
    removeWaste();
    waste_removed=1;
  }

  if(waste_removed==1)
  {
    cleanNow();
  }

  finish:
  return 1;
}


int removeWaste() 
{
  mesaureWaterPerc();
  while(availablePerc>5)
  {
    turnOnMotor(wasteM);
    mesaureWaterPerc();
  }
  return 1;
}

void cleanNow()
{
  mesaureWaterPerc();
  while(availablePerc<20)
  {
    turnOnMotor(waterM);
    mesaureWaterPerc();
  }

  while(availablePerc>5)
  {
    turnOnMotor(wasteM);
    mesaureWaterPerc();
  }
  
}

int searchInArray(int arr[],int length,int toSearch)
{
    for(int i=0; i<length; i++)
    {
        if(arr[i] == toSearch)
        {
            return 1;
        }
    }
    return 0;
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
