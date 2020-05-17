#ifndef GONIEC_HH
#define GONIEC_HH

#include "figura.hh"
#include "wspolrzedne.hh"

class goniec: public figura{
    public:
    goniec(kolor _kol, wspolrzedne _wsp);
    mozliwosc *zasady_ruchu();
    ~goniec();
};

#endif