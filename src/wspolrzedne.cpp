#include "inc/wspolrzedne.hh"

wspolrzedne::wspolrzedne(){
    this->x=0;
    this->y=0;
}

wspolrzedne::wspolrzedne(int _x, int _y){
    this->x=_x;
    this->y=_y;
}

wspolrzedne wspolrzedne::operator =(const wspolrzedne _wsp){
    this->x = _wsp.x;
    this->y = _wsp.y;
    return *this;
}

bool wspolrzedne::operator ==(const wspolrzedne _wsp) const{
    if(this->x == _wsp.x && this->y == _wsp.y){
        return true; //jesli obydwie wspolrzedne sa rowne zwraca true
    }
    return false; // jesli ktoras wspolrzedna sie rozni zwraca false
}

bool wspolrzedne::operator !=(const wspolrzedne _wsp) const{
    if(this->x != _wsp.x || this->y != _wsp.y){
        return true; // jesli ktoras wspolrzedna sie rozni zwraca true
    }
    return false; // jesli obydwie wspolrzedne sa takie same zwraca false
}

wspolrzedne wspolrzedne::operator +(const wspolrzedne dodaj) const{
    wspolrzedne wynik;
    wynik.x = this->x + dodaj.x;
    wynik.y = this->y + dodaj.y;
    return wynik;
}

void wspolrzedne::operator +=(const wspolrzedne dodaj){
    this->x += dodaj.x;
    this->y += dodaj.y;
}

wspolrzedne wspolrzedne::operator () (int _x, int _y){
    this->x = _x;
    this->y = _y;
    return *this;
}