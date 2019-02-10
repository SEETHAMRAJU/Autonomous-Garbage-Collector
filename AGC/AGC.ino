// brk -> GND
// dir -> 5v = reverse
// vcc brk pwm dir gnd

// base motors
int motors[] = {8, 9, 10, 11}; //pwm pins
int dir[] = {40, 41, 42, 43};

//steppers
int step_delay = 200;
int base_stepper_pul = 33;
int base_stepper_ena = 31;
int base_stepper_dir = 32;
int arm_stepper_pul = 36;
int arm_stepper_ena = 34;
int arm_stepper_dir = 35;

int USS_front;
int USS_back;
int USS_left;
int USS_right;


void setup() {
  // put your setup code here, to run once:
  pinMode(base_stepper_pul,OUTPUT);
  pinMode(base_stepper_ena,OUTPUT);
  pinMode(base_stepper_dir,OUTPUT);
  pinMode(arm_stepper_pul,OUTPUT);
  pinMode(arm_stepper_ena,OUTPUT);
  pinMode(arm_stepper_dir,OUTPUT);

  digitalWrite(arm_stepper_ena, HIGH);
  digitalWrite(base_stepper_ena, HIGH);
  Serial.begin(9600);
  
  for(int i = 0; i < 4; i++){
    pinMode(motors[i], OUTPUT);
    pinMode(dir[i], OUTPUT);
  }
  delay(2000);
}


void loop() {
  // put your main code here, to run repeatedly:
  int spd = 130;
  moveFront(spd);
  /*
  delay(400);
  moveBack(spd);
  delay(400);
  moveRight(spd);
  delay(400);
  moveLeft(spd);
  delay(4000);
  */
}



void stop(){
  analogWrite(motors[0], 0);
  analogWrite(motors[1], 0);
  analogWrite(motors[2], 0);
  analogWrite(motors[3], 0);
  delay(80);
}

void moveFront(int s){
  digitalWrite(dir[0], LOW);
  digitalWrite(dir[1], LOW);
  digitalWrite(dir[2], LOW);
  digitalWrite(dir[3], LOW);

  analogWrite(motors[0], s);
  analogWrite(motors[1], s);
  analogWrite(motors[2], s);
  analogWrite(motors[3], s);
  delay(50);
  stop();
}

void moveBack(int s){
  digitalWrite(dir[0], HIGH);
  digitalWrite(dir[1], HIGH);
  digitalWrite(dir[2], HIGH);
  digitalWrite(dir[3], HIGH);

  analogWrite(motors[0], s);
  analogWrite(motors[1], s);
  analogWrite(motors[2], s);
  analogWrite(motors[3], s);
  delay(50);
  stop();
}

void moveLeft(int s){
  digitalWrite(dir[0], HIGH);
  digitalWrite(dir[1], LOW);
  digitalWrite(dir[2], LOW);
  digitalWrite(dir[3], HIGH);

  analogWrite(motors[0], s);
  analogWrite(motors[1], s);
  analogWrite(motors[2], s);
  analogWrite(motors[3], s);
  delay(50);
  stop();
}

void moveRight(int s){
  digitalWrite(dir[0], LOW); //bakward
  digitalWrite(dir[1], HIGH);
  digitalWrite(dir[2], HIGH);
  digitalWrite(dir[3], LOW);

  analogWrite(motors[0], s);
  analogWrite(motors[1], s);
  analogWrite(motors[2], s);
  analogWrite(motors[3], s);
  delay(50);
  stop();
}

void turnRight(){
  digitalWrite(dir[0], LOW); //bakward
  digitalWrite(dir[1], HIGH);
  digitalWrite(dir[2], LOW);
  digitalWrite(dir[3], HIGH);

  analogWrite(motors[0], s);
  analogWrite(motors[1], s);
  analogWrite(motors[2], s);
  analogWrite(motors[3], s);
  delay(50);
  stop();
}

void turnLeft(){
  digitalWrite(dir[0], HIGH); //bakward
  digitalWrite(dir[1], LOW);
  digitalWrite(dir[2], HIGH);
  digitalWrite(dir[3], LOW);

  analogWrite(motors[0], s);
  analogWrite(motors[1], s);
  analogWrite(motors[2], s);
  analogWrite(motors[3], s);
  delay(50);
  stop();  
}

void base_stepper_move(int steps, int dir){
  digitalWrite(base_stepper_dir,dir);
  for(int i = 0; i < steps; i++)
  {
    digitalWrite(base_stepper_pul,HIGH);
    delayMicroseconds(step_delay);
    digitalWrite(base_stepper_pul,LOW);
    delayMicroseconds(step_delay);
  }
}
void arm_stepper_move(int steps, int dir){
  digitalWrite(arm_stepper_dir,dir);
  for(int i = 0; i < steps; i++)
  {
    Serial.println(i);
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
