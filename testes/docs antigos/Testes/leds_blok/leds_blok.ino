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

void setup() {
  for(int i=22;i<53;i=i+2){
    pinMode(i, OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int j=22;j<53;j=j+2){
   digitalWrite(j, HIGH);
   delay(500);
   digitalWrite(j, LOW); 
  }

}
