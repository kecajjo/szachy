#include "inc/plansza.hh"
#include <iostream>

plansza::plansza(){
    // ustawia stan poczatkowy szachownicy
    this->wynik = 0;
    this->biel = new druzyna(biali);
    this->czern = new druzyna(czarni);
    for(int i=0;i<16;i++){
        figura *biala = (*this->biel)[i]; // wykorzystanie operatora [] z druzyny
        figura *czarna = (*this->czern)[i]; // wykorzystanie operatora [] z druzyny
        (*this)(biala->aktualna_pozycja()) = biala; // wykorzystanie operatora ()
        (*this)(czarna->aktualna_pozycja()) = czarna; // wykorzystanie operatora ()
    }
    for(int i=2;i<6;i++){
        for(int j=0;j<ROZMIAR;j++){
            (*this)(j,i) = nullptr; // wykorzystanie operatora()
        }
    }
    // biali zaczynaja
    this->tura = biali;
}

kolor plansza::czyja_tura(){
    return tura;
}

figura* plansza::zwroc_pole(wspolrzedne wsp){
    // w tablicy najpierw jest numer wiersza, potem numer kolumny dlatego [y][x] nie [x][y]
    return this->pola[wsp.y][wsp.x];
}

bool plansza::czy_puste(wspolrzedne wsp){
    if(this->pola[wsp.y][wsp.x] == nullptr){
        return true; // nikogo nie ma
    }
    return false; // pole zajete
}

void plansza::zmien_pole(wspolrzedne wsp, figura *fig){

    this->pola[wsp.y][wsp.x] = fig;
}

