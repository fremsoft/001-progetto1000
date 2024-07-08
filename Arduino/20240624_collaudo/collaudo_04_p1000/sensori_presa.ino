/*
 * Quando il motore viene comandato con una speed positiva (CW):
 *  l'encoder della mano DX, genera impulsi (20x4) mentre apre la presa
 * e
 *  l'encoder della mano SX, genera impulsi (20x4) mentre chiude la presa
 *
 * poi si crea una pausa
 *                
 */

unsigned long t0_encoder_dx;
unsigned long t0_encoder_sx;

void setup_sensori_presa() {

  pinMode ( SENSORE_A_MANO_DX, INPUT );
  pinMode ( SENSORE_B_MANO_DX, INPUT );
  pinMode ( SENSORE_A_MANO_SX, INPUT );
  pinMode ( SENSORE_B_MANO_SX, INPUT );

  t0_encoder_dx = 0;
  t0_encoder_sx = 0;

}

int encoder_presa_mano_DX() {
  static int stato_passato=0;
  int stato;

  stato = ((digitalRead(SENSORE_A_MANO_DX))?(1):(0))
            + 
          ((digitalRead(SENSORE_B_MANO_DX))?(2):(0));
          
  if (stato != stato_passato) {
    t0_encoder_dx = millis();
    stato_passato = stato;
    return stato; 
  }

  return -1;
} 

unsigned long deltaT_encoder_presa_mano_DX() {
  return (millis() - t0_encoder_dx);
}
    
int encoder_presa_mano_SX() {
  static int stato_passato=0;
  int stato;

  stato = ((digitalRead(SENSORE_A_MANO_SX))?(1):(0))
            + 
          ((digitalRead(SENSORE_B_MANO_SX))?(2):(0));
          
  if (stato != stato_passato) {
    t0_encoder_sx = millis();
    stato_passato = stato;
    return stato; 
  }

  return -1;
} 

unsigned long deltaT_encoder_presa_mano_SX() {
  return (millis() - t0_encoder_sx);
}
