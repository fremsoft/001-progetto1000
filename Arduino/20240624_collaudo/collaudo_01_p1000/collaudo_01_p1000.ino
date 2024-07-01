/*
  Collaudo del Robot P1000.

  Questo programma serve a collaudare tutte le funzionalità
  del robot P1000, una alla volta:

  * collaudo della SD-Card e DAC (sdcard.ino)
  * collaudo motori
  * collaudo sensori angolari dei polsi
  
  https://youtube.com/live/JlR_kjjwWjE

  Bologna, 24 giugno 2024
*/

#include "defs.h"

void setup() {

  // SERIALE DI SERVIZIO PER DEBUG
  Serial.begin(9600);
  
  while (!Serial) {
    /* wait for serial port to connect. Needed for native USB port only */
    /* do nothing */;    
  }

  setup_motori();
  setup_joystick();
  
  setup_sdcard();

  //play_something( "audio/track001.raw" );
  //play_something( "audio/track002.raw" );

}

void loop() {
  char s[100];
/*  
sprintf(s, "JOY-SX x:%d\ty:%d\tJOY-DX x:%d\ty:%d"
           , getJoystickSxX()
           , getJoystickSxY()
           , getJoystickDxX()
           , getJoystickDxY() );         
*/
/*
sprintf(s, "A0:%d  A1:%d  A2:%d  A3:%d  A4:%d  A5:%d"
           , analogRead(A0)
           , analogRead(A1)
           , analogRead(A2)
           , analogRead(A3)
           , analogRead(A4)
           , analogRead(A5) );
*/  
/*
sprintf(s, "SENS-SX:%d  SENS-DX:%d "
           , getRotazionePolsoSX()
           , getRotazionePolsoDX() );
*/
 //Serial.println(s);


  if (getJoystickDxX() > 500) {
    ruotaManoDx(DITO_CENTRALE_LONTANO);
  }
  else if (getJoystickDxX() < -500) {
    ruotaManoDx(DITO_CENTRALE_VICINO);
  }
  else if (getJoystickDxY() > 500) {
    ruotaManoDx(DITO_CENTRALE_ALTO);
  }
  else if (getJoystickDxY() < -500) {
    ruotaManoDx(DITO_CENTRALE_BASSO);
  }

  //setSpeedMotoreDxRotazione( getJoystickDxX() );
  setSpeedMotoreSxRotazione( getJoystickSxX() );
  
  setSpeedMotoreDxPresa( getJoystickDxY() );
  setSpeedMotoreSxPresa( getJoystickSxY() );

}
