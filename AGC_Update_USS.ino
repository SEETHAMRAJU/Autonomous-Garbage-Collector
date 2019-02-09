#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int spd = 120;

///////////////////////

int TrigPin1 =40;
int EchoPin1 =41;

int TrigPin2 =42;
int EchoPin2 =43;

int TrigPin3 =44;
int EchoPin3 =45;

int TrigPin4 =46;
int EchoPin4 =47;


///////////////////////

int step_delay;
int base_stepper_pul;
int base_stepper_ena;
int base_stepper_dir;
int arm_stepper_pul;
int arm_stepper_ena;
int arm_stepper_dir;

///////////////////////

long USS_1_D;
long USS_2_D;
long USS_3_D;
long USS_4_D;

long USS_1_T;
long USS_2_T;
long USS_3_T;
long USS_4_T;

///////////////////////
void setup(){
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  motor3.setSpeed(spd);
  motor4.setSpeed(spd);

  pinMode(base_stepper_pul,OUTPUT);
  pinMode(base_stepper_ena,OUTPUT);
  pinMode(base_stepper_dir,OUTPUT);
  pinMode(arm_stepper_pul,OUTPUT);
  pinMode(arm_stepper_ena,OUTPUT);
  pinMode(arm_stepper_dir,OUTPUT);

  pinMode(TrigPin1,OUTPUT);
  pinMode(EchoPin1,INPUT);
  pinMode(TrigPin2,OUTPUT);
  pinMode(EchoPin2,INPUT);
  pinMode(TrigPin3,OUTPUT);
  pinMode(EchoPin3,INPUT);
  pinMode(TrigPin4,OUTPUT);
  pinMode(EchoPin4,INPUT);

  Serial.begin(9600);
}

void loop(){

}
void base_stepper_move(int steps, int dir){
  base_stepper_dir = dir;
  for(int i = 0; i < steps; i++)
  {
    digitalWrite(base_stepper_pul,HIGH);
    delayMicroseconds(step_delay);
    digitalWrite(base_stepper_pul,LOW);
    delayMicroseconds(step_delay);
  }
}
void arm_stepper_move(int steps, int dir){
  arm_stepper_dir = dir;
  for(int i = 0; i < steps; i++)
  {
    digitalWrite(arm_stepper_pul,HIGH);
    delayMicroseconds(step_delay);
    digitalWrite(arm_stepper_pul,LOW);
    delayMicroseconds(step_delay);
  }
}
void base_stepper_stop(){
  digitalWrite(base_stepper_pul,HIGH);
}
void arm_stepper_stop(){
  digitalWrite(arm_stepper_pul,HIGH);
}
void moveFront(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void moveBack(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void moveRight(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}
void moveLeft(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void turnRight()
{
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWORD);
  motor4.run(FORWARD);   
}

void turnLeft()
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);    
}

void NextMove()
{
  digitalWrite(TrigPin1,LOW);
  delayMicroseconds(2);

  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);

  USS_1_T = pulseIn(EchoPin1, HIGH);
  USS_1_D = (USS_1_T)*0.034/2;


  digitalWrite(TrigPin2,LOW);
  delayMicroseconds(2);

  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);

  USS_2_T = pulseIn(EchoPin2, HIGH);
  USS_2_D = (USS_2_T)*0.034/2;

  digitalWrite(TrigPin3,LOW);
  delayMicroseconds(2);

  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);

  USS_3_T = pulseIn(EchoPin3, HIGH);
  USS_3_D = (USS_3_T)*0.034/2;

  digitalWrite(TrigPin4,LOW);
  delayMicroseconds(2);

  digitalWrite(TrigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin4, LOW);

  USS_4_T = pulseIn(EchoPin4, HIGH);
  USS_4_D = (USS_4_T)*0.034/2;

  if(USS_4_D > 80)
  {
    moveFront();
  }

  else if(USS_3_D > 45 && USS_1_D > 45)
  {
    if(USS_3_D > USS_1_D)
    {
      turnLeft();
    }

    else
    {
      turnRight();
    }
    
  }

  else if(USS_3_D > 45 && USS_1_D <45)
  {
    turnLeft();
  }

  else if(USS_3_D < 45 && USS_1_D >45)
  {
    turnRight();
  }

  else
  {
    moveBack();
  }
  
  
}



}
 
 
 
