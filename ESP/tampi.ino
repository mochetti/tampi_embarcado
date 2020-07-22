// tampi 1.0 - www.github.com/mochetti/tampi

#include "Arduino.h"
#include <ESP8266WiFi.h>            // bibliotecas do servidor          
#include <WebSocketsServer.h>
#include <WebSocketsClient.h>

WebSocketsServer webSocket(81);    // create a websocket server on port 81


// Pinos gerais

const int motorEsqA = 30;    // pinos digitais nos 74595
const int motorEsqB = 29;
const int motorDirA = 28;
const int motorDirB = 27;

const int farolEsq = 26;
const int farolDir = 25;

const int motorEsqPWM = D4;  // pinos digitais no ESP
const int motorDirPWM = D8;

int echoPin = D2;  // echo do ultrassonico
int trigPin = D3;  // trig do ultrassonico

int clkPin = D5;   // clk do 74595
int latchPin = D6; // latch do 74595
int dataPin = D7;  // dados seriais do 74595

int buzzerPin = D0;

int botaoPin = D1;    // botao
int analogPin = A0;  // pino analogico

// relacao de pinos dos 4067
const int tamp[] = {
  15, 14, 13, 12, 11, 10, 9, 8,   //  tampinhas superiores
  7, 6, 5,                       //  funcao A
  4, 3, 2                        //  funcao B
};

const int chaveMestraPin = 14;  // chave mestra

const int pot[] = {
  31, 30, 29, 28, 27, 26, 25, 24,   // potenciometros superiores
  23, 22, 21,                       // potenciometros funcao A
  20, 19, 18                        // potenciometros funcao B
};

// Constantes empíricas de movimento
const int tempoGiroEixo = 2000;     // em ms

// Variáveis gerais

const char *ssid = "tampi";        // essas informações estão no QRCode (?)
const char *password = "senha123";

const char* mdnsName = "esp8266"; // Domain name for the mDNS responder

byte shiftPinos[4];   // valores instantâneos dos pinos controlados pelos 74595

int chMestra = 0;  // modo de operacao (0 a 3)
bool mudancaShiftPinos = false;   // controla se houve mudanca nos pinos dos 74595

int tampinhas[14]; // array de acoes das tampinhas
int potenciometros[14]; // array dos potenciometros

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

  //chMestra = chaveMestra();
  chMestra = 0;
  switch (chMestra) {
    case 0:   // leitura somente das tampinhas
      Serial.println("case 0: tampinhas");
      WiFi.mode(WIFI_OFF);  // desliga o sinal pra poupar bateria
      break;
    case 1:   // leitura dos potenciometros
      break;
    case 2:   // recebe comandos no servidor
      Serial.println("case 2: servidor");
      startAP();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
      startWebSocket();            // Start a WebSocket server
      break;
    case 3:   // envia comandos no servidor
      //      startSTA();
      //      webSocket.begin("192.168.0.123", 81, "/"); // server address, port and URL
      //      webSocket.onEvent(webSocketEvent); // event handler
      //      //webSocket.setAuthorization("user", "Password"); // use HTTP Basic Authorization this is optional remove if not needed
      //      webSocket.setReconnectInterval(5000); // try ever 5000 again if connection has failed
      //      // start heartbeat (optional)
      //      // ping server every 15000 ms
      //      // expect pong from server within 3000 ms
      //      // consider connection disconnected if pong is not received 2 times
      //      webSocket.enableHeartbeat(15000, 3000, 2);
      break;
  }

  Serial.println("fim do setup");
  delay(10);
}

void loop() {
  switch (chMestra) {
    case 0:   // leitura somente das tampinhas
      //    Serial.println("case 0");
      if (botao()) {
        for (int i = 0; i < 8; i++) {
          acao(tampinhas[i]);           // tampinhas do topo
        }
        delay(2000);
      }
      break;
    case 1:   // leitura dos potenciometros também
      if (botao())
        for (int i = 0; i < 8; i++) {
          acao(i);      // tampinhas do topo
        }
      delay(2000);
      break;
    case 2:   // recebe comandos no servidor
      //      Serial.println("case 2");
      webSocket.loop();                           // constantly check for websocket events
      //      server.handleClient();
      // TODO: salvar os comandos recebidos em tampinhas[] e potenciometros[]

      break;
    case 3:   // envia comandos no servidor
      botao();
      webSocket.loop();                           // constantly check for websocket events
      break;
    case 4: // debug
      // imprime as leituras dos bocais
      for (int i = 0; i < 14; i++) {
        int p = aRead(pot[i]);
        int t = aRead(tamp[i]);
        Serial.printf("%d: %d   %d", i, t, p);
        Serial.println();
      }
      delay(1000);
      break;
  }
}
