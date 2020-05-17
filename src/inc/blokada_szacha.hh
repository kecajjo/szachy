#ifndef BLOKADA_SZACHA_HH
#define BLOKADA_SZACHA_HH

#include <iostream>
#include "wspolrzedne.hh"
// struktura zawiera pola na ktore mozna sie ruszyc podczas pojedynczego szacha, zeby zablokowac dostep do krola
struct blokada_szacha{
    private:
    wspolrzedne tablica[7]; // tyle ruchow maksymalnie moze miec dostepna figura
    public:
    int rozmiar;
    blokada_szacha(){
        this->rozmiar=0;
    }
    wspolrzedne operator[](int indeks) const{
        int roz = this->rozmiar;
        if(indeks<roz){
            return this->tablica[indeks];
        }
        // w razie proby odwolania do nieistniejacego elementu zwraca pierwszy element
        std::cout << "nie ma takiego elementu, zwrocono pierwszy element" << std::endl;
        return this->tablica[0];
    }

    wspolrzedne& operator[](int indeks){
        int roz = this->rozmiar;
        if(indeks<roz){
            return this->tablica[indeks];
        }
        // w razie proby odwolania do nieistniejacego elementu zwraca pierwszy element
        std::cout << "nie ma takiego elementu, zwrocono pierwszy element" << std::endl;
        return this->tablica[0];
    }

    void dodaj_elem(wspolrzedne wsp){
        if(rozmiar>6){
            std::cout << "proba przepelnienia tablicy blokady" << std::endl << "x: " << wsp.x << " y: " << wsp.y << std::endl;
            return;
        }
        this->tablica[rozmiar] = wsp;
        ++rozmiar;
    }
};

#endif