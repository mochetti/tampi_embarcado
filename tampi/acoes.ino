
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
