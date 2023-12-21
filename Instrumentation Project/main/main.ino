//logical variable
int resetMode=0;


//pin used
int low_level_pin=A0;
int upper_level_pin=A1;
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



//var
int availablePerc=0;
int space=0;
int inputOption_1_0[]={1,0};
int inputOption_1_2[]={1,2};
int motor_speed=250;
int lowerLevel=5;
int upperLevel=90;


//char key response of keypad
int Star= 42;
int Hash= 35;
int D=68;
int C=67;
int B=66;
int A=65;





//Lcd Display Library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//for store data
#include <EEPROM.h>
int PatienMotorSpeed[]={0,1,2};

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

void setup() {
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

    //sensor pin
    pinMode(low_level_pin,INPUT);
    pinMode(upper_level_pin,INPUT);
    digitalWrite(low_level_pin,LOW);
    digitalWrite(upper_level_pin,LOW);
    
}

void loop() {
  reset:
  if(resetMode)
  {
    turnOffAllMotor();

    option1:
      lcdCharDisplay(1,0,"Want to Clean",1,1);
      lcdCharDisplay(2,1,"1. Yes",0,1);
      lcdCharDisplay(2,2,"0. No",0,1);
      option1_input:
      char key1 = keypad.getKey();
      if (key1){
        if(searchInArray(nonIntegerKeys,6,key1))
        {
          warnInvalidInput();
          goto option1;
        }
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
        goto option1_input;
      }


    option2:
      lcdCharDisplay(0,0,"Want to Load?",1,1);
      lcdCharDisplay(2,1,"1. Yes",0,1);
      lcdCharDisplay(2,2,"0. No",0,1);
      option2_input:
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
          goto  option3;
        }
        if(getKeypadInteger(key2)==0)
        {
          goto option3;
        }
      }
      else
      {
        goto option2_input;
      }


    option3:
      lcdCharDisplay(1,0,"Release Speed:",1,1);
      lcdIntDisplay(5,1,getPatientMotorSpeed(),0,1);
      lcdCharDisplay(3,2,"Change Speed?",0,1);
      lcdCharDisplay(3,3,"1. Yes 0. No",0,1);
      options3_input:
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
        goto options3_input;
      }




    option3_digit1:
      lcdCharDisplay(0,0,"Enter Input (3digit)",1,1);
      option3_digit1_input:
      char key4 = keypad.getKey();
      if (key4)
      {
        if(searchInArray(nonIntegerKeys,6,key4))
        {
          warnInvalidInput();
          goto option3_digit1;
        }
        int digit1=getKeypadInteger(key4);
        EEPROM.write(PatienMotorSpeed[0], digit1);
        lcdIntDisplay(6,1,digit1,0,0);


        option3_digit2:
          char key5 = keypad.getKey();
          if (key5)
          {
            if(searchInArray(nonIntegerKeys,6,key5))
            {
              warnInvalidInput();
              goto option3_digit1;
            }
            int digit2=getKeypadInteger(key5);
            EEPROM.write(PatienMotorSpeed[1], digit2);
            lcdIntDisplay(7,1,digit2,0,0);

            option3_digit3:
              char key6 = keypad.getKey();
              if (key6)
              {
                if(searchInArray(nonIntegerKeys,6,key6))
                {
                  warnInvalidInput();
                  goto option3_digit1;
                }
                int digit3=getKeypadInteger(key6);
                EEPROM.write(PatienMotorSpeed[2], digit3);
                lcdIntDisplay(8,1,digit3,0,0);
                lcdCharDisplay(4,2,"Saving..",0,1);
                delay(1500);

                int patient_motor_speed=getPatientMotorSpeed();
                if(patient_motor_speed==0)
                {
                  lcdCharDisplay(0,0,"Warning!!!",1,1);
                  lcdCharDisplay(0,1,"Speed Must be",0,1);
                  lcdCharDisplay(0,2,"0-100",0,1);
                  lcdCharDisplay(0,3,"Try Again",0,1);
                  delay(2500);
                  goto option3_digit1;
                }
                
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
        goto option3_digit1_input;
      }

    option4:
    resetMode=0;
    goto reset;
  }


  initiateDevice:
  lcdCharDisplay(1,0,"Release Speed:",1,0);
  lcdIntDisplay(16,0,getPatientMotorSpeed(),0,0);
  lcdCharDisplay(1,1,"Choose a option?",0,1);
  lcdCharDisplay(2,2,"1. Patient Load",0,1);
  lcdCharDisplay(2,3,"2. Reset Device",0,1);
  initiateInput:
    char key7 = keypad.getKey();
    if (key7){
      if(searchInArray(inputOption_1_2,6,getKeypadInteger(key7)))
      {
        if(getKeypadInteger(key7)==1)
        {
          releaseToPatient();
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


void mesaureWaterPerc()
{
  int lower_read=analogRead(A0);
  int upper_read=analogRead(A1);
  int sensitivity=950;
  if(lower_read<950)
  {
    Serial.println("water low");
    availablePerc=0;
  }
  if(lower_read>sensitivity && upper_read<sensitivity)
  {
    Serial.println("water filled");
    availablePerc=50;
  }
  if(upper_read>sensitivity)
  {
    Serial.println("water over filled");
    availablePerc=100;
  }
  Serial.print("lower_read: ");
  Serial.println(lower_read);
  Serial.print("upper_read: ");
  Serial.println(upper_read);
}

void lcdCharDisplay(int col,int row,char text[],int clear,int auto_cursor)
{
  if(clear==1)
  {
    lcd.clear();
  }
  int column=col;
  if(auto_cursor)
  {
    int LCD_COLUMNS=20;
    int textLength = strlen(text);
    int startPosition = (LCD_COLUMNS - textLength) / 2;
    if(startPosition>0)
    {
      startPosition-=1;
    }
    column=startPosition;
  }
  lcd.setCursor(column, row);
  lcd.print(text);

  size_t length = strlen(text);
  Serial.println(length);
}

void lcdIntDisplay(int col,int row,int number,int clear,int auto_cursor)
{
  if(clear==1)
  {
    lcd.clear();
  }
  int column=col;
  if(auto_cursor)
  {
    int LCD_COLUMNS=20;
    int textLength = countDigits(number);
    int startPosition = (LCD_COLUMNS - textLength) / 2;
    if(startPosition>0 && startPosition%2==0)
    {
      startPosition-=1;
    }
    column=startPosition;
  }
  lcd.setCursor(column, row);
  lcd.print(number);
}

int countDigits(int num) {
    // Convert the integer to a string
    char str[20]; // Assumes the number won't be more than 20 digits long
    sprintf(str, "%d", num);

    // Calculate and return the length of the string
    return strlen(str);
}

void warnInvalidInput()
{
  lcdCharDisplay(3,0,"Invalid Input",1,1);
  lcdCharDisplay(3,2,"Input Again",0,1);
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


int takeIntegerInput(int validate_key[])
{
    initiate:
    char key = keypad.getKey();
    if (key){
      if(searchInArray(validate_key,6,getKeypadInteger(key)))
      {
        return getKeypadInteger(key);
      }
      else
      {
        warnInvalidInput();
        goto initiate;
      }
    }
    else
    {
      goto initiate;
    }
}

int takeCharInput(int validate_key[])
{
    initiate:
    char key = keypad.getKey();
    if (key){
      if(searchInArray(validate_key,6,key))
      {
        return key;
      }
      else
      {
        warnInvalidInput();
        goto initiate;
      }
    }
    else
    {
      goto initiate;
    }
}

void turnOnMotor(int motor_pin)
{
  //turn all other motor
  for(int i=0; i<4; i++)
  {
      if(motor_pin_arr[i] != motor_pin)
      {
          digitalWrite(motor_pin_arr[i], LOW);
      }
  }

  //controlling motor speed
  if(motor_pin!=patientM)  //if patient motor
  {
      digitalWrite(patientM_wasteM_PWM,motor_speed);
      digitalWrite(bankM_waterM_PWM,motor_speed);
  }


  //turning on the motor
  digitalWrite(motor_pin, HIGH);

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
  lcd.clear();
  while(availablePerc<upperLevel)
  {
    processingMessage(2,"Selline Loading..");
    turnOnMotor(bankM);
    mesaureWaterPerc();
  }
  turnOffAllMotor();
  lcdCharDisplay(2,0,"Selline Loaded",1,1);
  lcdCharDisplay(2,1,"Type 0 to close",0,1);
  int input=takeIntegerInput({0});
}

void releaseToPatient()
{
  mesaureWaterPerc();
  int patient_motor_speed=getPatientMotorSpeed();
  if(patient_motor_speed<=100 && patient_motor_speed>0)
  {
    digitalWrite(patientM_wasteM_PWM,patient_motor_speed);
  }
  else if(patient_motor_speed==0)
  {
    lcdCharDisplay(0,0,"Warning!!!",1,1);
    lcdCharDisplay(0,1,"Please Set Speed",0,1);
    lcdCharDisplay(0,2,"Must be 0-100",0,1);
    lcdCharDisplay(0,3,"Type 0 to Close",0,1);
    int input=takeIntegerInput({0});
    loop();
  }
  else
  {
    lcdCharDisplay(4,0,"Warning!!!",1,1);
    lcdCharDisplay(3,1,"Motor Speed Can't",0,1);
    lcdCharDisplay(4,2,"Greater than 100",0,1);
    lcdCharDisplay(4,3,"Type 0 to Close",0,1);
    int input=takeIntegerInput({0});
    loop();
  }

  lcd.clear();
  while(availablePerc>lowerLevel)
  {
    processingMessage(2,"Selline Releasing..");
    turnOnMotor(patientM);
    mesaureWaterPerc();
  }
  turnOffAllMotor();
  lcdCharDisplay(2,0,"Selline Released",1,1);
  lcdCharDisplay(2,1,"Type 0 to close",0,1);
  int input=takeIntegerInput({0});
  loop();
   
}

void processingMessage(int col,char text[])
{
  lcdCharDisplay(col,0,text,0,1);
  lcdCharDisplay(0,1,"Type C to Terminate",0,1);
  char key = keypad.getKey();
  if (key){
    if(key==C)
    {
      turnOffAllMotor();
      loop();
    }
  }
}

int getPatientMotorSpeed()
{
  int digit1=EEPROM[PatienMotorSpeed[0]];
  int digit2=EEPROM[PatienMotorSpeed[1]];
  int digit3=EEPROM[PatienMotorSpeed[2]];
  int final_value=digit1*100+digit2*10+digit3;
  if(final_value>100)
  {
    return 0;
  }
  return final_value;
}
int clean()
{
  mesaureWaterPerc();
  int waste_removed=0;
  warn:
  if(availablePerc>lowerLevel)
  {
    lcdCharDisplay(1,0,"Clean At Any Cost?",1,1);
    lcdCharDisplay(2,1,"1. Yes",0,1);
      lcdCharDisplay(2,2,"0. No",0,1);
      inputAgain:
      char key1 = keypad.getKey();
      if (key1){
        if(searchInArray(nonIntegerKeys,6,key1))
        {
          warnInvalidInput();
          goto warn;
        }
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
        goto inputAgain;
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
    lcdCharDisplay(4,0,"Cleaned",1,1);
    lcdCharDisplay(2,1,"Type 0 to close",0,1);
    int input=takeIntegerInput({0});
  }

  finish:
  return 1;
}


int removeWaste() 
{
  mesaureWaterPerc();
  lcd.clear();
  while(availablePerc>lowerLevel)
  {
    processingMessage(2,"Waste Removing..");
    turnOnMotor(wasteM);
    mesaureWaterPerc();
  }
  turnOffAllMotor();
  lcdCharDisplay(2,0,"Waste Removed",1,1);
  delay(1500);
  return 1;
}

void cleanNow()
{
  mesaureWaterPerc();
  lcd.clear();
  while(availablePerc<20)
  {
    processingMessage(3,"Loading Water");
    turnOnMotor(waterM);
    mesaureWaterPerc();
  }

  lcd.clear();
  while(availablePerc>lowerLevel)
  {
    processingMessage(3,"Loading Water");
    turnOnMotor(wasteM);
    mesaureWaterPerc();
  }
  turnOffAllMotor();
  
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
