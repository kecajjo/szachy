#include "inc/skoczek.hh"

skoczek::skoczek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 's'; // jak w notacji szachowej
}

std::list<mozliwosc> *skoczek::zasady_ruchu(){
    std::list<mozliwosc> *moja_lista = new std::list<mozliwosc>;
    // wszystkie mozliwosci ruchu po kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    moja_lista->push_back(mozliwosc(2,1,1));
    moja_lista->push_back(mozliwosc(2,-1,1));
    moja_lista->push_back(mozliwosc(-2,1,1));
    moja_lista->push_back(mozliwosc(-2,-1,1));
    moja_lista->push_back(mozliwosc(1,2,1));
    moja_lista->push_back(mozliwosc(-1,2,1));
    moja_lista->push_back(mozliwosc(1,-2,1));
    moja_lista->push_back(mozliwosc(-1,-2,1));

    return moja_lista;
}
