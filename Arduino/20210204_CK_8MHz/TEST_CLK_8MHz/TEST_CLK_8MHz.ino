/* Generatore di clock a 8MHz per Chip Camera OV7670
 *  su Arduino Mega. Questo Sketch produce un'onda 
 *  quadra di frequenza 8MHz su un pin di uscita
 *  partendo da un clock 16MHz, utilizzando OCR4A
 *  alla massima frequenza, cioè 16MHz ÷2.
 *
 *  Guarda il video: https://www.youtube.com/watch?v=z41dz3ocIu0
 *
 *  15-02-2021 - Emanuele Frisoni
 */

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
