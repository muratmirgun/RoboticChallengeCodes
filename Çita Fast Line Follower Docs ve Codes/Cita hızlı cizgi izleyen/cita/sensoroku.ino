void sensoroku(){  
   //**********çizgi sensörü pozisyon hesap kodları
  unsigned int sensors[8]; 
  unsigned int position = qtra.readLine(sensors,1,zemin); 
  hata= position-3500;
  }
  void flashyap(){
      digitalWrite(LED1, LOW);digitalWrite(LED2, LOW);digitalWrite(Buzzer, LOW); delay(250);
      digitalWrite(LED1, HIGH);digitalWrite(LED2, HIGH);digitalWrite(Buzzer, HIGH); delay(250);
      digitalWrite(LED1, LOW);digitalWrite(LED2, LOW);digitalWrite(Buzzer, LOW); delay(250);
      digitalWrite(LED1, HIGH);digitalWrite(LED2, HIGH);digitalWrite(Buzzer, HIGH); delay(250);
      digitalWrite(LED1, LOW);digitalWrite(LED2, LOW);digitalWrite(Buzzer, LOW); delay(250);
      digitalWrite(LED1, HIGH);digitalWrite(LED2, HIGH);digitalWrite(Buzzer, HIGH); delay(250);
      digitalWrite(LED1, LOW);digitalWrite(LED2, LOW);digitalWrite(Buzzer, LOW); delay(250);
      digitalWrite(LED1, HIGH);digitalWrite(LED2, HIGH);digitalWrite(Buzzer, HIGH); delay(250);
      digitalWrite(LED1, LOW);digitalWrite(LED2, LOW);digitalWrite(Buzzer, LOW); delay(250); 
          
  }
