// digitalWrite() através dos 74595 (acomoda o pino no array shiftPinos) -- precisa do shift() na sequencia!!
void dWrite(int pino, int estado) {
  bitWrite(shiftPinos[pino / 8], pino % 8, estado);
}

// envio de comandos para os 74595
void shift() {
  digitalWrite(latchPin, LOW);  // latch em nível baixo
  for (int i = 0; i < 4; i++) shiftOut(dataPin, clkPin, LSBFIRST, shiftPinos[i]); // carrega as informações
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
  return analogRead(analogPin);
}

/*  valores analogicos

     marrom - 1018
     verde - 933
     branco - 814
     vermelho - 732
     dourado - 686
     lilas - 598
     azul - 462
     laranja - 364
     amarelo - 169
     preto - 67
     rosa - 44
     cinza - 31

*/

// Leitura das tampinhas
void leitura() {
//  Serial.println("LEITURA: atualizando as tampinhas");
    for (int i = 0; i < 8; i++) tampinhasTopo[i] = classifica(aRead(tampinhasTopoPin[i]));
    for (int i = 0; i < 6; i++) tampinhasEsq[i] = classifica(aRead(tampinhasEsqPin[i]));
    for (int i = 0; i < 6; i++) tampinhasDir[i] = classifica(aRead(tampinhasDirPin[i]));
}

// Classifica a tampinha de acordo com a leitura analógica
int classifica(int analog) {
  int valor = 0;
  if (analog >= 15 && analog <= 37) valor = 1;     //cinza
  else if (analog > 37 && analog <= 55) valor = 2; //rosa
  else if (analog > 55 && analog <= 130) valor = 3; //preto
  else if (analog > 130 && analog <= 250) valor = 4; //amarelo
  else if (analog > 300 && analog <= 400) valor = 5; //laranja
  else if (analog > 400 && analog <= 500) valor = 6; //azul
  else if (analog > 550 && analog <= 650) valor = 7; //lilas
  else if (analog > 650 && analog <= 700) valor = 8; //dourado
  else if (analog > 700 && analog <= 750) valor = 9; //vermelho
  else if (analog > 750 && analog <= 850) valor = 10; //branco
  else if (analog > 900 && analog <= 950) valor = 11; //verde
  else if (analog > 950 && analog <= 1021) valor = 12; //marrom

  return valor;
}

// atualiza o array sensores[] com todos as leituras
void leituraSensores() {
  for(int i=0; i<30; i++) sensores[i] = 0;

  sprintf(sensores, "s%d,%d,%d,%d", 123, 314, 1234, 44);
  
//  for(int i=0; i<30; i++) Serial.print(dados[i]);
//  Serial.println();  

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
      pantera();
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
      asaBranca();    // asa branca
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
