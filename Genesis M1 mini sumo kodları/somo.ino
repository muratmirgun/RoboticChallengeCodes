int RPwm = 11;
int RDir = 13;
int LPwm = 3;
int LDir = 12;
int Rc = A0;
int Lc = A1;
int LSens = A2;
int RSens = A4;
int MSens = A3;
int baslat = 10;
int mod1 = 5;
int mod2 = 6;
int mod3 = 7;
int siren = 9;


void setup() { 
  pinMode(siren,OUTPUT); 
Serial.begin(9600);
tone (siren,1000,300);
delay(300);
tone (siren,900,300);
delay(300);
tone (siren,800,300);
delay(300);
tone (siren,700,300);
delay(300);
tone (siren,600,300);
delay(300);
tone (siren,700,300);
delay(300);
tone (siren,800,300);
delay(300);
tone (siren,900,300);
delay(300);
tone (siren,1000,300);
delay(300);
noTone(siren);
pinMode(RPwm, OUTPUT);  // Four PWM Channel Declared as Output
pinMode(RDir, OUTPUT); 
pinMode(LPwm, OUTPUT); 
pinMode(LDir, OUTPUT); 
pinMode(baslat,INPUT);
while(1){
if (digitalRead(baslat)== HIGH){
  continue;
  tone(siren , 523, 300);
  delay(300);
  noTone(9);
}
else if (digitalRead(baslat)== LOW){
  if(digitalRead(mod1)== 1 && digitalRead(mod1)== 1 && digitalRead(mod1)== 0) { 
    digitalWrite(RPwm,HIGH);
    digitalWrite(RDir,LOW);
    digitalWrite(LPwm,HIGH);
    digitalWrite(LDir,HIGH);
    delay(400);  
}
else if(digitalRead(mod1)== 0 && digitalRead(mod1)== 0 && digitalRead(mod1)== 1) {
  digitalWrite(RPwm,HIGH);
    digitalWrite(RDir,HIGH);
    digitalWrite(LPwm,HIGH);
    digitalWrite(LDir,LOW);
    delay(400);
  
}
else if(digitalRead(mod1)== 0 && digitalRead(mod1)== 0 && digitalRead(mod1)== 0) {
  while(1){
    if(digitalRead(MSens) == LOW){
    digitalWrite(siren,HIGH);
  }
 else if(digitalRead(LSens) == LOW){
   digitalWrite(siren,HIGH);
  }
 else if(digitalRead(RSens) == LOW){
 digitalWrite(siren,HIGH);
 }
else{
  digitalWrite(siren,LOW);
 }}  
break;
}}}}
void loop() {
  if(digitalRead(MSens) == LOW){
    digitalWrite(RPwm,HIGH);
    digitalWrite(RDir,HIGH);
    digitalWrite(LPwm,HIGH);
    digitalWrite(LDir,HIGH);
    delay(100);
  }
 else if(digitalRead(LSens) == LOW){
  while(digitalRead(MSens) == HIGH){
    digitalWrite(RPwm,HIGH);
    digitalWrite(RDir,HIGH);
    digitalWrite(LPwm,HIGH);
    digitalWrite(LDir,LOW);
  }}
 else if(digitalRead(RSens) == LOW){
 while(digitalRead(MSens) == HIGH){
    digitalWrite(RPwm,HIGH);
    digitalWrite(RDir,LOW);
    digitalWrite(LPwm,HIGH);
    digitalWrite(LDir,HIGH);
 }}
else{
  while(digitalRead(MSens) == HIGH || digitalRead(LSens) == HIGH || digitalRead(RSens) == HIGH ){
    analogWrite(RPwm,100);
    digitalWrite(RDir,LOW);
    analogWrite(LPwm,100);
    digitalWrite(LDir,HIGH);
 }}}
