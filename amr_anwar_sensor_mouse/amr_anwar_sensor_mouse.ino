// front, back, pwm
int m1[] = {6, 7, 8};
int m2[] = {9,10 , 11};
int sensors[] = {A0, A1, A2, A3};
int vel_m1 = 100 ;
int vel_m2 = 100 ;
bool flag = false;
void setup() {
  // put your setup code here, to run once:
  for ( int i = 0 ; i < 2 ; i++){
    pinMode(m1[i],OUTPUT);
    pinMode(m2[1],OUTPUT);
    }
  for (int i =0 ; i < 3 ; i++ ){
    pinMode(sensors[i], INPUT);
    }
}

void loop() {
  /* i = 0 up 
     i = 1 left 
     i = 2 right 
  */
  int values[] = {0, 0, 0 ,0};
  motor_move(values);
  
  for (int i =0 ; i < 3 ;i ++ ){
    values[i] = analogRead(sensors[i]);
    motor_move(values);     
  }
  
}

void motor_move(int values[]){
  /* i = 0 up 
     i = 1 left 
     i = 2 right 
  */
  
   if(values[1] > 1000 ){
      digitalWrite(m1[0],1);
      digitalWrite(m2[0],1);
      analogWrite(m1[2], vel_m1); // speed
      analogWrite(m2[2], vel_m2);
    }
   else if((values[0] > 1000)){
          motor_speed();
          digitalWrite(m1[0],1);
          analogWrite(m1[2], vel_m1);
          digitalWrite(m2[1],0);
          delay(2000);
    }
   else if (values[2] > 1000){
      motor_speed();
      digitalWrite(m1[1],1);
      analogWrite(m1[2], vel_m1);
      digitalWrite(m2[0],0);
      delay(2000);
    }
    
   else {
    motor_speed();
    digitalWrite(m1[1],1);
    digitalWrite(m2[1],1);
    analogWrite(m1[2], vel_m1); // speed
    analogWrite(m2[2], vel_m2);
   }
//   else if(left){
//    
//    }
     
  }

void motor_speed(){
  for ( int i = 0 ; i < 3 ; i++){
      analogWrite(m1[i], 0);
      analogWrite(m2[i], 0);
    }
  }
  
