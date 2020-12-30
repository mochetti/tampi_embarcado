// relacao de pinos dos 74595
const int A4067 = 1;  // ultimo q6
const int B4067 = 0;  // ultimo q7
const int C4067 = 7;  // ultimo q0
const int D4067 = 23;   // segundo q0
const int E4067 = 31;   // primeiro q0
const int F4067 = 15;  // terceiro q0

//const int leds[] = {
//  16, 17, 18, 19, 20, 21, 22, 23,  // leds superiores
//  24, 25, 26,                      // leds funcao A
//  27, 28, 29                      // leds funcao B
//};

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

// retorna o modo de operacao da chave mestra
int chaveMestra() {
  int valor = aRead(chaveMestraPin);
  if (valor < 256) return 0;
  if (valor < 512) return 1;
  if (valor < 768) return 2;
  else return 3;
}

// retorna um array com os valores das tampinhas
//Tampinha getTampinha(int i, bool p) {
//  Tampinha t;
//  t.acao = aRead(tamp[i]);
//  if (p) t.pot = aRead(pot[i]);
//  return t;
//}

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

bool botao() {
  if (digitalRead(botaoPin) == LOW) {
    Serial.println("BOTAO: atualizando as tampinhas");
    for (int i = 0; i < 14; i++) {
      int leitura = aRead(pot[i]);
      potenciometros[i] = map(leitura, 0, 512, 0, 1023);
      leitura = aRead(tamp[i]);
      Serial.println(leitura);
      // classifica cada tampinha
      if (leitura >= 15 && leitura <= 37) tampinhas[i] = 1;     //cinza
      else if (leitura > 37 && leitura <= 55) tampinhas[i] = 2; //rosa
      else if (leitura > 55 && leitura <= 130)tampinhas[i] = 3; //preto
      else if (leitura > 130 && leitura <= 250)tampinhas[i] = 4; //amarelo
      else if (leitura > 300 && leitura <= 400)tampinhas[i] = 5; //laranja
      else if (leitura > 400 && leitura <= 500)tampinhas[i] = 6; //azul
      else if (leitura > 550 && leitura <= 650)tampinhas[i] = 7; //lilas
      else if (leitura > 650 && leitura <= 700)tampinhas[i] = 8; //dourado
      else if (leitura > 700 && leitura <= 750)tampinhas[i] = 9; //vermelho
      else if (leitura > 750 && leitura <= 850)tampinhas[i] = 10; //branco
      else if (leitura > 900 && leitura <= 950)tampinhas[i] = 11; //verde
      else if (leitura > 950 && leitura <= 1021)tampinhas[i] = 12; //marrom
      else tampinhas[i] = 0;
    }
    return true;
  }
  return false;
}


// aqui que a brincadeira começa
void acao(int i) {
  Serial.print("ACAO: ");
  Serial.print(i);
  Serial.print(" - ");
  switch (i) {
    case 0:         // vazio
      Serial.println("vazio");
      break;

    case 1:     //cinza - loop (trava o código)
      Serial.println("loop");
      for (int i = 0; i < 8; i++) {
        acao(tampinhas[i]);           // tampinhas do topo
      }
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
    acao(tampinhas[i]);           // tampinhas do topo
    //    Serial.println(tampinhas[i]);
  }
}

// funcao direita
void funcaoDir() {
  for (int i = 11; i < 14; i++) {
    acao(tampinhas[i]);           // tampinhas do topo
    //    Serial.println(tampinhas[i]);
  }
}
