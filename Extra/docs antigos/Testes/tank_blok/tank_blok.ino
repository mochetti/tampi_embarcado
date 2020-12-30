#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h> 

// Armazena os dados recebidos
int recebidos[16];

// Inicializa o NRF24L01 nos pinos 9 (CE) e 53 (CS) do Arduino Mega
RF24 radio(9,10);

Servo myservo;

// Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE13CBAF433LL;

// Define o pino do led
int LED1 = 5;

void setup()
{
  // Servo conectado ao pino 4
  // Define o pino do led como saida
  pinMode(LED1, OUTPUT);
  // Inicializa a serial
  Serial.begin(57600);
  // Inicializa a comunicacao do NRF24L01
  radio.begin();
  // Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  // Mensagem inicial
  Serial.println("Aguardando dados...");
}

void loop()
{
  // Verifica sinal de radio
  if (radio.available())
  {
    bool done = false;    
    while (!done)
    {
      done = radio.read(recebidos, sizeof(recebidos));
      for(int i=0;i<16;i++){
      Serial.print(i);    
      Serial.print(" = ");
      Serial.println(recebidos[i]);
      
      }
      
    }
  }
}
