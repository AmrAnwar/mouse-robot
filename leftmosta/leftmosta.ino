byte pulses;
byte turns = 0;
bool fwd = true;
bool leftmost = true;

short readings[3];

#define STOPDST 800 // To be measured
#define WALL 700    // To be measured

void setup() {
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  pinMode(9,INPUT_PULLUP);
  
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  pinMode(12,HIGH);
  digitalWrite(12,HIGH);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {      
  readings[0] = analogRead(A0);
  readings[1] = analogRead(A1); // right sensor
  readings[2] = analogRead(A2); // left sensor
  if (leftmost) {
    if (readings[2] > WALL) {
      turn('l');
      if (turns < -3) leftmost = false;
      advance(7);
    }
    else if (readings[1] > WALL) {
      turn('r');
      if (turns > 3) leftmost = true;
      advance(7); 
    }
    else if (readings[0] < STOPDST) {
      test_backward();
      fwd = false;
    }
    else {
      test_forward();
      fwd = true;
    }
  }
  else {
    if (readings[1] > WALL) {
      turn('r');
      if (turns > 3) leftmost = true;
      advance(7); 
    }
    else if (readings[2] > WALL) {
      turn('l');
      if (turns < -3) leftmost = false;
      advance(7);
    }
    else if (readings[0] < STOPDST) {
      test_backward();
      fwd = false;
    }
    else {
      test_forward();
      fwd = true;
    }
  }
}

void test_forward() {
  digitalWrite(2,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  if(readings[2]<780)
    forward_right();
  else if(readings[1]<780)   
    forward_left();
  else
    forward();
}
  
  

void turn(char dir) {
  //delay(100);
  //mstop();
  //delay(300);
  if (readings[0] < STOPDST) advance(1);
  digitalWrite(2,LOW);
  digitalWrite(4,HIGH);
  if (dir == 'r') {
    // Serial.print("left,left");
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    turns++;
  }
  else {
    // Serial.print("left,left");
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    turns --; 
  }
    analogWrite(3,80);
    analogWrite(5,0); // We can attach the interrupt here
  while(pulses<5){
    Serial.println(pulses);
    if(digitalRead(9)){ 
      pulses++;  
      Serial.println(pulses);
    }
  }
  analogWrite(3,0);
  pulses=0;
  
}

void forward_left(){
  analogWrite(3,0);
  analogWrite(5,80);
  Serial.print("left");     
}

void forward_right(){
  Serial.print("right");
  analogWrite(3,80);
  analogWrite(5,0);
}
void forward(){
    analogWrite(3,100);
    analogWrite(5,100);      
}

void test_backward(){
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  while ((readings[1] = analogRead(A1)) < WALL && (readings[2] = analogRead(A2)) < WALL) {
    if(readings[2]<500) // left sensor
      backward_right();
    else if(readings[1]<400)  // right sensor
      backward_left();
    else
      backward(); 
  }
}

void backward_right(){
  Serial.print("right");
  analogWrite(3,0);
  analogWrite(5,80);
}

void backward_left(){
  analogWrite(3,80);
  analogWrite(5,0);
  Serial.print("left");     
}

void backward(){
  analogWrite(3,100);
  analogWrite(5,100);
}

void advance(byte advpulses) {
  if (fwd) {
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
  }
  else {
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
  }
  analogWrite(3,100);
  analogWrite(5,100);
  while (pulses < advpulses) {
    pulses++;
  }
  pulses = 0;
  analogWrite(3,0);
  analogWrite(5,0);
}

