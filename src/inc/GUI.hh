#ifndef GUI_HH
#define GUI_HH

#include "plansza.hh"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

class GUI{
    sf::RenderWindow okno;
    sf::Event wydarzenie;
    public:
    GUI();
    void wyswietl(const plansza &szachownica);
    // sprawdza czy zamknieto okno albo zaznaczono figure
    void sprawdzaj_wydarzenia();
};

#endif