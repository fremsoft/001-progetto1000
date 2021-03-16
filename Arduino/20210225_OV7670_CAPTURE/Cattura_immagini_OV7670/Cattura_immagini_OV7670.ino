/* Programma per il test della comunicazione I2C con 
 *  la Chip Camera OV7670. Proviamo anche a estrarre
 *  delle immagini dal bus dati, ma quello che otteniamo
 *  non è ancora accettabile!
 *  Il programma è scritto per Arduino Mega e OV7670.
 *
 *  Guarda i video: 
 *         https://www.youtube.com/watch?v=s_XzfoMg6WQ
 *         https://www.youtube.com/watch?v=J6CuJaAFM8s
 *
 *  21-02-2021 - Emanuele Frisoni
 *
 *
 *  INCLUDO LA LIBRERIA WIRE.H CHE SERVE AD UTILIZZARE 
 *  IL CANALE DI COMUNICAZIONE I2C SU PIN 20 e 21 SU
 *  ARDUINO MEGA
 */
#include <Wire.h>

/*  INDIRIZZO DELLA CHIP CAMERA OV7670 */
#define SCCB_ADDRESS  0x21

void setup() {
  int i;
  
  // CONFIGURA OUTPUT COMPARE OC4A
  // SUL PIN NUMERO 6 PER GENERARE 
  // UN CLOCK A frequenza = 8 MHz
  pinMode(6, OUTPUT);
  TCCR4A = 0x40;
  TCCR4B = 0x09;
  OCR4A = 0;

  // CONFIGURO I PIN 7-8-9 COME INGRESSI
  pinMode(7, INPUT);  //PCLK - PH4
  pinMode(8, INPUT);  //HREF - PH5
  pinMode(9, INPUT);  //VREF - PH6
    
  // PORT-L PINS per Debug
  pinMode(42, OUTPUT); /* PORT - L7 - Most Significant bit */ 
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT); /* PORT - L0 - Least Significant bit*/ 
  PORTL = 0;
 
  /* Start using I2C on Arduino Mega Pins 20(SDA) 21(SCL) */
  Wire.begin();

  Serial.begin(9600);
  while (!Serial); // Leonardo: wait for serial monitor
  
  Serial.println("\nLETTURA REGISTRI OV7670");
  for (i = 0; i <= 0xCF; i++ ) { read_reg( i ); }

  Serial.println("\nPROGRAMMAZIONE MODALITA' QQCIF");
  if(true) {
    /* QQCIF 352 x 288 7,5fps
       2,5Hz 
       371 mSec             72 righe 
       324 uSec / 1.87uS    88 
    */
    write_reg( 0x11, 0x01 );
    write_reg( 0x12, 0x00 );
    write_reg( 0x0C, 0x0C );
    write_reg( 0x3E, 0x12 );
    write_reg( 0x70, 0x3A );
    write_reg( 0x71, 0x35 );
    write_reg( 0x72, 0x22 );
    write_reg( 0x73, 0xF2 );
    write_reg( 0xA2, 0x2A );
    
    // RGB-565
    write_reg( 0x12, 0x04 );
    write_reg( 0x40, 0xD0 );

    // FEREZE AGC
    write_reg( 0x14, read_reg( 0x14 ) | 0x01 );
  }

  if(false) {
    /* QQVGA 160px x 480 */
    write_reg( 0x11, 0x01 );
    write_reg( 0x12, 0x00 );
    write_reg( 0x0C, 0x04 );
    write_reg( 0x3E, 0x1A );
    write_reg( 0x70, 0x3A );
    write_reg( 0x71, 0x35 );
    write_reg( 0x72, 0x22 );
    write_reg( 0x73, 0xF2 );
    write_reg( 0xA2, 0x02 );
  }

  if(false) {
    /* 36px x 60 */
    write_reg( 0x11, 0x01 );
    write_reg( 0x12, 0x04 );
    write_reg( 0x0C, 0x04 );
    write_reg( 0x3E, 0x1C );
    write_reg( 0x70, 0x3A );
    write_reg( 0x71, 0x35 );
    write_reg( 0x72, 0x33 );
    write_reg( 0x73, 0xF3 );
    write_reg( 0xA2, 0x02 );
    write_reg( 0x40, 0xD0 );
  }
}

