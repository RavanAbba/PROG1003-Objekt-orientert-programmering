/**
 *  Skjelett for obligatorisk oppgave nr 2 i PROG1003 - OOP.
 *
 *  Programmet er en kalender der man kan legge inn heldags og
 *  tidsbegrensede aktiviteter på spesifikke dager.
 *
 *  Hovedfunksjonalitet:
 *    - Inneholder klassen 'Aktivitet' og dens to subklasser
 *      'Tidsbegrenset' og 'Heldags'. Objekter av de to siste klassene legges
 *      inn for HVER ENKELT DAG inn i to ulike vectorer inni den selvlagede
 *      containerklassen: 'Dag'
 *    - De tre første klassene inneholder alle constructorer og funksjoner
 *      for å lese og skrive alle objektets data.
 *    - 'Dag' inneholder en del ulike funksjoner for å håndtere datastrukturen
 *      inni seg. Det er disse medlemsfunksjonene som kalles i fra funksjonene
 *      som startes/kalles fra 'main' for EN gitt dag.
 *    - Den globale vectoren 'gDagene' inneholder ALLE DE ULIKE DAGENE
 *      med hver sine ulike aktiviteter.
 *
 *  @file OBLIG2.CPP
 *  @author Ravan Abbasov
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"
#include <iomanip>                 // setw, setfill
using namespace std;


/*
 *  Enum 'aktivitetsType' (med hva slags aktivitet dette er).
 */
enum aktivitetsType {Jobb, Fritid, Skole, ikkeAngitt};


/**
 *  Baseklassen 'Aktivitet' (med navn og aktivitetstype).
 */
class Aktivitet  {
  private:
    string navn;
    aktivitetsType kategori;
  public:
    Aktivitet()  {  navn = ""; kategori = ikkeAngitt; }
    void lesData();
    void skrivData() const;
};


/**
 *  Subklassen 'Tidsbegrenset' (med tidspunkter for start/stopp av aktivitet).
 */
class Tidsbegrenset : public Aktivitet  {
  private:
    int  startTime, startMin, sluttTime, sluttMin;
    bool klokkeslettOK(const int time, const int minutt) const;
  public:
    Tidsbegrenset()  { sluttMin = sluttTime = startTime = startMin = 0; };
    void lesData();
    void skrivData() const;
};


/**
 *  Subklassen 'Heldags' (med nærmere beskrivelse av aktiviteten).
 */
class Heldags : public Aktivitet  {
  private:
    string beskrivelse;
  public:
    Heldags()  { beskrivelse = ""; };
    void lesData();
    void skrivData() const;
};


/**
 *  Selvlaget container-klasse 'Dag' (med dato og ulike aktiviteter).
 */
class Dag  {
  private:
    int dagNr, maanedNr, aarNr;
    vector <Tidsbegrenset*> tidsbegrensedeAktiviteter;
    vector <Heldags*> heldagsAktiviteter;

  public:
//    Dag()  {  };
    Dag(const int dag, const int maaned, const int aar) {
                           dagNr = dag;  maanedNr = maaned;  aarNr = aar; };
    ~ Dag();
    bool harDato(const int dag, const int maaned, const int aar) const;
    void nyAktivitet();
    void skrivAktiviteter() const;
    void skrivDato() const;
};


bool dagOK(const int dag, const int maaned, const int aar);
Dag* finnDag(const int dag, const int maaned, const int aar);
void frigiAllokertMemory();
void nyAktivitet();
void skrivDager(const bool inkludertAktiviteter);
void skrivEnDag();
void skrivMeny();


vector <Dag*> gDagene;           ///<  Dager med aktiviteter


/**
 *  Hovedprogrammet:
 */
int main ()  {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q')  {
        switch (kommando)  {
          case 'N': nyAktivitet();      break;
          case 'A': skrivDager(true);   break;
          case 'S': skrivEnDag();       break;
          default:  skrivMeny();        break;
        }
        kommando = lesChar("\nKommando");
    }

    frigiAllokertMemory();

    return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Leser inn ALLE klassens data.
 */
