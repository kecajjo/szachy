#ifndef WIEZA_HH
#define WIEZA_HH

#include "figura.hh"

class wieza: public figura{
    mozliwosc *zas_ruch;
    bool pierwszy_ruch; // true jesli wieza sie nie ruszyla, false jesli sie ruszyla
    public:
    wieza(kolor _kol, wspolrzedne _wsp);
    mozliwosc *zasady_ruchu();
    void ruszono(); // wieza zostala ruszona
    bool czy_pierwszy(); // zwraca czy wieza jeszcze sie nie ruszala
    // w razie cofniecia pierwszego ruchu wiezy
    void ustaw_nie_ruszono();
    ~wieza();
};

#endif