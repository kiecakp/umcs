
#include <8051.h>

__xdata unsigned char* CSDS = (__xdata unsigned char*) 0xFF30;    	// wskaznik ram na wybor wyswietlacza
__xdata unsigned char* CSDB = (__xdata unsigned char*) 0xFF38;          // wskaznik ram na bufor danych wyswietlacza

unsigned char KEYB[4];
unsigned char CZAS[7];		// tablica przetrzymujaca dane do zegarka
unsigned char SS;               // sekundy
unsigned char MM;               // minuty
unsigned char GG;               // godziny
unsigned char wcisnietyPrzycisk = 0;
unsigned char SStemp = 0;
unsigned char MMtemp = 0;
unsigned char GGtemp = 0;

unsigned char wzory[10] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111,	//0123
                            0b01100110, 0b01101101, 0b01111101, 0b00000111,     //4567
                            0b01111111, 0b01101111
                          };                           //89

void przelicz() {
    unsigned char A;
    unsigned char B;

    A = SS;
    B = 10;
    A = A / B;
    B = SS % B;
    if( SStemp == 1 ) {
        CZAS[0] = wzory[B] | 0b10000000;
        CZAS[1] = wzory[A] | 0b10000000;
    } else {
        CZAS[0] = wzory[B];
        CZAS[1] = wzory[A];
    }


    A = MM;
    B = 10;
    A = A / B;
    B = MM % B;
    if( MMtemp == 1 ) {
        CZAS[2] = wzory[B] | 0b10000000;
        CZAS[3] = wzory[A] | 0b10000000;
    } else {
        CZAS[2] = wzory[B];
        CZAS[3] = wzory[A];
    }

    A = GG;
    B = 10;
    A = A / B;
    B = GG % B;
    if( GGtemp == 1 ) {
        CZAS[4] = wzory[B] | 0b10000000;
        CZAS[5] = wzory[A] | 0b10000000;
    } else {
        CZAS[4] = wzory[B];
        CZAS[5] = wzory[A];
    }
}

void incGG() {
    GG = 0;
}
void incMMGG() {
    MM = 0;
    GG++;
    if( GG > 23 ) {
        incGG();
    }
}
void incSSMMGG() {
    SS = 0;
    MM++;
    if( MM > 59 ) {
        incMMGG();
    }
}

void keybSS(unsigned int task) {    // task = 0 inc, 1 dec
    if( task == 0 ) {
        SS++;
        if( SS > 59 ) {
            SS = 0;
        }
    } else {
        SS--;
        if( SS > 60 ) {
            SS = 59;
        }
    }
}
void keybMM(unsigned int task) {    // task = 0 inc, 1 dec
    if( task == 0 ) {
        MM++;
        if( MM > 59 ) {
            MM = 0;
        }
    } else {
        MM--;
        if( MM > 60 ) {
            MM = 59;
        }
    }
}
void keybGG(unsigned int task) {    // task = 0 inc, 1 dec
    if( task == 0 ) {
        GG++;
        if( GG > 23 ) {
            GG = 0;
        }
    } else {
        GG--;
        if( GG > 60 ) {
            GG = 23;
        }
    }
}

void t0_int() __interrupt(1) {  	// obsluga przerwania
    TH0 = 226;     // zeby nastepne przerwanie wystapilo po 1/960s
    F0 = 1;       // informujemy o wystapieniu rzerwania
}

void main() {

    int licznik;
    unsigned char wyswietlacz;
    unsigned char indexCZAS;
    unsigned char stabilnosc;
    unsigned char zegarekStop = 0;

    TMOD = 0b01110000;		// wylaczmy timer1, timer0 w trybie 0
    ET0 = 1;			// zgoda na przerwania od timer0
    EA = 1;				// globalna zgoda na przerwania
    TH0 = 226;			// zeby pierwsze przerwanie wystapilo po 1/960s
    TR0 = 1;			// zgoda na zliczanie przez timer0

    SS = 45;
    MM = 59;
    GG = 12;
    indexCZAS = 0;
    CZAS[6] = 0;
    KEYB[0] = 0;

    przelicz();

    P1_6 = 0;

    wyswietlacz = 0b00000001;     // ustawiamy najmlodszy wyswietlacz

    licznik = 960;
    for(;;) {
        if( !F0 ) {          // jesli nie odebrano przerwania
            continue;
        }
        F0 = 0;             // wystepilo przerwanie i zmniejszamy licznik o 1
        licznik--;

        P1_6 = 1;
        *CSDB = CZAS[indexCZAS];   // pobieramy cyfre z tablicy CZAS
        indexCZAS++;

        *CSDS = wyswietlacz;	   // ustawiamy wyswietlacz
        P1_6 = 0;

        wcisnietyPrzycisk = P3_5;

        if( wcisnietyPrzycisk == 1 ) {
            KEYB[0] = KEYB[0] | wyswietlacz;
        }

        wyswietlacz = wyswietlacz << 1;

        if( wyswietlacz == 0b10000000 ) {     // jezeli wyszlismy poza wyswietlacze
            indexCZAS = 0;
            wyswietlacz = 0b00000001;	      // wracamy do najmlodszego

            stabilnosc = KEYB[0];

            if( stabilnosc != 0 && stabilnosc == KEYB[1] && stabilnosc == KEYB[2] && stabilnosc != KEYB[3] ) {
                CZAS[6] = KEYB[0];

                // obsluga klawiszy

                if( KEYB[0] == 0b00000010 && zegarekStop == 0 ) {  // esc - zatrzymuje
                    zegarekStop = 1;
                    SStemp = 1;
                }
                if( KEYB[0] == 0b00000001 ) { // enter - wznawia
                    zegarekStop = 0;
                    SStemp = 0;
                    MMtemp = 0;
                    GGtemp = 0;
                }

                if( KEYB[0] == 0b00100000 && SStemp == 1 ) { 	// w lewo ss -> mm
                    MMtemp = 1;
                    SStemp = 0;
                } else if( KEYB[0] == 0b00100000 && MMtemp == 1 ) {  // w lewo mm -> gg
                    GGtemp = 1;
                    MMtemp = 0;
                }
				
				if( KEYB[0] == 0b00000100 && GGtemp == 1 ) {  // w prawo gg -> mm
                    MMtemp = 1;
                    GGtemp = 0;
                } else if( KEYB[0] == 0b00000100 && MMtemp == 1 ) {  // w prawo mm -> ss
                    SStemp = 1;
                    MMtemp = 0;
                }


                if( KEYB[0] == 0b00001000 && zegarekStop == 1) {   // w gore - inc
                    if( SStemp == 1 ) {
                        keybSS(0);
                    } else if( MMtemp == 1 ) {
                        keybMM(0);
                    } else if( GGtemp == 1 ) {
                        keybGG(0);
                    }
                }

                if( KEYB[0] == 0b00010000 && zegarekStop == 1) {    // w dol - dec
                    if( SStemp == 1 ) {
                        keybSS(1);
                    } else if( MMtemp == 1 ) {
                        keybMM(1);
                    } else if( GGtemp == 1 ) {
                        keybGG(1);
                    }
                }

                przelicz();
            }

            KEYB[3] = KEYB[2];
            KEYB[2] = KEYB[1];
            KEYB[1] = KEYB[0];
            KEYB[0] = 0;
        }

        przelicz();

        if( licznik ) {
            continue;
        }

        licznik = 960;
        P1_7 = !P1_7;

        if( zegarekStop == 0 ) {
            SS++;
            if( SS > 59 ) {
                incSSMMGG();
            }
        }

    }
}