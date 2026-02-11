/**
 *   Administrativ program som hådnterer og registrerer bussruter og busstop.
 *   Brukeren får opp meny med valg om ny ryte, slett rute og skrive ut alle rute/busstop.
 * 
 *
 *   @file	  oblig1.cpp
 *   @author  Ravan Abbasov
 */
#include <iostream>
#include <vector>
#include <string>
#include "LesData2.h"

using namespace std;




const int ANTSTOPP = 11; ///< Totalt antall ulike busstopp.

/*
* Rute med stoppested, nummeret på rute og totale reisen. 
*/
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

void nyRute();
bool ruteLesData(Rute & rute);
void ruteSkrivData(const Rute rute);
void skrivMeny();
void skrivNesteStoppesteder(const int stopp);
void skrivRuter();
void slett(const int nr);
void slett();
void slettRute();
void skrivStopp();

/**
 *  Hovedprogrammet.
 */
int main() {
    char kommando;

    skrivMeny();
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

/**
 *  Skriver menyen.
 */
void skrivMeny() {
    cout << "\n-----MENY-----\n";
    cout << "N - Ny rute\n";
    cout << "S - Slett rute\n";
    cout << "A - Skriv alle ruter";
    cout << "B - Skriv alle busstopp\n";
    cout << "Velg kommando:";

}

/**
 *  Skriver navnet på alle stoppestedene.
 */
void skrivStopp() {
    for (int i = 0; i < ANTSTOPP; i++) {
        cout << "\nBuss stop nr " << i+1 << ": "<< gBusstopp[i];
        
    }
}

/**
 *  Skriver alle stoppesteder  utfra i stoppested.
 *
 *  @param   stopp  - indeks (0-basert) til gjeldende stoppested
 */
void skrivNesteStoppesteder(const int stopp) {
    for (int i = 0; i < ANTSTOPP; i++) {
        if (gMinutter[stopp][i] > 0) {
            cout << "\nFra stopp nr " << (stopp + 1) << ": " << gBusstopp[stopp] << "\n";
            cout << "\nTil stopp nr " << (i + 1) << ": " << gBusstopp[i] << " (" << gMinutter[stopp][i] << " min)";
        }
    }
}

/**
 *  Skriver ut alle data for ruten med ' -->' mellom stoppesteder.
 *
 *  @param   rute  - ruten som skrives
 */
void ruteSkrivData(const Rute rute) {
    if (rute.stopp.size() == 0 ) {
        cout << "\nIngen stopp i denne rute.";
    }
    else {
         cout << "\nRute: ";

        cout << rute.stopp[0];

        for (int i = 1; i < rute.stopp.size(); i++ ) {
        cout << " --> " << rute.stopp[i];
        }
    }
}

/**
 *  Skriver ut alle rutene og data.
 */
void skrivRuter() {
    if (gRuter.size() == 0) {
        cout << "ingen ruter til å skrive.";
    }
    else {
        for (int i = 0; i < gRuter.size(); i++) {
            cout << "Rute nr " << i+1 << ":\n";
            // kaller funskjon med bruk av selve rute objektet.
            ruteSkrivData(*gRuter[i]);
        }
    }
    
}

/**
 *  Oppretter en ny rute og leser inn dens data.
 */
void nyRute() {

    Rute* nyRute = new Rute;

    if (ruteLesData(*nyRute)) {
        // legger pekeren inn i gRuter
        gRuter.push_back(nyRute);

        //Skriver ut indeks og data.
        int indeks = gRuter.size() - 1;
        cout << "Ny rute lagt til med indeks " << indeks << ":\n";
        ruteSkrivData(*nyRute);
    }
    else {
        delete nyRute;
    }

}


/**
 *  Leser rutens data og bygger opp stopp-listen.
 *
 *  @param   rute  - ruten som får sin data innlest
 *
 *  @return  true om ruten har mer enn ett stopp, ellers false
 */
bool ruteLesData(Rute & rute)  {
    bool flereStopp = false;

    rute.stopp.clear();
    rute.totMin = 0;

    rute.ruteNr = lesInt("\nOppgi rutenummer", 1, 9999);

    skrivStopp();
    int valgStart = lesInt("\nVelg startstopp", 1, ANTSTOPP);
    int fra = valgStart - 1;                         //  0 index
    rute.stopp.push_back(gBusstopp[fra]);

    bool ferdig = false;

    // Byttet fra while til do-while løkke som ble anbefalt.
    do {
        skrivNesteStoppesteder(fra);

        int valgNeste = lesInt("\nVelg neste stopp (0 = ferdig)", 0, ANTSTOPP);

        if (valgNeste == 0)  {
            ferdig = true;
        } else  {
            int til = valgNeste - 1;
            bool lovlig = false;

            if (gMinutter[fra][til] > 0)  {
                lovlig = true;
            }

            if (lovlig)  {
                rute.stopp.push_back(gBusstopp[til]);
                rute.totMin += gMinutter[fra][til];
                fra = til;
            } else  {
                cout << "\nUlovlig stopp fra dette stoppestedet. Proev igjen.\n";
            }
        }
    } while (!ferdig);

    if (rute.stopp.size() > 1)  flereStopp = true;

    return flereStopp;
}

/**
 *  Sletter rute.
 */
void slettRute()  {
    if (gRuter.empty())  {
        cout << "\n\nIngen ruter aa slette.\n";
    } else  {
        int valg = 0;

        skrivRuter();
        valg = lesInt("\nHvilken rute skal slettes (-1=alle, 0=ingen)", -1,
                      static_cast<int>(gRuter.size()));

        if (valg == -1)  {
            slett();
            cout << "\nAlle ruter er slettet.\n";
        } else if (valg == 0)  {
            cout << "\nIngen ruter ble slettet.\n";
        } else  {
            slett(valg);
            cout << "\nRute " << valg << " er slettet.\n";
        }
    }
}

/**
 *  Sletter rute nr ved å flytte bakerste inn i den slettede plass.
 *
 *  @param   nr  - rutens indeks (1-basert)
 */
void slett(const int nr)  {

    delete gRuter[nr-1];
    gRuter[nr-1] = gRuter.back();
    gRuter.pop_back();
}

/**
 *  Sletter alle rutene.
 */
void slett()  {
    while (!gRuter.empty())  {
        delete gRuter.back();
        gRuter.pop_back();
    }
}