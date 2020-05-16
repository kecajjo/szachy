#include "inc/plansza.hh"
#include "inc/szachy.hh"
#include <iostream>
#include <ctime> // do testow

int main(){
    plansza szachownica;
    
    while(1){
        szachownica.wyswietl();
        szachownica.czytaj_ruch();
    }
    
    return 0;
}