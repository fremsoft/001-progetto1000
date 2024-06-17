/*
  Collaudo del Robot P1000.

  Questo programma serve a collaudare tutte le funzionalità
  del robot P1000, una alla volta:

  * collaudo della SD-Card e DAC (sdcard.ino)

  https://youtube.com/live/nMA3yiVMv60
  https://youtube.com/live/GfSpqhEhOXs
  
  Bologna, 09 febbraio 2023
*/

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
  sprintf(s, "JOY-SX x:%d\ty:%d\tJOY-DX x:%d\ty:%d"
           , getJoystickSxX()
           , getJoystickSxY()
           , getJoystickDxX()
           , getJoystickDxY() );
           
            
  Serial.println(s);

  setSpeedMotoreDxRotazione( getJoystickDxX() );
  setSpeedMotoreSxRotazione( getJoystickSxX() );
  
  setSpeedMotoreDxPresa( getJoystickDxY() );
  setSpeedMotoreSxPresa( getJoystickSxY() );

}
