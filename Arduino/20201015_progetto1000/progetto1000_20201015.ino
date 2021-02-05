/*
    Questo è il primo progetto del Canale YouTube "PROGETTI con Emanuele Frisoni"
    https://youtube.com/c/fremsoft
    
    Guarda la playlist relativa a questo progetto: 
    https://www.youtube.com/watch?v=VcB0eAnL97o&list=PLxAafib4pWc7LSfuXC9RSEif6I1dyx5FP

    Sondaggio per la determinazione delle specifiche di progetto:
    1) Arduino o Microchip PIC?  *** ARDUINO ***
    2) Encoder Ottico o Accelerometro? *** ENCODER OTTICO ***
    3) Costruzioni LEGO o Stampa 3D? *** STAMPA 3D ***
    4) Stand alone o Comandato? *** SIA STANDALONE CHE COMANDATO ***
    5) Muto o Sonoro? *** SONORO ***
    6) Cieco o con Telecamera? *** TELECAMERA ***
    7) Procedurale o Intelligenza Artificiale? *** A.I. ***
    
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(300);                        // wait for 300 millisecond
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(300);                        // wait for 300 millisecond
  
}
