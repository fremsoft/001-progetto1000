/*
 * test dei potenziometri e dei pulsanti dei Joystick di Progetto 1000
 * 
 * Joystick di Sinistra             Joystick di destra
 *    VRx  A13 66=sx;1023=dx            VRx   A14 1023=sx;61=dx
 *    VRy  A12 66=av;1023=dietro        VRy   A15 1023=av;61=indietro
 *    Sw   A6  0=OFF; 1023=ON           Sw    A7  0=OFF; 1023=ON
 */


void setup() {
 
  Serial.begin ( 9600 );
  
}

void loop() {

  Serial.print("S6:");
  Serial.print(analogRead( A6 ));
  Serial.print(",S7:");
  Serial.print(analogRead( A7 ));
  Serial.print(",S12:");
  Serial.print(analogRead( A12 ));
  Serial.print(",S13:");
  Serial.print(analogRead( A13 ));
  Serial.print(",S14:");
  Serial.print(analogRead( A14 ));
  Serial.print(",S15:");
  Serial.println(analogRead( A15 ));
  


}
