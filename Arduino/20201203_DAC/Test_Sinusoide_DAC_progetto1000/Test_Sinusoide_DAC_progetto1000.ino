/* Generatore di onda sinusoidale su Arduino Mega
 *  con Convertitore Digitale Analogico (DAC R-2R)
 *  e amplificatore LM386N.
 *  La sinusoide viene memorizzata su un Array a 
 *  360 punti  (un valore per ogni grado della 
 *  circonferenza) in modo da ridurre al massimo 
 *  il carico computazionale del microprocessore.  
 *
 *  Guarda il video: https://www.youtube.com/watch?v=L2Mvvd9AcHA
 *
 *  03-12-2020 - Emanuele Frisoni
 */

int segnale[360];
int angolo;

// the setup function runs once when you press reset or power the board
void setup() {

  /* PORT-L PINS */
  pinMode(42, OUTPUT); /* PORT - L7 (MSb) */ 
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT); /* PORT - L0 (LSb) */ 

  for (angolo = 0; angolo < 360; angolo += 1)
  {
    segnale[angolo] = 128 + (126 * sin( (angolo * 6.28) / 360 ) );
  }

}

// the loop function runs over and over again forever
void loop() {
  
   angolo ++; if (angolo >= 360) { angolo = 0; }
   PORTL = segnale[angolo];

   /* delay(100); */ 
      
}
