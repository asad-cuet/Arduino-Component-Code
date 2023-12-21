int mAp = 0;
int mBp = 1;
int mApinA = 11;
int mApinB = 10;
int mBpinA = 9;
int mBpinB = 8;

void setup() {
   pinMode(mAp,OUTPUT);
   pinMode(mBp,OUTPUT);
   pinMode(mApinA,OUTPUT);
   pinMode(mApinB,OUTPUT);
   pinMode(mBpinA,OUTPUT);
   pinMode(mBpinB,OUTPUT);
   pinMode(A5, INPUT);
   pinMode(A4, INPUT);
}

void loop() {
  digitalWrite(mAp,HIGH);
  digitalWrite(mBp,HIGH);
       
  if(A5 == HIGH) {
    digitalWrite(mApinA,HIGH);
    digitalWrite(mApinB,LOW);
    digitalWrite(mBpinA,LOW);
    digitalWrite(mBpinB,HIGH);
    
  }
  if(A4 == HIGH) {
    digitalWrite(mApinA,LOW);
    digitalWrite(mApinB,HIGH);
    digitalWrite(mBpinA,HIGH);
    digitalWrite(mBpinB,LOW);    
    
  }
}