void Aktivitet::lesData() {
  int valg;         // trenger for å static_cast e enum.

  cout << "aktivitetens navn: ";
  cin >> navn;
  cout << "\naktivitetens kategori (0=Jobb, 1=Fritid, 2=Skole): ";
  cin >> valg;
  kategori = static_cast<aktivitetsType>(valg);
  
}


/**
 *  Skriver ut ALLE klassens data.
 */
void Aktivitet::skrivData() const {
  cout << "Skriver ut datamedlemene: \n";
  cout << navn << endl;
  
  // bruker switch for å skrive ut riktige kategori.
  switch (kategori) {
    case Jobb: cout << "Jobb"; break;
    case Fritid: cout << "Fritid"; break;
    case Skole: cout << "Skole"; break;
    case ikkeAngitt: cout << "Ikke angitt"; break;
  }
  cout << endl;

}


/**
 *  Leser inn ALLE klassens data, inkludert morklassens data.
 *
 *  @see   Aktivitet::lesData()
 *  @see   klokkeslettOK(...)
 */
void Tidsbegrenset::lesData() {
  Aktivitet::lesData(); 

  do  {
    cout << "timeslett for start (mellom 0 og 23): ";
    cin >> startTime;
    cout << "\nMinutt for start (mellom 0 og 59): ";
    cin >> startMin;
  } while (!klokkeslettOK(startTime, startMin));

  do {
    cout << "\nTimeslett for slutt (mellom 0 og 23): ";
    cin >> sluttTime;
    cout << "\nMinutt for slutt (mellom 0 og 59): ";
    cin >> sluttMin;
  } while (!klokkeslettOK(sluttTime, sluttMin) || (sluttTime < startTime) || 
          (sluttTime == startTime && sluttMin < startMin));

  


}


/**
 *  Privat funksjon som finner ut om input er et lovlig klokkeslett.
 *
 *  @param   time    -  Timen som skal evalueres til mellom 0 og 23
 *  @param   minutt  -  Minuttet som skal evalueres til mellom 0 og 59
 *  @return  Om parametrene er et lovlig klokkeslett eller ei
 */
bool Tidsbegrenset::klokkeslettOK(const int time, const int minutt) const {
// returnerer true hvis innenfor gyldige verdi.
  return (time >= 0 && time <=23 && minutt >= 0 && minutt <= 59);

}


/**
 *  Skriver ut ALLE klassens data, inkludert morklassens data.
 *
 *  @see   Aktivitet::skrivData()
 */
void Tidsbegrenset::skrivData() const {         //  Skriver mor-klassens data.
  Aktivitet::skrivData();

  cout << setw(2) << setfill('0') << startTime << ":"
  << setw(2) << setfill ('0') << startMin << " - "
  << setw(2) << setfill('0') << sluttTime << ":"
  << setw(2) << setfill('0') << sluttMin << endl;
}


/**
 *  Leser inn ALLE klassens data, inkludert morklassens data.
 *
 *  @see   Aktivitet::lesData()
 */
void Heldags::lesData() {
  Aktivitet::lesData();

  cout << "Beskrivelse av aktivitet: ";
  cin.ignore();
  getline(cin, beskrivelse);
}


/**
 *  Skriver ut ALLE klassens data, inkludert morklassens data.
 *
 *  @see   Aktivitet::skrivData()
 */
void Heldags::skrivData() const {
  Aktivitet::skrivData();
  cout << "\nBeskrivelse: \n";
  cout << beskrivelse << endl;

}


/**
 *  Destructor som sletter HELT begge vectorenes allokerte innhold.
 */