figura* plansza::operator ()(int _x, int _y) const{
    if(_x < ROZMIAR && _y < ROZMIAR){
        return this->pola[_y][_x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

figura*& plansza::operator ()(int _x, int _y){
    if(_x < ROZMIAR && _y < ROZMIAR){
        return this->pola[_y][_x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

figura* plansza::operator ()(wspolrzedne wsp) const{
    if(wsp.x < ROZMIAR && wsp.y < ROZMIAR){
        return this->pola[wsp.y][wsp.x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

figura*& plansza::operator ()(wspolrzedne wsp){
    if(wsp.x < ROZMIAR && wsp.y < ROZMIAR){
        return this->pola[wsp.y][wsp.x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

void plansza::rusz(wspolrzedne start, wspolrzedne koniec){
    
    // jesli podano pozycje startowa spoza szachownicy konczy dzialanie funkcji
    if(plansza::czy_poza_plansza(start)){
        std::cout << "Proba ruchu z pola poza plansza" << std::endl;
        return;
    }
    // jesli podano pole koncowe spoza szachownicy konczy dzialanie funkcji
    if(plansza::czy_poza_plansza(koniec)){
        std::cout << "Proba ruchu na pole poza plansza" << std::endl;
        return;
    }
    // jesli proba ruchu nastepuje z pustego pola konczy dzialanie funkcji
    if((*this)(start) == nullptr){
        std::cout << " Pole puste, nie mozna sie stad ruszyc" << std::endl;
        return;
    }

    figura *fig = (*this)(start);
    // przechowuje wektory w jakich moze sie poruszac figura
    std::list<mozliwosc> *wektory_ruchu = fig->zasady_ruchu();

    int rozmiar_listy = wektory_ruchu->size();
    std::list<mozliwosc>::iterator it = wektory_ruchu->begin();
    for(int i=0;i<rozmiar_listy;i++){
        // ile razy figura moze sie ruszyc o wektor
        int powtorzen = it->zasieg;
        // probuje ruszyc po danym wektorze
        bool czy_ruszono = this->rusz_po_wektorze(*fig, it->wektor, powtorzen, koniec);
        // jesli udalo sie ruszyc konczy dzialanie funkcji
        if(czy_ruszono == true){
            // trzeba usunac liste wektorow
            delete wektory_ruchu;
            return;
        }
        it++;
    }
    // jesli ruch bedzie sprzeczny z zasadami ruchu wypisze komunikat
    std::cout << std::endl << "RUCH NIEDOZWOLONY" << std::endl;
    // trzeba zwolnic miejsce po liscie wektorow
    delete wektory_ruchu;
}

void plansza::wyswietl(){
    
    char pomocniczy = '\0';

    for(int i=ROZMIAR-1;i>=0;i--){
        //wyswietla numery wierszy
        std::cout << i << "   ";

        // wyswietla ulozenie figur, "+" oznacza puste pole
        for(int j=0;j<ROZMIAR;j++){
            if((*this)(j,i) == nullptr){
                std::cout << "+ ";
            } else{
                // biali beda wypisywaniu wielkimi literami
                pomocniczy = (*this)(j,i)->zwroc_nazwe();
                if((*this)(j,i)->ktora_druzyna() == biali){
                    pomocniczy = toupper(pomocniczy);
                    std::cout << pomocniczy << " ";
                } else{
                    std::cout << pomocniczy << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    // wyswietla numery kolumn
    std::cout << std::endl << "    ";
    for(int i=0;i<ROZMIAR;i++){
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl << std::endl;
}

bool plansza::czy_poza_plansza(wspolrzedne wsp){
    if(wsp.x < 0 || wsp.x >= ROZMIAR || wsp.y < 0 || wsp.y >= ROZMIAR){
        return true;
    }
    return false;
}

bool plansza::rusz_po_wektorze(figura &fig,
        const wspolrzedne &wektor, int powtorzen, const wspolrzedne &koniec){

    // zmienna okreslajaca koncowe pole na ktore mozna sie ruszyc
    wspolrzedne mozliwy_ruch = fig.aktualna_pozycja();
    for(int i=0;i<powtorzen;i++){
        mozliwy_ruch += wektor;
        // jesli na drodze stoi jakas figura
        if((*this)(mozliwy_ruch) != nullptr){
            // wskaznik na blokujaca figure
            figura *na_drodze = (*this)(mozliwy_ruch);
            // jesli na drodze stoi figura w tym samym kolorze
            if(na_drodze->ktora_druzyna() == fig.ktora_druzyna()){
                // nie mozna sie ruszyc ani tu ani nigdzie dalej
                return false;
            } else{ // jesli na drodze stoi figura w innym kolorze
                // jesli to pionek to nie moze bic
                if(na_drodze->zwroc_nazwe() == 'p'){
                    return false;
                } else{ // jesli to inna figura przeciwnika to nalezy bic
                    zbij(na_drodze);
                    // rusza figure na dolecowe miejsce
                    this->aktualizuj_pola(koniec, fig);

                    // (*this)(fig.aktualna_pozycja()) = nullptr;
                    // fig.przesun(koniec);
                    // (*this)(koniec) = &fig;

                    // jesli udalo sie ruszyc zwraca true
                    return true;
                }
            }
        }

        // jesli pole koncowe mozna osiagnac zgodnie z zasadami ruchu 
        // to figura zmieni polozenie i funkcja zakonczy dzialanie
        if(koniec == mozliwy_ruch){
            // rusza figure na dolecowe miejsce
            this->aktualizuj_pola(koniec, fig);
            
            // (*this)(fig.aktualna_pozycja()) = nullptr;
            // fig.przesun(koniec);
            // (*this)(koniec) = &fig;

            // jesli udalo sie ruszyc zwraca true
            return true;
        }
    }
    // jesli nie udalo sie ruszyc zwraca false
    return false;
}

void plansza::zbij(figura *fig){
    fig->zbito();
    int zmiana_pkt = 0;
    switch(fig->zwroc_nazwe()){
        case 'p': zmiana_pkt = 1; break;
        case 'n': zmiana_pkt = 3;

    }

    if(fig->ktora_druzyna() == biali){
        this->wynik += zmiana_pkt;
    } else{
        this->wynik -=zmiana_pkt;
    }
}

void plansza::aktualizuj_pola(const wspolrzedne &docelowe, figura &fig){
    (*this)(fig.aktualna_pozycja()) = nullptr;
    fig.przesun(docelowe);
    (*this)(docelowe) = &fig;
}