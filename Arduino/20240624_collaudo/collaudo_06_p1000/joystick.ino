/*
 * Gestione dei due Joystick analogici collegati su :
 *    Joystick di Sinistra              Joystick di destra
 *    VRx  A13 66=sx;1023=dx            VRx   A14 1023=sx;61=dx
 *    VRy  A12 66=av;1023=dietro        VRy   A15 1023=av;61=indietro
 *    Sw   A6  0=OFF; 1023=ON           Sw    A7  0=OFF; 1023=ON
 * 
 */

void setup_joystick() {
  /* do nothing */ 
}

int getJoystickSxX() {
  return constrain(map( analogRead(A13), 66, 1023, -1000, 1000) , -1000, 1000);
}

int getJoystickSxY() {
  return constrain(map( analogRead(A12), 1023, 66, -1000, 1000) , -1000, 1000);
}
  
int getJoystickDxX() {
  return constrain(map( analogRead(A14), 1023, 61, -1000, 1000) , -1000, 1000);
} 

int getJoystickDxY() {
  return constrain(map( analogRead(A15), 61, 1023, -1000, 1000) , -1000, 1000);
} 

bool joystickSxPressed() {
  return (analogRead( A6 ) > 500);
}

bool joystickDxPressed() {
  return (analogRead( A7 ) > 500);
}
