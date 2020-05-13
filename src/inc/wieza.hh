#ifndef WIEZA_HH
#define WIEZA_HH

#include "figura.hh"

class wieza: public figura{
    public:
    wieza(kolor _kol, wspolrzedne _wsp);
    std::list<mozliwosc> *zasady_ruchu();
};

#endif