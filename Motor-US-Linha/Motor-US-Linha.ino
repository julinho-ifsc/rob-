#include <NewPing.h>

#define TRIGGER_PIN 23
#define ECHO_PIN 22
#define BUZZER 24

NewPing sonar(TRIGGER_PIN, ECHO_PIN);

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
  analogWrite(velocidadeA, 150);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 150);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 150);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 150);
}

void direitaF() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 150);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 50);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 150);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 50);
}

void direitaB() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 120);

  // Motor 2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(velocidadeB, 120);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 120);

  // Motor 4
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(velocidadeD, 120);
}

void esquerdaB() {
  // Motor 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(velocidadeA, 120);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 120);

  // Motor 3
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(velocidadeC, 120);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 120);
}

void esquerdaF() {
  // Motor 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(velocidadeA, 50);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 150);

  // Motor 3
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(velocidadeC, 50);

  // Motor 4
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeD, 150);
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
      esquerdaB();
    } else if (sinalDireita > referencia && sinalCentro < referencia && sinalEsquerda < referencia) {
      Serial.println("DIREITAF");
      direitaB();
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
