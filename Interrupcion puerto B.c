#include <stdint.h>
#include <pic16f887.h>
#include "Interrupcion Puerto B.h"

char ANTIREBOTE_CONTADOR1 = 0x00;
char ANTIREBOTE_CONTADOR2 = 0x00;


void InterruptPortB() {
    if (RBIF == 1){
        if (RB0 == 1) {
            ANTIREBOTE_CONTADOR1 = 0x01;
        }
        if (ANTIREBOTE_CONTADOR1 == 0x01 && RB0 == 0){
            PORTC = PORTC + 1;
            ANTIREBOTE_CONTADOR1 = 0x00;
        }
        //Contador descendente
         if (RB1 == 1) {
            ANTIREBOTE_CONTADOR2 = 0x01;
         }
        if (ANTIREBOTE_CONTADOR2 == 0x01 && RB1 == 0){
            PORTC = PORTC - 1;
            ANTIREBOTE_CONTADOR2 = 0x00;
        }
        RBIF = 0;
    }
        
}