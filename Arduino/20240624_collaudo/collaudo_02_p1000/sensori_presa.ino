/*
 * Quando il motore viene comandato con una speed positiva (CW):
 *  l'encoder della mano DX, genera impulsi (20x4) mentre apre la presa
 * e
 *  l'encoder della mano SX, genera impulsi (20x4) mentre chiude la presa
 *
 * poi si crea una pausa
 *                
 */

void setup_sensori_presa() {

  pinMode ( SENSORE_A_MANO_DX, INPUT );
  pinMode ( SENSORE_B_MANO_DX, INPUT );
  pinMode ( SENSORE_A_MANO_SX, INPUT );
  pinMode ( SENSORE_B_MANO_SX, INPUT );

}



