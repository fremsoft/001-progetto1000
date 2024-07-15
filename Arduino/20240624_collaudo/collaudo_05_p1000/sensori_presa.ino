/*
 * Quando il motore viene comandato con una speed positiva (CW):
 *  l'encoder della mano DX, genera impulsi (20x4) mentre apre la presa
 * e
 *  l'encoder della mano SX, genera impulsi (20x4) mentre chiude la presa
 *
 * poi si crea una pausa
 *                
 */

#include "PinChangeInterrupt.h"

volatile unsigned long t0_encoder_dx;
volatile unsigned long t0_encoder_sx;

volatile int corsa_dx;
volatile int corsa_sx;


void setup_sensori_presa() {

  pinMode ( SENSORE_A_MANO_DX, INPUT );
  pinMode ( SENSORE_B_MANO_DX, INPUT );
  attachPCINT(digitalPinToPCINT(SENSORE_A_MANO_DX), gestione_encoder_DX, CHANGE);
  attachPCINT(digitalPinToPCINT(SENSORE_B_MANO_DX), gestione_encoder_DX, CHANGE);
  
  pinMode ( SENSORE_A_MANO_SX, INPUT );
  pinMode ( SENSORE_B_MANO_SX, INPUT );
  attachPCINT(digitalPinToPCINT(SENSORE_A_MANO_SX), gestione_encoder_SX, CHANGE);
  attachPCINT(digitalPinToPCINT(SENSORE_B_MANO_SX), gestione_encoder_SX, CHANGE);
  
  t0_encoder_dx = 0;
  t0_encoder_sx = 0;
  corsa_dx = 0;
  corsa_sx = 0;
}

/* handler routine di interruzione */
void gestione_encoder_DX() {
  /* 
    durante la apertura 
     DX=2; 
     DX=0; 
     DX=1; 
     DX=3; 
  */
  int stato = ((digitalRead(SENSORE_A_MANO_DX))?(1):(0))
              + 
              ((digitalRead(SENSORE_B_MANO_DX))?(2):(0));
  static int stato_passato=0;

  t0_encoder_dx = millis();

  /* decremento la corsa quando apre */
  if  ((stato_passato == 1) && (stato == 3)) { corsa_dx--; }
  if  ((stato_passato == 0) && (stato == 1)) { corsa_dx--; }
  if  ((stato_passato == 2) && (stato == 0)) { corsa_dx--; }
  if  ((stato_passato == 3) && (stato == 2)) { corsa_dx--; }
  
  /* incremento la corsa quando chiude */
  if  ((stato_passato == 3) && (stato == 1)) { corsa_dx++; }
  if  ((stato_passato == 1) && (stato == 0)) { corsa_dx++; }
  if  ((stato_passato == 0) && (stato == 2)) { corsa_dx++; }
  if  ((stato_passato == 2) && (stato == 3)) { corsa_dx++; }

  stato_passato = stato;
}

unsigned long deltaT_encoder_presa_mano_DX() {
  return (millis() - t0_encoder_dx);
}

void azzera_corsa_mano_DX() {
  corsa_dx = 0;
}

int get_corsa_mano_DX() { 
  return corsa_dx;
}


/* handler routine di interruzione */
void gestione_encoder_SX() {
  /* 
    durante la apertura 
     SX=0; 
     SX=1; 
     SX=3; 
     SX=2; 
  */
  int stato = ((digitalRead(SENSORE_A_MANO_SX))?(1):(0))
              + 
              ((digitalRead(SENSORE_B_MANO_SX))?(2):(0));
  static int stato_passato=0;
  
  t0_encoder_sx = millis();

  /* decremento la corsa quando apre */
  if  ((stato_passato == 1) && (stato == 3)) { corsa_sx--; }
  if  ((stato_passato == 0) && (stato == 1)) { corsa_sx--; }
  if  ((stato_passato == 2) && (stato == 0)) { corsa_sx--; }
  if  ((stato_passato == 3) && (stato == 2)) { corsa_sx--; }
  
  /* incremento la corsa quando chiude */
  if  ((stato_passato == 3) && (stato == 1)) { corsa_sx++; }
  if  ((stato_passato == 1) && (stato == 0)) { corsa_sx++; }
  if  ((stato_passato == 0) && (stato == 2)) { corsa_sx++; }
  if  ((stato_passato == 2) && (stato == 3)) { corsa_sx++; }

  stato_passato = stato;
}

unsigned long deltaT_encoder_presa_mano_SX() {
  return (millis() - t0_encoder_sx);
}

void azzera_corsa_mano_SX() {
  corsa_sx = 0;
}

int get_corsa_mano_SX() { 
  return corsa_sx;
}
