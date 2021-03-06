/*  Tampi 1.0
 *  
 *  www.github.com/mochetti/tampi_embarcado
 *  
 *  by Thiago Mochetti
*/

#include "funcoes.h"

WebSocketsServer webSocket(81);    // create a websocket server on port 81
WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;

boolean wifi = false;
unsigned long tempo = 0;
unsigned long ultimaConexao = 0;

int pulsosEncoderEsq = 0;
int pulsosEncoderDir = 0;
bool encoderEsqPreto = false;
bool encoderDirPreto = false;
unsigned long tempoEncEsq = 0;
unsigned long tempoEncDir = 0;
int velEsq = 0;
int velDir = 0;

char sensores[30];

const char *ssid = "Tampi";        // essas informações estão no QRCode (?)
const char *password = "senha123";

const char* mdnsName = "esp8266"; // Domain name for the mDNS responder

byte shiftPinos[5];   // valores instantâneos dos pinos controlados pelos 74595
bool mudancaShiftPinos = false;   // controla se houve mudanca nos pinos dos 74595

int tampinhasTopo[8]; // array de acoes das tampinhas
int tampinhasEsq[6];
int tampinhasDir[6];

// Relação entre id das ações e cor da tampinha
const char *cores[] = {
  "Vazio",
  "Cinza",
  "Amarelo",
  "Vermelho"
  };

// Relação de clientes configurados como PC
int pc[] = {-1, -1, -1, -1, -1};
// Relação de clientes configurados como app
int app[] = {-1, -1, -1, -1, -1};

const int velGeral = 60;
const int tempoGiroEixo = 200;

unsigned int samplingPeriod;
#define SAMPLING_FREQUENCY 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.


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
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 


  Serial.begin(115200);        // em 9600 notei atrasos no websocket

  // motor(0, 0);

  // startAP();
  // if(wifi) startWS();

  Serial.println("fim do setup");
  delay(10);
}

void loop() {
  // Verifica se há conexões ativas
  if(wifi) {
    if(WiFi.softAPgetStationNum() > 0) {
      ultimaConexao = millis();
      webSocket.loop();
      // Verifica se há clente no websocket
      if(webSocket.connectedClients(false) > 0) {
        if(millis() - tempo > 2000) {
          tempo = millis();
//          for(int i=0; i<5; i++) Serial.print(pc[i]);
//          Serial.println();
        }
      }
    }
    else if (millis() - ultimaConexao > 15000) {
      wifi = false;
      WiFi.mode(WIFI_OFF);  // desliga o sinal pra poupar bateria
      Serial.println("Wifi desabilitado");
    }
  }

  // Não há conexão
  else {
//    leitura();
//    for (int i = 0; i < 8; i++) {
//      acao(tampinhasTopo[i]);           // tampinhas do topo
//    }
    // Serial.println(aRead(micPin));
    // delay(100);
    // freq();
    // for(int i=0; i<6; i++) {
    //   Serial.print(aRead(tampinhasDirPin[i]));
    //   Serial.print("  ");
    // }
    // Serial.println();
    // delay(100);
    Serial.println(aRead(ldrDirPin));
    delay(100);
  }

  // atualiza a leitura dos encoders
  // encoders();
}
