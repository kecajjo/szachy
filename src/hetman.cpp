#include "inc/hetman.hh"

hetman::hetman(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'h'; // jak w notacji szachowej
    this->zas_ruch = new mozliwosc[8]{
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
        mozliwosc(1,1,7),
        mozliwosc(-1,1,7),
        mozliwosc(1,-1,7),
        mozliwosc(-1,-1,7),
        mozliwosc(0,1,7),
        mozliwosc(0,-1,7),
        mozliwosc(1,0,7),
        mozliwosc(-1,0,7)
    };
}

mozliwosc *hetman::zasady_ruchu(){    
    return this->zas_ruch;
}

hetman::~hetman(){
    delete [] this->zas_ruch;
}