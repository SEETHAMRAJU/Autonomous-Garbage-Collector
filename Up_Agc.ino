#include<VarSpeedServo.h>
// brk -> GND
// dir -> 5v = reverse
// vcc brk pwm dir gnd

//Stepper motors spec
    //En High for both setups
    //stepper front dir 1
    //back dir 0

//Servo motor
VarSpeedServo servo;

// base motors
int motors[] = {8, 9, 10, 11}; //pwm pins
int dir[] = {40, 41, 42, 43};
int led1 = 6;
int led2 = 7;

//steppers
int arm_step_delay = 300;
int base_step_delay = 300;
int base_stepper_pul = 33;
int base_stepper_ena = 31;
int base_stepper_dir = 32;
int arm_stepper_pul = 36;
int arm_stepper_ena = 34;
int arm_stepper_dir = 35;

int frontUStrig = 3;
int frontUSecho = 4;

String incomingB = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(base_stepper_pul,OUTPUT);
  pinMode(base_stepper_ena,OUTPUT);
  pinMode(base_stepper_dir,OUTPUT);
  pinMode(arm_stepper_pul,OUTPUT);
  pinMode(arm_stepper_ena,OUTPUT);
  pinMode(arm_stepper_dir,OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(frontUStrig, OUTPUT);
  pinMode(frontUSecho, INPUT);

  digitalWrite(arm_stepper_ena, HIGH);
  digitalWrite(base_stepper_ena, HIGH);
  Serial.begin(9600);

  servo.attach(13);
  servo.write(0, 100);
  delay(500);
  for(int i = 0; i < 4; i++){
    pinMode(motors[i], OUTPUT);
    pinMode(dir[i], OUTPUT);
  }
  delay(3500);
}


void loop() {
  // put your main code here, to run repeatedly:
//  if(confirmation()) picK();
//  movE();
//  picK();
  if(Serial.available()>0)
  {
      incomingB = Serial.readString();
      if(incomingB.equals("y"))
      {
        delay(0);
       // picK();
      }

      else if(incomingB.equals("f"))
      {
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        moveFront(20); 
      }

      else if(incomingB.equals("b"))
      {
        digitalWrite(led1,HIGH);
        digitalWrite(led2,LOW);
        moveBack(20);
      }

      else if(incomingB.equals("l"))
      {
        digitalWrite(led1,LOW);
        digitalWrite(led2,HIGH);
        moveLeft(20);
      }

      else if(incomingB.equals("r"))
      {
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        moveRight(20);
      }
  }

  /*
  int spd = 130;
  moveFront(spd);
  delay(400);
  moveBack(spd);
  delay(400);
  moveRight(spd);
  delay(400);
  moveLeft(spd);
  delay(4000);
  */
}



void Vstop(){
  analogWrite(motors[0], 0);
  analogWrite(motors[1], 0);
  analogWrite(motors[2], 0);
  analogWrite(motors[3], 0);
  delay(90);
}

void moveFront(int steps){
    for(int i = 0; i < steps; i++){
  digitalWrite(dir[0], LOW);
  digitalWrite(dir[1], LOW);
  digitalWrite(dir[2], LOW);
  digitalWrite(dir[3], LOW);

  analogWrite(motors[0], 180);
  analogWrite(motors[1], 180);
  analogWrite(motors[2], 180);
  analogWrite(motors[3], 180);
  delay(10);
  Vstop();
    }
}

void moveBack(int steps){
    for(int i = 0; i < steps; i++){
  digitalWrite(dir[0], HIGH);
  digitalWrite(dir[1], HIGH);
  digitalWrite(dir[2], HIGH);
  digitalWrite(dir[3], HIGH);

  analogWrite(motors[0], 180);
  analogWrite(motors[1], 180);
  analogWrite(motors[2], 180);
  analogWrite(motors[3], 180);
  delay(10);
  Vstop();
    }
}

void moveLeft(int steps){
    for(int i = 0; i < steps; i++){
  digitalWrite(dir[0], HIGH);
  digitalWrite(dir[1], LOW);
  digitalWrite(dir[2], LOW);
  digitalWrite(dir[3], HIGH);

  analogWrite(motors[0], 180);
  analogWrite(motors[1], 180);
  analogWrite(motors[2], 180);
  analogWrite(motors[3], 180);
  delay(10);
  Vstop();
    }
}

