/*  Tampi 1.0
 *  
 *  www.github.com/mochetti/tampi_embarcado
 *  
 *  by Thiago Mochetti
*/

#include "Arduino.h"
#include <ESP8266WiFi.h>            // bibliotecas do servidor          
#include <WebSocketsServer.h>
#include <WebSocketsClient.h>

WebSocketsServer webSocket(81);    // create a websocket server on port 81

// Pinos do NodeMCU

const int pwmEsq = D4;  // pinos digitais no ESP
const int pwmDir = D8;

int echoPin = D2;  // echo do ultrassonico
int trigPin = D3;  // trig do ultrassonico

int clkPin = D5;   // clk do 74595
int latchPin = D6; // latch do 74595
int dataPin = D7;  // dados seriais do 74595

int buzzerPin = D0;

int botaoPin = D1;    // botao
int analogPin = A0;  // pino analogico

// Pinos dos shifts

const int A4067 = 27;
const int B4067 = 28;
const int C4067 = 29;
const int D4067 = 30;
const int E4067 = 26;
const int F4067 = 25;

const int ledsTopo[] = {
  16, 17, 18, 19, 20, 21, 22, 23
};
const int ledsEsq[] = {
  38, 37, 36, 35, 34, 33
};
const int ledsDir[] = {
  14, 13, 12, 11, 10, 9
};

const int AIN2 = 4;
const int AIN1 = 3;
const int STDBY = 2;
const int BIN1 = 1;
const int BIN2 = 0;

const int redPin = 7;
const int greenPin = 6;
const int bluePin = 5;

const int farolPin = 24;
const int irEsqLED = 39;
const int irDirLED = 15;
const int setaEsqPin = 32;
const int setaDirPin = 8;

// Pinos dos mux

const int batPin = 1;
const int micPin = 16;
const int ldrEsqPin = 0;
const int ldrDirPin = 25;
const int encoderEsq = 2;
const int encoderDir = 23;
const int irEsqAnalog = 3;
const int irDirAnalog = 24;
const int tampinhasTopoPin[] = {
  10, 11, 12, 13, 19, 20, 21, 22
};
const int tampinhasEsqPin[] = {
  9, 8, 7, 6, 5, 4
};
const int tampinhasDirPin[] = {
  31, 30, 29, 28, 27, 26
};

const int analogExtra1 = 15;
const int analogExtra2 = 14;
const int analogExtra3 = 18;
const int analogExtra4 = 17;

// Variáveis gerais

const char *ssid = "tampi";        // essas informações estão no QRCode (?)
const char *password = "senha123";

const char* mdnsName = "esp8266"; // Domain name for the mDNS responder

byte shiftPinos[5];   // valores instantâneos dos pinos controlados pelos 74595
bool mudancaShiftPinos = false;   // controla se houve mudanca nos pinos dos 74595

int tampinhasTopo[8]; // array de acoes das tampinhas
int tampinhasEsq[6];
int tampinhasDir[6];

int velGeral = 60;
int tempoGiroEixo = 200;

void setup() {

  // Declara os pinos
  pinMode(echoPin, INPUT);  // echo do ultrassonico como entrada
  pinMode(trigPin, OUTPUT); // trig do ultrassonico como saída
  pinMode(clkPin, OUTPUT);  // clk do 74595 como saída
  pinMode(latchPin, OUTPUT); // latch do 74595 como saída
  pinMode(dataPin, OUTPUT); // dados do 74595 como saída
  pinMode(botaoPin, INPUT);     // botão como entrada
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(latchPin, HIGH);

  Serial.begin(115200);        // em 9600 notei atrasos no websocket

  motor(0, 0);

  buzina(500, 8);
  buzina(700, 8);
  buzina(600, 8);

  startAP();
  startWebSocket();
//  conectando(true);

  Serial.println("fim do setup");
  delay(10);
}

void loop() {
    webSocket.loop();                           // constantly check for websocket events                        // constantly check for websocket events
    if(webSocket.connectedClients(false) > 0) {
    }
//  leitura();
//  for (int i = 0; i < tampinhasTopo.length; i++) {
//    acao(tampinhasTopo[i]);           // tampinhas do topo
//  }
//  delay(2000);
  
}
