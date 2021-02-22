// Biped-Manchot-1 - 22/02/2021
void(* resetFunc) (void) = 0;           // soft reset, not to modify
#include <Servo.h>
int Speed=12;                           // determines le speed of the robot
Servo Srv[4];                           // Servos table
int OnOff[4]={1,1,1,1};                 // when 1, servo is on. When 0, servo is off
int          RF=0, LF=1, RL=2, LL=3;    // RF=Right Foot, LF=Left Foot, RL=Right Leg, LL=Left Leg
int Err[4]={  -1,    6,    5,   -9};    // servo error for 90 ° position. You have to modify this according to your servos.

// 20/02/18 - sole 8x7 - speed=12 - symmetrical servos angles values movements 
int RFa[]= {  0, -5,-10,-15,-20,-21,-22,-23,-23,-23,-22,-21,-20,-15,-10, -5,      0,  5, 10, 15, 20, 21, 22, 23, 23, 23, 22, 21, 20, 15, 10,  5};
int LFa[]= {  0, -5,-10,-15,-20,-21,-22,-23,-23,-23,-22,-21,-20,-15,-10, -5,      0,  5, 10, 15, 20, 21, 22, 23, 23, 23, 22, 21, 20, 15, 10,  5};
int RLa[]= {-80,-70,-60,-50,-40,-30,-20,-10,  0, 10, 20, 30, 40, 50, 60, 70,     80, 70, 60, 50, 40, 30, 20, 10,  0,-10,-20,-30,-40,-50,-60,-70};
int LLa[]= {-80,-70,-60,-50,-40,-30,-20,-10,  0, 10, 20, 30, 40, 50, 60, 70,     80, 70, 60, 50, 40, 30, 20, 10,  0,-10,-20,-30,-40,-50,-60,-70};

int lgTab = (sizeof(RFa)/sizeof(int))-1;  // size of the angles movements tables

void  setup() {
  delay(800);                             // for reset consideration, not to modify
  Serial.begin(9600);
  pinMode(0,INPUT_PULLUP);                // start/stop/reset button attachment
  
  int a=90;                               // 90° Servos angle initialization
  if(OnOff[RF]){ Srv[RF].attach(4); Srv[RF].write(a+Err[RF]); } // Right Foot Servo attachment
  if(OnOff[LF]){ Srv[LF].attach(2); Srv[LF].write(a+Err[LF]); } // Left Foot Servo attachment
  if(OnOff[RL]){ Srv[RL].attach(5); Srv[RL].write(a+Err[RL]); } // Right Leg Servo attachment
  if(OnOff[LL]){ Srv[LL].attach(3); Srv[LL].write(a+Err[LL]); } // Left Leg Servo attachment
  Serial.print("\n\t To start, click on the Start button");
  while( digitalRead(0) );  delay(400);  Serial.print("\n\t Started");  // waiting for start button pressed 
}

void loop() {     // to be modify for testing your own walk
  if (! digitalRead(0)) resetFunc();    // soft reset, not to modify. Click on stop button to stop robot
  Walk('F');   // Forward uncomment for testing
  //Walk('B');   // Backward uncomment for testing
  //Walk('L');   // Turn Left uncomment for testing
  //Walk('R');   // Turn Right uncomment for testing
}

void Walk(char d){  // d=F=Forward, d=B=Backward, d=L=Turn Left, d=R=Turn Right, 
  int i, j, l, r, savSpeed=Speed;
  switch (d) {
    case 'F': i=0; j=lgTab; l=90;r=90;            break;
    case 'B': i=-lgTab; j=0; l=90;r=90;           break;
    case 'L': i=0; j=lgTab; l=0;r=90; Speed+=2;   break;
    case 'R': i=0; j=lgTab; l=90;r=0; Speed+=2;   break;
    default:                                      break;
  }
  for(i; i<=j; i++){        // this loop run the tables values of servos angles
    if(OnOff[RF]){ Srv[RF].write(RFa[abs(i)]+Err[RF]+90);}  delay(Speed);
    if(OnOff[LF]){ Srv[LF].write(LFa[abs(i)]+Err[LF]+90);}  delay(Speed);
    if(OnOff[RL]){ Srv[RL].write(RLa[abs(i)]+Err[RL]+ l);}  delay(Speed);
    if(OnOff[LL]){ Srv[LL].write(LLa[abs(i)]+Err[LL]+ r);}  delay(Speed);
  }
  Speed=savSpeed;
}
