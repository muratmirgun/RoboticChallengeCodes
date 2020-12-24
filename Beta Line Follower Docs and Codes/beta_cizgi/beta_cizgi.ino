#include <QTRSensors.h>
#define led_buzzer 13
#define buton 7 // baslatma butonunun bağlı olduğu pin numarasını tanımlıyoruz
#define iralici 2 // ir alicinin bağlanacağı pin
#define dip1 4 // mod anahtarı 1 - mod anahtarlarının bağlı olduğu pin numarasını tanımlıyoruz
#define dip2 5 // mod anahtarı 2 - mod anahtarlarının bağlı olduğu pin numarasını tanımlıyoruz
#define dip3 6  // mod anahtarı 3 - mod anahtarlarının bağlı olduğu pin numarasını tanımlıyoruz
#define solmotor1 3 // sol motor hız1 -  sol motoru kontrol etmek için gerekli pinler
#define solmotor2 11  // sol motor hız2 - bu iki pinden birine analogwrite ile çıkış yaparsanız motor o yönde döner . 2 pin aynı anda 0 yada 1 olursa motor durur.
#define sagmotor1 9  // sag motor hız1 -  sag motoru kontrol etmek için gerekli pinler
#define sagmotor2 10 // sag motor hız2 - bu iki pinden birine analogwrite ile çıkış yaparsanız motor o yönde döner . 2 pin aynı anda 0 yada 1 olursa motor durur.
int basla = 0; // robotun durma-çalışma kontrolünü sağlayan bayrak
int i = 0;
QTRSensorsAnalog qtra((unsigned char[]) {A0, A1 , A2, A3}, 4, 4); // cizgi sensorleri bu pinlere bağlanacak
unsigned int sensorValues[4]; // kac adet cizgi sensorumuz olduğunu belirtiyoruz

int tabanhiz = 180; // robot cizgiyi tam ortaladığı zaman ki hız. (en fazla 255)
int maxhiz = 255; // donuslerde vb, motorlara uygulanacak en fazla hız.
float Kp = 0.17;
float Kd = 3;
int sonhata = 0;
int hata = 0;
int sagmotorpwm = 0;
int solmotorpwm = 0;
int zemin = 1; // siyah pist üstüne beyaz çizgi için 1 olmalıdır. Beyaz pist üzerine siyah çizgi için 0 yapın.


void setup() {
  pinMode(buton, INPUT_PULLUP);
  pinMode(iralici, INPUT_PULLUP);
  pinMode(dip1, INPUT_PULLUP);
  pinMode(dip2, INPUT_PULLUP);
  pinMode(dip3, INPUT_PULLUP);
  pinMode(led_buzzer, OUTPUT);
  pinMode(solmotor1, OUTPUT);
  pinMode(solmotor2, OUTPUT);
  pinMode(sagmotor1, OUTPUT);
  pinMode(sagmotor2, OUTPUT);
  tone(led_buzzer, 500, 100);
  delay(50);
  noTone(led_buzzer);

  for (i = 0; i < 80; i++)
  {
    if (0 <= i && i < 5)  motorkontrol(-150, 150);
    if (5 <= i && i  < 15) motorkontrol(150, -150);
    if (15 <= i && i < 25)  motorkontrol(-150, 150);
    if (25 <= i && i < 35)  motorkontrol(150, -150);
    if (35 <= i && i < 45)  motorkontrol(-150, 150);
    if (45 <= i && i  < 55) motorkontrol(150, -150);
    if (55 <= i && i < 65)  motorkontrol(-150, 150);
    if (65 <= i && i < 70)  motorkontrol(150, -150);
    if ( i >= 70  )  {
      motorkontrol(0, 0);
      delay(5);
    }
    qtra.calibrate();
    delay(3);
  }

  motorkontrol(0, 0);
  tone(led_buzzer, 3000, 100);
  delay(50);
  noTone(led_buzzer);
}


void loop() {

  if (digitalRead(buton) == 0) {
    for (int a = 0; a < 5; a++) {
      tone(led_buzzer, 500, 100); delay(500); noTone(led_buzzer); delay(400); basla = 1;
    }
  }

  if (basla == 1) { // basla değişkeni 1 ise yani robotun calısması gerekiyorsa , ana program buraya yazılacak.
    hata = ( qtra.readLine(sensorValues, 1, zemin) - 1500);
    int duzeltmehizi = Kp * hata + Kd * (hata - sonhata);
    sonhata = hata;
    solmotorpwm = tabanhiz + duzeltmehizi  ;
    sagmotorpwm = tabanhiz - duzeltmehizi  ;
    solmotorpwm = constrain(solmotorpwm, -255, maxhiz); ///// Burada motorlara uygulanacak PWM değerlerine sınırlandırma getirilmiştir.
    sagmotorpwm = constrain(sagmotorpwm, -255, maxhiz);
    motorkontrol(sagmotorpwm, solmotorpwm);
  }
}


void motorkontrol(int sagmotorpwm, int solmotorpwm) {
  if (sagmotorpwm <= 0) {
    sagmotorpwm = abs(sagmotorpwm);
    analogWrite(sagmotor1, 0);
    analogWrite(sagmotor2, sagmotorpwm);
  }
  else {
    analogWrite(sagmotor1, sagmotorpwm);
    analogWrite(sagmotor2, 0);
  }

  if (solmotorpwm <= 0) {
    solmotorpwm = abs(solmotorpwm);
    analogWrite(solmotor1, solmotorpwm);
    analogWrite(solmotor2, 0);
  }
  else {
    analogWrite(solmotor1, 0);
    analogWrite(solmotor2, solmotorpwm);
  }

}
