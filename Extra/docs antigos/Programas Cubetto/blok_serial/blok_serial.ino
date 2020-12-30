/*
  90 - preto
  175 180 - violeta
  230 235 - laranja
  325 335 - amarelo
  510 520 - rosa
  650 660 - azul
  835 840 - verde
  935 940 - vermelho
  990 - branco
  */

  // Armazena os dados enviados
  int a[16];
  
void setup() {
  // Inicializa a comunicação serial na taxa especificada
  Serial.begin(9600);
  Serial1.begin(9600);

  // Declara os pinos digitais como saída
  for(int i=22;i<49;i=i+2){
    pinMode(i, OUTPUT);
  }
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
  // Declara o pino do botão como entrada
    pinMode(7, INPUT);    // Botão

  delay(500);
  start();

}

void loop() {
  
  if(digitalRead(7) == HIGH) {
    boolean apertado = true;
    unsigned long antes = millis();
    unsigned long agora = millis();
    while(agora - antes < 1500) {
      agora = millis();
      if(digitalRead(7) == LOW) apertado = false;
      delay(500);
    }
    if(apertado) {
      start();
    }
    else {
    delay(200);

    apagaLeds();                                  // apaga todos os leds
  for(int i=0;i<16;i++){
    // Leitura das tampinhas
    int leitura = analogRead(15-i);

  if(leitura>=30 && leitura <= 130)a[i]=1;      //preto
  else if(leitura>130 && leitura <= 205)a[i]=2; //violeta
  else if(leitura>205 && leitura <= 280)a[i]=3; //laranja
  else if(leitura>280 && leitura <= 400)a[i]=4; //amarelo
  else if(leitura>400 && leitura <= 600)a[i]=5; //rosa
  else if(leitura>600 && leitura <= 730)a[i]=6; //azul
  else if(leitura>730 && leitura <= 890)a[i]=7; //verde
  else if(leitura>890 && leitura <= 970)a[i]=8; //vermelho
  else if(leitura>970 && leitura <= 1020)a[i]=9;//branco
  else a[i]=0;
 //Serial.println(a[i]);
 delay(10);
  }
  for(int x=0; x<16; x++){
    Serial.print(a[x]);
    Serial1.print(a[x]);
  }
  // Espera os periféricos receberem. Talvez valha a pena checar pq tanto atraso
  delay(2500);
  for(int x=0; x<12; x++){
    if(a[x]) {
      if(a[x] == 8) {
        funcao();
        digitalWrite(2*x+22, HIGH);
      }
      else {
        pisca(x);
      }
    }
  }
  delay(1000);
    }
  }
}

void funcao(){
   digitalWrite(46, LOW);
   digitalWrite(48, LOW);
   digitalWrite(6, LOW);
   digitalWrite(7, LOW);
   for(int i=12; i<=15; i++){
      if(a[i] == 8) funcao();
   }
    if(a[12]) pisca(12);
    if(a[13]) pisca(13);
    if(a[14]) piscaX(6);
    if(a[15]) piscaX(7);
   digitalWrite(46, LOW);
   digitalWrite(48, LOW);
   digitalWrite(6, LOW);
   digitalWrite(7, LOW);
  }

void pisca(int x){
  boolean state = false;
    for(int i=0; i<=4;i++) {
      state = !state;
      digitalWrite(2*x+22, state);
      delay(500);
    }
  }

void piscaX(int x){
  boolean state = false;
    for(int i=0; i<=4;i++) {
      state = !state;
      digitalWrite(x, state);
      delay(500);
    }
}

void apagaLeds(){
  for(int j=22;j<49;j=j+2){
   digitalWrite(j, LOW); 
  }
  for(int j=5;j<7;j++){
   digitalWrite(j, LOW); 
  }
}

void flash(int j){
   digitalWrite(j, HIGH);
   delay(100);
   digitalWrite(j, LOW);
}

void start(){     // Padroes de start
    
    // Acende todos os leds na sequencia
  for(int j=22;j<49;j=j+2){
   digitalWrite(j, HIGH);
   delay(100);
   digitalWrite(j, LOW); 
  }
  for(int j=5;j<7;j++){
   digitalWrite(j, HIGH);
   delay(100);
   digitalWrite(j, LOW); 
  }

  // Cobrinha !
  int cobra[16] = {22, 24, 26, 28, 30, 44, 7, 6, 48, 46, 38, 36, 34, 32, 42, 40};
  for(int i=0; i<16; i++){
   flash(cobra[i]);
  }
  for(int i=15; i>=0; i--){
   flash(cobra[i]);
  }

  delay(250);
  
  // Pisca todos juntos
  for(int i=0; i<=3; i++){
    for(int j=22;j<49;j=j+2){
      digitalWrite(j, HIGH);
    }
    for(int j=5;j<7;j++){
      digitalWrite(j, HIGH);
    }
    delay(100);
    for(int j=22;j<49;j=j+2){
      digitalWrite(j, LOW);
    }
    for(int j=5;j<7;j++){
      digitalWrite(j, LOW);
    }
    delay(100);
  }
}

/*
 * // Acende linhas se cruzando
  for(int i=0; i<6; i++){
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(46, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  delay(300);
  digitalWrite(22, LOW);
  digitalWrite(24, LOW);
  digitalWrite(26, LOW);
  digitalWrite(28, LOW);
  digitalWrite(46, LOW);
  digitalWrite(48, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(30, HIGH);
  digitalWrite(32, HIGH);
  digitalWrite(34, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(38, HIGH);
  digitalWrite(40, HIGH);
  digitalWrite(42, HIGH);
  digitalWrite(44, HIGH);
  delay(300);
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(46, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(30, LOW);
  digitalWrite(32, LOW);
  digitalWrite(34, LOW);
  digitalWrite(36, LOW);
  digitalWrite(38, LOW);
  digitalWrite(40, LOW);
  digitalWrite(42, LOW);
  digitalWrite(44, LOW);
  delay(300);
  digitalWrite(22, LOW);
  digitalWrite(24, LOW);
  digitalWrite(26, LOW);
  digitalWrite(28, LOW);
  digitalWrite(46, LOW);
  digitalWrite(48, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  delay(300);
}*/



