#ifndef MOZLIWOSC_HH
#define MOZLIWOSC_HH

#include "wspolrzedne.hh"
struct mozliwosc{
    wspolrzedne wektor; // wektor jakim sie poruszamy
    int zasieg; // ile pol naraz moze pokonac figura
    mozliwosc(int _x, int _y, int _zasieg){
        this->wektor.x = _x;
        this->wektor.y = _y;
        this->zasieg = _zasieg;
    }

    mozliwosc(wspolrzedne _wsp, int _zasieg){
        this->wektor.x = _wsp.x;
        this->wektor.y = _wsp.y;
        this->zasieg = _zasieg;
    }

    mozliwosc operator =(mozliwosc moz){
        this->wektor = moz.wektor;
        this->zasieg = moz.zasieg;
        return *this;
    }
};

#endif