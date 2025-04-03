#include <8051.h>

__xdata unsigned char* LCDWC = (__xdata unsigned char*) 0xFF80;
__xdata unsigned char* LCDWD = (__xdata unsigned char*) 0xFF81;
__xdata unsigned char* LCDRC = (__xdata unsigned char*) 0xFF82;
__xdata unsigned char* LCDRD = (__xdata unsigned char*) 0xFF83;

__code unsigned char napis[] = "MILEGO DNIA!";
unsigned char rozkazy = 0b10000000;

void wait4LCD(){
	unsigned char temp = rozkazy & *LCDRC;
	if(temp == 0b10000000){
		wait4LCD();
	}
}

void main(){
	unsigned char i;
	i = 0;

	wait4LCD();
	*LCDWC = 0b00000001;
	
	wait4LCD();
	*LCDWC = 0b00111000;
	
	wait4LCD();
	*LCDWC = 0b00001100;
	
	wait4LCD();
	*LCDWC = 0b00000110;
	
// dane

        while(napis[i]){
		wait4LCD();
		*LCDWD = napis[i];
		i++;
        }
}