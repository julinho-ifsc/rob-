
/*-IMPORTACAO DO LCD COM I2C*/
#include <Wire.h>

// PINO DO SENSOR DE TENSAO ANALÓGICA(A2) UTILIZADA PELO SENSOR DE TENSÃO
int sensorTensaoDC = A1;

// DECLARAÇÃO DE VARIÁVEL QUE RECEBE O VALOR LIDO NA PORTA ANALÓGICA A1
float valorTensaoDC;

// DECLARAÇÃO DA VARIÁVEL DA MEDIA DE AMOSTRAGEM
int amostragem =1000;

// DECLARAÇÃO DA VARIÁVEL DA SOMA DA MEDIA DE AMOSTRAGEM
float mediaTotalTensaoDC =0;

// DECLARAÇÃO DE VARIÁVEL QUE RECEBE O VALOR FINAL CONVERTIDO EM VOLTS DC
float valorFinalTensaoDC = 0;

//VARIAVEIS COM OS VALORES DOS RESISTORES DO SENSOR DE TENSÃO DC
float R1 = 32600.0;
float R2 = 6810.0;

// DECLARAÇÃO LED
const int led = 13;



// DECLARAÇÃO DA VARIÁVEL AUXILIAR
int sensorValue_aux = 0;

// DECLARAÇÃO DA VARIÁVEL DA CONSTANTE DO ADC 5/1023
float voltsporUnidade = 0.004887586;// 5%1023

void setup(){
 // LED
 pinMode(led,OUTPUT);

 //VALOR REFERENCIAL
 analogReference(DEFAULT);

// INICIALIZA A PORTA SERIAL
 Serial.begin(9600);

// DECLARA QUE A PORTA DO SENSOR DE TENSAO DC
 pinMode(sensorTensaoDC, INPUT);

 //DECLARA O MODO DE OPERAÇÃO DO LED
   pinMode(led, OUTPUT);

 delay(500);
}

void loop() {

//REINICIA O VALOR ATUAL E ATUALIZA NA PRÓXIMA LEITURA
 valorFinalTensaoDC = 0;

 //REINICIA O VALOR ATUAL E ATUALIZA NA PRÓXIMA LEITURA
 mediaTotalTensaoDC = 0;

 //INICIA A AQUISIÇÃO DOS VALORES PARA MEDIR A CORRENTE CONSUMIDA
 //INICIA A AQUISIÇÃO DOS VALORES PARA MEDIR A TENSÃO CONSUMIDA
   for(int i=0; i < amostragem ; i++){

  //LEITURA DO VALOR NA PORTA ANALÓGICA(VARIA DE 0 ATÉ 1023)
   valorTensaoDC = analogRead(sensorTensaoDC);
   //CALCULA O VALOR A PARTIR DA RESOLUÇÃO DO ADC
   valorTensaoDC =(valorTensaoDC*voltsporUnidade);
   //INCLUE NO CALCULO OS VALORES DO DIVISOR DE TENSÃO
   mediaTotalTensaoDC = mediaTotalTensaoDC+ (valorTensaoDC / (R2/(R1+R2)));

     //UM PEQUENO INTERVALO ENTRE AS LEITURAS
     delay(1);
 }

  //RETIRA A MEDIA DOS VALORES DE LEITURA
  valorFinalTensaoDC = mediaTotalTensaoDC / amostragem;


// FUNCAO PWM

float valor_calculo = valorFinalTensaoDC;

float funcao_PWM = 731.85 / valor_calculo;
Serial.println("VALOR ATRIBUIDO A PWM: ");
Serial.println(funcao_PWM);


//ACENDER LED CASO ESTEJA ABAIXO DE 7 VOLTS
if (valorFinalTensaoDC <= 7) {
     Serial.println("NÍVEL DE TENSÃO FORA DO IDEAL, FAVOR TROCAR BATERIAS");
     digitalWrite(led, HIGH);
     delay(100);
     digitalWrite(led, LOW);
     delay(100);
     digitalWrite(led, HIGH);
     delay(100);
     digitalWrite(led, LOW);
 }



 //SAÍDA NA JANELA COM INFORMAÇÕES DA PORTA SERIAL
 Serial.print("LEITURA DE: ");
 //SAÍDA NA JANELA COM INFORMAÇÕES DA PORTA SERIAL
 Serial.print(valorFinalTensaoDC);
 //SAÍDA NA JANELA COM INFORMAÇÕES DA PORTA SERIAL
 Serial.println(" VOLTS");


delay(1000);
}
