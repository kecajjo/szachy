#ifndef SZACHY_HH
#define SZACHY_HH

#include "plansza.hh"
#include "lifo.hh"

class szachy{
    
    plansza szachownica;

    public:
    void czytaj_ruch(); // pozwala uzytkownikowi wpisac ruch
    void wyswietl_stan_gry();
    void ruch_gracza(wspolrzedne start, wspolrzedne koniec); // jesli jest to zgodne z zasadami rusza figure z pola start na pole koniec

    void test_wsz_ruch();
};

#endif