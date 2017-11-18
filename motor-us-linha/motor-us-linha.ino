#include <NewPing.h>

NewPing sonar(23, 22);

#define BUZZER 24
#define sensorPE A15
#define sensorE A14
#define sensorC A13
#define sensorD A12
#define sensorPD A11

int referencia = 200;
int sinalDireita = 0;
int sinalCentro = 0;
int sinalEsquerda = 0;
int sinalPEsquerda = 0;
int sinalPDireita = 0;

// MOTORES ÍMPARES = ESQUERDA; PARES = DIREITA
//motor 1
int velocidadeA = 7; //motor frente esquerda
int IN1 = 35 ;
int IN2 = 36 ;

//motor 2
int velocidadeB = 6;
int IN3 = 37 ;
int IN4 = 38 ;

//motor 3
int velocidadeC = 8;
int IN5 = 9 ;
int IN6 = 10 ;

//motor 4
int velocidadeD = 13;
int IN7 = 11 ;
int IN8 = 12 ;

//variavel auxiliar
int velocidade = 0;
int vel = 75;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
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
  motor1(vel*0.3+vel, HIGH, LOW);
  motor2(vel, LOW, HIGH);
  motor3(vel*0.3+vel, HIGH, LOW);
  motor4(vel, LOW, HIGH);
}

void direitaf() {
  motor1(vel, HIGH, LOW);
  motor2(0.75*vel, LOW, HIGH);
  motor3(vel, HIGH, LOW);
  motor4(0.75*vel, LOW, HIGH);
}

void esquerda() {
  motor1(vel, LOW, HIGH);
  motor2(vel*0.3+vel, HIGH, LOW);
  motor3(vel, LOW, HIGH);
  motor4(vel*0.3+vel, HIGH, LOW);
}

void esquerdaf() {
  motor1(vel*0.75, LOW, HIGH);
  motor2(vel, HIGH, LOW);
  motor3(vel*0.75, LOW, HIGH);
  motor4(vel, HIGH, LOW);
}

void parar() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
}

void loop() {
  float cm = sonar.ping_cm();  
  sinalEsquerda = analogRead(sensorE);
  sinalCentro = analogRead(sensorC);
  sinalDireita = analogRead(sensorD);
  sinalPEsquerda = analogRead(sensorPE);
  sinalPDireita = analogRead(sensorPD);
  Serial.print("Distancia: ");
  Serial.println(cm);
  Serial.print("Nivel Ponta Esquerda: ");
  Serial.println(sinalPEsquerda);
  Serial.print("Nivel Esquerda: ");
  Serial.println(sinalEsquerda);
  Serial.print("Nivel Centro: ");
  Serial.println(sinalCentro);
  Serial.print("Nivel Direita: ");
  Serial.println(sinalDireita);
  Serial.print("Nivel Ponta Direita: ");
  Serial.println(sinalPDireita);
  Serial.println("");
    
    if (cm < 15) {
      parar();  
    } else {
      if (sinalCentro < referencia ) {
        frente();
      } else if (sinalDireita < referencia && sinalCentro < referencia && sinalEsquerda < referencia) {
        frente();
      } else if (sinalDireita < referencia && sinalCentro < referencia && sinalEsquerda > referencia) {
        direitaf();
      } else if (sinalDireita > referencia && sinalCentro < referencia && sinalEsquerda < referencia) {
        esquerdaf();
      } else if (sinalDireita < referencia && sinalCentro > referencia) {
        direita();
      } else if (sinalEsquerda < referencia && sinalCentro > referencia) {
        esquerda();
      } else if (sinalPEsquerda < referencia && sinalEsquerda < referencia){
        esquerda();
      } else if (sinalPEsquerda < referencia) {
        esquerda();
      } else if (sinalPDireita < referencia && sinalDireita < referencia){
        direita();
      } else if (sinalPDireita < referencia) {
        direita();        
      } else {
        parar();
      }   
    }
}  
