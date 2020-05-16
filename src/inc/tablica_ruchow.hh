#ifndef TABLICA_RUCHOW_HH
#define TABLICA_RUCHOW_HH

#include <iostream>
#include "wspolrzedne.hh"
// struktura powstala by przyspieszyc dzialanie kosztem pamieci
// dodawanie elementow do vectora przy koniecznosci realokacji wydluzalo zbytnio czas dzialania programu
struct tablica_ruchow{
    private:
    wspolrzedne tablica[27]; // tyle ruchow maksymalnie moze miec dostepna figura
    public:
    int rozmiar;
    tablica_ruchow(){
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
        if(rozmiar>27){
            std::cout << "proba przepelnienia tablicy ruchow" << std::endl;
        }
        this->tablica[rozmiar] = wsp;
        ++rozmiar;
    }
};

#endif