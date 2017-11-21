int m1[2] = {6, 7};
int m2[] = {8,9};
int sensors[] = {A0, A1, A2, A3};

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
    values[i] = digitalRead(sensors[i]);
    motor_move(values);     
  }
  
}

void rotation(int right){
  if (right){
      digitalWrite(m1[0],1);
      digitalWrite(m2[1],0);
  }
  else {
      digitalWrite(m1[1],1);
      digitalWrite(m2[0],0);
    }
  delay(2000);
}
void motor_move(int values[]){
  /* i = 0 up 
     i = 1 left 
     i = 2 right 
  */
   if(values[0]){
      digitalWrite(m1[0],1);
      digitalWrite(m2[0],1);
    }
   else if((values[1])){
          motor_speed(0);
          digitalWrite(m1[0],1);
          digitalWrite(m2[1],0);
          delay(2000);
    }
   else if ((values[2])){
          motor_speed(0);
          digitalWrite(m1[1],1);
      digitalWrite(m2[0],0);
      delay(2000);
    }
    
   else {
      digitalWrite(m1[0],0);
      digitalWrite(m2[0],0);
   }
//   else if(left){
//    
//    }
     
  }

void motor_speed(int speed){
  for ( int i = 0 ; i < 2 ; i++){
      digitalWrite(m1[i], speed);
      digitalWrite(m2[i], speed);
    }
  }
  
