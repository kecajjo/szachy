#include "inc/szachy.hh"
#include <iostream>
#include <ctime> // do testow

int main(){
    szachy gra;
    kolor kol = gra.wybierz_kolor();
    gra.graj_przeciw_komputerowi(kol);
    
    return 0;
}