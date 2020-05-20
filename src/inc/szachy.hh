#ifndef SZACHY_HH
#define SZACHY_HH

#include "plansza.hh"
#include "lifo.hh"
#include <ctime>
#include <fstream>

#define GLEBOKOSC_SI 4

class szachy{
    
    plansza szachownica;
    // realizacja algorytmu alfa beta (ulepszony minmax)
    // zapamietuje pierwszy ruch
    // za pomoca alfa_beta_wewn sprawdza, ktory pierwszy ruch jest najlepszy
    ruch alfa_beta_zewn(int glebokosc);
    float alfa_beta_wewn(int glebokosc, float alfa, float beta, kolor kol); // algorytm alfa beta zwraca najlepszy wynik
    void usun_tab_wsz_ruch(tablica_ruchow **usun);

    public:
    void czytaj_ruch(); // pozwala uzytkownikowi wpisac ruch
    void wyswietl_stan_gry();
    void ruch_gracza(wspolrzedne start, wspolrzedne koniec); // jesli jest to zgodne z zasadami rusza figure z pola start na pole koniec
    void cofnij(); // cofa ruch
    bool czy_koniec(kolor kol);
    // sztuczna inteligencja wykarzystujaca algorytm alfa beta
    void ruch_si();
    void graj_przeciw_komputerowi(const kolor &kol_gracza);
};

#endif