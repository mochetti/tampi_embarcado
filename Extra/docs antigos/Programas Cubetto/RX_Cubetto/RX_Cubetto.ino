#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ODOMETRIA_ESQ A0
#define ODOMETRIA_DIR A1
#define TESTE_ODOMETRIA_ESQ A2
#define TESTE_ODOMETRIA_DIR A3
byte contOdoEsq = 0;//contador de pulsos, zerado a cada inicio de contagem (a cada novo comando)
byte contOdoDir = 0;
char ultContagemOdoEsq = 0;//ultima contagem desde a ultima medida
char ultContagemOdoDir = 0;
int valMinEsq = 1000;
int valMinDir = 1000;
int valMaxEsq = 0;
int valMaxDir = 0;
unsigned long tempoAnterior = 0;

int vel = 160;

#define PWM_MOTOR_ESQ 5
#define DIRECAO_PWM_MOTOR_ESQ_A 6
#define DIRECAO_PWM_MOTOR_ESQ_B 7
#define DIRECAO_PWM_MOTOR_DIR_A 8
#define DIRECAO_PWM_MOTOR_DIR_B 9
#define PWM_MOTOR_DIR 10

RF24 radio(2, 3);

// Armazena os bytes recebidos pelo rádio
byte text[17];

boolean dirE = false;
boolean dirD = false;
boolean got = false;

const byte rxAddr[6] = { 'U', 'n', 'e', 's', 'p' };

void setup()
{
  pinMode(PWM_MOTOR_ESQ, OUTPUT);
  pinMode(DIRECAO_PWM_MOTOR_ESQ_A, OUTPUT);
  pinMode(DIRECAO_PWM_MOTOR_ESQ_B, OUTPUT);
  pinMode(DIRECAO_PWM_MOTOR_DIR_A, OUTPUT);
  pinMode(DIRECAO_PWM_MOTOR_DIR_B, OUTPUT);
  pinMode(PWM_MOTOR_DIR, OUTPUT);
  pinMode(ODOMETRIA_ESQ, INPUT);
  pinMode(ODOMETRIA_DIR, INPUT);
  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
}

void loop()
{
  got = false;
  com();
  if(got) {
    delay(20);
    tampinhas();
  }
  //verificaOdoEsq();
  //verificaOdoDir();
}

// Recebe comandos novos
void com() {
  if (radio.available())
  {
    radio.read(&text, sizeof(text));
    if(text[0] == 0x80){
      got = true;
      for(int i = 1; i<17; i++){
          text[i] = text[i] - 48;
          Serial.print(text[i]);
          Serial.print(" ");
      }
      Serial.println("");
    }
  }
}

// Switch das tampinhas
void tampinhas() {

    for(int i=1; i<13; i++) {
      switch(text[i]){
        case 1:         // preto
        delay(2500);
        break;
        case 2:         // violeta
        delay(2500);
        break;
        case 3:         // laranja
        frente();
        delay(1500);
        break;
        case 4:         // amarelo
        retorno();
        delay(2000);
        break;
        case 5:         // rosa
        esquerda();
        delay(2500);
        break;
        case 6:         // azul
        re();
        delay(1500);
        break;
        case 7:         // verde
        direita();
        delay(2200);
        break;
        case 8:         // vermelho
        funcao();
        break;
        case 9:         // branco
        delay(2200);
        break;
        default:         // vazio
        freio();
        break;

      }
        freio();
        //delay(500);
    }
}

void funcao() {

  for(int i=13; i<17; i++) {
      switch(text[i]){
        case 1:         // preto
        delay(2500);
        break;
        case 2:         // violeta
        delay(2500);
        break;
        case 3:         // laranja
        frente();
        delay(1500);
        break;
        case 4:         // amarelo
        retorno();
        delay(2000);
        break;
        case 5:         // rosa
        esquerda();
        delay(2500);
        break;
        case 6:         // azul
        re();
        delay(1500);
        break;
        case 7:         // verde
        direita();
        delay(2200);
        break;
        case 8:         // vermelho
        funcao();
        break;
        case 9:         // branco
        delay(2200);
        break;
        default:         // vazio
        freio();
        break;

      }
          freio();
          //delay(500);
    }
}

void motor() {
  
    analogWrite(PWM_MOTOR_ESQ, vel);
    analogWrite(PWM_MOTOR_DIR, vel);
    
    digitalWrite(DIRECAO_PWM_MOTOR_ESQ_A, dirE);
    digitalWrite(DIRECAO_PWM_MOTOR_ESQ_B, !dirE);
    digitalWrite(DIRECAO_PWM_MOTOR_DIR_A, dirD);
    digitalWrite(DIRECAO_PWM_MOTOR_DIR_B, !dirD);
}

// Anda para frente
void frente() {

    Serial.println("Frente");

    dirE = LOW;
    dirD = LOW;
    motor();

    delay(400);
    freio();
    
}

// Vira para a direita
void direita() {

    Serial.println("Direita");

    dirE = LOW;
    dirD = HIGH;
    
    motor();

    delay(50);
    freio();
    
}

// Vira para a esquerda
void esquerda() {

    Serial.println("Esquerda");

    dirE = HIGH;
    dirD = LOW;
    
    motor();

    delay(50);
    freio();
    
}

// Retorno (180 graus)
void retorno() {

    Serial.println("Retorno");

    dirE = HIGH;
    dirD = LOW;
    
    motor();

    delay(250);
    freio();
    
}

// Anda de ré
void re() {

    Serial.println("Re");

    dirE = HIGH;
    dirD = HIGH;
    
    motor();

    delay(1000);
    freio();
    
}

// Para
void freio() {

    Serial.println("Freio");

    dirE = LOW;
    dirD = LOW;
    
    digitalWrite(DIRECAO_PWM_MOTOR_ESQ_A, dirE);
    digitalWrite(DIRECAO_PWM_MOTOR_ESQ_B, dirE);
    digitalWrite(DIRECAO_PWM_MOTOR_DIR_A, dirD);
    digitalWrite(DIRECAO_PWM_MOTOR_DIR_B, dirD);

    delay(1);    
}


