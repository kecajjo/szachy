#include "inc/pionek.hh"

pionek::pionek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->pierwszy_ruch=true;
    this->nazwa = 'p'; //jak w notacji szachowej
}

std::list<mozliwosc> *pionek::zasady_ruchu(){
    std::list<mozliwosc> *moja_lista = new std::list<mozliwosc>;
    if(this->kol == biali){
        moja_lista->push_back(mozliwosc(0,1,1));
        if(pierwszy_ruch == true){
            moja_lista->push_back(mozliwosc(0,2,1));
        }
    }
    if(this->kol == czarni){
        moja_lista->push_back(mozliwosc(0,-1,1));
        if(pierwszy_ruch == true){
            moja_lista->push_back(mozliwosc(0,-2,1));
        }
    }
    return moja_lista;
}
