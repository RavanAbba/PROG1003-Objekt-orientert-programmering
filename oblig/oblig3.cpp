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

class Iskrem {
    private:
    string smak;
    int pris;

    public:
    // constructor
    Iskrem(ifstream& inn) { inn >> smak >> pris; }

    virtual void lesFraFil(ifstream& inn) { inn >> smak >> pris; }

    virtual void skrivTilSkjerm() {cout << "smak: " << smak << "pris: " << pris;}
    virtual void skrivTilFil(ofstream& ut) {ut << smak << ' ' << pris << "\n";}
};

class Sorbet : public Iskrem {
    private:
    isType sorbet;

    public:
    Sorbet(ifstream& inn);
    virtual void lesFraFil(ifstream& inn);
    virtual void skrivTilSkjerm();
    virtual void skrivTilFIl(ofstream& ut);
    
};

class Floteis : public Iskrem {
    private:
    bool vegan;

    public: 
    Floteis(ifstream& inn);
    virtual void lesFraFil(ifstream& inn);
    virtual void skrivTilSkjerm();
    virtual void skrivTilFil(ofstream& ut);

};

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
    void sted();
};
