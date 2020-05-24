#include "inc/skoczek.hh"

skoczek::skoczek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 's'; // jak w notacji szachowej
    // wszystkie mozliwosci ruchu po kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    this->zas_ruch[0] = mozliwosc(2,1,1);
    this->zas_ruch[1] = mozliwosc(2,-1,1);
    this->zas_ruch[2] = mozliwosc(-2,1,1);
    this->zas_ruch[3] = mozliwosc(-2,-1,1);
    this->zas_ruch[4] = mozliwosc(1,2,1);
    this->zas_ruch[5] = mozliwosc(-1,2,1);
    this->zas_ruch[6] = mozliwosc(1,-2,1);
    this->zas_ruch[7] = mozliwosc(-1,-2,1);
}

mozliwosc *skoczek::zasady_ruchu(){
    return this->zas_ruch;
}

skoczek::~skoczek(){
}