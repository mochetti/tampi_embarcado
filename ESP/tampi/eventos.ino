void acoes(uint8_t * payload) {
  Serial.println("EVENTO WS: recebemos acoes");
  // atualiza as tampinhas
  int i = 1;    // index dentro de payload
  int t = 0;    // tampinha/potenciometro sendo construido
  int v = 0;    // index de valor
  char c = '\0';
  char valor[5] = {'\0', '\0', '\0', '\0', '\0'};  // o maior valor pode ter 4 caracteres (1023)
  // busca as tampinhas
  c = payload[1]; // começa a buscar em payload[1]
  while (c != '*') {
    //          Serial.printf("EVENTO WS: tampinha %d\n", t);
    while (c != ':') {
      //            Serial.printf("EVENTO WS: char %d = %c\n", i, c);
      valor[v] = c;
      v++;
      i++;
      c = payload[i];
    }
    tampinhas[t] = atoi(valor);               // converte para int
    for (int a = 0; a < 4; a++) valor[a] = '\0'; // limpa o array
    v = 0;
    t++;                                      // proxima tampinha
    i++;
    c = payload[i];
  }
  // busca os potenciometros
  t = 0;
  i++;
  c = payload[i];
  while (c != 'e') {
    //          Serial.printf("EVENTO WS: pot %d\n", t);
    while (c != ':') {
      //            Serial.printf("EVENTO WS: char %d = %c\n", i, c);
      valor[v] = c;
      v++;
      i++;
      c = payload[i];
    }
    potenciometros[t] = atoi(valor);               // converte para int
    for (int a = 0; a < 4; a++) valor[a] = '\0'; // limpa o array
    v = 0;
    t++;                                      // proximo pot
    i++;
    c = payload[i];
  }

  // debug dos arrays obtidos
  for (int i = 0; i < 14; i++) {
    Serial.printf("%d - t: %d   p: %d\n", i, tampinhas[i], potenciometros[i]);
  }
}

void movimento(uint8_t * payload) {
  Serial.println("EVENTO WS: movimento");
  int i = 1;    // index dentro de payload
  int v = 0;
  int m1 = 0;
  int m2 = 0;
  char c = '\0';
  char valor[5] = {'\0', '\0', '\0', '\0', '\0'};  // o maior valor pode ter 4 caracteres (1023)
  c = payload[1]; // começa a buscar em payload[1]
  while (c != ':') {
    valor[v] = c;
    i++;
    v++;
    c = payload[i];
  }
  m1 = atoi(valor);               // converte para int
  for (int a = 0; a < 4; a++) valor[a] = '\0'; // limpa o array
  i++;  // proxima tampinha
  v = 0;
  c = payload[i];
  while (c != 'e') {
    valor[v] = c;
    i++;
    v++;
    c = payload[i];
  }
  m2 = atoi(valor);               // converte para int

  motor(m1, m2);
}

void buzzer(uint8_t * payload) {
  Serial.println("EVENTO WS: buzzer");
  int nota;
  int tempo;
  int i = 1;    // index dentro de payload
  int v = 0;    // index de valor
  char c = '\0';
  char valor[5] = {'\0', '\0', '\0', '\0', '\0'};  // o maior valor pode ter 4 caracteres (1023)
  // busca as tampinhas
  c = payload[1]; // começa a buscar em payload[1]
  while (c != 'e') {
    while (c != ':') {
      valor[v] = c;
      v++;
      i++;
      c = payload[i];
    }
    nota = atoi(valor);               // converte para int
    for (int a = 0; a < 4; a++) valor[a] = '\0'; // limpa o array
    v = 0;
    i++;
    c = payload[i];

    while (c != '*') {
      valor[v] = c;
      v++;
      i++;
      c = payload[i];
    }
    tempo = atoi(valor);               // converte para int
    for (int a = 0; a < 4; a++) valor[a] = '\0'; // limpa o array
    v = 0;
    i++;
    c = payload[i];

    // toca a nota
    buzina(nota, tempo);
  }
}

void testeBuzzer(uint8_t * payload) {
  Serial.println("EVENTO WS: teste buzzer");
  int freq = 0;
  int i = 1;    // index dentro de payload
  char c = '\0';
  char valor[5] = {'\0', '\0', '\0', '\0', '\0'};
  c = payload[1]; // começa a buscar em payload[1]
  while (c != 'e') {
    valor[i - 1] = c;
    i++;
    c = payload[i];
  }
  freq = atoi(valor);
  buzina(freq);
}
