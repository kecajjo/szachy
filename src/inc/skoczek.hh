#ifndef SKOCZEK_HH
#define SKOCZEK_HH

#include "figura.hh"

class skoczek: public figura{
    mozliwosc *zas_ruch;
    public:
    skoczek(kolor _kol, wspolrzedne _wsp);
    mozliwosc *zasady_ruchu();
    ~skoczek();
};

#endif