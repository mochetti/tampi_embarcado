/*
http://primo.io

This sketch is part of the Primo Prototype Documentation.
http://docs.primo.io

Tested on the Arduino Mega 2560.
Load this into the Interface Board.

ANALOG VALUES FOR DIFFERENT RESISTORS:
10KΩ = 500
100KΩ = 920
4.7KΩ = 319
220Ω = 20
*/

//4.7kΩ
int forwardVal = 326;
//10kΩ
int leftVal = 511;
//220Ω
int rightVal = 22;
//100kΩ
int functionVal = 931;
//range 
int gap = 50;

int buttonPin = 50;
int butVal, pButVal;

boolean isExecuting = false;

int vals[16];

void setup() {  
  //led init
  for (int i = 22; i < 38; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  
  //turn on LEDs if a block is inserted
  for(int i = 0; i < 16; i++) {
    int led = i+22;

    //fix this
    if (analogRead(i) < 1010) {
      digitalWrite(led, HIGH);
    } 
    else {
      digitalWrite(led, LOW);
    }    
  }

  butVal = digitalRead(buttonPin);
  
  //if button press & not executing
  if(butVal == HIGH && pButVal == LOW && isExecuting == false) {
    isExecuting = true;
  }

  if(isExecuting) {
    readPins();

    for ( int i = 0; i < 12; i++) {
      if (vals[i] < 1010) {
        route(i);
      }
      else {
        break;
      }
    }    
  }  
  
  isExecuting = false;
  pButVal = butVal;

  //Serial.println(analogRead(0));
  delay(30);
}






