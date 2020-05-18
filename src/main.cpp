#include "inc/szachy.hh"
#include <iostream>
#include <ctime> // do testow

int main(){
    szachy gra;
    
    while(gra.czy_koniec(biali) == false && gra.czy_koniec(czarni) == false){
        gra.wyswietl_stan_gry();
        gra.czytaj_ruch();
    }
    
    return 0;
}