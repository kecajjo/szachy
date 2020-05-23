#ifndef GUI_HH
#define GUI_HH

#include "plansza.hh"
#include "wspolrzedne.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class GUI{

    sf::Texture plansza_tex;
    sf::Sprite plansza_sp;
    // tablica figur
    // pierwszy wymiar to rodzaj figury, drugi to kolor
    sf::Texture figury_tex[6][2];
    sf::Sprite figury_sp[6][2];
    // odleglosc miedzy polami planszy
    int siatka_x;
    int siatka_y;

    public:
    GUI();
    // kolor to kolor z ktorego perspektywy wyswietlamy plansze
    void wyswietl(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza);
    void renderuj(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza);
    // zaznacza pole ktore wybral uzytkownik i podaje jego wspolrzedne
    // jesli zamknal okno, zwraca wspolrzedne 10,10
    // kolor to kolor z ktorego perspektywy widzimy plansze
    wspolrzedne akcja_uzytkownika(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza);
    void koniec(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza, const kolor &zwyciezcy);
};

#endif