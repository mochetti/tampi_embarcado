#ifndef FUNCOES_H
#define FUNCOES_H

#include "Arduino.h"
#include <ESP8266WiFi.h>            // bibliotecas do servidor          
#include <WebSocketsServer.h>
// #include <WebSocketsClient.h>

// Pinos do NodeMCU

const int pwmEsq = D4;  // pinos digitais no ESP
const int pwmDir = D8;

const int echoPin = D2;  // echo do ultrassonico
const int trigPin = D3;  // trig do ultrassonico

const int clkPin = D5;   // clk do 74595
const int latchPin = D6; // latch do 74595
const int dataPin = D7;  // dados seriais do 74595

const int buzzerPin = D0;

const int botaoPin = D1;    // botao
const int analogPin = A0;  // pino analogico

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
const int encEsqPin = 2;
const int encDirPin = 23;
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

// Variáveis globais

extern WebSocketsServer webSocket;  // servidor websocket
extern WiFiEventHandler stationConnectedHandler;
extern WiFiEventHandler stationDisconnectedHandler;

extern boolean wifi;
extern unsigned long tempo;
extern unsigned long ultimaConexao;

extern int pulsosEncoderEsq;
extern int pulsosEncoderDir;
extern bool encoderEsqPreto;
extern bool encoderDirPreto;
extern unsigned long tempoEncEsq;
extern unsigned long tempoEncDir;
extern int velEsq;
extern int velDir;

extern char sensores[30];

extern const char *ssid;
extern const char *password;

extern const char* mdnsName; // Domain name for the mDNS responder

extern byte shiftPinos[5];   // valores instantâneos dos pinos controlados pelos 74595
extern bool mudancaShiftPinos;   // controla se houve mudanca nos pinos dos 74595

extern int tampinhasTopo[8]; // array de acoes das tampinhas
extern int tampinhasEsq[6];
extern int tampinhasDir[6];

// Relação entre id das ações e cor da tampinha
extern const char *cores[];

// Relação de clientes configurados como PC
extern int pc[];
// Relação de clientes configurados como app
extern int app[];

extern const int velGeral;
extern const int tempoGiroEixo;

// Funções
void startAP();
void startWS();
void leituraSensores();
void dWrite(int, int);
void shift();
int aRead(int);
void musica(char *);
void motor(int, int);
void buzina(int);
void buzina(int, int);
void funcaoEsq();
void funcaoDir();
int classifica(int);
void encoders();
void conexaoCliente(const WiFiEventSoftAPModeStationConnected&);
void desconexaoCliente(const WiFiEventSoftAPModeStationDisconnected&);
String macToString(const unsigned char*);
void webSocketEvent(uint8_t, WStype_t, uint8_t *, size_t);

#endif