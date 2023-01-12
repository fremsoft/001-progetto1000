//#define ENCODER_A  54 
//#define ENCODER_B  55 
#define ENCODER_A  A0
#define ENCODER_B  A1

/*
 * PF 0 54 A0
 * PF 1 55 A1
 * PF 2 56 A2
 * PF 3 57 A3
 * PF 4 58 A4
 * PF 5 59 A5
 * PF 6 60 A6
 * PF 7 61 A7
 * PK 0 62 A8
 * PK 1 63 A9
 * PK 2 64 A10
 * PK 3 65 A11
 * PK 4 66 A12
 * PK 5 67 A13
 * PK 6 68 A14
 * PK 7 69 A15
 */


void setup() {

  Serial.begin(115200);

/*
  pinMode ( ENCODER_A, INPUT );
  pinMode ( ENCODER_B, INPUT );
  */
    
}

void loop() {

  
  Serial.print("0,1000,Encoder-A:");
  Serial.print(analogRead(ENCODER_A));
  Serial.print(",Encoder-B:");
  Serial.println(analogRead(ENCODER_B));
  
/*
  Serial.print("0,1000,Encoder-A:");
  Serial.print(digitalRead(ENCODER_A)*900 + 75);
  Serial.print(",Encoder-B:");
  Serial.println(digitalRead(ENCODER_B)*900 + 25);
*/
}
