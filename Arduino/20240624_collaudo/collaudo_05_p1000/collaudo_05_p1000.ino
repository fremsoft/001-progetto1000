/*
  Collaudo del Robot P1000.

  Questo programma serve a collaudare tutte le funzionalità
  del robot P1000, una alla volta:

  * collaudo della SD-Card e DAC (sdcard.ino)
  * collaudo motori
  * collaudo sensori angolari dei polsi
  * collaudo encoder apertura delle mani
  * all'accensione la mano DX, poi apre la mano SX  
  * gestione dei sensori degli encoder a interrupt
    con https://github.com/NicoHood/PinChangeInterrupt v1.2.9
  
  https://youtube.com/live/fq-8lViOZlg
  
  Bologna, 15 luglio 2024
*/

#include "defs.h"

enum STATI_MACCHINA {
  ST_RESET = 0,
  ST_CERCA_APERTURA_MANO_DX,
  ST_MANO_DX_APERTA,
  ST_CERCA_APERTURA_MANO_SX,
  ST_MANO_SX_APERTA,
  ST_APRI_CHIUDI
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

sprintf(s, "DX=%d; SX=%d, r=%d, s=%d"
           , get_corsa_mano_DX()
           , get_corsa_mano_SX()
           , regime, stato_macchina
          );
  Serial.println(s);


  switch (stato_macchina) {

    case ST_RESET:
      setSpeedMotoreDxPresa(500);
      regime = 0;
      stato = get_corsa_mano_DX(); 
      delay(100);
      stato_macchina = ST_CERCA_APERTURA_MANO_DX;
      break;

    case ST_CERCA_APERTURA_MANO_DX:
      if (regime < 3) {
        if (stato != get_corsa_mano_DX()) {
          //ogni volta che c'è un cambio di stato nell'encoder
          regime++;
          stato = get_corsa_mano_DX();
        }
      } else {
        t = deltaT_encoder_presa_mano_DX();  // si aggiorna ad interrupt
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
      stato = get_corsa_mano_SX();
      delay(100);
      stato_macchina = ST_CERCA_APERTURA_MANO_SX;
      break;

    case ST_CERCA_APERTURA_MANO_SX:
      if (regime < 3) {
        if (stato != get_corsa_mano_SX()) {
          //ogni volta che c'è un cambio di stato nell'encoder
          regime++;
          stato = get_corsa_mano_SX();
        }
      } else {
        t = deltaT_encoder_presa_mano_SX();  // si aggiorna ad interrupt
        if (t > DELTA_T_BUCO_ENCODER) {
          // la mano SX ora è aperta
          setSpeedMotoreSxPresa(0);
          stato_macchina = ST_MANO_SX_APERTA;
        }
      }

    case ST_MANO_SX_APERTA:
      /* do something more */
      setSpeedMotoreDxPresa(0);
      setSpeedMotoreSxPresa(0);
      delay(100);
      azzera_corsa_mano_DX();
      azzera_corsa_mano_SX();
      stato_macchina = ST_APRI_CHIUDI;
      break;

    case ST_APRI_CHIUDI:
      if (joystickDxPressed()) {
        // apri e chiudi mano DX
        if (get_corsa_mano_DX() <= 0) {
          // la mano è aperta
          // la chiudiamo per afferrare il cubo
          setSpeedMotoreDxPresa(FORZA_CHIUSURA_MANO_DX);
          while (get_corsa_mano_DX() <= 0) /* wait */;
          do {
            t = deltaT_encoder_presa_mano_DX();  // si aggiorna ad interrupt
          } while (t < DELTA_T_BUCO_ENCODER);
          // la mano ha afferrato qualcosa (o è arrivata al buco)
          setSpeedMotoreDxPresa(0);   
        }
        else {
          // la mano sta afferrrando il cubo
          // la apriamo per mollare il cubo
          stato = get_corsa_mano_DX();
          setSpeedMotoreDxPresa(FORZA_APERTURA_MANO_DX);
          while (get_corsa_mano_DX() == stato) /* wait */;
          do {
            t = deltaT_encoder_presa_mano_DX();  // si aggiorna ad interrupt
          } while (t < DELTA_T_BUCO_ENCODER);
          // la mano ha afferrato qualcosa (o è arrivata al buco)
          setSpeedMotoreDxPresa(0);   
        }
      }

      if (joystickSxPressed()) {
        // apri e chiudi mano SX
        if (get_corsa_mano_SX() <= 0) {
          // la mano è aperta
          // la chiudiamo per afferrare il cubo
          setSpeedMotoreSxPresa(FORZA_CHIUSURA_MANO_SX);
          while (get_corsa_mano_SX() <= 0) /* wait */;
          do {
            t = deltaT_encoder_presa_mano_SX();  // si aggiorna ad interrupt
          } while (t < DELTA_T_BUCO_ENCODER);
          // la mano ha afferrato qualcosa (o è arrivata al buco)
          setSpeedMotoreSxPresa(0);   
        }
        else {
          // la mano sta afferrrando il cubo
          // la apriamo per mollare il cubo
          stato = get_corsa_mano_SX();
          setSpeedMotoreSxPresa(FORZA_APERTURA_MANO_SX);
          while (get_corsa_mano_SX() == stato) /* wait */;
          do {
            t = deltaT_encoder_presa_mano_SX();  // si aggiorna ad interrupt
          } while (t < DELTA_T_BUCO_ENCODER);
          // la mano ha afferrato qualcosa (o è arrivata al buco)
          setSpeedMotoreSxPresa(0);   
        }
      }
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
