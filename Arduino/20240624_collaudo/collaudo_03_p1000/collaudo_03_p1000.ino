/*
  Collaudo del Robot P1000.

  Questo programma serve a collaudare tutte le funzionalità
  del robot P1000, una alla volta:

  * collaudo della SD-Card e DAC (sdcard.ino)
  * collaudo motori
  * collaudo sensori angolari dei polsi
  * collaudo encoder apertura delle mani
  * se pigio il tasto del joystick DX apre la mano DX
  * se pigio il tasto del joystick SX apre la mano SX
  
  
  https://youtube.com/live/EF7QHxl3fxA

  Bologna, 08 luglio 2024
*/

#include "defs.h"

void setup() {

  // SERIALE DI SERVIZIO PER DEBUG
  Serial.begin(115200);
  
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

int regime=0;

void loop() {
  char s[100];
  int stato;
  unsigned long t;
  
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
/*
sprintf(s, "A8:%d,A9:%d,A10:%d,A11:%d"
           , digitalRead(A8)
           , digitalRead(A9)
           , digitalRead(A10)
           , digitalRead(A11) );
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

  //setSpeedMotoreDxPresa( getJoystickDxY() );
  //setSpeedMotoreSxPresa( getJoystickSxY() );

  // per favore uno alla volta!!!!!!
  if (joystickDxPressed()) {
    setSpeedMotoreDxPresa( 500 );
    regime = 0;
    delay(100);
  }
  if (joystickSxPressed()) {
    setSpeedMotoreSxPresa( -500 );
    regime = 0;
    delay(100);
  }

/*
  stato = encoder_presa_mano_DX();
  if(stato >= 0) {
    t = millis();
    sprintf(s, "stato:%d,t:%ld"
           , stato
           , t );
    Serial.println(s);
  }
*/

  stato = encoder_presa_mano_DX();  // rinfresca anche il deltaT
  if (regime < 3) {
    if(stato >= 0) {
      regime ++;
    }
  }
  else {
    t = deltaT_encoder_presa_mano_DX(); // si aggiorna il deltaT nella 'encoder_presa_mano_DX()'
    if (t > DELTA_T_BUCO_ENCODER) {
      setSpeedMotoreDxPresa( 0 );
    }
  }

  stato = encoder_presa_mano_SX();  // rinfresca anche il deltaT
  if (regime < 3) {
    if(stato >= 0) {
      regime ++;
    }
  }
  else {
    t = deltaT_encoder_presa_mano_SX(); // si aggiorna il deltaT nella 'encoder_presa_mano_SX()'
    if (t > DELTA_T_BUCO_ENCODER) {
      setSpeedMotoreSxPresa( 0 );
    }
  }

}
