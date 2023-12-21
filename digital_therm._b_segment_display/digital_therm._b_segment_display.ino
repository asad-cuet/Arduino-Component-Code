
int digit[10][7] = {   {1,1,1,1,1,1,0},  //0
              {0,1,1,0,0,0,0},  //1
              {1,1,0,1,1,0,1},  //2
              {1,1,1,1,0,0,1},  //3
              {0,1,1,0,0,1,1},  //4
              {1,0,1,1,0,1,1},  //5
              {1,0,1,1,1,1,1},  //6
              {1,1,1,0,0,0,0},  //7
              {1,1,1,1,1,1,1}, //8
              {1,1,1,1,0,1,1}  //9
};


int x,y,z,cel;
float temp;

void setup () {
    for(x=0;x<=11;x++) {
      pinMode(x,OUTPUT);
    }
    }

    void loop() {
         temp = analogRead(A0);
         cel = 0.48828*temp;
      for(z=0;z<=10;z++) {
         digitalWrite(10, LOW);
         for(y=0;y<=6;y++) {
                digitalWrite(y+1,digit[cel/10][y]);
         }
         delay(20);
         digitalWrite(10, HIGH);
         digitalWrite(11, LOW);
         for(y=0;y<=6;y++) {
          digitalWrite(y+1,digit[cel%10][y]);\
         }
         delay(20);
         digitalWrite(11, HIGH);
      }
    }
