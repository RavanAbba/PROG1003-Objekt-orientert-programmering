/**
 *  obligatorisk oppgave 3
 * 
 * Programmet holder oversikt over isbiler og iskremer.
 * Skriver fra fil, skriver ut isbiler og legger til iskrem.
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
 #include <cctype>      // toupper

using namespace std;

enum isType {Sorbe, Granite, Slush};

vector <Isbil*> gAlleIsbiler;        // global variabel som peker til alle isbilene
// ============================================================
//  Klassedeklarasjoner
// ============================================================

class Iskrem {
    private:
    string smak;
    int pris;

    public:
    Iskrem(ifstream& inn);
    Iskrem();               //tror jeg må ha dette som default constructor når jeg oppreder ny iskrem
    virtual void lesData();
    virtual void skrivTilSkjerm() const;
    virtual void skrivTilFil(ofstream& ut);
};

// ------------------------------------------------------------

class Sorbet : public Iskrem {
    private:
    isType sorbet;

    public:
    Sorbet(ifstream& inn);
    Sorbet();                   //samme grunn som over
    virtual void lesData();
    virtual void skrivTilSkjerm() const;
    virtual void skrivTilFil(ofstream& ut);
    
};

// ------------------------------------------------------------

class Floteis : public Iskrem {
    private:
    bool vegan;

    public: 
    Floteis(ifstream& inn);
    Floteis();              //samme grunn som over
    virtual void lesData();
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
    string hentSted() const;
};

// ============================================================
//  Deklarasjon av globale variabler
// ============================================================

void skrivMeny();
void skrivAlleIsbiler();
void skrivBilOgEvtLeggInn(const bool leggInn);
void skrivTilFil();
void lesFraFil();
Isbil* finnIsbil(const string& sted);

// ============================================================
//  Hovedprogrammet
// ============================================================

int main() {
    char valg;

    lesFraFil();

    do {

        skrivMeny();

        cout << "\nValg: ";
        cin >> valg;
        valg = toupper(valg);

        switch (valg) {

            case 'A': skrivAlleIsbiler(); break;

            case 'E': skrivBilOgEvtLeggInn(false); break;

            case 'L': skrivBilOgEvtLeggInn(true); break;

            case 'Q': cout << "Avslutter programmet.\n"; break;

            default: cout << "Ugyldig valg.\n";
        }

    } while (valg != 'Q');

    skrivTilFil();

    for (Isbil* bil : gAlleIsbiler)
        delete bil;

    return 0;

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
 * Tom constructor
 */
Iskrem::Iskrem() { }

/**
 * Leser smak og pris.
 */
void Iskrem::lesData() {
    cout << "smak: ";
    cin.ignore();
    getline(cin, smak);

    pris = lesInt("Pris: ", 0, 1000);
}

/**
 * skriver til skjerm smak og pris.
 */
void Iskrem::skrivTilSkjerm() const {
    cout << "smak: " << smak << " pris: " << pris;
}

/**
 * skriver smak og pris til fil.
 * 
 * @param ut  Filen det skal skrives til.
 */
