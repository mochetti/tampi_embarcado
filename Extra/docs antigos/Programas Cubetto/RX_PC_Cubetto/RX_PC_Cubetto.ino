#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 3);

// Armazena os bytes recebidos pelo rádio
byte text[17];

const byte rxAddr[6] = { 'U', 'n', 'e', 's', 'p' };

void setup()
{
  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
}

void loop()
{
  // Checa por dados no rádio
  if (radio.available())
  {
    // Recebe os dados
    radio.read(&text, sizeof(text));
    if(text[0] == 0x80){
      // Envia para o PC
      for(int i = 1; i<17; i++){
          text[i] = text[i] - 48;     // Verificar se é necessário
          Serial.print(text[i]);
          Serial.print(",");
    }
      Serial.println("");
    }
  }
}
