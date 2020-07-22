// relacao de pinos dos 74595
const int A4067 = 1;  // ultimo q6
const int B4067 = 0;  // ultimo q7
const int C4067 = 7;  // ultimo q0
const int D4067 = 23;   // segundo q0
const int E4067 = 31;   // primeiro q0
const int F4067 = 15;  // terceiro q0

int echoPin = D2;  // echo do ultrassonico
int trigPin = D3;  // trig do ultrassonico

// relacao de pinos dos 4067
const int tamp[] = {
  0, 1, 2, 3, 4, 5, 6, 7,     // tampinhas superiores
  8, 9, 10,                   // tampinhas funcao A
  11, 12, 13                  // tampinhas funcao B
};

const int chaveMestraPin = 14;  // chave mestra

const int motorEsqA = 30;    // pinos digitais nos 74595
const int motorEsqB = 29;
const int motorDirA = 28;
const int motorDirB = 27;

const int motorEsqPWM = D4;  // pinos digitais no ESP
const int motorDirPWM = D8;

const int pot[] = {
  16, 17, 18, 19, 20, 21, 22, 23,   // potenciometros superiores
  24, 25, 26,                       // potenciometros funcao A
  27, 28, 29                        // potenciometros funcao B
};

int clkPin = D5;   // clk do 74595
int latchPin = D6; // latch do 74595
int dataPin = D7;  // dados seriais do 74595

int buzzerPin = D1;

int analogPin = A0;

byte shiftPinos[4];   // valores instantâneos dos pinos controlados pelos 74595

void setup() {
  // Declara os pinos
  pinMode(clkPin, OUTPUT);  // clk do 74595 como saída
  pinMode(latchPin, OUTPUT); // latch do 74595 como saída
  pinMode(dataPin, OUTPUT); // dados do 74595 como saída

  pinMode(buzzerPin, OUTPUT);

  pinMode(echoPin, INPUT);  // echo do ultrassonico como entrada
  pinMode(trigPin, OUTPUT); // trig do ultrassonico como saída

  Serial.begin(9600);
  digitalWrite(latchPin, HIGH);

  Serial.println("frente maximo");
  motores(0, 0, 1023);    // frente maximo
  delay(2000);
  Serial.println("frente devagar");
  motores(0, 0, 512);    // frente devagar
  delay(2000);
  Serial.println("para");
  motores(0, 0, 0);    // para
  delay(2000);
  Serial.println("tras maximo");
  motores(1, 1, 1023);    // tras maximo
  delay(2000);
  Serial.println("tras devagar");
  motores(1, 1, 512);    // tras devagar
  delay(2000);
  Serial.println("para");
  motores(0, 0, 0);    // para
  delay(2000);
}

// digitalWrite() através dos 74595 (acomoda o pino no array shiftPinos)
void dWrite(int pino, int estado) {
  bitWrite(shiftPinos[pino / 8], pino % 8, estado);
}

// envio de comandos para os 74595
void shift() {
  //  Serial.print("Shift: ");
  //  for(int i=0; i<4; i++) {
  //    Serial.print(shiftPinos[i]);
  //    Serial.print(" ");
  //  }
  //  Serial.println();
  digitalWrite(latchPin, LOW);  // latch em nível baixo
  for (int i = 0; i < 4; i++) {
    shiftOut(dataPin, clkPin, LSBFIRST, shiftPinos[i]); // carrega as informações
  }
  digitalWrite(latchPin, HIGH); // latch em nível alto
}

// analogRead através de um canal dos 4067
int aRead(int pino) {
  dWrite(A4067, bitRead(pino % 16, 0));
  dWrite(B4067, bitRead(pino % 16, 1));
  dWrite(C4067, bitRead(pino % 16, 2));
  dWrite(D4067, bitRead(pino % 16, 3));
  dWrite(E4067, pino / 16);     // enable em 0 habilita
  dWrite(F4067, 1 - pino / 16);
  shift();
  //  delay(5);
  return analogRead(analogPin);
}

void loop() {
  
}

// ativa os motores
void motores(int esq, int dir, int vel) {
  Serial.print(esq);
    Serial.print("  ");
    Serial.print(dir);
    Serial.print("  ");
    Serial.println(vel);
    Serial.print(motorEsqPWM);
    Serial.print("  ");
    Serial.println(motorDirPWM);
    Serial.print(motorEsqA);
    Serial.print("  ");
    Serial.print(motorEsqB);
    Serial.print("  ");
    Serial.print(motorDirA);
    Serial.print("  ");
    Serial.println(motorDirB);
    
    analogWrite(motorEsqPWM, vel);
    analogWrite(motorDirPWM, vel);
  
    dWrite(motorEsqA, esq);
    dWrite(motorEsqB, 1-esq);
    dWrite(motorDirA, dir);
    dWrite(motorDirB, 1-dir);
    shift();
}
