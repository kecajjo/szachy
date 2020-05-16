#ifndef WSPOLRZEDNE_HH
#define WSPOLRZEDNE_HH

struct wspolrzedne{
    int x;
    int y;
    wspolrzedne(int _x, int _y);
    wspolrzedne();
    wspolrzedne operator =(const wspolrzedne _wsp);
    bool operator ==(const wspolrzedne _wsp) const;
    bool operator !=(const wspolrzedne _wsp) const;
    wspolrzedne operator +(const wspolrzedne dodaj) const;
    void operator +=(const wspolrzedne dodaj);
    bool czy_poza_plansza();
    wspolrzedne operator  () (int _x, int _y); // zamienia wspolrzedne na podane wartosci
    wspolrzedne operator *(int mnoznik);
};

#endif