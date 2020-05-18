#include "inc/krol.hh"

krol::krol(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'k'; // jak w notacji szachowej
}

mozliwosc *krol::zasady_ruchu(){
    mozliwosc *moj_vector = new mozliwosc[8]{
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    (mozliwosc(1,1,1)),
    (mozliwosc(-1,1,1)),
    (mozliwosc(1,-1,1)),
    (mozliwosc(-1,-1,1)),
    (mozliwosc(0,1,1)),
    (mozliwosc(0,-1,1)),
    (mozliwosc(1,0,1)),
    (mozliwosc(-1,0,1))
    };

    return moj_vector;
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