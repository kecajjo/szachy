#include "inc/figura.hh"

void figura::zbito(){
    this->czy_aktywny=false;
}

wspolrzedne figura::aktualna_pozycja() const{
    return this->pozycja;
}

void figura::przesun(wspolrzedne nowa_pozycja){
    this->pozycja = nowa_pozycja;
}

char figura::zwroc_nazwe() const{
    return this->nazwa;
}

kolor figura::ktora_druzyna() const{
    return this->kol;
}