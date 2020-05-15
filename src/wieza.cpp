#include "inc/wieza.hh"

wieza::wieza(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'w'; // jak w notacji szachowej
}

std::vector<mozliwosc> *wieza::zasady_ruchu(){
    std::vector<mozliwosc> *moj_vector = new std::vector<mozliwosc>;
    // wszystkie mozliwosci ruchu po kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    moj_vector->push_back(mozliwosc(0,1,7));
    moj_vector->push_back(mozliwosc(0,-1,7));
    moj_vector->push_back(mozliwosc(1,0,7));
    moj_vector->push_back(mozliwosc(-1,0,7));
    return moj_vector;
}

void wieza::ruszono(){
    this->pierwszy_ruch = false;
}