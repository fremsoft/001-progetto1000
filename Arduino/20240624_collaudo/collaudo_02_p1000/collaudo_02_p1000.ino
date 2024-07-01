/*
  Collaudo del Robot P1000.

  Questo programma serve a collaudare tutte le funzionalità
  del robot P1000, una alla volta:

  * collaudo della SD-Card e DAC (sdcard.ino)
  * collaudo motori
  * collaudo sensori angolari dei polsi
  * collaudo encoder apertura delle mani
  
  https://youtube.com/live/C2Kz-iKF64s

  Bologna, 01 luglio 2024
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
  setup_sensori_angolari();
  setup_sensori_presa();
  
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
sprintf(s, "A4:%d,A2:%d,A5:%d,A1:%d,A3:%d,A0:%d"
           , analogRead(A4)
           , analogRead(A2)
           , analogRead(A5)
           , analogRead(A1)
           , analogRead(A3)
           , analogRead(A0) );
*/
/*
sprintf(s, "SENS-SX:%d  SENS-DX:%d "
           , getRotazionePolsoSX()
           , getRotazionePolsoDX() );
*/

sprintf(s, "A8:%d,A9:%d,A10:%d,A11:%d"
           , digitalRead(A8)
           , digitalRead(A9)
           , digitalRead(A10)
           , digitalRead(A11) );

Serial.println(s);


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

  if (getJoystickSxX() < -500) {
    ruotaManoSx(DITO_CENTRALE_LONTANO);
  }
  else if (getJoystickSxX() > 500) {
    ruotaManoSx(DITO_CENTRALE_VICINO);
  }
  else if (getJoystickSxY() > 500) {
    ruotaManoSx(DITO_CENTRALE_ALTO);
  }
  else if (getJoystickSxY() < -500) {
    ruotaManoSx(DITO_CENTRALE_BASSO);
  }


  //setSpeedMotoreDxRotazione( getJoystickDxX() );
  //setSpeedMotoreSxRotazione( getJoystickSxX() );
  
  setSpeedMotoreDxPresa( getJoystickDxY() );
  setSpeedMotoreSxPresa( getJoystickSxY() );

}
