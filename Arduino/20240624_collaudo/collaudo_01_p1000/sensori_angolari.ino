/*
 * I sensori angolari sono fotoresistori, 
 * 3 per ogni mano, che indicano la posizione 
 * angolare del polso
 *
 * I sensori sono connessi ad A0-A5:
 *  A0 -  mano      A2 -  mano 
 *  A1 -   DX       A4 -   SX
 *  A3 -            A5 -  
 */
#include "defs.h"

int getRotazionePolsoSX() {
  int retval = 0;
  
  int a1 = analogRead(SENSORE_1_MANO_SX);
  int a2 = analogRead(SENSORE_2_MANO_SX);
  int a3 = analogRead(SENSORE_3_MANO_SX);
   
  if ( 
       (a1 > SOGLIA_DI_LUCE_FINESTRELLA_H) 
        ||
       (a2 > SOGLIA_DI_LUCE_FINESTRELLA_H)
        ||
       (a3 > SOGLIA_DI_LUCE_FINESTRELLA_H)
  ) {

    if (a1 > SOGLIA_DI_LUCE_FINESTRELLA_L) {
      retval += 1;
    }

    if (a2 > SOGLIA_DI_LUCE_FINESTRELLA_L) {
      retval += 2;
    }

    if (a3 > SOGLIA_DI_LUCE_FINESTRELLA_L) {
      retval += 4;
    }

  }

  return retval;
}


int getRotazionePolsoDX() {
  int retval = 0;

  int a1 = analogRead(SENSORE_1_MANO_DX);
  int a2 = analogRead(SENSORE_2_MANO_DX);
  int a3 = analogRead(SENSORE_3_MANO_DX);
   
  if ( 
       (a1 > SOGLIA_DI_LUCE_FINESTRELLA_H) 
        ||
       (a2 > SOGLIA_DI_LUCE_FINESTRELLA_H)
        ||
       (a3 > SOGLIA_DI_LUCE_FINESTRELLA_H)
  ) {
    
    if (a1 > SOGLIA_DI_LUCE_FINESTRELLA_L) {
      retval += 1;
    }

    if (a2 > SOGLIA_DI_LUCE_FINESTRELLA_L) {
      retval += 2;
    }

    if (a3 > SOGLIA_DI_LUCE_FINESTRELLA_L) {
      retval += 4;
    }
  
  }
  
  return retval;
}

