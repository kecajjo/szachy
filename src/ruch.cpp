#include "inc/ruch.hh"

ruch::ruch(){
    this->wynik = -100000;
    this->skad = wspolrzedne(10,10);
    this->docelowo = wspolrzedne(10,10);
    this->zbito = nullptr;
    this->pierw_ruch = true; // wieksza szansa na wykrycie bledu
    this->ruch_spec = '\0';
    this->szach = nullptr;
    this->podw_szach = false;
}

ruch::ruch(const float &_wynik, const wspolrzedne &_skad, const wspolrzedne &_docelowo,
        figura *_zbito, figura *_szach, bool _podw_szach, bool _pierw_r, char _ruch_spec){

    this->wynik = _wynik;
    this->skad = _skad;
    this->docelowo = _docelowo;
    this->zbito = _zbito;
    this->pierw_ruch = _pierw_r;
    this->ruch_spec = _ruch_spec;
    this->szach = _szach;
    this->podw_szach = _podw_szach;
}

ruch ruch::operator =(const ruch &_ruch){
    this->wynik = _ruch.wynik;
    this->skad = _ruch.skad;
    this->docelowo = _ruch.docelowo;
    this->zbito = _ruch.zbito;
    this->pierw_ruch = _ruch.pierw_ruch;
    this->ruch_spec = _ruch.ruch_spec;
    this->szach = _ruch.szach;
    this->podw_szach = _ruch.podw_szach;
    return _ruch;
}

void ruch::wykon_pierw_ruch(){
    this->pierw_ruch = true;
}

bool ruch::czy_pier_ruch() const{
    return this->pierw_ruch;
}

void ruch::ustaw_szach(figura *fig){
    this->szach = fig;
}

figura* ruch::zwroc_szach() const{
    return this->szach;
}

void ruch::ustaw_podw_szach(const bool &ustaw){
    this->podw_szach = ustaw;
}

bool ruch::czy_podw_szach() const{
    return this->podw_szach;
}

void ruch::ustaw_skad(const wspolrzedne &wsp){
    this->skad = wsp;
}

wspolrzedne ruch::zwroc_skad() const{
    return this->skad;
}

void ruch::ustaw_docelowo(const wspolrzedne &wsp){
    this->docelowo = wsp;
}

wspolrzedne ruch::zwroc_docelowo() const {
    return this->docelowo;
}

char ruch::zwroc_ruch_spec() const{
    return this->ruch_spec;
}

void ruch::ustaw_ruch_spec(const char &ustaw){
    this->ruch_spec = ustaw;
}

float ruch::zwroc_wynik() const{
    return this->wynik;
}

figura* ruch::zwroc_zbito() const{
    return this->zbito;
}
