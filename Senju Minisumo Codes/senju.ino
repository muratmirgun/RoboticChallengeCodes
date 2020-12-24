#define solpwm1 3
#define solpwm2 11
#define sagpwm1 9
#define sagpwm2 10

#define solqtr A5
#define sagqtr A4
#define solsensor A3
#define sagsensor A2


#define led_buzzer 13
#define button 6
#define pot A6
#define ir 2

#define DS1 12
#define DS2 8
#define DS3 7

int qtr = 700;
int Speed = 20;
int irr=0;
int MaxSpeed = 102; // Rskip önümüzdeyken maksimum hız.
int LastValue = 5; // Last Value Variable for remembering last Opponent sensor sense.

void setup()
{

  pinMode(solpwm1, OUTPUT);
  pinMode(solpwm2, OUTPUT);
  pinMode(sagpwm1, OUTPUT);
  pinMode(sagpwm2, OUTPUT);

  pinMode(solsensor, INPUT);
  pinMode(sagsensor, INPUT);
  pinMode(solqtr, INPUT_PULLUP);
  pinMode(sagqtr, INPUT_PULLUP);
  
  pinMode(led_buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(pot, INPUT_PULLUP);
  pinMode(ir, INPUT);

  pinMode(DS1, INPUT_PULLUP);
  pinMode(DS2, INPUT_PULLUP);
  pinMode(DS3, INPUT_PULLUP);


  digitalWrite(led_buzzer, LOW);
  digitalWrite(solpwm1, LOW);
  digitalWrite(solpwm2, LOW);
  digitalWrite(sagpwm1, LOW);
  digitalWrite(sagpwm2, LOW);

//Serial.begin(9600);
  tone(led_buzzer, 200, 350);
  delay(300);
  noTone(led_buzzer);

  tone(led_buzzer, 300, 200);
  tone(led_buzzer, 4000, 500);
  noTone(led_buzzer);

}


void loop() {

 

Wait:
qtr=analogRead(pot);

if (analogRead(solqtr) < qtr || analogRead(sagqtr) < qtr) {
   tone(led_buzzer, 300, 10);
}else if (digitalRead(solsensor) == LOW || digitalRead(sagsensor) == LOW) {
    digitalWrite(led_buzzer, HIGH);
  } else {
    noTone(led_buzzer);
    digitalWrite(led_buzzer, LOW);
  }


   if (digitalRead(ir)==1) {
    irr=1;

    /*for (int i = 0; i < 6; i++) {
      Set_Motor(0, 0, 1);
      tone(led_buzzer, 523, 200);
      delay(200);
      noTone(led_buzzer);
      delay(600);
    }*/

    if (digitalRead(DS1) == 0 && digitalRead(DS2) == 1 && digitalRead(DS3) == 1) {
      //Serial.print("sola dön");
      Set_Motor(-100, 100, 120);
      Set_Motor(80, 80, 20);
      LastValue = 7 ;
    }

    else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 1) {
     // Serial.print("sola açı");
      Set_Motor(80, 80, 170);
      LastValue = 7;
    }

    else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 1 && digitalRead(DS3) == 0) {
     // Serial.print("Sag");
      Set_Motor(100, -100, 120);
      Set_Motor(80, 80, 20);
      LastValue = 3;
    }
    else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0) {
      //Serial.print("saga açı");
      Set_Motor(80, 80, 170);

      LastValue = 3;
    } 
   

    noTone(led_buzzer);
    goto Start;
  }


  if (digitalRead(button) == 0) {

    for (int i = 0; i < 6; i++) {
      Set_Motor(0, 0, 1);
      tone(led_buzzer, 523, 200);
      delay(200);
      noTone(led_buzzer);
      delay(600);
    }

    if (digitalRead(DS1) == 0 && digitalRead(DS2) == 1 && digitalRead(DS3) == 1) {
      //Serial.print("sola dön");
      Set_Motor(-100, 100, 120);
      Set_Motor(80, 80, 20);
      LastValue = 7 ;
    }

    else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 1) {
     // Serial.print("sola açı");
      Set_Motor(80, 80, 170);
      LastValue = 7;
    }

    else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 1 && digitalRead(DS3) == 0) {
     // Serial.print("Sag");
      Set_Motor(100, -100, 120);
      Set_Motor(80, 80, 20);
      LastValue = 3;
    }
    else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0) {
      //Serial.print("saga açı");
      Set_Motor(80, 80, 170);

      LastValue = 3;
    } 
   

    noTone(led_buzzer);
    goto Start;
  }

