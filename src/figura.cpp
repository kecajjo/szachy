#include "inc/figura.hh"

void figura::zbito(){
    this->czy_aktywny=false;
}

wspolrzedne figura::aktualna_pozycja(){
    return this->pozycja;
}

void figura::przesun(wspolrzedne nowa_pozycja){
    this->pozycja = nowa_pozycja;
}

char figura::zwroc_nazwe(){
    return this->nazwa;
}

kolor figura::ktora_druzyna(){
    return this->kol;
}