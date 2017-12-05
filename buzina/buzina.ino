/*
  First bar of Dixie AKA the Dukes of Hazzard Horn
 
 */
 
 // these are the frequencies for the notes from middle C
// to one octave above middle C:
const int note[] = {
262, // C
554, // C#
294, // D
622, // D#
330, // E
348, // F
740, // F#
390, // G
830, // G#
880, // A
932, // A#
988, // B
1046  // C next octave
};

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




}
