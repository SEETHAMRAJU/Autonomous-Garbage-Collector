#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int spd = 120;

///////////////////////

int step_delay;
int base_stepper_pul;
int base_stepper_ena;
int base_stepper_dir;
int arm_stepper_pul;
int arm_stepper_ena;
int arm_stepper_dir;

///////////////////////

int USS_front;
int USS_back;
int USS_left;
int USS_right;

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
