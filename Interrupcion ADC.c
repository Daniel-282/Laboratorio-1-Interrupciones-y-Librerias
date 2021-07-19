#include <stdint.h>
#include <pic16f887.h>
#include "Interrupcion ADC.h"

unsigned char Low_ADC;
unsigned char High_ADC;
unsigned char Resultado_ADC;
char DisplayLow_ADC;
char DisplayHigh_ADC;

void InterruptADC(char* DisplayLow_ADC, char* DisplayHigh_ADC){
    if (ADIF == 1){    
        ADIF = 0;
    
        High_ADC = ADRESH;
        High_ADC = High_ADC << 6;
    
        Low_ADC = ADRESL;
        Low_ADC = (Low_ADC & 0b11111100) >> 2;
    
        Resultado_ADC = High_ADC + Low_ADC;
        
        *DisplayLow_ADC = Resultado_ADC & 0b00001111;
        *DisplayHigh_ADC = (Resultado_ADC & 0b11110000)>>4;
    }
}
