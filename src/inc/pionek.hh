#ifndef PIONEK_HH
#define PIONEK_HH

#include "figura.hh"

class pionek: public figura{
    bool pierwszy_ruch; // true jesli pionek sie nie ruszyl, false jesli sie ruszyl
    public:
    pionek(kolor _kol, wspolrzedne _wsp);
    mozliwosc *zasady_ruchu();
    void ruszono(); // pionek zostal ruszony
    // w razie cofniecia pierwszego ruchu pionka
    void ustaw_nie_ruszono();
    bool czy_pierwszy(); // zwraca czy pionek pionek jeszcze sie nie ruszal
    // zapisuje wektory jakimi pionki moga bic do przekazanej tablicy
    void zasady_bicia(wspolrzedne *tablica_zasad);
    ~pionek();
};

#endif