#include <NewPing.h>

#define NO_ECHO 5000
NewPing sonar(23, 22, 150);

#define BUZZER 24
#define sensorPE A15
#define sensorE A14
#define sensorC A13
#define sensorD A12
#define sensorPD A11

int referencia = 900;
int sinalDireita = 0;
int sinalCentro = 0;
int sinalEsquerda = 0;

//motor 1
int velocidadeA = 7;
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

void motor1(int velocity, int rotation1, int rotation2) {
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
  motor1(70, HIGH, LOW);
  motor2(70, HIGH, LOW);
  motor3(70, HIGH, LOW);
  motor4(70, HIGH, LOW);
}

void direitaF() {
  motor1(70, HIGH, LOW);
  motor2(50, HIGH, LOW);
  motor3(70, HIGH, LOW);
  motor4(50, HIGH, LOW);
}

void direitaB() {
  motor1(70, HIGH, LOW);
  motor2(70, LOW, HIGH);
  motor3(70, HIGH, LOW);
  motor4(70, LOW, HIGH);
}

void esquerdaB() {
  motor1(70, LOW, HIGH);
  motor2(70, HIGH, LOW);
  motor3(70, LOW, HIGH);
  motor4(70, HIGH, LOW);
}

void esquerdaF() {
  motor1(50, LOW, HIGH);
  motor2(70, HIGH, LOW);
  motor3(50, LOW, HIGH);
  motor4(40, HIGH, LOW);
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
  Serial.print("Distancia: ");
  Serial.println(cm);

  sinalEsquerda = analogRead(sensorE);
  sinalCentro = analogRead(sensorC);
  sinalDireita = analogRead(sensorD);

  Serial.print("Nivel Esquerdo : ");
  Serial.println(sinalEsquerda);
  Serial.print("Nível Centro: ");
  Serial.println(sinalCentro);
  Serial.print("Nivel Direito : ");
  Serial.println(sinalDireita);
  Serial.println("");
  Serial.println(NO_ECHO);
  Serial.println(cm);

  if (cm == NO_ECHO) {
    
    
    if (cm < 15) {
      Serial.println("PARAR");
      parar();
    } else {
      Serial.print("ANDAR P/ ");
  
      if (sinalCentro < referencia ) {
        Serial.println("FRENTE");
        frente();
      } else if (sinalDireita < referencia && sinalCentro < referencia && sinalEsquerda < referencia) {
        Serial.println("FRENTE");
        frente();
      } else if (sinalDireita < referencia && sinalCentro < referencia && sinalEsquerda > referencia) {
        Serial.println("ESQUERDAF");
        esquerdaF();
      } else if (sinalDireita > referencia && sinalCentro < referencia && sinalEsquerda < referencia) {
        Serial.println("DIREITAF");
        direitaF();
      } else if (sinalDireita < referencia && sinalCentro > referencia) {
        Serial.println("DIREITAB");
        direitaB();
      } else if (sinalEsquerda < referencia && sinalCentro > referencia) {
        Serial.println("ESQUERDAB");
        esquerdaB();
      }
      else {
        Serial.println("PARAR");
        parar();
      }
    }
    Serial.println("");
  }
  else {
        Serial.println("PARAR");
        parar();
  }
}  
