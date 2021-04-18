/* Programma per la realizzazione di un Web Server con ESP-01S
 *  su Arduino Mega. 
 *  
 *  Il dispositivo deve essere configurato in modalità SoftAP
 *  attraverso un paio di comandi AT e la configurazione rimarrà
 *  scritta in Flash in modo permanente.
 *  
 *  I comandi da inviare una tantum (o anche tutte le volte) sono:
 *    AT+CWMODE_DEF=3    e    AT+CWSAP_DEF="WiFi-P1000","",11,0,4,0
 *    
 *  Per far funzionare il dispositivo occorre alimentarlo a 3,3V 
 *  con almeno 250mA e tutti i segnali verso il modulo Wi-Fi devono
 *  essere a 3,3V (si può usare un partitore resistivo da Arduino 
 *  Mega verso il modulo Wi-Fi con R1 = 680 ohm e R2 = 1200 ohm).
 *  
 *  Il modulo è connesso ad Arduino tramite RX2 e TX2, i pin della 
 *  Seriale numero 2 con BAUD rate 115200 e UART N81.
 *  
 *  Guarda il video: https://youtu.be/byh3Blp6xDA 
 *
 *  15-04-2021 - Emanuele Frisoni
 */
 
char ch;         // Il canale del chiamante
int  n_to_rcv;   // Numero di byte da ricevere
String request;  // Richesta del chiamante (browser)
String htmlPage; // La pagina Web comprensiva di HTTP Header

String faviconHeader;  // L'intestazione per la favicon
                       // Il bytecode della favicon
