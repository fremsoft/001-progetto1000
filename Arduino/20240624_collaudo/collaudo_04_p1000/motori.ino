/*
 * I motori del robot P1000 sono i seguenti:
 * 
 *  * MOT1 ( mano DX 1 ) 10-11
 *  * MOT2 ( mano DX 2 ) 12-23(in origine era 13)
 *  * MOT3 ( mano SX 1 )  2-3
 *  * MOT4 ( mano SX 2 )  4-5
 *  
 */

#include "defs.h"

int angolo_mano_dx, angolo_mano_sx;

void setup_motori() {

  Serial.println("Setup motori");
  analogWrite( MOT1A, 0 ); //pinMode ( MOT1A, OUTPUT ); digitalWrite( MOT1A, LOW );
  analogWrite( MOT1B, 0 ); //pinMode ( MOT1B, OUTPUT ); digitalWrite( MOT1B, LOW );
  analogWrite( MOT2A, 0 );//pinMode ( MOT2A, OUTPUT ); digitalWrite( MOT2A, LOW );
  pinMode ( MOT2B, OUTPUT ); digitalWrite( MOT2B, LOW );
  analogWrite( MOT3A, 0 ); //pinMode ( MOT3A, OUTPUT ); digitalWrite( MOT3A, LOW );
  analogWrite( MOT3B, 0 ); //pinMode ( MOT3B, OUTPUT ); digitalWrite( MOT3B, LOW );
  analogWrite( MOT4A, 0 ); //pinMode ( MOT4A, OUTPUT ); digitalWrite( MOT4A, LOW );
  analogWrite( MOT4B, 0 ); //pinMode ( MOT4B, OUTPUT ); digitalWrite( MOT4B, LOW );
  
  angolo_mano_dx = 0;
  angolo_mano_sx = 0;

}

/* il range di velocità va da -1000 a +1000 */
void setSpeedMotoreDxPresa( int speed1000 ) {

  if (speed1000 > 50) {
    analogWrite( MOT1A, map(speed1000, 0, 1000, 50, 255));
    analogWrite( MOT1B, 0 );
  }
  else if (speed1000 < -50) {
    analogWrite( MOT1A, 0 );
    analogWrite( MOT1B, map(speed1000, 0, -1000, 50, 255));
  }
  else {
    analogWrite( MOT1A, 0 );
    analogWrite( MOT1B, 0 );
  }
}

/* il range di velocità va da -1000 a +1000          */
/* valori positivi devono far girare                 */
/* la faccia del cubo in senso orario                */
void setSpeedMotoreDxRotazione( int speed1000 ) {
  // commentare la definizione sbagliata
  
  //const int m1=MOT2A, m2=MOT2B; 
  const int m1=MOT2B, m2=MOT2A;
  
  if (speed1000 > 50) {
    digitalWrite( m1, 1 ); /* analogWrite( m1, map... ); su pin 23 non c'è PWM */
    analogWrite( m2, 255 - map(speed1000, 0, 1000, 50, 255) ); 
  }
  else if (speed1000 < -50) {
    digitalWrite( m1, 0 ); /* analogWrite( m1, 0 );   su pin 23 non c'è PWM */
    analogWrite( m2, map(speed1000, 0, -1000, 50, 255) ); 
  }
  else {
    digitalWrite( m1, 0 ); /* analogWrite( m2, 0 );  su pin 23 non c'è PWM */
    analogWrite( m2, 0 ); 
  }
}

/* il range di velocità va da -1000 a +1000 */
void setSpeedMotoreSxPresa( int speed1000 ) {

  if (speed1000 > 50) {
    analogWrite( MOT3A, map(speed1000, 0, 1000, 50, 255));
    analogWrite( MOT3B, 0 );
  }
  else if (speed1000 < -50) {
    analogWrite( MOT3A, 0 );
    analogWrite( MOT3B, map(speed1000, 0, -1000, 50, 255));
  }
  else {
    analogWrite( MOT3A, 0 );
    analogWrite( MOT3B, 0 );
  }
}

