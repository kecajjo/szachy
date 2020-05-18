#ifndef RUCH_HH
#define RUCH_HH

#include "wspolrzedne.hh"
#include "figura.hh"

struct ruch{
    float wynik;
    wspolrzedne skad;
    wspolrzedne docelowo;
    // wskaznik na istniejaca figure
    // wiec w destruktorze nie usuwamy
    figura* zbito;
    // potrzebne do roszady, pierwszego
    // ruchu pionkiem i bicia w przelocie
    bool pierw_ruch;
    // ruch specjalny to promocja, roszada, bicie w przelocie
    bool ruch_spec;
    // czy druzyna ktora sie ruszala byla szachowana
    figura* szach;
    bool podw_szach;
    ruch();
    ruch(const float &_wynik, const wspolrzedne &_skad, const wspolrzedne &_docelowo,
        figura *_zbito, figura *_szach = nullptr, bool _podw_szach = false,
        bool _pierw_r = false, bool _ruch_spec = false);
    ruch operator =(const ruch &_ruch);
    void wykon_pierw_ruch(); // zrobiono pierwszy ruch figura
    void wykon_ruch_spec(); // wykonano specjalny ruch
    void ustaw_szach(figura *fig);
    void ustaw_podw_szach(bool ustaw);
    void ustaw_skad(const wspolrzedne &wsp);
    wspolrzedne zwroc_skad();
    void ustaw_docelowo(const wspolrzedne &wsp);
    wspolrzedne zwroc_docelowo();
};

#endif