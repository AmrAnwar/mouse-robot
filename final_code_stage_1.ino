// =========

#define x(p) p/8
#define y(p) p - ((p/8) * 8)

#define MAXPATH 20

void slv_maze(char, char);
char flt_path(void);

static char maze[64][5] = {

  {0, 0, 1, 1, 12}, {1, 0, 1, 0, 11}, {1, 0, 1, 0, 10}, {1, 0, 1, 1, 9 },
  {1, 0, 1, 0, 10}, {1, 0, 1, 0, 11}, {1, 0, 1, 0, 12}, {1, 0, 0, 0, 13},

  {0, 1, 0, 1, 13}, {0, 0, 1, 1, 10}, {1, 0, 0, 1, 9 }, {0, 1, 0, 1, 8 },
  {0, 0, 1, 1, 3 }, {1, 0, 1, 1, 2 }, {1, 0, 1, 0, 1 }, {1, 0, 1, 1, 0} ,

  {0, 1, 0, 1, 12}, {0, 1, 1, 0, 9 }, {1, 1, 1, 0, 8 }, {1, 1, 0, 1, 7 },
  {0, 1, 0, 0, 4 }, {0, 1, 1, 1, 3 }, {1, 0, 0, 0, 4 }, {0, 1, 0, 1, 1 },

  {0, 1, 1, 0, 11}, {1, 0, 0, 1, 10}, {0, 0, 1, 0, 7 }, {1, 1, 1, 0, 6 },
  {1, 0, 1, 0, 5 }, {1, 1, 0, 1, 4 }, {0, 0, 1, 1, 3 }, {1, 1, 0, 0, 2 },

  {0, 0, 0, 1, 12}, {0, 1, 1, 1, 9 }, {1, 0, 1, 0, 8 }, {1, 0, 1, 0, 7 },
  {1, 0, 1, 1, 6 }, {1, 1, 0, 0, 5 }, {0, 1, 1, 1, 4 }, {1, 0, 0, 1, 5 },

  {0, 1, 1, 1, 11}, {1, 1, 0, 1, 10}, {0, 0, 1, 1, 11}, {1, 0, 0, 1, 10},
  {0, 1, 0, 1, 7 }, {0, 0, 1, 0, 6 }, {1, 1, 0, 0, 5 }, {0, 1, 0, 1, 6 },

  {0, 1, 0, 1, 12}, {0, 1, 0, 1, 11}, {0, 1, 1, 0, 10}, {1, 1, 1, 0, 9 },
  {1, 1, 1, 1, 8 }, {1, 0, 1, 0, 9 }, {1, 0, 1, 0, 8 }, {1, 1, 0, 0, 7 },

  {0, 1, 0, 0, 13}, {0, 1, 1, 0, 12}, {1, 0, 1, 0, 13}, {1, 0, 0, 0, 14},
  {0, 1, 1, 0, 9 }, {1, 0, 1, 0, 10}, {1, 0, 1, 0, 11}, {1, 0, 0, 0, 12}

};

// ==========


int speed_left;
int speed_right;
int puls=0;
boolean flag=true;
boolean left_flag = true;
boolean flag_l = true;
boolean flag_m = true;
boolean flag_s = false; 
boolean flag_left_rotation = true ;
boolean flag_rotation = false; 


boolean puls_forwardd_flag = true; 
int puls_forwardd = 0 ;

int puls_move = 0 ;


//int maze [3][3][4] = {
//  { {"\0\1\1\1"}, {"\0\1\1\1"}, {"\0\1\1\1"}},
//  { {"\0\1\1\1"}, {"\0\1\1\1"}, {"\0\1\1\1"}},
//  { {"\0\1\1\1"}, {"\0\1\1\1"}, {"\0\1\1\1"}},
//};


int i =0 ;

int m1_forward = 4 ;
int m1_backward = 2 ;


int m2_forward = 6 ;
int m2_backward = 7 ;

