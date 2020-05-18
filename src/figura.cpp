#include "inc/figura.hh"

void figura::zbito(){
    this->czy_aktywny = false;
}

void figura::zmien_na_aktywna(){
    this->czy_aktywny = true;
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

bool figura::czy_aktywna(){
    if(this->czy_aktywny == true){
        return true;
    }
    return false;
}