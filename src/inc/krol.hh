#ifndef KROL_HH
#define KROL_HH

#include "figura.hh"

class krol: public figura{
    bool pierwszy_ruch; // true jesli krol sie nie ruszyl, false jesli sie ruszyl
    public:
    krol(kolor _kol, wspolrzedne _wsp);
    mozliwosc *zasady_ruchu();
    void ruszono(); // krol zostal ruszony
    ~krol();
};

#endif