#ifndef KROL_HH
#define KROL_HH

#include "figura.hh"

class krol: public figura{
    public:
    krol(kolor _kol, wspolrzedne _wsp);
    std::list<mozliwosc> *zasady_ruchu();
};

#endif