/* il range di velocità va da -1000 a +1000          */
/* valori positivi devono far girare                 */
/* la faccia del cubo in senso orario                */
void setSpeedMotoreSxRotazione( int speed1000 ) {
  // commentare la definizione sbagliata
  
  //const int m1=MOT4A, m2=MOT4B; 
  const int m1=MOT4B, m2=MOT4A;
  
  if (speed1000 > 50) {
    analogWrite( m1, map(speed1000, 0, 1000, 50, 255));
    analogWrite( m2, 0 );
  }
  else if (speed1000 < -50) {
    analogWrite( m1, 0 );
    analogWrite( m2, map(speed1000, 0, -1000, 50, 255));
  }
  else {
    analogWrite( m1, 0 );
    analogWrite( m2, 0 );
  }
}

void ruotaManoDx(int destinazione) {
  int speed;
  unsigned long t0, t1;
  
  if (angolo_mano_dx != destinazione) {

    if ((angolo_mano_dx == DITO_CENTRALE_ALTO) && (destinazione == DITO_CENTRALE_VICINO)) {
      speed = -500;
    } else 
    if ((angolo_mano_dx == DITO_CENTRALE_LONTANO) && (destinazione == DITO_CENTRALE_ALTO)) {
      speed = -500;
    } else 
    if ((angolo_mano_dx == DITO_CENTRALE_BASSO) && (destinazione == DITO_CENTRALE_LONTANO)) {
      speed = -500;
    } else 
    if ((angolo_mano_dx == DITO_CENTRALE_VICINO) && (destinazione == DITO_CENTRALE_BASSO)) {
      speed = -500;
    } else {
      speed = 500;
    }
    setSpeedMotoreDxRotazione( speed );

    while (getRotazionePolsoDX() != 0) /* do nothing */;
    delay(50);

    while (getRotazionePolsoDX() != destinazione) /* do nothing */;
    t0 = millis();
    setSpeedMotoreDxRotazione( 0 );
    delay(100);

    while (getRotazionePolsoDX() != destinazione) {
      t1 = millis();
      setSpeedMotoreDxRotazione( 
        constrain( 
          map(t1 - t0, 0, 1000, 0, -speed/3)
          ,-500 ,500) 
      );
    }
    setSpeedMotoreDxRotazione( 0 );

    angolo_mano_dx = destinazione;
  }
}

void ruotaManoSx(int destinazione) {
  int speed;
  unsigned long t0, t1;
  
  if (angolo_mano_sx != destinazione) {

    if ((angolo_mano_sx == DITO_CENTRALE_ALTO) && (destinazione == DITO_CENTRALE_LONTANO)) {
      speed = -500;
    } else 
    if ((angolo_mano_sx == DITO_CENTRALE_LONTANO) && (destinazione == DITO_CENTRALE_BASSO)) {
      speed = -500;
    } else 
    if ((angolo_mano_sx == DITO_CENTRALE_BASSO) && (destinazione == DITO_CENTRALE_VICINO)) {
      speed = -500;
    } else 
    if ((angolo_mano_sx == DITO_CENTRALE_VICINO) && (destinazione == DITO_CENTRALE_ALTO)) {
      speed = -500;
    } else {
      speed = 500;
    }
    setSpeedMotoreSxRotazione( speed );

    while (getRotazionePolsoSX() != 0) /* do nothing */;
    delay(50);

    while (getRotazionePolsoSX() != destinazione) /* do nothing */;
    t0 = millis();
    setSpeedMotoreSxRotazione( 0 );
    delay(100);

    while (getRotazionePolsoSX() != destinazione) {
      t1 = millis();
      setSpeedMotoreSxRotazione( 
        constrain( 
          map(t1 - t0, 0, 1000, 0, -speed/3)
          ,-500 ,500) 
      );
    }
    setSpeedMotoreSxRotazione( 0 );

    angolo_mano_sx = destinazione;
  }
}

void apriManoDx() {
  //setSpeedMotoreDxPresa( getJoystickDxY() );

}
void chiudiManoDx() {
  //setSpeedMotoreDxPresa( getJoystickDxY() );
    
}

void apriManoSx() {
  //setSpeedMotoreSxPresa( getJoystickSxY() );
    
}
void chiudiManoSx() {
  //setSpeedMotoreSxPresa( getJoystickSxY() );
    
}




