#ifndef DRUZYNA_HH
#define DRUZYNA_HH

#include "figura.hh"
#include "goniec.hh"
#include "hetman.hh"
#include "krol.hh"
#include "pionek.hh"
#include "skoczek.hh"
#include "wieza.hh"

class druzyna{
    kolor kol;
    // 0 to krol, 1 hetman, 2-3 wieze, 4-5 gonce, 6-7 skoczki, 
    // 8-15 pionki i figury po promocji
    figura *wszystkie_fig[16];
    bool szach; // czy druzyna jest szachowana
    public:
    druzyna(kolor _kol);
    kolor sprawdz_kolor();
    figura* operator[](int indeks) const;
    figura*& operator[](int indeks);
    bool czy_szach(); // zwraca czy druzyna jest szachowana czy nie
    void ustaw_szach(bool _szach); // pozwala ustawic czy druzyna jest w szachu czy nie
};

#endif