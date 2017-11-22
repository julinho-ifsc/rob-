int led1 = 10;
int led2 = 9;
int led3 = 8;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {    
  if (Serial1.available()) {
    String str = Serial1.readString();
    
    Serial.println(str);
  
    if (str == "BC6A9A03") {
      digitalWrite(led3, HIGH);
      digitalWrite(led1, LOW);
    } else {
      digitalWrite(led1, HIGH);
      digitalWrite(led3, LOW);
    }
  }
}
