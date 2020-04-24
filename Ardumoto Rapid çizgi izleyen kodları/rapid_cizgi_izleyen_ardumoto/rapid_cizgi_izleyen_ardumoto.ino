#include <QTRSensors.h>

#define sagtabanhiz 120
#define soltabanhiz 120
#define solmotoryon  13
#define solmotorpwmpin 11
#define sagmotoryon 12
#define sagmotorpwmpin 3


//QTRSensorsRC qtrrc((unsigned char[]) { A5, A4, A3, A2, A1 , A0, 7, 6} ,8, 2500, QTR_NO_EMITTER_PIN); // Motozade ise

QTRSensorsRC qtrrc((unsigned char[]) { 2, 4, 5, 6, 7 , 8, 9, 10} ,8, 2500, QTR_NO_EMITTER_PIN); // ardumoto ise

unsigned int sensorValues[8];

void setup()
{
      delay(500);
      pinMode(sagmotoryon, OUTPUT);
      pinMode(sagmotorpwmpin, OUTPUT);
      pinMode(solmotoryon, OUTPUT);
      pinMode(solmotorpwmpin, OUTPUT);
      int i;
      digitalWrite(13,HIGH);
       
     for (int i = 0; i < 200; i++)
     { 
         if ( 0 <= i && i < 5   )  hafifsagadon();       
         if ( 5 <= i && i  < 15   )  hafifsoladon(); 
         if ( 15 <= i && i < 25   )  hafifsagadon();       
         if ( 25 <= i && i < 35   )  hafifsoladon(); 
         if ( 35 <= i && i < 45   )  hafifsagadon();       
         if ( 45 <= i && i < 55  )  hafifsoladon(); 
         if ( 55 <= i && i < 65   )  hafifsagadon();       
         if ( 65 <= i && i < 75  )  hafifsoladon();
         if ( 75 <= i && i < 85   )  hafifsagadon();       
         if ( 85 <= i && i < 90  )  hafifsoladon();
  
         if ( i >= 90  )  {frenle(); delay(5);}
        
       qtrrc.calibrate(); 
       delay(4);
      } 
    digitalWrite(13,LOW);
    delay(2000);
} 

int sonhata = 0;
float Kp = 0.14;
float Kd = 2;

int sagmotorpwm = 0;
int solmotorpwm = 0;
int zemin=1;

void loop()
{ 

  
 

  // Pozisyon hesabı QTRlibrary tarafından yaptırılıyor
  unsigned int sensorValues[8];   
  unsigned int position = qtrrc.readLine(sensorValues,1,zemin); 
  int hata = position-3500;

  // zemin değiştirme kodları
  //if ( sensorValues[0]<200 && sensorValues[7]<200  ) { zemin=0;  }//beyaz
  //if ( sensorValues[0]>750 && sensorValues[7]>750  ) { zemin=1;  }//siyah
 

 
  //////////// motorlara verilecek hız düzeltme oran hesabı
  int duzeltmehizi = Kp * hata + Kd*(hata - sonhata);
  sonhata = hata;
    
   
  //////////// Motorlara uygulanacak kesin hız ayarları
   sagmotorpwm = sagtabanhiz + duzeltmehizi  ;
   solmotorpwm = soltabanhiz - duzeltmehizi  ;
  
   sagmotorpwm = constrain(sagmotorpwm, -250, 200); ///// Burada motorlara uygulanacak PWM değerlerine sınırlandırma getirilmiştir.
   solmotorpwm = constrain(solmotorpwm, -250, 200); 
   motorkontrol(sagmotorpwm,solmotorpwm);
  //   Seri monitörde hata, sağ ve sol motor hız değerlerini gösternek için alttaki satırı aktif yapınız
  //   Serial.print(hata);  Serial.print(" "); Serial.print(sagmotorpwm); Serial.print(" "); Serial.println(solmotorpwm); delay(100);  

}
// Motor kontrol alt programı
void motorkontrol(int sagmotorpwm, int solmotorpwm){

  if(sagmotorpwm<=0) {
      sagmotorpwm=abs(sagmotorpwm);
      digitalWrite(sagmotoryon, LOW);
      analogWrite(sagmotorpwmpin, sagmotorpwm);
    }
  else {
      digitalWrite(sagmotoryon, HIGH);
      analogWrite(sagmotorpwmpin, sagmotorpwm);
  }
  
  if(solmotorpwm<=0) {
     solmotorpwm=abs(solmotorpwm);
     digitalWrite(solmotoryon, HIGH);
     analogWrite(solmotorpwmpin, solmotorpwm);
    }
   else {
    digitalWrite(solmotoryon, LOW);
    analogWrite(solmotorpwmpin, solmotorpwm);
   }
}


void frenle(){motorkontrol(0,0);}

void hafifsagadon(){motorkontrol(50,-50);}

void hafifsoladon(){motorkontrol(-50,50);}