void Iskrem::skrivTilFil(ofstream& ut) {
    ut << smak << ' ' << pris << "\n";
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
 * tom constructor
 */
Sorbet::Sorbet() : Iskrem() { }

/**
 * leser alle sorbet data fra fil.
 */
void Sorbet::lesData() {
    int input;

    Iskrem::lesData();     //leser smak og pris
  
    input = lesInt("Type (0=Sorbe,1=Granite,2=Slush): ", 0, 2);  //les sorbet type
    sorbet = static_cast<isType>(input);    //konverter til enum
}

/**
 * skriver ut alle sorbet data til skjerm
 */
void Sorbet::skrivTilSkjerm() const{
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
 * 
 * @param ut  Filen det skal skrives til.
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
 * tom constructor.
 */
Floteis::Floteis() : Iskrem() { }

/**
 * leser alle fløteis data.
 */
void Floteis::lesData() {
    Iskrem::lesData();
    vegan = lesInt("Vegan (0 = nei, 1 = ja)", 0, 1);
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
 * 
 * @param ut  Filen det skal skrives til
 */
void Floteis::skrivTilFil(ofstream& ut) {
    Iskrem::skrivTilFil(ut);
    ut << vegan << "\n";
}

// ============================================================
//  isbil – implementasjon
// ============================================================

/**
 * constructor.
 */
Isbil::Isbil(ifstream& inn) {
    int antall;
    int typeNr;

    inn >> sted >> antall;
    for (int i = 0; i < antall; i++) {
        inn >> typeNr;
        if (typeNr == 1) iskremer.push_back(new Sorbet(inn));
        else iskremer.push_back(new Floteis(inn));
    }
}

/**
 * Destructor. sletter alle iskrem i listet.
 */
Isbil::~Isbil() {
    for (auto* is : iskremer) delete is;
    iskremer.clear();
}

/**
 * Leser ny iskrem og legger den til.
 */
void Isbil::leggTilIskrem() {
    int valg = lesInt("1 = Sorbet, 2 = Floteis: ", 1, 2);
    Iskrem* ny;

    if (valg == 1) {
        ny = new Sorbet();
    }
    else {
        ny = new Floteis();
    }
    ny->lesData();              //les datta fra bruker
    iskremer.push_back(ny);     //legg i lista
}

/**
 * skriver ut sted og antallet is.
 */
void Isbil::skrivKort() {
    cout << sted << "\n Antall is: " << iskremer.size();
}

/**
 * Skriver alle data om isbilen og alle iskremene.
 */
void Isbil::skrivLang() {
    skrivKort();
    for ( Iskrem* iskrem : iskremer) {
        iskrem->skrivTilSkjerm();
    }
}

/**
 * skriver ut til fil.
 * 
 * @param ut  Filen det skal skrives til.
 */
void Isbil::skrivTilFil(ofstream& ut) {
    ut << sted << " " << iskremer.size() << "\n";
    //looper gjennom hver iskrem og skriver ut en om gangen.
    for (Iskrem* iskrem : iskremer) {
        iskrem->skrivTilFil(ut);
    }
}

/**
 * returner bilens lokasjon
 */
string Isbil::hentSted() const {
    return sted;
}

// ============================================================
//  Globale funksjoner
// ============================================================

/**
 * skriver ut meny
 */
void skrivMeny() {
    char valg;
    cout << "\nA - Skriv ut alle isbiler";
    cout << "\nE - Skriv en isbil";
    cout << "\nL - Legg til iskrem";
    cout << "\nQ - Avslutt";
    cout << "\nValg: ";
    cin >> valg;
    valg = toupper(valg);

    switch (valg) {
        case 'A': skrivAlleIsbiler(); break;
        case 'E': skrivBilOgEvtLeggInn(false); break;
        case 'L': skrivBilOgEvtLeggInn(true); break;
        case 'Q': cout << "Avslutter programmet.\n"; break;
        default: cout << "Ugyldig valg.\n";
    }
}

/**
 * Skriver ut alle isbilenes hoveddata
 */
void skrivAlleIsbiler() {
    if (gAlleIsbiler.empty()) {
        cout << "ingen isbiler registrert. \n";
    }
    else {
        for (Isbil* bil : gAlleIsbiler) {
            bil->skrivKort();
        }
    }
}

/**
 * skriver alle isbiler, hvis den finnes så leser den ett sted fra brukeren og skriver alle data til isbil
 * 
 * @param leggInn - true hvis bruker skal legge inn ny iskrem
 * @see skrivAlleIsbiller()
 * @see finnIsbil()
 * @see Isbil::leggTilIskrem()
 */
void skrivBilOgEvtLeggInn(const bool leggInn) {
    string sted;
    skrivAlleIsbiler();

    if (gAlleIsbiler.empty()) cout << "Ingen isbiller er registret.\n";
    else {
        cout << "\nSted: ";
        cin.ignore();
        getline(cin, sted);

        //sjekker om bilen fins
        Isbil* bil = finnIsbil(sted);

        if (bil != nullptr) {
            bil->skrivLang();

            if (leggInn) bil->leggTilIskrem();
        }
        else cout << "Fant ikke isbil.\n";
    }
}

/**
 * skriver aøøe bilene og dens data til fil.
 */
void skrivTilFil() {
    //oppretter fil
    ofstream ut("ISBIL.DTA");
    //skriver antall bil til fil
    ut << gAlleIsbiler.size() << "\n";
    //skriver hver bil til fil
    for (Isbil* isbil : gAlleIsbiler) isbil->skrivTilFil(ut);
}

/**
 * leser hele datasktrukturen fra fil
 */
void lesFraFil() {
    int antall;
    //leser fra filen
    ifstream inn("ISBIL.DTA");

    if (!inn) cout << "fant ikke filen.\n";
    else {
        inn >> antall;
        for (int i = 0; i < antall; i++) {
            gAlleIsbiler.push_back(new Isbil(inn));
        }
    }
}

/**
 * returnerer lokasjon hvis det er riktig.
 * 
 * @param sted - område, lokasjon til isbil.
 */
Isbil* finnIsbil(const string& sted) {
    for (Isbil* bil : gAlleIsbiler) {
        if (bil->hentSted() == sted) return bil;
    }

    return nullptr;
}