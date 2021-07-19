#include <stdint.h>
#include <pic16f887.h>
#include "Interrupcion TMR0.h"

char contador = 0x00;
unsigned char sumaADC;
unsigned char DISPLAY[0b00010000] =  {0b1000000, //contiene los digitos
                                      0b1111001, //0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
                                      0b0100100, // en formato para ser mostradosendisplay
                                      0b0110000, // de 7segmentos
                                      0b0011001,
                                      0b0010010,
                                      0b0000010,
                                      0b1111000,
                                      0b0000000,
                                      0b0010000,
                                      0b0001000,
                                      0b0000011,
                                      0b1000110,
                                      0b0100001,
                                      0b0000110,
                                      0b0001110,};

void InterruptTMR0(char DisplayLow_ADC, char DisplayHigh_ADC){
    if (TMR0IF){
        TMR0 = 6;
                
        contador = !contador;
        
        if (contador == 0x01){
            RE1 = 0;
            RE0 = 1;
            PORTD = DISPLAY[DisplayLow_ADC];     // muestro digito  del 0-15 en 7seg en display en portd 
        }
        
        if (contador == 0x00){
            RE0 = 0;
            RE1 = 1;
            PORTD = DISPLAY[DisplayHigh_ADC];     // muestro digito  del 0-15 en 7seg en display en portd 
        }
        sumaADC = (DisplayHigh_ADC << 4) + DisplayLow_ADC;
        
        if (PORTC < sumaADC){ //Alarma para saber si la digitalizacion sobrepaso el valor de referencia
            RA0 = 1;
        }
        else {
            RA0 = 0;
        }
        
        TMR0IF = 0;       
    }   
}

