#ifndef PIONEK_HH
#define PIONEK_HH

#include "figura.hh"

class pionek: public figura{
    bool pierwszy_ruch;
    public:
    pionek(kolor _kol, wspolrzedne _wsp);
    std::list<mozliwosc> *zasady_ruchu();
};

#endif