#include "inc/hetman.hh"

hetman::hetman(kolor _kol, wspolrzedne _wsp){
    this->kol = _kol;
    this->pozycja = _wsp;
    this->czy_aktywny=true;
    this->nazwa = 'h'; // jak w notacji szachowej
}

std::vector<mozliwosc> *hetman::zasady_ruchu(){
    std::vector<mozliwosc> *moj_vector = new std::vector<mozliwosc>{
    // wszystkie mozliwosci ruchu po skosie i kolumnach
    // dowolna ilosc powtorzen (max 7 przez wymiar planszy)
    (mozliwosc(1,1,7)),
    (mozliwosc(-1,1,7)),
    (mozliwosc(1,-1,7)),
    (mozliwosc(-1,-1,7)),
    (mozliwosc(0,1,7)),
    (mozliwosc(0,-1,7)),
    (mozliwosc(1,0,7)),
    (mozliwosc(-1,0,7))
    };
    
    return moj_vector;
}