//motor 1
int velocidadeA = 6;
int IN1 = 48;
int IN2 = 49;


//motor 2
int velocidadeB = 7;
int IN3 = 46;
int IN4 = 47;

//motor 3
int velocidadeC = 8;
int IN5 = 9;
int IN6 = 10;

//motor 4
int velocidadeD = 13;
int IN7 = 11;
int IN8 = 12;

int vel = 60;

//Inicializa Pinos
void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(velocidadeA, OUTPUT);
  pinMode(velocidadeB, OUTPUT);
  pinMode(velocidadeC, OUTPUT);
  pinMode(velocidadeD, OUTPUT);
}

void motor1(int velocity, int rotation1, int rotation2) { //motor1(100,1,0)
  digitalWrite(IN1, rotation1);
  digitalWrite(IN2, rotation2);
  analogWrite(velocidadeA, velocity);
}

void motor2(int velocity, int rotation1, int rotation2) {
  digitalWrite(IN3, rotation1);
  digitalWrite(IN4, rotation2);
  analogWrite(velocidadeB, velocity);
}

void motor3(int velocity, int rotation1, int rotation2) {
  digitalWrite(IN5, rotation1);
  digitalWrite(IN6, rotation2);
  analogWrite(velocidadeC, velocity);
}

void motor4(int velocity, int rotation1, int rotation2) {
  digitalWrite(IN7, rotation1);
  digitalWrite(IN8, rotation2);
  analogWrite(velocidadeD, velocity);
}

void frente() {
  motor1(vel, HIGH, LOW);
  motor2(vel, HIGH, LOW);
  motor3(vel, HIGH, LOW);
  motor4(vel, HIGH, LOW);
}

void direita() {
  motor1(vel, HIGH, LOW);
  motor2(vel, LOW, HIGH);
  motor3(vel, HIGH, LOW);
  motor4(vel, LOW, HIGH);
}

void esquerda() {
  motor1(vel, LOW, HIGH);
  motor2(vel, HIGH, LOW);
  motor3(vel, LOW, HIGH);
  motor4(vel, HIGH, LOW);
}

void parar() {
  motor1(vel, HIGH, HIGH);
  motor2(vel, HIGH, HIGH);
  motor3(vel, HIGH, HIGH);
  motor4(vel, HIGH, HIGH);
}

void loop() {
    // frente();
    // delay(5000);

    // direita();
    // delay(2000);

    // esquerda();
    // delay(200);

    // parar();
    // delay(200);
  }

