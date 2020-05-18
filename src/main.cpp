#include "inc/szachy.hh"
#include <iostream>
#include <ctime> // do testow

int main(){
    szachy gra;
    
    while(gra.czy_koniec(biali) == false && gra.czy_koniec(czarni) == false){
        gra.wyswietl_stan_gry();
        gra.czytaj_ruch();
        gra.wyswietl_stan_gry();
        gra.ruch_si();
    }
    if(gra.czy_koniec(biali) == true){
        std::cout << "Czarni wygrali" << std::endl;
    }
    if(gra.czy_koniec(czarni) == true){
        std::cout << "biali wygrali" << std::endl;
    }
    
    return 0;
}