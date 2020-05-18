#include "inc/ruch.hh"

ruch::ruch(){
    this->wynik = -100000;
    this->skad = wspolrzedne(10,10);
    this->docelowo = wspolrzedne(10,10);
    this->zbito = nullptr;
    this->pierw_ruch = true; // wieksza szansa na wykrycie bledu
    this->ruch_spec = false;
    this->szach = nullptr;
    this->podw_szach = false;
}

ruch::ruch(const float &_wynik, const wspolrzedne &_skad, const wspolrzedne &_docelowo,
        figura *_zbito, figura *_szach, bool _podw_szach, bool _pierw_r, bool _ruch_spec){

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

void ruch::wykon_ruch_spec(){
    this->ruch_spec = true;
}

void ruch::ustaw_szach(figura *fig){
    this->szach = fig;
}

void ruch::ustaw_podw_szach(bool ustaw){
    this->podw_szach = ustaw;
}
