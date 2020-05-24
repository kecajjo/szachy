#include "inc/krol.hh"

krol::krol(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'k'; // jak w notacji szachowej
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    this->zas_ruch[0] = mozliwosc(1,1,1);
    this->zas_ruch[1] = mozliwosc(-1,1,1);
    this->zas_ruch[2] = mozliwosc(1,-1,1);
    this->zas_ruch[3] = mozliwosc(-1,-1,1);
    this->zas_ruch[4] = mozliwosc(0,1,1);
    this->zas_ruch[5] = mozliwosc(0,-1,1);
    this->zas_ruch[6] = mozliwosc(1,0,1);
    this->zas_ruch[7] = mozliwosc(-1,0,1);
}

mozliwosc *krol::zasady_ruchu(){
    return this->zas_ruch;
}

void krol::ruszono(){
    this->pierwszy_ruch = false;
}

void krol::ustaw_nie_ruszono(){
    this->pierwszy_ruch = true;
}

bool krol::czy_pierwszy(){
    return this->pierwszy_ruch;
}

krol::~krol(){
}