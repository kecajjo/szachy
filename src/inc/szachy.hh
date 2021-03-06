#ifndef SZACHY_HH
#define SZACHY_HH

#include "plansza.hh"
#include "lifo.hh"
#include "GUI.hh"
#include <fstream>
#include <SFML/Graphics.hpp>

#define GLEBOKOSC_SI 4

class szachy{
    
    plansza szachownica;
    GUI obsluga_okienka;
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
    // zwraca czy koniec gry
    // ustawia zmiena zwyciezca na odpowiedni kolor
    bool czy_koniec(kolor &zwyciezca);
    // sztuczna inteligencja wykarzystujaca algorytm alfa beta
    void ruch_si();
    void graj_przeciw_komputerowi(const kolor &kol_gracza);
    // zapisuje do pliku jak gracz sie probowal ruszyc
    void logi_gracza(const wspolrzedne &start, const wspolrzedne &koniec) const;
    // pozwala wybrac kolor ktorym sie gra
    kolor wybierz_kolor();

};

#endif