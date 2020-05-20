#ifndef RUCH_HH
#define RUCH_HH

#include "wspolrzedne.hh"
#include "figura.hh"

struct ruch{
    private:
    float wynik;
    wspolrzedne skad;
    wspolrzedne docelowo;
    // wskaznik na istniejaca figure
    // wiec w destruktorze nie usuwamy
    figura* zbito;
    // potrzebne do roszady i pierwszego ruchu pionkiem
    bool pierw_ruch;
    // ruch specjalny to promocja='p', roszada='r', bicie w przelocie='b', brak='\0'
    char ruch_spec;
    // czy druzyna ktora sie ruszala byla szachowana
    figura* szach;
    bool podw_szach;

    public:
    ruch();
    ruch(const float &_wynik, const wspolrzedne &_skad, const wspolrzedne &_docelowo,
        figura *_zbito, figura *_szach = nullptr, bool _podw_szach = false,
        bool _pierw_r = false, char _ruch_spec = '\0');
    ruch operator =(const ruch &_ruch);
    void wykon_pierw_ruch(); // zrobiono pierwszy ruch figura
    bool czy_pier_ruch() const;
    void ustaw_szach(figura *fig);
    figura* zwroc_szach() const;
    void ustaw_podw_szach(const bool &ustaw);
    bool czy_podw_szach() const;
    void ustaw_skad(const wspolrzedne &wsp);
    wspolrzedne zwroc_skad() const;
    void ustaw_docelowo(const wspolrzedne &wsp);
    wspolrzedne zwroc_docelowo() const;
    char zwroc_ruch_spec() const;
    void ustaw_ruch_spec(const char &ustaw);
    float zwroc_wynik() const;
    figura* zwroc_zbito() const;
};

#endif