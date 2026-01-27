/**
 *   Programeksempel nr 21 - STL:  list, stack, queue.
 *
 *   Eksemplet viser bruk av containerne 'list', 'stack' og 'queue', samt
 *   bruken av NOEN av de TILHØRENDE funksjonene i de AKTUELLE containerne.
 *
 *   @file     EKS_21.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  string
#include <list>                      //  list
#include <stack>                     //  stack
#include <queue>                     //  queue
using namespace std;


template <typename T>                //  'template' er IKKE pensum i emnet!
     void skrivListe(const list <T> liste);
void skrivStakk(stack <int> stakk);
void skrivKo(queue <int> ko);


/**
 *  Hovedprogrammet:
 */
int main()  {

// ***************************************************************************
cout << "\n**************************   LIST:   **************************\n";
// ***************************************************************************

    list <int> liste1, liste2;         //  Definerer 2x list-containere.

    for (int i = 0;  i < 13;  i++) {   //  Initierer/fyller listene:
        liste1.push_back(i * 3);
        liste2.push_front(i * 4);
    }

    cout << "\nInitielle lister:\n";   //  Skriver listenes initielle innhold:
    cout << "\t'liste1':  ";     skrivListe(liste1);
    cout << "\t'liste2':  ";     skrivListe(liste2);

                                       //  SKRIVER første og siste element:
    cout << "liste1.front():        " << liste1.front() << '\n';
    cout << "liste1.back():         " << liste1.back()  << "\n\n";

    cout << "liste1.pop_front():  ";   //  FJERNER/SLETTER første element:
    liste1.pop_front();        skrivListe(liste1);

    cout << "liste2.size() for:     " << liste2.size() << '\n';
    cout << "liste2.pop_back():   ";   //  FJERNER/SLETTER bakerste element:
    liste2.pop_back();         skrivListe(liste2);
    cout << "liste2.size() etter:   " << liste2.size() << "\n\n";

    cout << "liste1.reverse():    ";   //  SNUR/REVERSERER listen:
    liste1.reverse();          skrivListe(liste1);

    cout << "liste2.sort():       ";   //  SORTERER listen:
    liste2.sort();             skrivListe(liste2);

    liste1.sort();          //  I dette tilfellet:  = liste1.reverse();
    cout << "liste1.sort/reverse() og liste1.remove(...):  ";
    liste1.remove(10);                 //  FJERNER/SLETTER gitt elementer:
    liste1.remove(12);
    liste1.remove(13);      //  Finnes ikke - så ingenting skjer.
                               skrivListe(liste1);

    cout << "liste1.swap(liste2):\n";  //  BYTTER to listers innhold:
    liste1.swap(liste2);
    cout << "\t'liste1':  ";     skrivListe(liste1);
    cout << "\t'liste2':  ";     skrivListe(liste2);

    cout << "liste1.merge(liste2):";   //  FLYTTER over og FLETTER lister:
    liste1.merge(liste2);      skrivListe(liste1);

    cout << "'liste2' etterpaa: ";
    if (!liste2.empty())  skrivListe(liste2);
    else cout << "     TOMT !!!\n\n";  //  ALT FLYTTET OVER, dvs. TOMT !!!

    cout << "liste1.size() for:     " << liste1.size() << '\n';
    cout << "liste1.unique():     "; // FJERNER ETTERFØLGENDE(!!!) DUPLIKATER:
    liste1.unique();           skrivListe(liste1);
    cout << "liste1.size() etter:   " << liste1.size() << '\n';
                                    //  NB:  Skal ALLE duplikater fjernes,
                                    //       forutsetter det at listen/dataene
                                    //       er sorterte først !!

//  NB: Totalt er nesten 40x ulike funksjoner tilgjengelig!


// **************************************************************************
cout << "\n\n\n***********************   STACK:   ***********************\n";
// **************************************************************************

    stack <int> stakk;  //  Default brukes 'deque' i stakken. Og dette er like
                        //  greit, selv om vi ikke har lært noe om dette.
                        //  Alternativt kunne stakken ha vært opprettet via:
                        //     stack <int, vector <int> > stakk;   eller
                        //     stack <int, list <int> > stakk;
                        //  Men, i vårt emne spiller dette liten rolle.

    stakk.push(41);     //  Legger stadig inn ny elementer FORREST i stakken:
    stakk.push(312);
    stakk.push(29);
    stakk.push(304);
    stakk.push(17);
    stakk.push(22);

    cout << "\nInitiell 'stakk':  ";   skrivStakk(stakk);

    cout << "stakk.size():  " << stakk.size() << '\n';  //  Antall i stakken.
    cout << "stakk.top():   " << stakk.top()  << '\n';  //  SER PÅ den første.

    cout << "\nstakk.pop(): ";
    stakk.pop();                  skrivStakk(stakk);    //  TAR UT den første.

//  I tillegg finnes:  emplace, swap


// **************************************************************************
cout << "\n\n\n***********************   QUEUE:   ***********************\n";
// **************************************************************************

    queue <int> ko;                  //  Samme kommentar som for 'stack'.

    ko.push(41);            //  Legger stadig inn ny elementer BAKERST i køen:
    ko.push(312);
    ko.push(29);
    ko.push(304);
    ko.push(17);
    ko.push(22);
    ko.push(304);

    cout << "\nInitiell 'ko':  ";     skrivKo(ko);

    cout << "ko.size():    " << ko.size()  << '\n';   //  Antall i køen.
    cout << "ko.front():   " << ko.front() << '\n';   //  SER PÅ den første.
    cout << "ko.back():    " << ko.back()  << '\n';   //  SER PÅ den siste.

    cout << "ko.pop():   ";
    ko.pop();                         skrivKo(ko);  //  TAR UT den første.

//  I tillegg finnes:  emplace, swap


// **************************************************************************
cout << "\n\n\n****************   LIST (med 'string'):   ****************\n";
// **************************************************************************

    list <string> tekster;              //  Liste med tekster/strenger.

    tekster.push_front("Charlie");      //  Legger inn forrest og bakerst:
    tekster.push_front("Henry");
    tekster.push_front("Dennis");
    tekster.push_back("Patrick");
    tekster.push_back("Ian");
    tekster.push_back("Fredrik");

    cout << "\nInitiell 'tekster':   ";     skrivListe(tekster);

    tekster.reverse();                  //  SNUR hele listen:
    cout << "\n'tekster' reversert:  ";     skrivListe(tekster);

    tekster.sort();                     //  SORTERER hele listen:
    cout << "\n'tekster' sortert:    ";     skrivListe(tekster);

    tekster.pop_back();                 //  TAR UT/FJERNER den bakerste/siste.
    tekster.pop_front();                //  TAR UT/FJERNER den første.
    tekster.remove("Ian");              //  TAR UT/FJERNER (om mulig) 'Ian'.
    cout << "\nFjernet forreste, bakerste og 'Ian':  ";   skrivListe(tekster);

    cout << "Antall i listen:  " << tekster.size() << "\n\n";
    tekster.clear();                    //  ALT i listen SLETTES/FJERNES.
    if (tekster.empty()) cout << "Listen er naa tom (cleared)!\n\n";



// **************************************************************************
// **   NB:  Skal senere se på/bruke containere med PEKERE til OBJEKTER.   **
// **************************************************************************

    return 0;
}


