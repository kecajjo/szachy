#include "inc/hetman.hh"

hetman::hetman(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'h'; // jak w notacji szachowej
}

std::vector<mozliwosc> *hetman::zasady_ruchu(){
    std::vector<mozliwosc> *moja_lista = new std::vector<mozliwosc>;
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    moja_lista->push_back(mozliwosc(1,1,7));
    moja_lista->push_back(mozliwosc(-1,1,7));
    moja_lista->push_back(mozliwosc(1,-1,7));
    moja_lista->push_back(mozliwosc(-1,-1,7));
    moja_lista->push_back(mozliwosc(0,1,7));
    moja_lista->push_back(mozliwosc(0,-1,7));
    moja_lista->push_back(mozliwosc(1,0,7));
    moja_lista->push_back(mozliwosc(-1,0,7));
    
    return moja_lista;
}