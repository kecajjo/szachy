#include "inc/pionek.hh"

pionek::pionek(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nie_ruszyl=true;
    this->nazwa = 'p'; //jak w notacji szachowej
    if(_kol == biali){
        this->pierwszy_ruch[0] = mozliwosc(0,1,2);
        this->nastepny_ruch[0] = mozliwosc(0,1,1);
    } else{
        this->pierwszy_ruch[0] = mozliwosc(0,-1,2);
        this->nastepny_ruch[0] = mozliwosc(0,-1,1);
    }
}

mozliwosc *pionek::zasady_ruchu(){
    if(nie_ruszyl == true){
        return this->pierwszy_ruch;
    }
    return this->nastepny_ruch;
}

void pionek::ruszono(){
    this->nie_ruszyl = false;
}

void pionek::ustaw_nie_ruszono(){
    this->nie_ruszyl = true;
}

bool pionek::czy_pierwszy(){
    return this->nie_ruszyl;
}

void pionek::zasady_bicia(wspolrzedne *tablica_zasad) const{

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