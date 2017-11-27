const byte senfront = A0;
const byte senright = A1;
const byte senleft = A2;
const byte mleft1 = 0;
const byte mleft2 = 1;
const byte mleftpwm = 3;
const byte mright1 = 2;
const byte mright2 = 4;
const byte mrightpwm = 5;

const short stopdst = 900; // To be measured
const short wall = 200; // To be measured
short error = 0;
short diff = 0;
short last_error = 0;
short kp = 2;
short kd = 1;
short pwmright = 255;
short pwmleft = 255;

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  pinMode(mleft1, OUTPUT);
  pinMode(mleft2, OUTPUT);
  pinMode(mleftpwm, OUTPUT);
  pinMode(mright1, OUTPUT);
  pinMode(mright2, OUTPUT);
  pinMode(mrightpwm, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*
  Serial.print(analogRead(A0));
  Serial.print("\n");
  delay(100);
  */
}

void pid() {
  //if (senright > wall && senleft > wall) {
    // use two sensors
    error = analogRead(senleft) - analogRead(senright);
    diff = error - lasterror; 
    last_error = error;
    error *= kp;
    error += diff * kd;
    //increase left reduce right
    pwmleft += last_error;
    pwmright -= last_error;
    if (pwmleft > 255) pwmleft = 255;
    else if (pwmleft < 0) pwmleft = 0;
    if (pwmright > 255) pwmright = 255;
    else if (pwmright < 0) pwmright = 0;
       
  // }
  /*else if (senright < wall){
    // use the left sensor
  }
  else if (senleft < wall){
    // use the right sensor
  }
  else{
    //use the last_error
  }*/
}

