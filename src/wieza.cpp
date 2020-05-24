#include "inc/wieza.hh"

wieza::wieza(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'w'; // jak w notacji szachowej
    // wszystkie mozliwosci ruchu po kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    this->zas_ruch[0] = mozliwosc(0,1,7);
    this->zas_ruch[1] = mozliwosc(0,-1,7);
    this->zas_ruch[2] = mozliwosc(1,0,7);
    this->zas_ruch[3] = mozliwosc(-1,0,7);
}

mozliwosc *wieza::zasady_ruchu(){
    return this->zas_ruch;
}

void wieza::ruszono(){
    this->pierwszy_ruch = false;
}

void wieza::ustaw_nie_ruszono(){
    this->pierwszy_ruch = true;
}

bool wieza::czy_pierwszy(){
    return this->pierwszy_ruch;
}

wieza::~wieza(){
}