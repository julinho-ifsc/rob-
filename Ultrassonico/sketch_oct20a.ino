#include <NewPing.h>

#define TRIGGER_PIN 22
#define ECHO_PIN 23
#define MAX_DISTANCE 150


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {

  Serial.begin(115200);
pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);

}

void loop() {

 Serial.print("Distancia: ");
 Serial.println(sonar.ping_cm());
 float cm = sonar.ping_cm();
 
}

