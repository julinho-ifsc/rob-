#include <Wire.h>

const int SENSOR_DC_PIN = A1;
const int LED_PIN = 13;
const int MIN_VOLTS = 7;
const int SAMPLES_NUMBER = 1000;
const float RESISTOR_1_VALUE = 32600.0;
const float RESISTOR_2_VALUE = 6810.0;
const float VOLTS_BY_UNIT = 0.004887586;
const float VOLTAGE_PWM_PROPORTION = 731.85;

void setup() {
  Serial.begin(9600);

  analogReference(DEFAULT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_DC_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  float voltageAccumulator = 0;

  for (int i = 0; i < SAMPLES_NUMBER; i++) {
    float voltageReading = analogRead(SENSOR_DC_PIN);
    float voltageValue = voltageReading * VOLTS_BY_UNIT;

    voltageAccumulator = voltageAccumulator + (voltageValue / (RESISTOR_2_VALUE / (RESISTOR_1_VALUE + RESISTOR_2_VALUE)));

    delay(1);
  }

  float averageVoltage = voltageAccumulator / SAMPLES_NUMBER;
  float finalVelocity = VOLTAGE_PWM_PROPORTION / averageVoltage;

  Serial.println("VALOR ATRIBUIDO A PWM: ");
  Serial.println(finalVelocity);

  if (averageVoltage <= MIN_VOLTS) {
    Serial.println("NÍVEL DE TENSÃO FORA DO IDEAL, FAVOR TROCAR BATERIAS");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
 }

  Serial.print("LEITURA DE: ");
  Serial.print(averageVoltage);
  Serial.println(" VOLTS");

  delay(1000);
}
