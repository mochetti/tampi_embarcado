#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Portas MISO e MOSI do SPI
RF24 radio(2, 3);

// Identificador do rádio
const byte txAddr[6] = { 'U', 'n', 'e', 's', 'p' };
char txBuf[17] = {128};
const unsigned char caractere_inicial = 0x80;

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(txAddr);
  
  radio.stopListening();
}

void loop()
{
  if(Serial.available() > 0) {
    Serial.println("Chegou");
    Serial.readBytes(&txBuf[1], sizeof(txBuf));
  
    txBuf[0] = caractere_inicial;
    // Envia os dados
    radio.write(&txBuf, sizeof(txBuf));
    for(int i=0; i<sizeof(txBuf); i++) Serial.print(txBuf[i]);
    Serial.println("");
  }
  
  //radio.write(numero, sizeof(numero));
  // Debug
  
  delay(10);
}
