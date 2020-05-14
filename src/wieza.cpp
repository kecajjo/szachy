#include "inc/wieza.hh"

wieza::wieza(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'w'; // jak w notacji szachowej
}

std::list<mozliwosc> *wieza::zasady_ruchu(){
    std::list<mozliwosc> *moja_lista = new std::list<mozliwosc>;
    // wszystkie mozliwosci ruchu po kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    moja_lista->push_back(mozliwosc(0,1,7));
    moja_lista->push_back(mozliwosc(0,-1,7));
    moja_lista->push_back(mozliwosc(1,0,7));
    moja_lista->push_back(mozliwosc(-1,0,7));
    return moja_lista;
}

void wieza::ruszono(){
    this->pierwszy_ruch = false;
}