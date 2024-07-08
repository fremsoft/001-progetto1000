/*
  Collaudo del Robot P1000.

  Questo programma serve a collaudare tutte le funzionalità
  del robot P1000, una alla volta:

  * collaudo della SD-Card e DAC (sdcard.ino)
  * collaudo motori
  * collaudo sensori angolari dei polsi
  * collaudo encoder apertura delle mani
  * all'accensione la mano DX, poi apre la mano SX  
  
  https://youtube.com/live/EF7QHxl3fxA

  Bologna, 08 luglio 2024
*/

#include "defs.h"

enum STATI_MACCHINA {
  ST_RESET = 0,
  ST_CERCA_APERTURA_MANO_DX,
  ST_MANO_DX_APERTA,
  ST_CERCA_APERTURA_MANO_SX,
  ST_MANO_SX_APERTA
} stato_macchina;

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

  stato_macchina = ST_RESET;
}

int regime = 0;

void loop() {
  char s[100];
  int stato;
  unsigned long t;

   
sprintf(s, "JOY-SX x:%d\ty:%d\tJOY-DX x:%d\ty:%d"
           , getJoystickSxX()
           , getJoystickSxY()
           , getJoystickDxX()
           , getJoystickDxY() );         

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
  Serial.println(s);



  switch (stato_macchina) {

    case ST_RESET:
      setSpeedMotoreDxPresa(500);
      regime = 0;
      delay(100);
      stato_macchina = ST_CERCA_APERTURA_MANO_DX;
      break;

    case ST_CERCA_APERTURA_MANO_DX:
      stato = encoder_presa_mano_DX();  // rinfresca anche il deltaT
      if (regime < 3) {
        if (stato >= 0) {
          //ogni volta che c'è un cambio di stato nell'encoder
          regime++;
        }
      } else {
        t = deltaT_encoder_presa_mano_DX();  // si aggiorna il deltaT nella 'encoder_presa_mano_DX()'
        if (t > DELTA_T_BUCO_ENCODER) {
          // la mano DX ora è aperta
          setSpeedMotoreDxPresa(0);
          stato_macchina = ST_MANO_DX_APERTA;
        }
      }
      break;

    case ST_MANO_DX_APERTA:
      setSpeedMotoreSxPresa(-500);
      regime = 0;
      delay(100);
      stato_macchina = ST_CERCA_APERTURA_MANO_SX;
      break;

    case ST_CERCA_APERTURA_MANO_SX:
      stato = encoder_presa_mano_SX();  // rinfresca anche il deltaT
      if (regime < 3) {
        if (stato >= 0) {
          //ogni volta che c'è un cambio di stato nell'encoder
          regime++;
        }
      } else {
        t = deltaT_encoder_presa_mano_SX();  // si aggiorna il deltaT nella 'encoder_presa_mano_SX()'
        if (t > DELTA_T_BUCO_ENCODER) {
          // la mano SX ora è aperta
          setSpeedMotoreSxPresa(0);
          stato_macchina = ST_MANO_SX_APERTA;
        }
      }

    case ST_MANO_SX_APERTA:
      /* do something more */
      break;

    default:
      /*
      if (getJoystickDxX() > 500) {
        ruotaManoDx(DITO_CENTRALE_LONTANO);
      } else if (getJoystickDxX() < -500) {
        ruotaManoDx(DITO_CENTRALE_VICINO);
      } else if (getJoystickDxY() > 500) {
        ruotaManoDx(DITO_CENTRALE_ALTO);
      } else if (getJoystickDxY() < -500) {
        ruotaManoDx(DITO_CENTRALE_BASSO);
      }

      if (getJoystickSxX() < -500) {
        ruotaManoSx(DITO_CENTRALE_LONTANO);
      } else if (getJoystickSxX() > 500) {
        ruotaManoSx(DITO_CENTRALE_VICINO);
      } else if (getJoystickSxY() > 500) {
        ruotaManoSx(DITO_CENTRALE_ALTO);
      } else if (getJoystickSxY() < -500) {
        ruotaManoSx(DITO_CENTRALE_BASSO);
      }
      */
      break;
  }
}
