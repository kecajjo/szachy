#include "inc/goniec.hh"
#include "inc/figura.hh"

goniec::goniec(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'g'; // tak jak w notacji szachowej
}

mozliwosc *goniec::zasady_ruchu(){
    mozliwosc *moj_vector = new mozliwosc[4]{
    // wszystkie mozliwosci ruchu po skosie
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    (mozliwosc(1,1,7)),
    (mozliwosc(-1,1,7)),
    (mozliwosc(1,-1,7)),
    (mozliwosc(-1,-1,7))
    };
    
    return moj_vector;
}
