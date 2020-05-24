#include "inc/hetman.hh"

hetman::hetman(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'h'; // jak w notacji szachowej
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    this->zas_ruch[0] = mozliwosc(1,1,7);
    this->zas_ruch[1] = mozliwosc(-1,1,7);
    this->zas_ruch[2] = mozliwosc(1,-1,7);
    this->zas_ruch[3] = mozliwosc(-1,-1,7);
    this->zas_ruch[4] = mozliwosc(0,1,7);
    this->zas_ruch[5] = mozliwosc(0,-1,7);
    this->zas_ruch[6] = mozliwosc(1,0,7);
    this->zas_ruch[7] = mozliwosc(-1,0,7);
}

mozliwosc *hetman::zasady_ruchu(){    
    return this->zas_ruch;
}

hetman::~hetman(){
}