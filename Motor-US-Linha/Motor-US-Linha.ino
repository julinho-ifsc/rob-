#include <NewPing.h>

#define TRIGGER_PIN 23
#define ECHO_PIN 22
#define MAX_DISTANCE 150
#define BUZZER 24

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

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
int velocidadeA = 34;
int IN1 = 35 ;
int IN2 = 36 ;

//motor 2
int velocidadeB = 39;
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
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
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

void frente() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 130);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 130);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 130);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 130);
}

void direitaB() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 130);

  // Motor 2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(velocidadeB, 130);

  // Motor 3
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(velocidadeC, 130);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 130);
}

 void direitaF() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 130);

  // Motor 2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(velocidadeB, 100);

  // Motor 3
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(velocidadeC, 100);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 130);
}

void esquerdaB() {
  // Motor 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(velocidadeA, 130);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 130);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 130);

  // Motor 4
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(velocidadeD, 130);
}

void esquerdaF() {
  // Motor 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(velocidadeA, 100);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 130);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 100);

  // Motor 4
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(velocidadeD, 130);
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

void voltar() {
  // Motor 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(velocidadeA, 130);

  // Motor 2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(velocidadeB, 130);

  // Motor 3
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(velocidadeC, 130);

  // Motor 4
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,HIGH);
  analogWrite(velocidadeD,130);
}

void loop() {
  Serial.print("Distancia: ");
  Serial.println(sonar.ping_cm());
  float cm = sonar.ping_cm();

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
    } else if (sinalDireita > referencia && sinalCentro < referencia && sinalEsquerda < referencia){
      Serial.println("DIREITAF");
      direitaF();
    } else if (sinalDireita < referencia && sinalCentro > referencia) {
      Serial.println("DIREITAB");
      direitaB();
    } else if (sinalEsquerda < referencia && sinalCentro > referencia) {
      Serial.println("ESQUERDAB");
      esquerdaB();
    } else if (sinalDireita > referencia && sinalCentro > referencia && sinalEsquerda > referencia) {
      Serial.println("PARAR");
      parar();
      delay(1000);
      Serial.println("VOLTAR");
      voltar();
      delay(1500);
      Serial.println("DIREITAB");
      direitaB();
    } else {
      Serial.println("PARAR");
      parar();
    }
  }

  Serial.println("");
}