goto Wait;


Start:

 if (digitalRead(ir)==0 && irr==1) {
  Set_Motor(0, 0, 1);
  irr=0;
  goto Wait;
  
 }

if (analogRead(solqtr)>900 && analogRead(sagqtr)>900 ){


  if (digitalRead(solsensor) == LOW && digitalRead(sagsensor) == LOW  ) {
    Set_Motor(MaxSpeed, MaxSpeed, 1);
    digitalWrite(led_buzzer, HIGH);
    //LastValue = 5;
  }else

  if (digitalRead(solsensor) == LOW && digitalRead(sagsensor) == HIGH  ) {
    Set_Motor(MaxSpeed, MaxSpeed, 1);
    //Set_Motor(-20, 50, 1);
    digitalWrite(led_buzzer, HIGH);
    LastValue = 7;
  }else

  if (digitalRead(solsensor) == HIGH && digitalRead(sagsensor) == LOW  ) {
     Set_Motor(MaxSpeed, MaxSpeed, 1);
    //Set_Motor(50, -20, 1);
    digitalWrite(led_buzzer, HIGH);
    LastValue = 3;
  }else

  if (digitalRead(solsensor) == HIGH && digitalRead(sagsensor) == HIGH ) {

    digitalWrite(led_buzzer, LOW);

    if (LastValue == 7) {
    Set_Motor(-70, 70, 2);
    } else  // Left Turning Based on SPD (A7) Trimpot
     
    if (LastValue == 3) {
    Set_Motor(70, -70, 2); // Right Turning Based on SPD (A7) Trimpot
    }
    
  }

}else

if (analogRead(solqtr)<qtr && analogRead(sagqtr)>900 ){
  Set_Motor(-102, -102, 150);
  Set_Motor(102, -102, 100);
  //LastValue=3;
   digitalWrite(led_buzzer, LOW);
}else

if (analogRead(solqtr)>900 && analogRead(sagqtr)<qtr ){
  Set_Motor(-102, -102, 150);
  Set_Motor(-102, 102, 100);
 // LastValue=7; 
   digitalWrite(led_buzzer, LOW);
}else

if (analogRead(solqtr)<qtr && analogRead(sagqtr)<qtr ){
if (LastValue==3){
    Set_Motor(-102, -102, 150);
  Set_Motor(102, -102, 100);
  //LastValue=3;
   digitalWrite(led_buzzer, LOW);
}else

if (LastValue==7){
    Set_Motor(-102, -102, 150);
  Set_Motor(-102, 102, 100);
  //LastValue=7;
   digitalWrite(led_buzzer, LOW);
}

  
}

  
  goto Start;
}



void Set_Motor (float Lval, float Rval, int timex) {
  Lval = Lval * 2.5;
  Rval = Rval * 2.5;

  if (Lval >= 0) {
    analogWrite(solpwm1, LOW);
    digitalWrite(solpwm2, Lval);
  } else {
    Lval= abs(Lval);
    digitalWrite(solpwm1, Lval);
    analogWrite(solpwm2, LOW);
  }

  if (Rval >= 0) {
    analogWrite(sagpwm1, Rval);
    digitalWrite(sagpwm2, LOW);
  } else {
    Rval= abs(Rval);
    digitalWrite(sagpwm1, LOW);
    analogWrite(sagpwm2, Rval);
  }
  delay(timex);
}

