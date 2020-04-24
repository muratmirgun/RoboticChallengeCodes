void motorkontrol(int solmotorpwm, int sagmotorpwm){
  
   
  if(sagmotorpwm<0) {

      sagmotorpwm=sagmotorpwm*(-1);
      digitalWrite(sagmotor1, LOW);
     analogWrite(sagmotor2, sagmotorpwm);
     
    }
    
  else {

   
    
      analogWrite(sagmotor1, sagmotorpwm);
      digitalWrite(sagmotor2, LOW);
      
  }

  
  
  if(solmotorpwm<0) {

     
    
     solmotorpwm=solmotorpwm*(-1);
     analogWrite(solmotor1, solmotorpwm);
     digitalWrite(solmotor2, LOW);
    
    }
   else {

   
    
    digitalWrite(solmotor1, LOW);
    analogWrite(solmotor2, solmotorpwm);

   }
}


void frenle(){motorkontrol(0,0);}
void hafifsagadon(){motorkontrol(35,-35);}
void hafifsoladon(){motorkontrol(-35,35);}


