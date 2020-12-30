/*
  90 - preto
  175 180 - violeta
  230 235 - laranja
  325 335 - amarelo
  510 520 - rosa
  650 660 - azul
  835 840 - verde
  935 940 - vermelho
  990 - branco
  */

  #include <SPI.h>
  #include "nRF24L01.h"
  #include "RF24.h"

  // Armazena os dados enviados
  int a[16];

  RF24 radio(9,10);

  // Define o endereco para comunicacao entre os modulos
  const uint64_t pipe = 0xE13CBAF433LL;
  
void setup() {
  Serial.begin(57600);
  // Inicializa a comunicacao do NRF24L01
  radio.begin();
  // Entra em modo de transmissao
  radio.openWritingPipe(pipe);

  // Declara os pinos digitais como saída
  for(int i=22;i<49;i=i+2){
    pinMode(i, OUTPUT);
  }
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, INPUT);    // Botão
    // acende todos os leds na sequencia
  for(int j=22;j<49;j=j+2){
   digitalWrite(j, HIGH);
   delay(500);
   digitalWrite(j, LOW); 
  }
  for(int j=5;j<7;j++){
   digitalWrite(j, HIGH);
   delay(500);
   digitalWrite(j, LOW); 
  }
  

}

void loop() {
  if(digitalRead(7) == HIGH) digitalWrite(6, HIGH);
  else digitalWrite(6, LOW);

 /* for(int i=0;i<16;i++){
    // Leitura das tampinhas
    int leitura = analogRead(i);

  if(leitura>=30 && leitura <= 130)a[i]=1;      //preto
  else if(leitura>130 && leitura <= 205)a[i]=2; //violeta
  else if(leitura>205 && leitura <= 280)a[i]=3; //laranja
  else if(leitura>280 && leitura <= 400)a[i]=4; //amarelo
  else if(leitura>400 && leitura <= 600)a[i]=5; //rosa
  else if(leitura>600 && leitura <= 730)a[i]=6; //azul
  else if(leitura>730 && leitura <= 890)a[i]=7; //verde
  else if(leitura>890 && leitura <= 970)a[i]=8; //vermelho
  else if(leitura>970 && leitura <= 1020)a[i]=9;//branco
  else a[i]=0;
 Serial.println(a[i]);
 delay(10);
  }
  radio.write(a, 16);
  delay(5000);
*/
}
