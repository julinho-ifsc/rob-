 #include <NewPing.h>

 #define TRIGGER_PIN 22
 #define ECHO_PIN 23
 #define MAX_DISTANCE 150

 NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//motor 1
int velocidadeA = 34;
int IN1 = 35;
int IN2 = 36;

//motor 2
int velocidadeB = 39;
int IN3 = 37;
int IN4 = 38;

//motor 3
int velocidadeC = 8;
int IN5 = 9;
int IN6 = 10;

//motor 4
int velocidadeD = 13;
int IN7 = 11;
int IN8 = 12;

//variavel auxiliar
int velocidade = 0;

//Inicializa Pinos
void setup() {
  Serial.begin(9600);
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
  analogWrite(velocidadeA, 255);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 255);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 100);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 100);
}

void direita() {
  // Motor 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(velocidadeA, 100);

  // Motor 2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(velocidadeB, 100);

  // Motor 3
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(velocidadeC, 100);

  // Motor 4
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(velocidadeD, 100);
}

void esquerda() {
  // Motor 1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(velocidadeA, 100);

  // Motor 2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(velocidadeB, 100);

  // Motor 3
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(velocidadeC, 100);

  // Motor 4
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(velocidadeD, 100);
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

  if (cm < 20) {
    parar()
  } else{
    frente();
    delay(5000);

    // direita();
    // delay(200);

    // esquerda();
    // delay(200);

    parar();
    delay(200);
  }
}
