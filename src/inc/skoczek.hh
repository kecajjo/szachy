#ifndef SKOCZEK_HH
#define SKOCZEK_HH

#include "figura.hh"

class skoczek: public figura{
    public:
    skoczek(kolor _kol, wspolrzedne _wsp);
    std::vector<mozliwosc> *zasady_ruchu();
};

#endif