#ifndef FIGURA_HH
#define FIGURA_HH

#include "wspolrzedne.hh"
#include "mozliwosc.hh"

enum kolor{
    biali = -1,
    czarni = 1
    // nikt = 0
};

class figura{
    protected:
    char nazwa;
    wspolrzedne pozycja;
    kolor kol;
    bool czy_aktywny; // jesli false to figura zbita

    public:
    void zbito();
    wspolrzedne aktualna_pozycja() const;
    void przesun(wspolrzedne nowa_pozycja);
    char zwroc_nazwe() const;
    virtual mozliwosc *zasady_ruchu() = 0;
    kolor ktora_druzyna() const;
};

#endif