char str[20];
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
  int i=0;
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  

  while (Serial1.available()){
    char c = Serial1.read();
    str += c;
    Serial.println(str);

  }  
    if(str = "bc6a9a03") {
      digitalWrite(led1, HIGH);
      Serial.print(str);
    }  else {
      digitalWrite(led3, HIGH);
      delay(3000);
      digitalWrite(led3, LOW);
      return;
    }
  }// Receptor Jorge