/*
 * I motori del robot P1000 sono i seguenti:
 * 
 *  * MOT1 ( mano DX 1 ) 10-11
 *  * MOT2 ( mano DX 2 ) 12-23(in origine era 13)
 *  * MOT3 ( mano SX 1 )  2-3
 *  * MOT4 ( mano SX 2 )  4-5
 *  
 */

// MOTORI MANO DX
#define MOT1A 10
#define MOT1B 11
#define MOT2A 12
#define MOT2B 23    // in origine era 13

// MOTORI MANO SX
#define MOT3A 2
#define MOT3B 3
#define MOT4A 4
#define MOT4B 5

void setup_motori() {

  Serial.println("Setup motori");
  pinMode ( MOT1A, OUTPUT ); digitalWrite( MOT1A, LOW );
  pinMode ( MOT1B, OUTPUT ); digitalWrite( MOT1B, LOW );
  pinMode ( MOT2A, OUTPUT ); digitalWrite( MOT2A, LOW );
  pinMode ( MOT2B, OUTPUT ); digitalWrite( MOT2B, LOW );
  pinMode ( MOT3A, OUTPUT ); digitalWrite( MOT3A, LOW );
  pinMode ( MOT3B, OUTPUT ); digitalWrite( MOT3B, LOW );
  pinMode ( MOT4A, OUTPUT ); digitalWrite( MOT4A, LOW );
  pinMode ( MOT4B, OUTPUT ); digitalWrite( MOT4B, LOW );
  
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
/* valori positivi devono far girare in senso orario */
/* guardando la faccia del cubo                      */
void setSpeedMotoreDxRotazione( int speed1000 ) {
  // commentare la definizione sbagliata
  
  //const int m1=MOT2A, m2=MOT2B; 
  const int m1=MOT2B, m2=MOT2A;
  
  if (speed1000 > 50) {
    analogWrite( m1, map(speed1000, 0, 1000, 50, 255) );
    digitalWrite( m2, 0 ); /* analogWrite( m2, 0 ); su pin 23 non c'è PWM */
  }
  else if (speed1000 < -50) {
    analogWrite( m1, 255 - map(speed1000, 0, -1000, 50, 255) ); /* analogWrite( m1, 0 );   su pin 23 non c'è PWM */
    digitalWrite( m2, 1 ); /* analogWrite( m2, map(speed1000, 0, -1000, 50, 255));  su pin 23 non c'è PWM */
  }
  else {
    analogWrite( m1, 0 );
    digitalWrite( m2, 0 ); /* analogWrite( m2, 0 );  su pin 23 non c'è PWM */
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
/* valori positivi devono far girare in senso orario */
/* guardando la faccia del cubo                      */
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