int path[3][3]  = { {0, 0}, {0, 2} , {1, 2} };

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

char x;


void loop() {
  // =============

  char s, i;
  char *str;
  
  slv_maze(56, 15);
  s = flt_path();

  for (i = 0; i < s; ++i){
    Serial.print(sh_path[i][0]);
    Serial.print(" ");
    Serial.print(sh_path[i][1]);
    Serial.println("------------------------");
  }


  // ==========

  if( digitalRead(9) ){
    if (! flag_rotation ){
      
    if(flag_m){
        puls_move++;
//      Serial.println("MOVED");    
//      Serial.println(puls_move);
      flag_m=false;
      }
    }
  }
  else {flag_m=true;}      
        int *init ;
        int *next ;
        init = path[i]; 
        next = path[i+1];
        // edit 1/2 
        int del_x = init[0] - next[0];
        int del_y = init[1] - next[1];
        if (del_x < 0) del_x *= -1;
        if (del_y < 0) del_y *= -1;
        
        int stop_count = del_x + del_y;
        if ( (puls_move >= stop_count * 8)  && ( analogRead(A0) > 900  || analogRead(A1) > 900) ){
          i++;
//          Serial.println("i");
//          Serial.println(i);
          puls_move = 0 ;
          if ( i == 2 ){
            mstop();
            flag_s = true; 
            }
          return loop();
          flag_left_rotation = true; 
          }

        if (! flag_s ){
         if ( init[0] == next[0] && init[1] != next[1] ){
          
           if ( init[1] > next[1]){
                // don't know 
            }
           else{
            // forward up 
            test_forward();
            }
          }
          
         else if ( init[0] != next[0] && init[1] == next[1] ){

           if ( init[0] < next[0]){
            // left 
            // forward
            
            if ( flag_left_rotation ){
                           flag_left_rotation = false; 
                           forward_fuc();

              left(m1_forward, m2_backward);
              
              }

              else {
              test_forward();
              }
            }
            //////////////////
            
           else{
                // right_forward

                            // right
            // forward
            
            if ( flag_left_rotation ){
              flag_left_rotation = false; 
              forward_fuc();
              
              left(m2_forward, m1_backward );
              
              }

              else {
//              Serial.println("just forward ");
              test_forward();
//            left();
              }


              
            }
            
          } // with rotation 
//          
        }
        


}

//----------

//======

char stpcount;
char pathcount;


void slv_maze(char curr_pnt, char end_pnt)
{
  stpcount  = 1;
  pathcount = 0;

  path[pathcount][0]   = x(curr_pnt);
  path[pathcount++][1] = y(curr_pnt);

  while (curr_pnt != end_pnt) {
    char adj_pnts[4];
    char clst_dis, clst_pnt;
    char i, j;

    for (i = 0, j = 0; i < 4; ++i) {
      if (maze[curr_pnt][i] == 1) {
        switch (i) {
        case 0:
          *(adj_pnts + j++) = curr_pnt - 1;
          maze[curr_pnt-1][2] = -1;
          break;
        case 1:
          *(adj_pnts + j++) = curr_pnt - 8;
          maze[curr_pnt-8][3] = -1;
          break;
        case 2:
          *(adj_pnts + j++) = curr_pnt + 1;
          maze[curr_pnt+1][0] = -1;
          break;
        case 3:
          *(adj_pnts + j++) = curr_pnt + 8;
          maze[curr_pnt+8][1] = -1;
          break;
        }
      }
    }

    clst_dis = 20;
    for (i = 0; i < j; ++i) {
      if (maze[adj_pnts[i]][4] < clst_dis) {
        clst_dis = maze[adj_pnts[i]][4];
        clst_pnt = adj_pnts[i];
      }
    }
   
    curr_pnt = clst_pnt;
    path[pathcount][0]   = x(curr_pnt);
    path[pathcount++][1] = y(curr_pnt);
    ++stpcount;
  }
}

