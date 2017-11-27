// front, back, pwm
int m1[] = {6, 7, 8}; // motor left {front, back , pwm}
int m2[] = {9,10 , 11};
/* A0 up
   A1 left
   A2 right
*/
int sensors[] = {A0, A1, A2, A3};
int vel_m1 = 100 ; // motor left pwn signal
int vel_m2 = 100 ;
bool flag = false;

//
const short stopdst = 900; // To be measured
const short wall = 200; // To be measured
short error = 0;
short diff = 0;
short lasterror = 0;
short kp = 2;
short kd = 1;
short pwmright = 255;
short pwmleft = 255;
//

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

  // pid code
  error = values[1] - values[2];
  diff = error - lasterror;
  lasterror = error;
  error *= kp;
  error += diff * kd;
  //increase left reduce right
  pwmleft += lasterror;
  pwmright -= lasterror;
  if (pwmleft > 255) pwmleft = 255;
  else if (pwmleft < 0) pwmleft = 0;
  if (pwmright > 255) pwmright = 255;
  else if (pwmright < 0) pwmright = 0;

  //
  // serial values
  for( int i  =0 ; i < 3 ; i ++){
    Serial.print(values[i]);
    Serial.print(" ");
    }
    Serial.println();


   if(values[1] > 1000 ){
      digitalWrite(m1[0],1);
      digitalWrite(m2[0],1);
      analogWrite(m1[2], pwmleft); // speed
      analogWrite(m2[2], pwmright);
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


  }

void motor_speed(){
  for ( int i = 0 ; i < 3 ; i++){
      analogWrite(m1[i], 0);
      analogWrite(m2[i], 0);
    }
  }
