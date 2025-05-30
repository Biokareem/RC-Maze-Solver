#define ir_centerR 7
#define ir_centerL 8
#define ir_left 6
#define ir_right 11

int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int en1 = 9;
int en2 = 10;

void forward();
void turn_left();
void turn_right();
void stop();
void reverse();

void setup() {
  pinMode(ir_centerR, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(ir_centerL, INPUT);
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);
}

int irRvalue_center;
int irLvalue_center;
int irRvalue;
int irLvalue;

void getReadings() {
  irRvalue_center = digitalRead(ir_centerR);
  irLvalue_center = digitalRead(ir_centerL);
  irRvalue = digitalRead(ir_right);
  irLvalue = digitalRead(ir_left);
}

void loop() {
  // put your main code here, to run repeatedly:
  getReadings();
  int flagL = 0;
  int flagR = 0;

  if ((irRvalue_center == 1 && irLvalue_center == 1) && (irRvalue == 0 && irLvalue == 0)) {
    forward();
  }

  else if ((irRvalue_center == 0 && irLvalue_center == 1) && (irRvalue == 0 && irLvalue == 0)) {
    analogWrite(en1, 150);
    analogWrite(en2, 60);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (irRvalue_center == 1 && irLvalue_center == 0) {
    analogWrite(en1, 60);
    analogWrite(en2, 150);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  else if ((irRvalue == 0 && irLvalue == 1)) {
    flagL = 1;
    delay(20);
    turn_left();
    while (true) {
      getReadings();
      if ((irRvalue_center == 1 && irLvalue_center == 1))
        break;
    }
  } else if ((irRvalue == 1 && irLvalue == 0)) {
    flagR = 1;
    delay(20);
    turn_right();
    while(true){
      getReadings();
      if((irRvalue_center == 1 && irLvalue_center == 1)){
        break;
      }
    }
  } else if ((irRvalue_center == 0 && irLvalue_center == 0) && (irRvalue == 0 && irLvalue == 0)) {
    while(irRvalue == 0){
      reverse();
      getReadings();
      if(irRvalue_center == 1 || irLvalue_center == 1){
        break;
      }
    }
  }

  else if (irRvalue == 1 && irLvalue == 1) {
    if (flagL == 1) {
      flagL = 0;
      delay(20);
      turn_left();
      while(true){
        getReadings();
        if((irRvalue_center == 1 && irLvalue_center == 1)){
        break;
        }
      }
    } else if (flagR == 1) {
      flagR = 0;
      delay(20);
      turn_right();
      while(true){
        getReadings();
        if((irRvalue_center == 1 && irLvalue_center == 1)){
        break;
        }
      }
    }
  }

/*else {
  stop(); }
 
}*/}
void stop() {
  analogWrite(en1, 160);
  analogWrite(en2, 60);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void turn_left() {
  analogWrite(en1, 100);
  analogWrite(en2, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  // delay(1000);
}

void turn_right() {
  analogWrite(en1, 0);
  analogWrite(en2, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // delay(1000);
}

void reverse(){
  analogWrite(en1, 150);
  analogWrite(en2, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
