#define SENFRONT A0
#define SENLEFT A1
#define SENRIGHT A2
#define SENBACK A3
#define MLEFTF 2
#define MLEFTB 4
#define PWMLEFT 3
#define MRIGHTF 6
#define MRIGHTB 7
#define PWMRIGHT 5

#define STOPDST 900 // To be measured
#define WALL 200    // To be measured
#define MID 400     // To be measured
#define TPERIOD 500 // To be measured
#define FPERIOD 500 // To be measured
#define BPERIOD 300 // To be measured
#define KP 1        // To be calibrated
#define KI 1        // To be calibrated

short error = 0;
short sum = 0;
short pwmright = 255;
short pwmleft = 255;
short readings[3];

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  pinMode(MLEFTF, OUTPUT);
  pinMode(MLEFTB, OUTPUT);
  pinMode(PWMLEFT, OUTPUT);
  pinMode(MRIGHTF, OUTPUT);
  pinMode(MRIGHTB, OUTPUT);
  pinMode(PWMRIGHT, OUTPUT);

  // Power pins
}

void loop() {
  // put your main code here, to run repeatedly:
  readings[0] = analogRead(SENFRONT);
  readings[1] = analogRead(SENLEFT);
  readings[2] = analogRead(SENRIGHT);
  if (readings[1] < WALL) tleft();
  else if (readings[2] < WALL) tright();
  else if (readings[0] > STOPDST) backward();
  else forward();
}

void calc_error() {
  if (readings[2] > WALL && readings[1] > WALL) error = readings[1] - readings[2]; // use two sensors
  else if (readings[2] < WALL) error = readings[1] - MID; // use the left sensor
  else if (readings[1] < WALL) error = MID - readings[2]; // use the right sensor
  sum += error;
  error *= KP;
  error += sum * KI;
}

void check_pwm() {
  if (pwmleft > 255) pwmleft = 255;
  else if (pwmleft < 0) pwmleft = 0;
  if (pwmright > 255) pwmright = 255;
  else if (pwmright < 0) pwmright = 0;
}

void forward() {
  calc_error();
  // increase left reduce right
  pwmleft += error;
  pwmright -= error;
  check_pwm();
  analogWrite(PWMRIGHT, pwmright);
  analogWrite(PWMLEFT, pwmleft);
}

void backward() {
  digitalWrite(MRIGHTF, LOW);
  digitalWrite(MRIGHTB, HIGH);
  digitalWrite(MLEFTF, LOW);
  digitalWrite(MLEFTB, HIGH);
  while (readings[2] > WALL && readings[1] > WALL) {
    calc_error();
    // reduce left increase right
    pwmleft -= error;
    pwmright += error;
    check_pwm();
    analogWrite(PWMRIGHT, pwmright);
    analogWrite(PWMLEFT, pwmleft);
    readings[1] = analogRead(SENLEFT);
    readings[2] = analogRead(SENRIGHT);
  }
  delay(BPERIOD);
}

void tleft(){
  analogWrite(PWMRIGHT, 255);
  analogWrite(PWMLEFT, 255);
  digitalWrite(MRIGHTF, HIGH);
  digitalWrite(MRIGHTB, LOW);
  digitalWrite(MLEFTF, LOW);
  digitalWrite(MLEFTB, HIGH);
  delay(TPERIOD);
  digitalWrite(MLEFTF, HIGH);
  digitalWrite(MLEFTB, LOW);
  delay(FPERIOD);
}

void tright() {
  analogWrite(PWMRIGHT, 255);
  analogWrite(PWMLEFT, 255);
  digitalWrite(MLEFTF, HIGH);
  digitalWrite(MLEFTB, LOW);
  digitalWrite(MRIGHTF, LOW);
  digitalWrite(MRIGHTB, HIGH);
  delay(TPERIOD);
  digitalWrite(MRIGHTF, HIGH);
  digitalWrite(MRIGHTB, LOW);
  delay(FPERIOD);
}
