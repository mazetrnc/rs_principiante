const int pinPWMA = 6;
const int pinAIN2 = 7;
const int pinAIN1 = 8;
const int pinBIN1 = 9;
const int pinBIN2 = 10;
const int pinPWMB = 11;
const int pinSTBY = 12;
const int rir_pin = A0;
const int mir_pin = A1;
const int lir_pin = A2;

const int waitTime = 2000;  //espera entre fases
const int speed = 150;      //velocidad de giro

const int pinMotorA[3] = { pinPWMA, pinAIN2, pinAIN1 };
const int pinMotorB[3] = { pinPWMB, pinBIN1, pinBIN2 };

enum moveDirection {
  forward,
  backward
};

enum turnDirection {
  clockwise,
  counterClockwise
};

void setup() {
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
  pinMode(lir_pin, INPUT);
  pinMode(rir_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int est_lir = digitalRead(lir_pin);
  int est_rir = digitalRead(rir_pin);
  int est_mir = digitalRead(mir_pin);
  Serial.print("izquierdo: ");
  Serial.print(est_lir);
  Serial.print("  ----  medio: ");
  Serial.print(est_mir);
  Serial.print("  ----  derecho: ");
  Serial.println(est_rir);

  if(est_mir == 1){
    if(est_lir == 0 && est_rir == 0){
      move(forward, speed);
    }
    else if(est_lir == 1 && est_rir == 0){
      turn(counterClockwise, speed);
    }
    else if(est_lir == 0 && est_rir == 1){
      turn(clockwise, speed);
    }
    else if(est_lir == 1 && est_rir == 1){
      fullStop();
    }
  }
  else{
    if(est_lir == 1 && est_rir == 0){
      turn(counterClockwise, speed);
    }
    else if(est_lir == 0 && est_rir == 1){
      turn(clockwise, speed);
    }  
    else if(est_lir == 0 && est_rir == 0){
      turn(clockwise, speed);
    }  
  }
  delay(100);
}

//Funciones que controlan el vehiculo
void move(int direction, int speed) {
  if (direction == forward) {
    moveMotorForward(pinMotorA, speed);
    moveMotorForward(pinMotorB, speed);
  } else {
    moveMotorBackward(pinMotorA, speed);
    moveMotorBackward(pinMotorB, speed);
  }
}

void turn(int direction, int speed) {
  if (direction == clockwise) {
    moveMotorForward(pinMotorA, speed);
    moveMotorBackward(pinMotorB, speed);
  } else {
    moveMotorBackward(pinMotorA, speed);
    moveMotorForward(pinMotorB, speed);
  }
}

void fullStop() {
  disableMotors();
  stopMotor(pinMotorA);
  stopMotor(pinMotorB);
}

//Funciones que controlan los motores
void moveMotorForward(const int pinMotor[3], int speed) {
  enableMotors();
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);

  analogWrite(pinMotor[0], speed);
}

void moveMotorBackward(const int pinMotor[3], int speed) {
  enableMotors();
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);

  analogWrite(pinMotor[0], speed);
}

void stopMotor(const int pinMotor[3]) {
  disableMotors();
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);

  analogWrite(pinMotor[0], 0);  
}

void enableMotors() {
  digitalWrite(pinSTBY, HIGH);
}

void disableMotors() {
  digitalWrite(pinSTBY, LOW);
}