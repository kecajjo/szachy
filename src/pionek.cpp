#include "inc/pionek.hh"

pionek::pionek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->pierwszy_ruch=true;
    this->nazwa = 'p'; //jak w notacji szachowej
}

std::vector<mozliwosc> *pionek::zasady_ruchu(){
    std::vector<mozliwosc> *moja_lista = new std::vector<mozliwosc>;
    if(this->kol == biali){
        if(pierwszy_ruch == true){
            moja_lista->push_back(mozliwosc(0,1,2));
        } else{
            moja_lista->push_back(mozliwosc(0,1,1));
        }
    }
    if(this->kol == czarni){
        if(pierwszy_ruch == true){
            moja_lista->push_back(mozliwosc(0,-1,2));
        } else{
            moja_lista->push_back(mozliwosc(0,-1,1));
        }
    }
    return moja_lista;
}

void pionek::ruszono(){
    this->pierwszy_ruch = false;
}

void pionek::zasady_bicia(wspolrzedne *tablica_zasad){

    // pionki czarne bija w jedna strone a pionki biale w druga
    if(this->kol == biali){
        tablica_zasad[0] = wspolrzedne(1,1);
        tablica_zasad[1] = wspolrzedne(-1,1);
    } else{
        tablica_zasad[1] = wspolrzedne(-1,-1);
        tablica_zasad[1] = wspolrzedne(-1,-1);
    }
}