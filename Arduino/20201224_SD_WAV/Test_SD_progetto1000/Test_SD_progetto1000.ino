/*
  SD card file dump

  This example shows how to read a file from the SD card using the
  SD library and send it over the serial port.

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11 (UNO) / 51 (MEGA)
 ** MISO - pin 12 (UNO) / 50 (MEGA)
 ** CLK -  pin 13 (UNO) / 52 (MEGA)
 ** CS -   pin 10 (UNO) / 53 (MEGA)  [(for MKRZero SD: SDCARD_SS_PIN)]

  Appunti:
 ** https://www.arduino.cc/en/Hacking/PinMapping2560
 ** https://www.arduino.cc/en/reference/SPI
 ** https://www.arduino.cc/en/reference/SD
   
  created  22 December 2010
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe

  riadattato il 17 Dicembre 2020
  per Progetto1000 da Emanuele Frisoni
  
  Guarda il video: https://www.youtube.com/watch?v=kRmUnPmCAZg

  This example code is in the public domain.
*/

#include <SPI.h>
#include <SD.h>

#define  DEBUG_PIN             8

#define  CSPIN                53    /* per Arduino Mega il default è 53 */
#define  NOMEFILE  "datalog.txt"

#define SIZE_CIRCULAR_BUFFER 64
#define MASK_CIRCULAR_BUFFER 0x3F

volatile unsigned char circular_buffer[ SIZE_CIRCULAR_BUFFER ];
volatile unsigned char circular_buffer_head, circular_buffer_tail, circular_buffer_len;

void play_something(char * nomefile);


void setup() {
  /* Open serial communications and wait for port to open: */
  Serial.begin(9600);
  
  while (!Serial) {
    /* wait for serial port to connect. Needed for native USB port only */
    /* do nothing */;    
  }

  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(CSPIN)) {
    
    Serial.println("Card failed, or not present");
    while (1); 
    
  }
  
  Serial.println("card initialized.");


  /* inizializzazione buffer circolare */
  circular_buffer_head = 0;
  circular_buffer_tail = 0;
  circular_buffer_len  = 0;

  /* impostazione Timer 3 per dare 
   * un interrupt a 8ksps ogni 125 uSec
   * Quarzo = 16MHz; 62,5 nSec ---> 2000 impulsi ogni 125 uSec
   */
  cli();
  TCCR3A = 0x00;
  // prescaler 
  TCCR3B = 0x01;    /* modalità Clear Timer on Compare Match e senza prescaler */
  // conteggio da raggiungere
  OCR3A = (2000 - 1);
  // attivo CTC Mode
  TCCR3B |= 0x08;
  // abilita interrupt on match counter
  TIMSK3 = 0x02;
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
   

#ifdef DEBUG_MODE 
  pinMode( DEBUG_PIN , OUTPUT); 
#endif

}

void loop() {

  play_something( "audio/track001.raw" );
  play_something( "audio/track002.raw" );
  
}


void play_something( const char * nomefile )
{
  /* open the file. note that only one file can be open at a time,
   * so you have to close this one before opening another.
   */
  File dataFile = SD.open( nomefile );
  int c;

  if (dataFile) {

    /* if the file is present, send its content on the serial line for debug */
    while (dataFile.available()) { 

      while (circular_buffer_len >= (SIZE_CIRCULAR_BUFFER - 1)) /* do nothing */;
      
      c = dataFile.read();

      // Debug: Serial.println( c );

      circular_buffer[ circular_buffer_head ] = c;
      circular_buffer_head = (circular_buffer_head + 1) & MASK_CIRCULAR_BUFFER; 
      circular_buffer_len ++;
      
    }

    /* close file when finished */
    dataFile.close();
  }
  else {

    /* if the file isn't open, pop up an error: */
    Serial.println("error opening ");
    Serial.println( nomefile );
      
  }
}

#ifdef DEBUG_MODE 
volatile int debug_var;
#endif

/* TIMER 3 COMPARE MATCH INTERRUPT */
ISR(TIMER3_COMPA_vect) {

#ifdef DEBUG_MODE 
   if (debug_var != 0) {
     debug_var = 0;
     digitalWrite( DEBUG_PIN , LOW );
   }
   else {
     debug_var = 1;
     digitalWrite( DEBUG_PIN , HIGH );
   }
#endif

   if (circular_buffer_len > 0)
   {
      PORTL = circular_buffer[ circular_buffer_tail ];
      
      circular_buffer_tail = (circular_buffer_tail + 1) & MASK_CIRCULAR_BUFFER; 
      circular_buffer_len --;
   }
    
}
