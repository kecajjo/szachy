#include "inc/wieza.hh"

wieza::wieza(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'w'; // jak w notacji szachowej
}

mozliwosc *wieza::zasady_ruchu(){
    mozliwosc *moj_vector = new mozliwosc[4]{
    // wszystkie mozliwosci ruchu po kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    (mozliwosc(0,1,7)),
    (mozliwosc(0,-1,7)),
    (mozliwosc(1,0,7)),
    (mozliwosc(-1,0,7))
    };
    return moj_vector;
}

void wieza::ruszono(){
    this->pierwszy_ruch = false;
}