const byte faviconImg[331] = {
    0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x00, 0x01, 0x00, 0x04, 0x00, 0x28, 0x01,
    0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xce, 0xa6, 0x00, 0x0e, 0x00, 0x23, 0x12, 0xce, 0x9a, 0x00, 0x09, 0xc2, 0x9f, 0x12,
    0x00, 0x00, 0xc2, 0x9b, 0xcf, 0x8c, 0x00, 0x18, 0xce, 0xaf, 0xce, 0xbd, 0x00, 0xef, 0x9f, 0x87,
    0xef, 0x9f, 0x87, 0xef, 0x9f, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x05, 0x55, 0x50, 0x33, 0x33, 0x04, 0x44, 0x40, 0x05, 0x55, 0x50, 0x33, 0x33,
    0x04, 0x44, 0x40, 0x05, 0x55, 0x50, 0x33, 0x33, 0x04, 0x44, 0x40, 0x05, 0x55, 0x50, 0x33, 0x33,
    0x04, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x10, 0x66, 0x66,
    0x03, 0x33, 0x30, 0x01, 0x11, 0x10, 0x66, 0x66, 0x03, 0x33, 0x30, 0x01, 0x11, 0x10, 0x66, 0x66,
    0x03, 0x33, 0x30, 0x01, 0x11, 0x10, 0x66, 0x66, 0x03, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x05, 0x55, 0x50, 0x22, 0x22, 0x01, 0x11, 0x10, 0x05, 0x55, 0x50, 0x22, 0x22,
    0x01, 0x11, 0x10, 0x05, 0x55, 0x50, 0x22, 0x22, 0x01, 0x11, 0x10, 0x05, 0x55, 0x50, 0x22, 0x22,
    0x01, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    
void setup() {

  /* Configuro il pin per accendere e spegnere il LED BUILTIN
   *  di Arduino Mega  */
  pinMode(LED_BUILTIN, OUTPUT);

  /* Sul pin 4 di Arduino Mega è stato collegato il Reset di ESP-01S 
   *  attivo basso (0 = RESET) sempre attraverso il partitore resistivo 
   *  680/1200 ohm per trasformare i segnali a 5V in 3V */
  pinMode(4, OUTPUT);  // RESET
  digitalWrite(4, HIGH);  

  /* Impostazione della seriale di servizio per il debug */
  Serial.begin(115200); while(!Serial); 
  
  /* Impostazione della seriale RX2(17)/TX2(16) per dialogare
   *  con il modulo Wi-Fi ESP-01S a 115200 BAUD N-8-1 */
  Serial2.begin(115200);

  /* Invio un comando AT per verificare la connessione */
  Serial2.println("AT/r/n");

  /* Todo: gestire la risposta OK di ESP-01S */

  /* Inizializzazione della risposta del server sulla variabile
   *  globale `htmlPage`      
   */
  htmlPage.reserve(1024);               // prevent ram fragmentation
  htmlPage = F("HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html\r\n"
               "Connection: close\r\n"  // the connection will be closed 
                                        // after completion of the response
                  
               /*"Refresh: 5\r\n"         // refresh the page automatically every 5 sec*/
               
               "\r\n"
               "<!DOCTYPE HTML>"
               "<html>"
               "<head>"
               "<title>Progetto-1000</title>"
               "<meta charset=\"UTF-8\">"
               "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" >"
               "<meta http-equiv=\"X-UA-Compatible\" content=\"ie-edge\">"
               "</head>"
               "<body>"
               "<h1>It Works!</h1>"
               "<h2>Hello dal tuo caro amico Fremsoft</h2>"
               "<ul>"
               "<li><a href=\"led_on\">ACCENDI LED</a><br/><br/></li>"
               "<li><a href=\"led_off\">SPEGNI LED</a></li>"
               "</ul>"
               "</body>"
               "</html>"
               "\r\n");

  faviconHeader = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: 'image/ico'\r\n"
                  "\r\n";

                  
  /* Per il Debug informo che il modulo ha subito un Restart 
   *  e mostro lunghezza e testo della variabile `htmlPage`
   */
  Serial.print( "RESTART\n len=" );
  Serial.println( htmlPage.length() );
  Serial.print( htmlPage );

  /* Comando un RESET al modulo ESP-01S */
  Serial2.println("AT+RST");
  Serial.println("AT+RST");            // echo per Debug

  /* Attendo che il modulo ESP-01S si riavii correttamente */
  delay ( 5000 );
  
/* Imposta Multiple Connection: AT+CIPMUX=1 */
  Serial2.println("AT+CIPMUX=1");
  Serial.println("AT+CIPMUX=1");       // echo per Debug

  /* Attendo che il modulo ESP-01S recepisca il comando */
  delay ( 1000 );
  
/* Imposta WebServer in ascolto su porta 80: AT+CIPSERVER=1,80 */
  Serial2.println("AT+CIPSERVER=1,80");
  Serial.println("AT+CIPSERVER=1,80"); // echo per Debug
  
}

void loop() {
  
  char c;
  static int status = 0;

/*
 * Tipico messaggio trasmesso da ESP-01S quando 
 * qualcuno interroga il server dalla rete Wi-Fi
 * 
 
+IPD,0,477:GET / HTTP/1.1
Host: 192.168.4.1
Connection: keep-alive
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Ag ... 
Recv 180 bytes

 */
 
  /* Se ci sono caratteri disponibili sulla linea seriale di ESP-01S */  
  if (Serial2.available() > 0) {

    /* Leggo un carattere e lo carico sulla variabile `c` 
     *  la variabile `status` indica la situazione del parser
     *  che ha il compito di interpretare il messaggio in arrivo
     *  da ESP/01S
     */
    c = Serial2.read();
    
    switch(status) {
      
      case 0 : 
        if (c=='+') { status++; } 
        else {
          /* Per tutti gli altri comandi mostra echo di tutto ciò che arriva da ESP-01S */
          Serial.write(c);                        // echo per Debug
        }
        break;  
            
      case 1 : 
        if (c=='I') { status++; } else { status = 0; } 
        break;   
           
      case 2 : 
        if (c=='P') { status++; } else { status = 0; } 
        break;   
           
      case 3 : 
        if (c=='D') { status++; } else { status = 0; } 
        break;   
          
      case 4 : 
        if (c==',') { status++; } else { status = 0; } 
        break;  
            
      case 5 : 
        /* In questa posizione c'è il numero del canale del chiamante
         *  lo memorizzo nella variabile globale `ch`  */
        if ((c>='0') && (c<='9')) { ch = c; status++; } 
        break;  
              
      case 6 : 
        /* azzero la variabile globale `n_to_rcv` quando incontro la 
         * virgola, il prossimo campo sarà proprio il numero di caratteri
         * in arrivo da ESP-01S come numero decimale in formato ASCII */
        if (c==',') { n_to_rcv = 0; request = ""; status++; } 
        break;
      
      case 7 : 
        /* Ricostruisco il numero decimale un byte alla volta */
        if ((c>='0') && (c<='9')) { 
          n_to_rcv = ((10*n_to_rcv) + c) - '0'; 
        } 
        else { 
          status++;
          /* Per Debug, mostra se ha letto bene 
           *  il valore numerico dalla stringa
           *  Serial.print ("N-TO-RCV: "); Serial.println(n_to_rcv);   
           */ 
        } 
        break;
        
      case 8 : 
        /* In attesa di un carattere 'spazio', qui è situata
         *  una delle seguenti diciture: GET, POST, ... */
        --n_to_rcv; 
        if (c == ' ') { status++; } 
        break;
        
      case 9 : 
        /* In attesa di un carattere 'spazio', qui è situato
         *  il URL che segue il nume dominio o l'indirizzo IP 
         *  lo trascrivo nella variabile globale `request` */
        --n_to_rcv; 
        if (c == ' ') { status++; } else { request.concat(c); } 
        break;
        
      case 10: 
        /* In attesa di ricevere tutti gli altri caratteri */
        if (((--n_to_rcv) <= 5) && (c=='\n')) { status++; } 
        break;
        
      case 11 : 
        /* Il messaggio del Web Browser è terminato, ora tocca 
         *  al Web Server prendere la parola e rispondere */

        /* Se viene richiesta la favicon, trasmette questo: */
        if (request.compareTo("/favicon.ico") == 0) {
          
          /* Restituisce la favicon.ico */

          Serial2.print("AT+CIPSENDBUF=");
          // Serial.print("AT+CIPSENDBUF=");     // echo per Debug
        
          Serial2.write(ch);
          // Serial.write(ch);                   // echo per Debug
        
          Serial2.print(",");
          // Serial.print(",");                  // echo per Debug
        
          Serial2.println( faviconHeader.length() + sizeof(faviconImg) + 2 );
          // Serial.println( faviconHeader.length() + sizeof(faviconImg) + 2 ); // echo per Debug
        
          delay(100);

          Serial2.print( faviconHeader );
          // Serial.print( faviconHeader );            // echo per Debug

          Serial2.write( faviconImg, sizeof(faviconImg) );
          
          Serial2.print( "\r\n" );
          

          /* Mostra sulla console di debug la pagina richiesta */
          Serial.println();
          Serial.print("sent answer to ");
          Serial.println( request );
          
        } 
        /* altrimenti se viene richiesto altro: */
        else {
        
          Serial2.print("AT+CIPSENDBUF=");
          // Serial.print("AT+CIPSENDBUF=");     // echo per Debug
        
          Serial2.write(ch);
          // Serial.write(ch);                   // echo per Debug
        
          Serial2.print(",");
          // Serial.print(",");                  // echo per Debug
        
          Serial2.println(htmlPage.length());
          // Serial.println (htmlPage.length()); // echo per Debug
        
          delay(100);

          Serial2.print(htmlPage);
          // Serial.print (htmlPage);            // echo per Debug

          /* Mostra sulla console di debug la pagina richiesta */
          Serial.println();
          Serial.print("sent answer to ");
          Serial.println( request );


          /* In base alla richiesta: Accende o Spegne il BUILTIN LED
           **/
          if (request.compareTo("/led_on") == 0) {
            digitalWrite(LED_BUILTIN, HIGH);
          }      

          if (request.compareTo("/led_off") == 0) {
            digitalWrite(LED_BUILTIN, LOW);
          } 
          
        }             
        
        delay(50);

        /* Chiude la connessione TCP */
        Serial2.print("AT+CIPCLOSE=");
        // Serial.print("AT+CIPCLOSE=");       // echo per Debug
        
        Serial2.write(ch);
        // Serial.write(ch);                   // echo per Debug

        Serial2.println();
        // Serial.println();                   // echo per Debug

        status = 0;
        break;
        
    }

    /* echo locale di tutto ciò che arriva da ESP-01S */
    // Serial.write(c);                        // echo per Debug
  }

  /* Tutto quello che scrivo sul Monitor Seriale 
   *  viene trasmesso a ESP-01S */
  if (Serial.available() > 0) {
    
    Serial2.write( Serial.read() );
    
  }
}



#if 0

ALCUNI COMANDI UTILI CHE SI POSSONO DIGITARE SU MONITOR SERIALE DI ARDUINO IDE


AT+CWMODE_DEF=3

OK

WIFI DISCONNECT
WIFI CONNECTED
WIFI GOT IP

AT+CWSAP_CUR?

+CWSAP_CUR:"ESP_7839F5","",11,0,4,0

OK

WIFI CONNECTED
WIFI GOT IP

AT+CWSAP_DEF="WiFi-P1000","",11,0,4,0


OK
AT+CIPMUX=1


OK
AT+CIPSERVER=1,80


OK


0,CONNECT

+IPD,0,518:GET / HTTP/1.1
Host: 192.168.4.1
Connection: keep-alive
sent answer

Cache-Control: max-age=0
x-wap-profile: http://218.249.47.94/X
Recv 180 bytes

SEND OK
1,CONNECT
2,CONNECT

+IPD,1,507:GET / HTTP/1.1
Host: 192.168.4.1
Connection: keep-alive
sent answer

Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Ag
Recv 180 bytes

SEND OK
0,CLOSED
0,CONNECT

+IPD,0,518:GET / HTTP/1.1
Host: 192.168.4.1
Connection: keep-alive
sent answer

Cache-Control: max-age=0
Accept: text/html,application/xhtml+x
Recv 180 bytes

SEND OK

AT+CWDHCPS_CUR?

+CWDHCPS_CUR:120,192.168.4.2,192.168.4.101
OK

AT+CIPSTA_CUR?

+CIPSTA_CUR:ip:"192.168.1.9"
+CIPSTA_CUR:gateway:"192.168.1.254"
+CIPSTA_CUR:netmask:"255.255.255.0"

OK

AT+CIPAP_CUR?

+CIPAP_CUR:ip:"192.168.4.1"
+CIPAP_CUR:gateway:"192.168.4.1"
+CIPAP_CUR:netmask:"255.255.255.0"

OK

AT+CIPSTATUS

STATUS:2

OK

AT+CIPSEND=0,180
***  delay(100);
HTTP/1.1 200 OK
Content-Type: text/html
Connection: close
Refresh: 5

<!DOCTYPE HTML><html><h1>It Works!</h1><h2>Hello dal tuo caro amico Fremsoft</h2></html>

******************* server waiting

0,CONNECT
1,CONNECT

+IPD,0,477:GET / HTTP/1.1
Host: 192.168.4.1
Connection: keep-alive
sent answer

Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Ag
Recv 180 bytes

SEND OK

#endif