void moveRight(int steps){
    for(int i = 0; i < steps; i++){
  digitalWrite(dir[0], LOW); //bakward
  digitalWrite(dir[1], HIGH);
  digitalWrite(dir[2], HIGH);
  digitalWrite(dir[3], LOW);

  analogWrite(motors[0], 180);
  analogWrite(motors[1], 180);
  analogWrite(motors[2], 180);
  analogWrite(motors[3], 180);
  delay(10);
  Vstop();
    }
}

void turnRight(int steps){
    for(int i = 0; i < steps; i++){
  digitalWrite(dir[0], LOW); //bakward
  digitalWrite(dir[1], HIGH);
  digitalWrite(dir[2], LOW);
  digitalWrite(dir[3], HIGH);

  analogWrite(motors[0], 180);
  analogWrite(motors[1], 180);
  analogWrite(motors[2], 180);
  analogWrite(motors[3], 180);
  delay(10);
  Vstop();
    }
}

void turnLeft(int steps){
    for(int i = 0; i < steps; i++){
  digitalWrite(dir[0], HIGH); //bakward
  digitalWrite(dir[1], LOW);
  digitalWrite(dir[2], HIGH);
  digitalWrite(dir[3], LOW);

  analogWrite(motors[0], 180);
  analogWrite(motors[1], 180);
  analogWrite(motors[2], 180);
  analogWrite(motors[3], 180);
  delay(10);
  Vstop();
    }
}

void base_stepper_move(int steps, int dir){
  digitalWrite(base_stepper_dir,dir);
  for(int i = 0; i < steps; i++)
  {
    digitalWrite(base_stepper_pul,HIGH);
    delayMicroseconds(base_step_delay);
    digitalWrite(base_stepper_pul,LOW);
    delayMicroseconds(base_step_delay);
  }
}
void arm_stepper_move(long int steps, int dir){
  digitalWrite(arm_stepper_dir,dir);
  for(long int i = 0; i < steps; i++)
  {
    //Serial.println(i);
    digitalWrite(arm_stepper_pul,HIGH);
    delayMicroseconds(arm_step_delay);
    digitalWrite(arm_stepper_pul,LOW);
    delayMicroseconds(arm_step_delay);
  }
}
void base_stepper_stop(){
  digitalWrite(base_stepper_pul,HIGH);
}
void arm_stepper_stop(){
  digitalWrite(arm_stepper_pul,HIGH);
}


int checkObject(){
    int t, dis;
  digitalWrite(frontUStrig, LOW);
  delayMicroseconds(2);
  digitalWrite(frontUStrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontUStrig, LOW);

  t = pulseIn(frontUSecho, HIGH);
  dis = t*0.034/2;

  return dis;
}

int confirmation(){
  int cnt;
  for(int i = 0; i < 10; i++){
    int dis = checkObject();
    Serial.println(dis);
    if(dis <= 22 && dis >= 16){
      cnt++;
    }
    delay(100);
  }
  if(cnt > 4) return 1;
  else return 0;
}


void picK()
{
  digitalWrite(led1, HIGH);
  servo.write(0, 80);
  delay(2000);
  arm_stepper_stop();
  base_stepper_stop();
  delay(500);
  base_stepper_move(10000,1);
  base_stepper_stop();

  arm_stepper_move(32000,0);  //36000
  arm_stepper_stop();

  servo.write(38, 20);
  delay(4000);

  base_stepper_move(10000,0);
  base_stepper_stop();
  
  arm_stepper_move(27000,1); //30000
  arm_stepper_stop();

  servo.write(0, 80);
  delay(2000);

  arm_stepper_move(5000,1);
  arm_stepper_stop();
  digitalWrite(led1, LOW);
  
}

void movE()
{
  int lol = checkObject();
  delay(500);
  Serial.println("#" + lol);
  if(lol>50)
  {
    moveFront(155);
//    delay(500);
//    Vstop();
  }

  else
  {
   Vstop();
   int i =0;
   while(i>=0)
   {
    if(!confirmation())
    {
      moveFront(150);
//      delayMicroseconds(500);
//      Vstop();
      i+=1;
    }

    else
    {
      i=-1;
      picK();
    }
  }
}
}
