#include "inc/szachy.hh"
#include <iostream>
#include <ctime> // do testow

int main(){
    szachy gra;
    
    while(1){
        gra.wyswietl_stan_gry();
        gra.czytaj_ruch();
    }
    
    return 0;
}