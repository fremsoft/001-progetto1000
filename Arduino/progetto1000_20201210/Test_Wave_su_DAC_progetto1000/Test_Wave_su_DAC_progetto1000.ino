#include "ciao_wav.h"

long int size_ciao;
long int indice_ciao;

/* Mettere PLOTTER : 
 *    - false  - per sentire il suono dal DAC 
 *    - true   - per visualizzare la forma d'onda con plotter seriale
 */
#define   PLOTTER   true

// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(9600);  /* porta seriale per il debug */

  /* PORT-L PINS */
  pinMode(42, OUTPUT); /* PORT - L7 - Most Significant bit */ 
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT); /* PORT - L0 - Least Significant bit*/ 

  size_ciao = sizeof(ciao_wav);
  indice_ciao = 0;
}

// the loop function runs over and over again forever
void loop() {

#if PLOTTER 

   /* Mostra la forma d'onda sulla seriale di servizio per plotter */
   Serial.println(pgm_read_byte_far(&ciao_wav[indice_ciao]));

#else

   /* Scrive il valore 8 bit prelevato da memoria programma in Flash
    *  su PORT-L: scrittura simultanea su 8 linee di uscita 42-29
    *  in un unico colpo di clock, vedi articolo:
    *  
    *  https://forum.arduino.cc/index.php?topic=577294.0      
    */

   PORTL = pgm_read_byte_far(&ciao_wav[indice_ciao]); 
   
#endif

   /* incrementa indice e ricomincia quando giunge alla fine */
   indice_ciao ++; if (indice_ciao >= size_ciao) { indice_ciao = 0; }
   
   /* La traccia audio è registrata a 44.1 ksps 
    *  1000000uS / 44100Hz = 22,68uSec
    */
   delayMicroseconds(22);   
   
}
