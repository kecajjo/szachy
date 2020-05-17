#include "inc/pionek.hh"

pionek::pionek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->pierwszy_ruch=true;
    this->nazwa = 'p'; //jak w notacji szachowej
}

mozliwosc *pionek::zasady_ruchu(){
    // inicjalizujemy tylko 1 mozliwoscia wiec moze byc push back
    mozliwosc *moj_vector;
    if(this->kol == biali){
        if(pierwszy_ruch == true){
            moj_vector = new mozliwosc[1]{(mozliwosc(0,1,2))};
        } else{
            moj_vector = new mozliwosc[1]{(mozliwosc(0,1,1))};
        }
    }
    if(this->kol == czarni){
        if(pierwszy_ruch == true){
            moj_vector = new mozliwosc[1]{(mozliwosc(0,-1,2))};
        } else{
            moj_vector = new mozliwosc[1]{(mozliwosc(0,-1,1))};
        }
    }
    return moj_vector;
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
        tablica_zasad[0] = wspolrzedne(1,-1);
        tablica_zasad[1] = wspolrzedne(-1,-1);
    }
}

pionek::~pionek(){
}