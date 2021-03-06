#ifndef FIGURA_HH
#define FIGURA_HH

#include "wspolrzedne.hh"
#include "mozliwosc.hh"

enum kolor{
    biali = -1,
    czarni = 1,
    nikt = 0 // wykorzystywane tylko przy sprawdzaniu mata/pata
};

class figura{
    protected:
    char nazwa;
    wspolrzedne pozycja;
    kolor kol;
    bool czy_aktywny; // jesli false to figura zbita

    public:
    virtual ~figura(){}
    void zbito();
    void zmien_na_aktywna();
    wspolrzedne aktualna_pozycja() const;
    void przesun(wspolrzedne nowa_pozycja);
    char zwroc_nazwe() const;
    virtual mozliwosc *zasady_ruchu() = 0;
    kolor ktora_druzyna() const;
    bool czy_aktywna(); // sprawdza czy dana figura byla juz zbita
};

#endif