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
#define  DAC_SHUT_DOWN        40
#define  NOMEFILE  "datalog.txt"

#define  MOT1A                10
#define  MOT1B                11
#define  MOT2A                12
#define  MOT2B                13

#define  MOT3A                2
#define  MOT3B                3
#define  MOT4A                4
#define  MOT4B                5

#define  MOT5A                28
#define  MOT5B                26
#define  MOT6A                24
#define  MOT6B                22

#define  SENS0                A0
#define  SENS1                A1
#define  SENS2                A2
#define  SENS3                A3
#define  SENS4                A4
#define  SENS5                A5
#define  SENS6                A6
#define  SENS7                A7
#define  SENS8                A8
#define  SENS9                A9
#define  SENS10               A10
#define  SENS11               A11
#define  SENS12               A12
#define  SENS13               A13
#define  SENS14               A14
#define  SENS15               A15


volatile signed int vel_mot1;       /* velocita va da -100 a +100 */


#define SIZE_CIRCULAR_BUFFER 64
#define MASK_CIRCULAR_BUFFER 0x3F

volatile unsigned char circular_buffer[ SIZE_CIRCULAR_BUFFER ];
volatile unsigned char circular_buffer_head, circular_buffer_tail, circular_buffer_len;

void mio_delay(int msec);
void play_something(char * nomefile);


void setup() {
  /* Open serial communications and wait for port to open: */
  Serial.begin(115200);
  
  while (!Serial) {
    /* wait for serial port to connect. Needed for native USB port only */
    /* do nothing */;    
  }

#if FALSE
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(CSPIN)) {
    
    Serial.println("Card failed, or not present");
    while (1); 
    
  }
  
  Serial.println("card initialized.");
#endif

  /* inizializzazione buffer circolare */
  circular_buffer_head = 0;
  circular_buffer_tail = 0;
  circular_buffer_len  = 0;

  /* impostazione Timer 3 per dare 
   * un interrupt a 8ksps ogni 125 uSec
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

  pinMode(DAC_SHUT_DOWN, OUTPUT); /* ABILITAZIONE AMPLIFICATORE ATTIVO BASSO */ 
  digitalWrite( DAC_SHUT_DOWN, LOW );
  
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

  //play_something( "audio/track001.raw" );
  //play_something( "audio/track002.raw" );

  pinMode(MOT1A, OUTPUT); 
  pinMode(MOT1B, OUTPUT); 
  digitalWrite( MOT1A, HIGH );
  digitalWrite( MOT1B, HIGH );
  vel_mot1 = 50;
  
}

void loop() {

  static unsigned long t1 = millis(), t2;
  static int inversione = 1;
  static int passi = 0, stato = 0;

  /*
   
   Serial.print ( "0," );
   Serial.print ( analogRead( SENS0 ) );
   Serial.print ( "," );
   Serial.println ( analogRead( SENS1 ) );
  
  */

  /*
   CALCOLO RPM
   
  while ( digitalRead(SENS15) == 0 ) /* do nothing * /;

  t2 = 60000000UL / (micros() - t1);
  t1 = micros();

  while ( digitalRead(SENS15) == 1 ) /* do nothing * /;

  Serial.println ( t2 );
  */

  /* 
   *  CONTEGGIO PASSI
   *  
   */
   switch( stato )
   {

//  stato   0   1   2   3   0 
//   14     0   1   1   0   0
//   15     0   0   1   1   0

    case 0: 
      if ( digitalRead(SENS14) == 1) { stato = 1; }
      if ( digitalRead(SENS15) == 1) { stato = 3; }
      break;    
       
    case 1: 
      if ( digitalRead(SENS14) == 0) { stato = 0; passi --; }
      if ( digitalRead(SENS15) == 1) { stato = 2; }
      break;    
    
    case 2: 
      if ( digitalRead(SENS14) == 0) { stato = 3; }
      if ( digitalRead(SENS15) == 0) { stato = 1; }
      break;    

    case 3: 
      if ( digitalRead(SENS14) == 1) { stato = 2; }
      if ( digitalRead(SENS15) == 0) { stato = 0; passi++; }
      break;    
    
   }

   t2 = (millis() - t1);
   if (t2 >= 100) 
   {
     t1 = millis();
     Serial.println ( passi );

     inversione --; 
     if (inversione <= 0) 
     {
       if (vel_mot1 == 50) 
         { vel_mot1 = -50; }
       else 
         { vel_mot1 = 50; }
     
       inversione = 100;
     }
   }

}

void loop1() {

  Serial.println("Motore Avanti");

  vel_mot1 = 30;

  while (vel_mot1 < 80) {
    mio_delay(50);
    vel_mot1 ++;
  }

  mio_delay(2000);

  while (vel_mot1 > 30) {
    mio_delay(50);
    vel_mot1 --;
  }

  vel_mot1 = 0;
  mio_delay(2000);


  Serial.println("Motore Indietro");

  vel_mot1 = -30;

  while (vel_mot1 > -80) {
    mio_delay(50);
    vel_mot1 --;
  }

  mio_delay(2000);

  while (vel_mot1 < -30) {
    mio_delay(50);
    vel_mot1 ++;
  }
  
  vel_mot1 = 0;
  mio_delay(2000);

}

void mio_delay(int msec)
{
  unsigned long t;

  t = millis() + msec;
  while (millis() < t) { /* do_nothing */ } 

}

void play_something( const char * nomefile )
{
  /* open the file. note that only one file can be open at a time,
   * so you have to close this one before opening another.
   */
  File dataFile = SD.open( nomefile );
  int c;

  if (dataFile) {

    digitalWrite( DAC_SHUT_DOWN, HIGH );
  
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

    digitalWrite( DAC_SHUT_DOWN, LOW );
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

/* TIMER 3 COMPARE MATCH INTERRUPT OGNI 125 uSEC = 8 Ksps */
ISR(TIMER5_COMPA_vect) {
  static int contatore_pwm = 0;
  
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

   /* GESTIONE DAC */
   if (circular_buffer_len > 0)
   {
      PORTL = circular_buffer[ circular_buffer_tail ];
      
      circular_buffer_tail = (circular_buffer_tail + 1) & MASK_CIRCULAR_BUFFER; 
      circular_buffer_len --;
   }

   /* GESTIONE PWM MOTORI */
   contatore_pwm++; if (contatore_pwm >= 100) { contatore_pwm = 0; }
   if (vel_mot1 > 0)
   {
     /* il motore deve girare in avanti - orario */
     digitalWrite( MOT1A, ((vel_mot1 >= contatore_pwm)?(LOW):(HIGH)) );
     digitalWrite( MOT1B, HIGH );
   }
   else if (vel_mot1 < 0)
   {
     /* il motore deve girare indietro - antiorario*/
     digitalWrite( MOT1A, HIGH );
     digitalWrite( MOT1B, ((abs(vel_mot1) >= contatore_pwm)?(LOW):(HIGH)) );
   }
   else
   {
     /* il motore deve stare fermo */
     digitalWrite( MOT1A, HIGH );
     digitalWrite( MOT1B, HIGH );
   }
      
}
