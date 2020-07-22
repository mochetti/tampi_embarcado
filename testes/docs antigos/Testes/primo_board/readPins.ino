void readPins() {
  for(int i = 0; i < 16; i++) {
    vals[i] = analogRead(i);
  }  
}

