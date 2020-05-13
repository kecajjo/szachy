#include "inc/goniec.hh"
#include "inc/figura.hh"

goniec::goniec(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'g'; // tak jak w notacji szachowej
}

std::list<mozliwosc> *goniec::zasady_ruchu(){
    std::list<mozliwosc> *moja_lista = new std::list<mozliwosc>;
    // wszystkie mozliwosci ruchu po skosie
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    moja_lista->push_back(mozliwosc(1,1,7));
    moja_lista->push_back(mozliwosc(-1,1,7));
    moja_lista->push_back(mozliwosc(1,-1,7));
    moja_lista->push_back(mozliwosc(-1,-1,7));
    
    return moja_lista;
}
