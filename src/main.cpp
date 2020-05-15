#include "inc/plansza.hh"
#include <iostream>
#include <ctime> // do testow

int main(){
    plansza szachownica;
    // skoczek bije pionka nad wieza i bije hetmana
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(1,0), wspolrzedne(2,2));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(2,2), wspolrzedne(1,4));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(1,4), wspolrzedne(0,6));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(0,6), wspolrzedne(2,5));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(2,5), wspolrzedne(3,7));

    // pionek probuje bic wieze
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(0,1), wspolrzedne(0,3));

    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(0,3), wspolrzedne(0,4));
    szachownica.rusz(wspolrzedne(0,4), wspolrzedne(0,5));
    szachownica.rusz(wspolrzedne(0,5), wspolrzedne(0,6));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(0,6), wspolrzedne(0,7));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(0,6), wspolrzedne(1,7));//bicie skoczka
    szachownica.wyswietl();

    // hetman probuje bic swojego gonca
    szachownica.rusz(wspolrzedne(3,0), wspolrzedne(2,0));
    szachownica.wyswietl();

    // hetman probuje przeskoczyc nad pionkiem przeciwnika
    szachownica.rusz(wspolrzedne(4,1), wspolrzedne(4,3));
    szachownica.rusz(wspolrzedne(4,3), wspolrzedne(4,4));
    szachownica.rusz(wspolrzedne(3,0), wspolrzedne(5,2));
    szachownica.rusz(wspolrzedne(3,6), wspolrzedne(3,4));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(5,2), wspolrzedne(2,5));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(5,2), wspolrzedne(1,6));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(5,2), wspolrzedne(0,7));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(5,2), wspolrzedne(3,4));
    szachownica.wyswietl();
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;

    //std::clock_t start_czasu = std::clock();
    //for(int i=0;i<2000000;i++){
    //    szachownica.rusz(wspolrzedne(3,4), wspolrzedne(0,1));
    //    szachownica.rusz(wspolrzedne(0,1), wspolrzedne(3,4));
    //}
    //std::clock_t koniec_czasu = std::clock();

    // pionek probuje bic powodujac ze wlasny krol jest szachowany
    //szachownica.rusz(wspolrzedne(4,4), wspolrzedne(4,5));
    //szachownica.rusz(wspolrzedne(4,5), wspolrzedne(5,6));
    //szachownica.rusz(wspolrzedne(3,4), wspolrzedne(4,5));
    //szachownica.rusz(wspolrzedne(5,1), wspolrzedne(5,3));
    //szachownica.rusz(wspolrzedne(5,3), wspolrzedne(5,4));
    //szachownica.rusz(wspolrzedne(5,4), wspolrzedne(5,5));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(4,6), wspolrzedne(5,5));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(4,5), wspolrzedne(4,1));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(4,6), wspolrzedne(5,5));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(4,1), wspolrzedne(1,4));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(4,6), wspolrzedne(5,5));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(2,6), wspolrzedne(2,5));
    //szachownica.rusz(wspolrzedne(1,4), wspolrzedne(0,3));
    //szachownica.rusz(wspolrzedne(3,1), wspolrzedne(3,3));
    //szachownica.rusz(wspolrzedne(3,3), wspolrzedne(3,4));
    //szachownica.wyswietl();
    //szachownica.rusz(wspolrzedne(2,5), wspolrzedne(3,4));
    //szachownica.wyswietl();

    // proba ruszenia gonca co spowoduje szacha
    szachownica.rusz(wspolrzedne(3,7), wspolrzedne(2,5));
    szachownica.rusz(wspolrzedne(2,7), wspolrzedne(3,6));
    szachownica.rusz(wspolrzedne(4,7), wspolrzedne(3,7));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(3,6), wspolrzedne(4,5));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(3,4), wspolrzedne(3,2));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(3,6), wspolrzedne(4,5));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(3,2), wspolrzedne(2,2));
    szachownica.rusz(wspolrzedne(3,6), wspolrzedne(4,5));
    szachownica.rusz(wspolrzedne(4,5), wspolrzedne(3,4));
    szachownica.rusz(wspolrzedne(2,2), wspolrzedne(3,2));
    szachownica.wyswietl();
    szachownica.rusz(wspolrzedne(3,4), wspolrzedne(4,3));
    szachownica.wyswietl();

    //std::cout << (float)(koniec_czasu - start_czasu)/CLOCKS_PER_SEC << std::endl;
    
    return 0;
}