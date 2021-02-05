void setup() {
  // put your setup code here, to run once:

  // CONFIGURA OUTPUT COMPARE OC4A
  // SUL PIN NUMERO 6 PER GENERARE 
  // UN CLOCK A frequenza = 8 MHz
  pinMode(6, OUTPUT);
  TCCR4A = 0x40;
  TCCR4B = 0x09;
  OCR4A = 0;
}

void loop() {
    
}
