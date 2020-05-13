#include "inc/plansza.hh"

int main(){
    plansza szachownica;
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(3,7), wspolrzedne(2,3));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(7,7), wspolrzedne(7,3));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(1,7), wspolrzedne(2,5));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(0,6), wspolrzedne(0,4));

    szachownica.wyswietl();
    return 0;
}