char flt_path()
{
  char i, j, k;
  char c, r;
  
  for (i = 0, j = 0; i < pathcount; ++j) {

    sh_path[j][0] = path[i][0];
    sh_path[j][1] = path[i][1];

    k = 0;
    c = path[i][0];
    r = path[i][1];
    
    ++i;

    while (path[i][0] == c && path[i + 1][0] == c)
      ++i, ++k;

    while (!k && path[i][1] == r && path[i + 1][1] == r)
      ++i;
  }
  return j;
}


//======










//////////////
void test_forward(){
    if(analogRead(A2)<500){forward_right();
       flag_rotation = true; 
    }
     
     else if(analogRead(A1)<400){
      
      flag_rotation = true; 
      forward_left();}
     
     else{
      flag_rotation = false ;
      forward();}
  }
  
void left(int x_forward , int y_backward)
{      // Serial.print("left,left");
  delay(100);
  mstop();
  delay(300);
  while(puls<3){
  
       Serial.println(puls);
        digitalWrite(2,LOW);
        digitalWrite(6,LOW);
        digitalWrite(y_backward ,HIGH); //y_backward 
        digitalWrite(x_forward ,HIGH); //x_forward

         analogWrite(5,120);   
        analogWrite(3,120);
     
        
  if( digitalRead(9)){
    if(flag_l){
      puls++;  
      Serial.println(puls);
      flag_l=false;
      }
  }
      else{
        flag_l=true;}
  }
        mstop();
        delay(500);
       while(analogRead(A0) < 600 ){
        forward_left();
        }
        puls=0;
        mstop();
      
  
  }

//void left()
//{      // Serial.print("left,left");
//  delay(100);
//  mstop();
//  delay(300);
//  while(puls<8){
//       Serial.println(puls);
//        digitalWrite(2,LOW);
//        digitalWrite(4,HIGH);
//        digitalWrite(6,HIGH);
//        digitalWrite(7,LOW);
//        analogWrite(3,100);
//        analogWrite(5,0);
//        
//  if( digitalRead(9)){
//    if(flag_l){
//      puls++;  
//      Serial.println(puls);
//      flag_l=false;
//      }
//  }
//      else{
//        flag_l=true;}
//  }
//        mstop();
//        delay(500);
//       while(analogRead(A0) < 600 ){
//        forward_left();
//        }
//        puls=0;
//        mstop();
//      
//  
//  }
  
void mstop(){     
  digitalWrite(2,LOW);
    digitalWrite(4,LOW);
      digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        }

void forward_left(){
  digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
      digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        analogWrite(3,0);
        analogWrite(5,80);
     Serial.print("left");
       
  }
  void forward_right(){
   Serial.print("right");
     digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
      digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        analogWrite(3,80);
        analogWrite(5,0);
       
     
    
    }
  void backward(){
  digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
      digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        analogWrite(3,70);
        analogWrite(5,70);
 

  }
  void forward(){
      if(analogRead(A0)>800){
  digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
      digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        analogWrite(3,100);
        analogWrite(5,100);

      
    }
    else if (analogRead(A1) > 780  ){
      flag_rotation = true; 

      forward_left();

      delay(500);

      }
          else if (analogRead(A2) > 780 ){
                              flag_rotation = true; 

      forward_right();

      delay(500);

      }
      else{
              mstop();

        }
    }


void forward_fuc()
{      // Serial.print("left,left");
  mstop();
  delay(1000);
  while(puls_forwardd<4){
  
        test_forward();
        
  if( digitalRead(9)){
    if(puls_forwardd_flag){
      puls_forwardd++;  
      Serial.println(puls);
      puls_forwardd_flag=false;
      }
  }
      else{
        puls_forwardd_flag=true;}
  }
  puls_forwardd = 0;
        mstop();
  
  }    