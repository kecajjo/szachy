#ifndef GUI_HH
#define GUI_HH

#include "plansza.hh"
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
    // polozenie konkretnych pol na planszy w pikselach
    sf::Vector2f pola[8][8];

    public:
    GUI();
    void rysuj(const plansza &szachownica, sf::RenderWindow &okienko);
};

#endif