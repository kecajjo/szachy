#include "inc/skoczek.hh"

skoczek::skoczek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 's'; // jak w notacji szachowej
    this->zas_ruch = new mozliwosc[8]{
        // wszystkie mozliwosci ruchu po kolumnach
        // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
        mozliwosc(2,1,1),
        mozliwosc(2,-1,1),
        mozliwosc(-2,1,1),
        mozliwosc(-2,-1,1),
        mozliwosc(1,2,1),
        mozliwosc(-1,2,1),
        mozliwosc(1,-2,1),
        mozliwosc(-1,-2,1)
    };
}

mozliwosc *skoczek::zasady_ruchu(){
    return this->zas_ruch;
}

skoczek::~skoczek(){
    delete [] this->zas_ruch;
}