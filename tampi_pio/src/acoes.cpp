/**
 * Funções externas do Tampi
 * 
 */

#include "funcoes.h"

void motor(int velE, int velD) {

  analogWrite(pwmEsq, abs(velE));
  analogWrite(pwmDir, abs(velD));

  int sentido = 0;
  if (velE < 0) sentido = 1;
  dWrite(AIN1, sentido);
  dWrite(BIN1, 1 - sentido);
  sentido = 0;
  if (velD < 0) sentido = 1;
  dWrite(AIN2, sentido);
  dWrite(BIN2, 1 - sentido);

  shift();
}

// anda
void andar(int analog) {
  //  Serial.println("ACAO: andar");
  int tempo = map(analog, 0, 1023, 0, 2000);
  motor(velGeral, velGeral);
  delay(tempo);
  motor(0, 0);
}

// girar pra esquerda
void girarEsq(int analog) {
  //  Serial.println("ACAO: girar pra esquerda");

  int tempo = map(analog, 0, 1023, 0, tempoGiroEixo);
  motor(-velGeral, velGeral);
  delay(tempo);
  motor(0, 0);
}

// girar pra esqudireitaerda
void girarDir(int analog) {
  //  Serial.println("ACAO: girar pra direita");

  int tempo = map(analog, 0, 1023, 0, tempoGiroEixo);
  motor(velGeral, -velGeral);
  delay(tempo);
  motor(0, 0);
}

float distancia() {
  //  Serial.println("ACAO: distancia");
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  float distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

void buzina(int analog) {
  tone(buzzerPin, analog, 16);
}

void buzina(int freq, int tempo) {
  //  Serial.println("ACAO: buzina");
  if (freq == 0 || tempo == 0) return;
  tone(buzzerPin, freq, 1000 / tempo);
  delay(1000 / tempo * 1.3);
  noTone(buzzerPin);
}


void farol(int analog) {
  //  Serial.println("ACAO: farol");
  int tempo = map(analog, 0, 1023, 0, 3000);
  dWrite(farolPin, 1);    // acende
  shift();
  delay(2000);
  dWrite(farolPin, 0);    // apaga
  shift();
}

void setaEsq(int analog) {

}

void setaDir(int analog) {
  
}

void musica(char *) {
  
}

void microfone(int analog) {
  if (aRead(micPin) > analog) {
    funcaoEsq();
  }
}

void ultrassonico(int analog) {
  if (distancia() < analog) {
    funcaoDir();
  }
}

void ldrEsq(int analog) {
  if (aRead(ldrEsqPin) > analog) {
    funcaoEsq();
  }
}

void ldrDir(int analog) {
  if (aRead(ldrDirPin) > analog) {
    funcaoDir();
  }
}

// aqui que a brincadeira começa
void acao(int i) {
  Serial.print("ACAO: ");
  Serial.print(i);
  Serial.print(" - ");
  Serial.println(cores[i]);
  switch (i) {
    case 0:         // vazio
//      Serial.println("vazio");
      break;

    case 1:     //cinza - loop (trava o código)
      Serial.println("loop");
//      for (int i = 0; i < 8; i++) {
//        acao(tampinhas[i]);           // tampinhas do topo
//      }
      break;

    case 2:         // rosa
      Serial.println("pantera");
      musica("pantera");
      delay(1000);
      break;

    case 3:         // preto - microfone (funcao esq)
      Serial.println("microfone");
      girarEsq(500);
      break;

    case 4:         // amarelo - funcao esq
      Serial.println("funcao esq");
      funcaoEsq();
      break;

    case 5:         // laranja - gira dir
      Serial.println("gira dir");
      girarDir(500);
      delay(1000);
      break;

    case 6:         // azul - gira esq
//      Serial.println("gira esq");
      girarEsq(500);
      delay(1000);
      break;

    case 7:         // lilas - funcao dir
      Serial.println("funcao dir");
      girarEsq(500);
//      funcaoDir();
      break;

    case 8:       // dourado - ultrassonico (funcao dir)
      Serial.println("ultrassonico");
      ultrassonico(0);
      break;

    case 9:         // vermelho - anda
      Serial.println("anda");
      andar(500);
      delay(1000);
      break;

    case 10:         // branco
      Serial.println("asa branca");
      musica("asa branca");    // asa branca
      delay(1000);
      break;

    case 11:         // verde
      Serial.println("verde");
      break;

    case 12:       // marrom
      Serial.println("farol");
      farol(500);
      break;

    default:         // vazio
      break;
  }
}

// funcao esquerda
void funcaoEsq() {
//  Serial.println("COMANDO: funcao esquerda");
  for (int i = 8; i < 11; i++) {
//    acao(tampinhas[i]);           // tampinhas do topo
    //    Serial.println(tampinhas[i]);
  }
}

// funcao direita
void funcaoDir() {
  for (int i = 11; i < 14; i++) {
//    acao(tampinhas[i]);           // tampinhas do topo
    //    Serial.println(tampinhas[i]);
  }
}