/**
 *  Skriver HELE en listes innhold.
 *
 *  NB:  Her brukes 'template' som IKKE er pensum i emnet !!!
 *       Det brukes også 'iterator' som innføres i EKS_23.CPP
 *
 *  @param   liste - list-container av datatypen 'T'
 */
template <typename T>                    //  'T' - fleksibel datatype.
                                         //  'const' eller '&', da listen
                                         //     IKKE endres, bare traverseres.
void skrivListe(const list <T> liste) {  //  Går igjennom HELE listen,
  for (auto it = liste.begin();  it != liste.end();  it++) //   vha. ITERATOR:
        cout << "  " << *it;                  //  Skriver den TILPEKTE.
    cout << "\n\n";
}


/**
 *  Skriver HELE en stakks innhold.
 *
 *  @param   stakk - stack-container med int'er (lagret i en 'deque')
 */
void skrivStakk(stack <int> stakk)  {  //  Får KOPI av stakken !!!
                                //  Hadde det vært brukt '&', så hadde
                                //    originalen vært brukt - og blitt tømt!!!
    while (!stakk.empty())  {          //  Ennå elementer igjen:
        cout << "  " << stakk.top();   //  Viser/skriver den første/øverste.
        stakk.pop();                   //  Tar ut/av den første/øverste.
    }
    cout << "\n\n";
}


/**
 *  Skriver HELE en køs innhold.
 *
 *  @param   ko - queue-container med int'er (lagret i en 'deque')
 */
void skrivKo(queue <int> ko)  {         //  Samme  kommentar som 'skrivStakk'.
    while (!ko.empty())  {              //  Ennå elementer igjen:
        cout << "  " << ko.front();     //  Viser/skriver den første.
        ko.pop();                       //  Tar ut/fjerner den første.
    }
    cout << "\n\n";
}
