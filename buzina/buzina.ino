const int melody[] ={
  390, //g
  330, //e
  262, //low c
  262, //low c
  262, //low c
  294, //low d
  330, //e
  348, //f
  390, //g
  390, //g
  390, //g
  330, //e
};

const int time[] ={
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  8
};

void setup() {
  pinMode(4, OUTPUT);
}

void loop() {
  for (int i=0; i<= 11; i++){
    tone(4, melody[i], 2980/time[i]);
    delay(3000/time[i]);
  }
  digitalWrite(4, HIGH);
  delay(1000);
}
