#ifndef HETMAN_HH
#define HETMAN_HH

#include "figura.hh"

class hetman: public figura{
    public:
    hetman(kolor _kol, wspolrzedne _wsp);
    mozliwosc *zasady_ruchu();
    ~hetman();
};

#endif