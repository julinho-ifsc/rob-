//Programa : Motor shield com sensor TCRT5000
//Adaptacoes : FILIPEFLOP
//
//Baseado no programa original de Michael McRoberts

int SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5;

//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;

//limiar do sensor
int threshold = 5;

//Rotina de calibracao do sensor
void calibrate() {
  //Executa 10 vezes para obter uma media
  for (int x=0; x<10; x++) {
    delay(100);
    SENSOR1 = analogRead(A11); // Sensor ponta esquerda
    SENSOR2 = analogRead(A15); // Sensor meia esquerda
    SENSOR3 = analogRead(A14); // Sensor central
    SENSOR4 = analogRead(A13); // Sensor meia direita
    SENSOR5 = analogRead(A12); // Sensor ponta direita

    leftOffset = leftOffset + SENSOR2;
    centre = centre + SENSOR3;
    rightOffset = rightOffset + SENSOR4;
    delay(100);
  }
  //obtem a media para cada sensor
  leftOffset = leftOffset /10;
  rightOffset = rightOffset /10;
  centre = centre / 10;
  //calcula os deslocamentos para os sensores esquerdo e direito
  leftOffset = centre - leftOffset;
  rightOffset = centre - rightOffset;
}

void setup() {
  Serial.begin(9600);
  calibrate();
  delay(3000);
}

void loop() {
  //le os sensores e adiciona os deslocamentos
  SENSOR1 = analogRead(A11);
  SENSOR2 = analogRead(A15) + leftOffset;
  SENSOR3 = analogRead(A14);
  SENSOR4 = analogRead(A13) + rightOffset;
  SENSOR5 = analogRead(A12);

  Serial.print("Ponta Esquerda: ");
  Serial.println(SENSOR1);
  Serial.print("Meia Esquerda: ");
  Serial.println(SENSOR2);
  Serial.print("Centro: ");
  Serial.println(SENSOR3);
  Serial.print("Meia Direita: ");
  Serial.println(SENSOR4);
  Serial.print("Direita: ");
  Serial.println(SENSOR5);

  delay(1000);
}
