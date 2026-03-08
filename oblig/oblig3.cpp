/**
 *  obligatorisk oppgave 3
 * 
 * 
 * 
 * @file oblig3.cpp
 * @author Ravan Abbasov
 */

 #include <iostream>    //cin, cout
 #include <string>      
 #include <vector>
 #include <fstream>     // lese og skrive fra fil
 #include <list>
 #include "LesData2.h" 

using namespace std;

enum isType {Sorbe, Granite, Slush};


// ============================================================
//  Klassedeklarasjoner
// ============================================================

class Iskrem {
    private:
    string smak;
    int pris;

    public:
    Iskrem(ifstream& inn);
    virtual void lesFraFil(ifstream& inn);

    virtual void skrivTilSkjerm() const;
    virtual void skrivTilFil(ofstream& ut);
};

// ------------------------------------------------------------

class Sorbet : public Iskrem {
    private:
    isType sorbet;

    public:
    Sorbet(ifstream& inn);
    virtual void lesFraFil(ifstream& inn);
    virtual void skrivTilSkjerm();
    virtual void skrivTilFil(ofstream& ut);
    
};

// ------------------------------------------------------------

class Floteis : public Iskrem {
    private:
    bool vegan;

    public: 
    Floteis(ifstream& inn);
    virtual void lesFraFil(ifstream& inn);
    virtual void skrivTilSkjerm() const;
    virtual void skrivTilFil(ofstream& ut);

};

// ------------------------------------------------------------

class Isbil {
    private:
    string sted;
    list<Iskrem*> iskremer;

    public: 
    Isbil(ifstream& inn);
    ~Isbil();
    void leggTilIskrem();
    void skrivKort();
    void skrivLang();
    void skrivTilFil(ofstream& ut);
    void hentSted();
};

/**
 * Hovedprogrammet
 */
int main() {

}

// ============================================================
//  Iskrem – implementasjon
// ============================================================


/**
 * constructor som leser smak og pris fra fil.
 */
Iskrem::Iskrem(ifstream& inn) { 
    inn >> smak >> pris; 
}

/**
 * Leser alle smak og pris fra fil.
 */
void Iskrem::lesFraFil(ifstream& inn) {
     inn >> smak >> pris; 
}

/**
 * skriver til skjerm smak og pris.
 */
void Iskrem::skrivTilSkjerm() const {
    cout << "smak: " << smak << "pris: " << pris;
}

/**
 * skriver smak og pris til fil.
 */
void Iskrem::skrivTilFil(ofstream& ut) {
    ut << smak << ' ' << pris << ' ' << "\n";
}


// ============================================================
//  Sorbet – implementasjon
// ============================================================


/**
 * constructor, leser smak, pris og sorbetype fra fil
 */
Sorbet::Sorbet(ifstream & inn) : Iskrem(inn) {
    int type;
    inn >> type;
    sorbet = static_cast<isType>(type);
}

/**
 * leser alle sorbet data fra fil.
 */
void Sorbet::lesFraFil(ifstream & inn) {
    int input;

    Iskrem::lesFraFil(inn);     //leser smak og pris
  
    inn >> input;                //les sorbet type
    sorbet = static_cast<isType>(input);    //konverter til enum
}

/**
 * skriver ut alle sorbet data til skjerm
 */
void Sorbet::skrivTilSkjerm() {
    Iskrem::skrivTilSkjerm();
    cout << "type: ";
    switch (sorbet) {
        case Sorbe: cout << "Sorbe"; break;
        case Granite: cout << "Granite"; break;
        case Slush: cout << "Slush"; break;
    }
}

/**
 * skriver ut alle Sorbet data til fil
 */
void Sorbet::skrivTilFil(ofstream& ut) {
    Iskrem::skrivTilFil(ut);
    ut << sorbet;
}

// ============================================================
//  Floteis – implementasjon
// ============================================================

/**
 * constructor, leser smak, pris og vengastatus fra fil.
 */
Floteis::Floteis(ifstream& inn) : Iskrem(inn) {
    inn >> vegan;
}

/**
 * leser alle fløteis data fra fil.
 */
void Floteis::lesFraFil(ifstream& inn) {
    Iskrem::lesFraFil(inn);
    inn >> vegan;
}

/**
 * skriver alle fløteis data til skjerm.
 */
void Floteis::skrivTilSkjerm() const{
    Iskrem::skrivTilSkjerm();
    cout << "vegan: " << (vegan ? "Ja" : "Nei") << "\n";
}

/**
 * skrive alle fløteis data til fil.
 */
void Floteis::skrivTilFil(ofstream& ut) {
    Iskrem::skrivTilFil(ut);
    ut << vegan << "\n";
}

// ============================================================
//  isbil – implementasjon
// ============================================================

Isbil::Isbil(ifstream& inn) {
    inn >> sted;
}