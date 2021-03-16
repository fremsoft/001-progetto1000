/*
  SD card file dump

  This example shows how to read a file from the SD card using the
  SD library and send it over the serial port.

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11 (UNO) / 51 (MEGA)
 ** MISO - pin 12 (UNO) / 50 (MEGA)
 ** CLK -  pin 13 (UNO) / 52 (MEGA)
 ** CS -   pin 10 (UNO) / 53 (MEGA)  [(for MKRZero SD: SDCARD_SS_PIN)]

  Appunti:
 ** https://www.arduino.cc/en/Hacking/PinMapping2560
 ** https://www.arduino.cc/en/reference/SPI
 ** https://www.arduino.cc/en/reference/SD
   
  created  22 December 2010
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe

  riadattato il 17 Dicembre 2020
  per Progetto1000 da Emanuele Frisoni
  
  Guarda il video: https://www.youtube.com/watch?v=E36JJB-z9BE

  This example code is in the public domain.
*/

#include <SPI.h>
#include <SD.h>

#define  CSPIN                53    /* per Arduino Mega il default è 53 */
#define  NOMEFILE  "datalog.txt"


void setup() {
  /* Open serial communications and wait for port to open: */
  Serial.begin(9600);
  
  while (!Serial) {
    /* wait for serial port to connect. Needed for native USB port only */
    /* do nothing */;    
  }

  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(CSPIN)) {
    
    Serial.println("Card failed, or not present");
    
  }
  else
  {
    Serial.println("card initialized.");

    /* open the file. note that only one file can be open at a time,
     * so you have to close this one before opening another.
     */
    File dataFile = SD.open( NOMEFILE );

    if (dataFile) {

      /* if the file is present, send its content on the serial line for debug */
      while (dataFile.available()) { Serial.write(dataFile.read()); }

      /* close file when finished */
      dataFile.close();
    }
    else {

      /* if the file isn't open, pop up an error: */
      Serial.println("error opening " NOMEFILE );
      
    }
  }
}

void loop() {

  /* do nothing */

}
