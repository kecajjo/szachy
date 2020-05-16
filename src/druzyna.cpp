#include "inc/druzyna.hh"
#include <iostream>

druzyna::druzyna(kolor _kol){
    this->kol = _kol;
    this->szach = nullptr;
    this->szach_podwojny = false;
    switch(_kol){
     case biali:
        this->wszystkie_fig[0] = new krol(biali, wspolrzedne(4,0));
        this->wszystkie_fig[1] = new hetman(biali, wspolrzedne(3,0));
        this->wszystkie_fig[2] = new wieza(biali, wspolrzedne(0,0));
        this->wszystkie_fig[3] = new wieza(biali, wspolrzedne(7,0));
        this->wszystkie_fig[4] = new goniec(biali, wspolrzedne(2,0));
        this->wszystkie_fig[5] = new goniec(biali, wspolrzedne(5,0));
        this->wszystkie_fig[6] = new skoczek(biali, wspolrzedne(1,0));
        this->wszystkie_fig[7] = new skoczek(biali, wspolrzedne(6,0));
        for(int i=0;i<8;i++){
            this->wszystkie_fig[i+8] = new pionek(biali, wspolrzedne(i,1));
        }
      break;
      case czarni:
        this->wszystkie_fig[0] = new krol(czarni, wspolrzedne(4,7));
        this->wszystkie_fig[1] = new hetman(czarni, wspolrzedne(3,7));
        this->wszystkie_fig[2] = new wieza(czarni, wspolrzedne(0,7));
        this->wszystkie_fig[3] = new wieza(czarni, wspolrzedne(7,7));
        this->wszystkie_fig[4] = new goniec(czarni, wspolrzedne(2,7));
        this->wszystkie_fig[5] = new goniec(czarni, wspolrzedne(5,7));
        this->wszystkie_fig[6] = new skoczek(czarni, wspolrzedne(1,7));
        this->wszystkie_fig[7] = new skoczek(czarni, wspolrzedne(6,7));
        for(int i=0;i<8;i++){
            this->wszystkie_fig[i+8] = new pionek(czarni, wspolrzedne(i,6));
        }
      break;
      default:
        std::cout <<"BLAD, ZLA NAZWA DRUZYNY W KONSTRUKTORZE" << std::endl;
      break;
    }
}

figura* druzyna::operator[](int indeks) const{
    if(indeks<16){
        return this->wszystkie_fig[indeks];
    }
    // w razie proby odwolania do nieistniejacego elementu zwraca pierwszy element
    std::cout << "nie ma takiego elementu, zwrocono pierwszy element" << std::endl;
    return this->wszystkie_fig[0];
}

figura*& druzyna::operator[](int indeks){
    if(indeks<16){
        return this->wszystkie_fig[indeks];
    }
    // w razie proby odwolania do nieistniejacego elementu zwraca pierwszy element
    std::cout << "nie ma takiego elementu, zwrocono pierwszy element" << std::endl;
    return this->wszystkie_fig[0];
}

figura* druzyna::czy_szach(){
    return this->szach;
}

void druzyna::ustaw_szach(figura* _szach){
    this->szach = _szach;
}

bool druzyna::czy_podwojny_szach(){
    return this->szach_podwojny;
}

void druzyna::ustaw_podwojny_szach(bool _szach){
    this->szach_podwojny = _szach;
}