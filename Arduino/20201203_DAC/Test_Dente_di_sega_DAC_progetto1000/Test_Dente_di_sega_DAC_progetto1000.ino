/* Generatore di onda a dente di sega su Arduino Mega
 *  con Convertitore Digitale Analogico (DAC R-2R)
 *  e amplificatore LM386N.
 *
 *  Guarda il video: https://www.youtube.com/watch?v=L2Mvvd9AcHA
 *  
 *  03-12-2020 - Emanuele Frisoni
 */

#define MODO_PARALLELO 0

int segnale;


// the setup function runs once when you press reset or power the board
void setup() {
  
  /* PORT-L PINS */
  pinMode(42, OUTPUT); /* PORT - L7 */ 
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT); /* PORT - L0 */ 

  segnale = 0;
}

// the loop function runs over and over again forever
void loop() {

  segnale = (segnale + 1) & 0xFF;

#if MODO_PARALLELO 
   
  PORTL = segnale;

#else

  digitalWrite(49, bitRead(segnale, 0));
  digitalWrite(48, bitRead(segnale, 1));
  digitalWrite(47, bitRead(segnale, 2));
  digitalWrite(46, bitRead(segnale, 3));
  digitalWrite(45, bitRead(segnale, 4));
  digitalWrite(44, bitRead(segnale, 5));
  digitalWrite(43, bitRead(segnale, 6));
  digitalWrite(42, bitRead(segnale, 7));

#endif

  delayMicroseconds( 10 );
      
}