Dag :: ~ Dag() {
  //sjekker gjennom vektoren
  for (int i = 0; i < tidsbegrensedeAktiviteter.size(); i++) {
    //sletter pekeren på lokasjon i.
    delete tidsbegrensedeAktiviteter[i];
  }
  tidsbegrensedeAktiviteter.clear();     // tømmer selve vektoren for pekeren

//gjør det samme for andre vektoren.
  for (int i = 0; i < heldagsAktiviteter.size(); i++ ) {
    delete heldagsAktiviteter[i];
}
  heldagsAktiviteter.clear();
}

/**
 *  Finner ut om selv er en gitt dato eller ei.
 *
 *  @param   dag     -  Dagen som skal sjekkes om er egen dag
 *  @param   maaned  -  Måneden som skal sjekkes om er egen måned
 *  @param   aar     -  Året som skal sjekkes om er eget år
 *  @return  Om selv er en gitt dato (ut fra parametrene) eller ei
 */
bool Dag::harDato(const int dag, const int maaned, const int aar) const {
  //returner true hvis alt stemmer.
  return (dagNr == dag && maanedNr == maaned && aarNr == aar);
}


/**
 *  Oppretter, leser og legger inn en ny aktivitet på dagen.
 *
 *  @see   Tidsbegrenset::lesData()
 *  @see   Heldags::lesData()
 */
void Dag::nyAktivitet()  {

//  Lag innmaten
}


/**
 *  Skriver ut ALLE aktiviteter på egen dato (og intet annet).
 *
 *  @see   Heldags::skrivData()
 *  @see   Tidsbegrenset::skrivData()
 */
void Dag::skrivAktiviteter() const {

//  Lag innmaten
}


/**
 *  Skriver KUN ut egen dato.
 */
void Dag::skrivDato() const {

//  Lag innmaten
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Returnerer om en dato er lovlig eller ei.
 *
 *  @param   dag     -  Dagen som skal sjekkes
 *  @param   maaned  -  Måneden som skal sjekkes
 *  @param   aar     -  Året som skal sjekkes
 *  @return  Om datoen er lovlig/OK eller ei
 */
bool dagOK(const int dag, const int maaned, const int aar)  {

//  Lag innmaten
}


/**
 *  Returnerer om mulig en peker til en 'Dag' med en gitt dato.
 *
 *  @param   dag     -  Dagen som skal bli funnet
 *  @param   maaned  -  Måneden som skal bli funnet
 *  @param   aar     -  Året som skal bli funnet
 *  @return  Peker til aktuell Dag (om funnet), ellers 'nullptr'
 *  @see     harDato(...)
 */
Dag* finnDag(const int dag, const int maaned, const int aar)  {

//  Lag innmaten
}


/**
 *  Frigir/sletter ALLE dagene og ALLE pekerne i 'gDagene'.
 */
void frigiAllokertMemory()  {

//  Lag innmaten
}


/**
 *  Legger inn en ny aktivitet på en (evt. ny) dag.
 *
 *  @see   skrivDager(...)
 *  @see   dagOK(...)
 *  @see   finnDag(...)
 *  @see   Dag::nyAktivitet()
 */
void nyAktivitet()  {

//  Lag innmaten
}


/**
 *  Skriver ut ALLE dagene (MED eller UTEN deres aktiviteter).
 *
 *  @param   inkludertAktiviteter - Utskrift av ALLE aktivitetene også, eller ei
 *  @see     Dag::skrivDato()
 *  @see     Dag::skrivAktiviteter()
 */
void skrivDager(const bool inkludertAktiviteter)  {

//  Lag innmaten
}


/**
 *  Skriver ut ALLE data om EN gitt dag.
 *
 *  @see   skrivDager(...)
 *  @see   dagOK(...)
 *  @see   finnDag(...)
 *  @see   Dag::skrivAktiviteter()
 */
void skrivEnDag()  {

//  Lag innmaten
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
   cout << "\nDisse kommandoene kan brukes:\n"
        << "\tN - Ny aktivitet\n"
        << "\tA - skriv ut Alle dager med aktiviteter\n"
        << "\tS - Skriv EN gitt dag og (alle) dens aktiviteter\n"
        << "\tQ - Quit / avslutt\n";
}
