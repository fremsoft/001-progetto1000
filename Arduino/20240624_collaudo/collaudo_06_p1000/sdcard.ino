/*
 * SD-Card collegata tramite SPI ai seguenti pin:
 *   ** MOSI - pin 11 (UNO) / 51 (MEGA)
 *   ** MISO - pin 12 (UNO) / 50 (MEGA)
 *   ** CLK -  pin 13 (UNO) / 52 (MEGA)
 *   ** CS -   pin 10 (UNO) / 53 (MEGA)  [(for MKRZero SD: SDCARD_SS_PIN)]
 *     
 *  DAC 8 bit per output audio su       pin     42..49
 *  che corrispondono rispettivamente a PORTL (MSb..LSb)
 *  
 *  Temporizzato da TIMER 5 che produce un interrupt ogni 125uS
 *  che corrisponde a una frequenza di 8kHz
 *  
 * Appunti:     
 * ** https://www.arduino.cc/en/Hacking/PinMapping2560     
 * ** https://www.arduino.cc/en/reference/SPI     
 * ** https://www.arduino.cc/en/reference/SD   
 * 
 * Bologna, 09 febbraio 2023
 */
#include <SPI.h>
#include <SD.h>

#define  CSPIN                53    /* per Arduino Mega il default è 53 */

#define SIZE_CIRCULAR_BUFFER 64
#define MASK_CIRCULAR_BUFFER 0x3F

volatile unsigned char circular_buffer[ SIZE_CIRCULAR_BUFFER ];
volatile unsigned char circular_buffer_head, circular_buffer_tail, circular_buffer_len;

void play_something(char * nomefile);


void setup_sdcard() {
  
  Serial.println("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(CSPIN)) {  
    Serial.println("Card failed, or not present");
    while ( true );   
  }
  
  Serial.println("SD-Card initialized.");

  /* inizializzazione buffer circolare */
  circular_buffer_head = 0;
  circular_buffer_tail = 0;
  circular_buffer_len  = 0;

  /* impostazione Timer 5 (originariamente Timer 3) per dare 
   * un interrupt a 8ksps : ogni 125 uSec
   * Quarzo = 16MHz; 62,5 nSec ---> 2000 impulsi ogni 125 uSec
   */
  cli();
  TCCR5A = 0x00;
  // prescaler 
  TCCR5B = 0x01;    /* modalità Clear Timer on Compare Match e senza prescaler */
  // conteggio da raggiungere
  OCR5A = (2000 - 1);
  // attivo CTC Mode
  TCCR5B |= 0x08;
  // abilita interrupt on match counter
  TIMSK5 = 0x02;
  sei();

  /* PORT-L PINS per DAC */
  pinMode(42, OUTPUT); /* PORT - L7 - Most Significant bit */ 
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT); /* PORT - L0 - Least Significant bit*/ 
  PORTL = 128;
  
}



void play_something( const char * nomefile )
{
  // Apre il file su SD-Card di nome "nomefile"
  // e lo suona su PORT-L (DAC 8 bit)
  
  File dataFile = SD.open( nomefile );
  
  int c;
  
  if (dataFile) {
    // se il file esiste ed è riuscito ad aprirlo
    
    while (dataFile.available()) { 

      while (circular_buffer_len >= (SIZE_CIRCULAR_BUFFER - 1)) /* do nothing */;
      
      c = dataFile.read();

      // Debug: Serial.println( c );

      circular_buffer[ circular_buffer_head ] = c;
      circular_buffer_head = (circular_buffer_head + 1) & MASK_CIRCULAR_BUFFER; 
      circular_buffer_len ++;
      
    }

    // chiude il file quando ha finito di leggerlo
    dataFile.close();
  }
  else {

    // se non riesce ad aprire il file "nomefile"
    Serial.print("error opening : ");
    Serial.println( nomefile );
      
  }
}

/* TIMER 5 COMPARE MATCH INTERRUPT */
ISR(TIMER5_COMPA_vect) {

   if (circular_buffer_len > 0)
   {
      PORTL = circular_buffer[ circular_buffer_tail ];
      
      circular_buffer_tail = (circular_buffer_tail + 1) & MASK_CIRCULAR_BUFFER; 
      circular_buffer_len --;
   }
    
}
