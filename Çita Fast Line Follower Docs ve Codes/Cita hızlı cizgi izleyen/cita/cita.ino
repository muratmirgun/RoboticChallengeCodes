#include <QTRSensors.h>

#define sagmotor1 9
#define sagmotor2 10 
#define solmotor1 3
#define solmotor2 11
#define MZ80 5

#define IRALICI 12
#define startbuton 2

#define LED1 4
#define LED2 8

#define Buzzer 13


QTRSensorsAnalog qtra((unsigned char[]) { A0, A1, A2, A3, A4 , A5, A6, A7} , 8);
unsigned int sensors[8];

int tabanhiz=255; // buradaki ayar robotun sıfır hata ile giderken gittiği hızı gösterir. Pistteki virajlar arttıkça 80 e kadar düşürülebilir. En yüksek verilebilecek değer 255 tir. 
int maxhiz=255;
int sonhata = 0;
float Kp = 0.16;
float Kd = 1.6;
float Ki = 0.001;

int ekhiz = 0;
int sagmotorpwm = 0;
int solmotorpwm = 0;
int integral = 0;
int hata = 0;
int zemin=1;
int sonmotor1yon=0;
int sonmotor2yon=0;
char veri;

void setup()
{
  pinMode(sagmotor1, OUTPUT);
  pinMode(sagmotor2, OUTPUT);
  pinMode(solmotor1, OUTPUT);
  pinMode(solmotor2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
   pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
  pinMode(MZ80, INPUT_PULLUP);
  pinMode(startbuton, INPUT_PULLUP);

  delay(1000);
  //**** kalibrasyon kodları kalibrasyon arduino üzerindeki led yanık oldugu sürece devam eder robotun çizgi sensörünü tam ortalayarak  yerleştirilmelidir
  
  int i;
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  for (int i = 0; i < 150; i++)
  {
//    if ( 0 <= i && i < 5   )  hafifsagadon();
//    if ( 5 <= i && i  < 15   )  hafifsoladon();
//    if ( 15 <= i && i < 25   )  hafifsagadon();
//    if ( 25 <= i && i < 35   )  hafifsoladon();
//    if ( 35 <= i && i < 40   )  hafifsagadon();
//    if ( 45 <= i && i < 55   )  hafifsoladon();
//    if ( 55 <= i && i < 65   )  hafifsagadon();
//    if ( 65 <= i && i < 75   )  hafifsoladon();
//    if ( 75 <= i && i < 80   )  hafifsagadon();


    if ( i >= 80  )  {
      frenle();
      delay(3);
    }
   
    qtra.calibrate();
    delay(1);
  }
   flashyap();
   digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
//  if (digitalRead(startbuton)==HIGH) { do frenle();  while(digitalRead(startbuton)==HIGH);}  // başlangıç işlemini buton kontrollü yapmak için aktifleştirmek gerekir
  if (digitalRead(MZ80)==LOW) { do frenle();  while(digitalRead(MZ80)==LOW);}  // başlangıçta engel varsa durup bekler. MZ80 sensörü vb takılı olmalıdır
Serial.begin(9600);
}
void loop(){ 

 if (Serial.available() > 0)     // Send data only when you receive data:
  {
   motorkontrol(0, 0);
  veri=Serial.read();
    if (veri == 'P') Kp=Serial.parseFloat();
    if (veri == 'D') Kd=Serial.parseFloat();
   if (veri == 'M') maxhiz=Serial.parseInt();
   if (veri == 'T') tabanhiz=Serial.parseInt();

  }

  
  //********Burada çizginin pozisyon hesabı zemine bağlı oalrak otomatik yapılmaktadır
  unsigned int sensors[8]; 
  unsigned int position = qtra.readLine(sensors,1,zemin); 
  hata= position-3500;

  
  integral+=hata;   //çizgiden uzaklaştıkça hataları toplar
 
   //////////// motorlara verilecek hız düzeltme oran hesabı
   int duzeltmehizi = Kp * hata + Kd*(hata - sonhata) + Ki*integral;
  sonhata = hata;


  if (digitalRead(MZ80)==LOW) { do {frenle(); delay(1);}  while(digitalRead(MZ80)==LOW);} // yarış içinde engel engel varsa durup bekler. MZ80 sensörü vb takılı olmalıdır


//  if (sensors[0]<100 && sensors[7]<100 ) { zemin=0;  }//beyaz zemin siyah çizgiyi tespit eder
//  if (sensors[0]>750 && sensors[7]>750 ) { zemin=1;  }//siyah zemin beyaz çizgiyi tespit eder
  
  //************* Motorlara uygulanacak kesin hız ayarları****
   sagmotorpwm = tabanhiz + duzeltmehizi + ekhiz  ;
   solmotorpwm = tabanhiz - duzeltmehizi + ekhiz ;  
   //********************
  
   
   /// motorlara hız ayarlarının uygulanması********
   sagmotorpwm = constrain(sagmotorpwm, -255, maxhiz); // Burada motorlara uygulanacak PWM değerlerine sınırlandırma getirilmiştir.
   solmotorpwm = constrain(solmotorpwm, -255, maxhiz);
   motorkontrol(solmotorpwm,sagmotorpwm);
   //**************

}