void loop() {
  
  unsigned int px1, px2, pixel;
  int n_riga;
  int n_pixel;

  int r = 36;
  int c = 40;

  // 7 PCLK - PH4  0001 0000  0x10
  // 8 HREF - PH5  0010 0000  0x20
  // 9 VREF - PH6  0100 0000  0x40

  Serial.println( "<html><body><table>");

  for (r=0; r< 70; r++) {
    
    Serial.println( "<tr>");

    for (c=0; c<82; c++) {

      n_riga = 0;
      // ASPETTO CHE V-SYNC VADA BASSO
      while ( (PINH & 0x40) != 0 ) { /* do nothing */ }
    
      // ASPETTO CHE H-SYNC VADA ALTO
      while ( (PINH & 0x60) == 0 ) { /* do nothing */ }

      // CICLA FINCHE' V-SYNC E' BASSO
      while ( (PINH & 0x40) == 0 ) 
      {               
        // CONTO QUANTE RIGHE CI SONO IN UNA SCHERMATA
        n_riga ++;
        n_pixel = 0;
        
        // INIZIA LA PRIMA RIGA
        while ( (PINH & 0x20) != 0 ) { 
    
          // ATTENDO PRIMO FRONTE POSITIVO DI P-CLK
          while ( (PINH & 0x10) == 0 ) { /* do nothing */ }
    
          // HO INDIVIDUATO UN FRONTE POSITIVO
          // CAMPIONO IL 1' BYTE  
          // DEBUG: PORTL = 0x80;  
          px1 = PINC;  // PARTE ALTA DI RGB-565 (R5-G3M)
          // DEBUG: PORTL = 0x00;
    
          // ATTENDO FRONTE NEGATIVO DI P-CLK
          while ( (PINH & 0x10) != 0 ) { /* do nothing */ }
    
          // ATTENDO SECONDO FRONTE POSITIVO DI P-CLK
          while ( (PINH & 0x10) == 0 ) { /* do nothing */ }
    
          // HO INDIVIDUATO IL SECONDO FRONTE POSITIVO
          // CAMPIONO IL 2' BYTE
          px2 = PINC;  // PARTE BASSA DI RGB-565 (G3L-B5)
          
          n_pixel ++ ;
    
          if (n_riga == r) {
    
             if (n_pixel == c) {
         
                pixel = ( px1 << 8 ) | ( px2 );
                
             }
            
          }
          
          // ATTENDO FRONTE NEGATIVO DI P-CLK
          while ( (PINH & 0x10) == 0 ) { /* do nothing */ }
    
          // DOVREI AVERE ANCHE IL FRONTE NEGATIVO DI H-SYNC
        }
       
        while ( (PINH & 0x60) == 0 ) { /* do nothing */ }
      }

      if (true) {

        // SCRITTURA OUTPUT HTML        
        Serial.print( "<td style=\"width:4px; height:4px; font-size:1px; background: #");
        Serial.print((pixel >> 12) & 0xF, HEX); Serial.print((pixel >> 8) & 0xF, HEX);  
        Serial.print((pixel >> 7)  & 0xF, HEX); Serial.print((pixel >> 3) & 0xF, HEX);  
        Serial.print((pixel >> 1)  & 0xF, HEX); Serial.print((pixel << 3) & 0xF, HEX);  
        Serial.print( "\">&nbsp;</td>");

      }
      else {

        // SCRITTURA DEL SINGOLO PIXEL
        Serial.print("N. riga = ");
        Serial.print(r);
        Serial.print(", N. pixel = ");
        Serial.print(c);  
        Serial.print(", R = ");
        Serial.print((pixel >> 8) & 0xF8);  
        Serial.print(", G = ");
        Serial.print((pixel >> 3) & 0xFC);  
        Serial.print(", B = ");
        Serial.println((pixel << 3) & 0xF8); 
         
      }

    }
      
    Serial.println( "</tr>");
  }

  Serial.println( "</table></body></html>");
  
  while (1); /* ciclo infinito: ferma esecuzione */
  
}


/* 
 *  FUNZIONE PER LA LETTURA DI UN REGISTRO DELLA CHIP CAMERA OV7670
 */
byte read_reg(byte regNumber ) {
    byte val;

    // LETTURA DEL REGISTRO
    Wire.beginTransmission(SCCB_ADDRESS);
    Wire.write(regNumber);
    Wire.endTransmission();
  
    Wire.requestFrom((uint8_t)SCCB_ADDRESS, (uint8_t)1);
    val = Wire.read();

    // DEBUG:
    Serial.print("[");
    Serial.print(regNumber, HEX);
    Serial.print("] = ");
    Serial.println(val, HEX);

    return val;
}

/* 
 *  FUNZIONE PER LA SCRITTURA DI UN REGISTRO DELLA CHIP CAMERA OV7670
 */
void write_reg(byte regNumber, byte to_val ) {
    byte from_val;

    // LETTURA DEL REGISTRO PER MODALITA' VERBOSE
    Wire.beginTransmission(SCCB_ADDRESS);
    Wire.write(regNumber);
    Wire.endTransmission();
  
    Wire.requestFrom((uint8_t)SCCB_ADDRESS, (uint8_t)1);
    from_val = Wire.read();

    // SCRITTURA DEL VALORE NEL REGISTRO DESIDERATO
    Wire.beginTransmission(SCCB_ADDRESS);
    Wire.write(regNumber);
    Wire.write(to_val);
    Wire.endTransmission();

    // DEBUG:
    Serial.print("[");
    Serial.print(regNumber, HEX);
    Serial.print("] from ");
    Serial.print(from_val, HEX);
    Serial.print(" to ");
    Serial.println(to_val, HEX);
}
