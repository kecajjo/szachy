#include "inc/krol.hh"

krol::krol(kolor _kol, wspolrzedne _wsp){
    this->pierwszy_ruch = true;
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'k'; // jak w notacji szachowej
}

std::vector<mozliwosc> *krol::zasady_ruchu(){
    std::vector<mozliwosc> *moja_lista = new std::vector<mozliwosc>;
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    moja_lista->push_back(mozliwosc(1,1,1));
    moja_lista->push_back(mozliwosc(-1,1,1));
    moja_lista->push_back(mozliwosc(1,-1,1));
    moja_lista->push_back(mozliwosc(-1,-1,1));
    moja_lista->push_back(mozliwosc(0,1,1));
    moja_lista->push_back(mozliwosc(0,-1,1));
    moja_lista->push_back(mozliwosc(1,0,1));
    moja_lista->push_back(mozliwosc(-1,0,1));

    return moja_lista;
}

void krol::ruszono(){
    this->pierwszy_ruch = false;
}