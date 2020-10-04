// ativa os motores
//void motores(int esq, int dir, int vel) {
//  analogWrite(motorEsqPWM, vel);
//  analogWrite(motorDirPWM, vel);
//
//  dWrite(motorEsqA, esq);
//  dWrite(motorEsqB, 1 - esq);
//  dWrite(motorDirA, dir);
//  dWrite(motorDirB, 1 - dir);
//  shift();
//}

// permite velocidades distintas
void motor(int velE, int velD) {

  analogWrite(motorEsqPWM, abs(velE));
  analogWrite(motorDirPWM, abs(velD));

  int sentido = 0;
  if (velE < 0) sentido = 1;
  dWrite(motorEsqA, sentido);
  dWrite(motorEsqB, 1 - sentido);
  sentido = 0;
  if (velD < 0) sentido = 1;
  dWrite(motorDirA, sentido);
  dWrite(motorDirB, 1 - sentido);

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

int distancia() {
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
  dWrite(farolEsqPin, 1);    // acende
  dWrite(farolDirPin, 1);
  shift();
  delay(2000);
  dWrite(farolEsqPin, 0);    // apaga
  dWrite(farolDirPin, 0);
  shift();
}

void seta (int analog) {

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
