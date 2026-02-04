#include <iostream>
#include <vector>
#include <string>
#include "LesData2.h"

using namespace std;




const int ANTSTOPP = 11; ///< Totalt antall ulike busstopp.


struct Rute {
vector <string> stopp; // Rutens ulike stoppesteder.
int ruteNr, // Reelt rutenr, f.eks. 42, 165, 718
totMin; // Totalt antall minutter å kjøre på ruten
}; // (fra første til siste stoppested).


vector <Rute*> gRuter; ///< Pekere til rutene.

const vector <string> gBusstopp = ///< Navn på alle busstopp.
{ "Skysstasjonen", "Fahlstroms plass", "Sykehuset",
"Gjovik stadion", "Bergslia", "Overby", "Nybrua",
"NTNU", "Kallerud", "Hunndalen", "Mustad fabrikker" };

const int gMinutter[ANTSTOPP][ANTSTOPP] = ///< Min.mellom stoppesteder.
// const vector <vector <int> > gMinutter = // Alternativt (nå lært i vår).
{ { 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Skysstasjonen = 0
{ 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4}, // Fahlstrøms plass = 1
{ 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Sykehuset = 2
{ 0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0}, // Gjøvik stadion = 3
{ 0, 0, 0, 3, 0, 2, 0, 0, 0, 0, 0}, // Bergslia = 4
{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}, // Øverby = 5
{ 0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 2}, // Nybrua = 6
{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0}, // NTNU = 7
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Kallerud = 8
{ 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2}, // Hunndalen = 9
{ 0, 4, 0, 0, 0, 0, 2, 0, 0, 2, 0} }; // Mustad fabrikker = 10

void skrivMeny();
void skrivStopp();
void skrivRuter();
void skrivNesteStoppesteder(const int stopp);
void nyRute();
bool ruteLesData(Rute & rute);
void slettRute();

int main() {
    char kommando;
    skrivNesteStoppesteder(0);

    do {
        switch (kommando)
        {
        case 'N': nyRute();         break;
        case 'S': slettRute();      break;
        case 'A': skrivRuter();     break;
        case 'B': skrivStopp();     break;
        default: skrivMeny();       break;
        } 
        kommando = lesChar("\nSkriv kommando: ");

    } while (kommando != 'Q');

    return 0;
}
void skrivMeny() {
    cout << "\n-----MENY-----\n";
    cout << "N - Ny rute\n";
    cout << "S - Slett rute\n";
    cout << "A - Skriv alle ruter";
    cout << "B - Skriv alle busstopp\n";
    cout << "Velg kommando:";

}

void skrivStopp() {
    for (int i = 0; i < ANTSTOPP; i++) {
        cout << "\nBuss stop nr " << i+1 << ": "<< gBusstopp[i];
        
    }
}

void skrivNesteStoppesteder(const int stopp) {
    for (int i = 0; i < ANTSTOPP; i++) {
        if (gMinutter[stopp][i] > 0) {
            cout << "\nFra stopp nr " << (stopp + 1) << ": " << gBusstopp[stopp] << "\n";
            cout << "\nTil stopp nr " << (i + 1) << ": " << gBusstopp[i] << " (" << gMinutter[stopp][i] << " min)";
        }
    }
}

void ruteSkrivData() {
    
}

bool ruteLesData(Rute & rute) {


}

void nyRute() {

}

void skrivRuter() {

}