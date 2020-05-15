#include "inc/plansza.hh"
#include <iostream>

plansza::plansza(){

this->czas1 = 0;
this->czas2 = 0;
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

    // jesli podano pole docelowe spoza szachownicy konczy dzialanie funkcji
    if(plansza::czy_poza_plansza(koniec)){
        std::cout << "Proba ruchu na pole poza plansza" << std::endl;
        return;
    }

    // jesli proba ruchu nastepuje z pustego pola konczy dzialanie funkcji
    if((*this)(start) == nullptr){
        std::cout << " Pole puste, nie mozna sie stad ruszyc" << std::endl;
        return;
    }
std::clock_t czas2_start = std::clock();
    std::vector<wspolrzedne> *mozliwe_pola_koncowe = mozliwe_ruchy(start);
    // jesli nie mozna sie ruszyc na zadne pole konczy dzialanie funkcji
    if(mozliwe_pola_koncowe == nullptr){
        return;
    }

std::clock_t czas2_koniec = std::clock();
this->czas2 += (double)(czas2_koniec-czas2_start)/CLOCKS_PER_SEC;
    int rozmiar = mozliwe_pola_koncowe->size();
    for(int i=0;i<rozmiar;i++){
        // czy chcemy sie ruszyc na dostepne dla figury pole
        if(koniec == (*mozliwe_pola_koncowe)[i]){
            // jesli ruszamy sie na pole, ktore nie jest puste
            if((*this)(koniec) != nullptr){
                // bijemy figure na polu docelowym
                this->zbij((*this)(koniec));
            }
            // zwolnienie pamieci z vectora mozliwych pol koncowych
            delete mozliwe_pola_koncowe;
            // aktualizuje pole i konczy dzialanie funkcji
            this->aktualizuj_pola(koniec, *(*this)(start));
            return;
        }
    }
    // zwolnienie pamieci z listy mozliwych pol koncowych
    delete mozliwe_pola_koncowe;

    // nie mozna sie tak ruszyc
    std::cout << "RUCH NIEDOZWOLONY" << std::endl;
}

std::vector<wspolrzedne> *plansza::mozliwe_ruchy(wspolrzedne start){

    // jesli podano pozycje startowa spoza szachownicy zwraca nullptr
    if(plansza::czy_poza_plansza(start)){
        std::cout << "Proba ruchu z pola poza plansza" << std::endl;
        return nullptr;
    }

    // jesli proba ruchu nastepuje z pustego pola zwraca nullptr
    if((*this)(start) == nullptr){
        std::cout << " Pole puste, nie mozna sie stad ruszyc" << std::endl;
        return nullptr;
    }

    std::vector<wspolrzedne> *tablica_ruchow = new std::vector<wspolrzedne>;
std::clock_t czas1_start = std::clock();
    figura *fig = (*this)(start);
    // przechowuje wektory w jakich moze sie poruszac figura
    std::vector<mozliwosc> *wektory_ruchu = fig->zasady_ruchu();
std::clock_t czas1_koniec = std::clock();
this->czas1 += (double)(czas1_koniec-czas1_start)/CLOCKS_PER_SEC;
    int rozmiar_listy = wektory_ruchu->size();
    for(int i=0;i<rozmiar_listy;i++){
        // dodaje do listy ruchy ktore mozna wykonac po danym wektorze
        this->mozliwy_po_wektorze(*fig, (*wektory_ruchu)[i], tablica_ruchow);
    }
    // trzeba zwolnic miejsce po liscie wektorow, lista w destruktorze sie czysci
    delete wektory_ruchu;

    // uwzglednienie bicia przez pionki
    if(fig->zwroc_nazwe() == 'p'){
        pionek *pion = dynamic_cast<pionek*>(fig);
        mozliwe_bicia_pionkiem(*pion, tablica_ruchow);
    }
    // zwraca wszystkie dostepne z danego pola ruchy
    return tablica_ruchow;
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

void plansza::mozliwy_po_wektorze(figura &fig,
        const mozliwosc &_mozliwosc, std::vector<wspolrzedne> *tablica_ruchow){

    // ile razy mozna powtorzyc rucho o wektor
    int powtorzen = _mozliwosc.zasieg;
    // wektor jakim sie poruszamy
    wspolrzedne wektor = _mozliwosc.wektor;
    // zmienna okreslajaca koncowe pole na ktore mozna sie ruszyc
    wspolrzedne mozliwy_ruch = fig.aktualna_pozycja();

    // jesli bede szachowany po ruchu w tym wektorze, to jest on zakazany
    bool bede_szach = this->czy_bede_szachowany(mozliwy_ruch, wektor);
    if(bede_szach == true){
        return;
    }

    for(int i=0;i<powtorzen;i++){
        mozliwy_ruch += wektor;
        // jesli wyjdzie poza plansze konczy dzialanie funkcji
        if(plansza::czy_poza_plansza(mozliwy_ruch)){
            return;
        }
        // jesli na drodze stoi jakas figura
        if((*this)(mozliwy_ruch) != nullptr){
            // wskaznik na blokujaca figure
            figura *na_drodze = (*this)(mozliwy_ruch);
            // jesli na drodze stoi figura w tym samym kolorze
            if(na_drodze->ktora_druzyna() == fig.ktora_druzyna()){
                // nie mozna sie ruszyc ani tu ani nigdzie dalej
                return;
            } else{ // jesli na drodze stoi figura w innym kolorze
                // jesli ruszamy pionkiem to nie moze bic tak jak sie rusza
                if(fig.zwroc_nazwe() == 'p'){
                    return;
                } else{// mozna bic, ale dalej sie nie ruszymy
                    tablica_ruchow->push_back(mozliwy_ruch);
                    return;
                }
            }
        }
        // nie ma na drodze zadnych przeszkod
        tablica_ruchow->push_back(mozliwy_ruch);
    }
}

void plansza::zbij(figura *fig){
    fig->zbito();
    int zmiana_pkt = 0;
    switch(fig->zwroc_nazwe()){
        case 'p': zmiana_pkt = 1; break;
        case 's': zmiana_pkt = 3; break;
        case 'g': zmiana_pkt = 3; break;
        case 'w': zmiana_pkt = 5; break;
        case 'h': zmiana_pkt = 9; break;
        case 'k':zmiana_pkt = 100; break;
        default: 
            std::cout << "Proba zbicia, nie ma takiego rodzaju figury" << std::endl;
            break;
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

void plansza::mozliwe_bicia_pionkiem(pionek &pion, std::vector<wspolrzedne> *tablica_ruchow){
    wspolrzedne wektory_bicia[2];
    pion.zasady_bicia(wektory_bicia);
    wspolrzedne pozycja_piona = pion.aktualna_pozycja();
    for(int i=0;i<2;i++){ // mozna bic na 2 sposoby
        if(czy_bede_szachowany(pozycja_piona, wektory_bicia[i]) == false){
            wspolrzedne proba_bicia = pozycja_piona + wektory_bicia[i];
            if(plansza::czy_poza_plansza(proba_bicia) == false){ // czy pole znajduje sie na planszy
                // if chroni przed proba sprawdzenia koloru jesli pole wskazuje na nullptr
                if((*this)(proba_bicia) != nullptr){
                    if((*this)(proba_bicia)->ktora_druzyna() != pion.ktora_druzyna()){ // jesli pole jest zajete przez przeciwnika
                        tablica_ruchow->push_back(proba_bicia);
                    }
                }
            }
        }
    }
}

druzyna* plansza::zwroc_druzyne(kolor kol){
    if(kol == biali){
        return this->biel;
    }
    if(kol == czarni){
        return this->czern;
    }
    std::cout << "NIE MA TAKIEJ DRUZYNY" << std::endl;
    return nullptr;
}

// TODO dokonczyc
bool plansza::czy_bede_szachowany(wspolrzedne start, wspolrzedne wektor){
    
    if((*this)(start) == nullptr){
        std::cout << "proba ruchu z pustego pola" << std::endl;;
        return false;
    }

    figura *fig = (*this)(start);
    // jesli ruszono czym innym niz krolem
    if(fig->zwroc_nazwe() != 'k'){
        bool czy_zakaz_ruchu = this->czy_odsloni_krola(start, wektor);
        if(czy_zakaz_ruchu == true){
            return true;
        }
    }
    return false;
}

bool plansza::czy_odsloni_krola(wspolrzedne start, wspolrzedne wektor){

    figura *fig = (*this)(start);
    kolor kol = fig->ktora_druzyna();
    figura *kr = (*(this->zwroc_druzyne(kol)))[0]; // druzyna[0] zwraca krola z tej druzyny
    wspolrzedne poz_krola = kr->aktualna_pozycja();
    wspolrzedne mozliwy_atak(10,10); // jesli nie zostanie zmienione to na pewno wyjdzie poza plansze
    mozliwy_atak = wektor_od_krola(start, poz_krola);

    // jesli figura nie ma wspolnego skosu, wiersza ani kolumny z krolem
    if(mozliwy_atak == wspolrzedne(10,10)){
        return false;
    }

    // jesli true to atak mozliwy po przekatnej,
    // jesli false to atak mozliwy po wierszach albo kolumnach
    bool po_przekatnej;

    if(mozliwy_atak == wspolrzedne(0,1) || mozliwy_atak == wspolrzedne(0,-1)
     || mozliwy_atak == wspolrzedne(1,0) || mozliwy_atak == wspolrzedne(-1,0)){
        
        po_przekatnej = false;
    } else{
        po_przekatnej = true;
    }

    // ruszajac sie w ten sposob nie da sie odslonic krola
    if(wektor == mozliwy_atak){
        return false;
    } else{ // sprawdzamy tylko od miejsca za miejscem z ktorego chcemy sie ruszyc
        start += mozliwy_atak;
        while(plansza::czy_poza_plansza(start) == false){
            // jesli jakies pole jest zajete
            if((*this)(start) != nullptr){
                fig = (*this)(start);
                if(po_przekatnej == true){
                    // jesli zajmuje je goniec albo hetman
                    if(fig->zwroc_nazwe() == 'g' || fig->zwroc_nazwe() == 'h'){
                        // jesli jest przeciwnego koloru
                        if(fig->ktora_druzyna() != kol){
                            return true;
                        }
                    }
                    // na drodze byla juz jakas figura, wiec zwracamy false
                    return false;
                } else{
                    // jesli zajmuje je wieza albo hetman
                    if(fig->zwroc_nazwe() == 'w' || fig->zwroc_nazwe() == 'h'){
                        // jesli jest przeciwnego koloru
                        if(fig->ktora_druzyna() != kol){
                            return true;
                        }
                    }
                    // na drodze byla juz jakas figura, wiec zwracamy false
                    return false;
                }
            }
            // co obieg petli przesuwamy sie o wektor czyli jedno pole
            start += mozliwy_atak;
        }
        // jesli wyszlo poza zakres planszy to nie odsloni krola
        return false;
    }
    return false;
}

wspolrzedne plansza::wektor_od_krola(wspolrzedne poz_fig, wspolrzedne poz_krola){
    
    wspolrzedne wynik(10,10);
    // jesli roznica x i y jest taka sama
    // to ruszana figura jest pod skosem do krola
    int roznica_x = poz_fig.x - poz_krola.x;
    int roznica_y = poz_fig.y - poz_krola.y;
    if(roznica_x == roznica_y){
        // figura jest po przekatnej na polnocny wschod od krola
        if(poz_fig.x > poz_krola.x){
            wynik = wspolrzedne(1,1);
        } else{ // figura jest na poludniowy zachod od krola
            wynik = wspolrzedne(-1,-1);
        }
    }

    // jesli roznica a.x - b.x == b.y -a.y
    // to ruszana figura jest pod skosem do krola
    roznica_x = poz_fig.x - poz_krola.x;
    roznica_y = poz_krola.y - poz_fig.y;
    if(roznica_x == roznica_y){
        // figura jest po przekatnej na poludniowy wschod od krola
        if(poz_fig.x > poz_krola.x){
            wynik = wspolrzedne(-1,1);
        } else{ // figura jest na polnocny zachod od krola
            wynik = wspolrzedne(1,-1);
        }
    }

    // jesli krol i figura sa w tej samej kolumnie
    if(poz_fig.x == poz_krola.x){
        // figura jest na polnoc
        if(poz_fig.y > poz_krola.y){
            wynik = wspolrzedne(0,1);
        } else{ // figura jest na poludnie
            wynik = wspolrzedne(0,-1);
        }
    }

    // jesli krol i figura sa w tym samym wierszu
    if(poz_fig.y == poz_krola.y){
        // figura jest na wschod
        if(poz_fig.x > poz_krola.x){
            wynik = wspolrzedne(1,0);
        } else{
            wynik = wspolrzedne(-1,0);
        }
    }

    if(wynik != wspolrzedne(10,10)){
        // jesli miedzy krolem a sprawdzana figura cos stoi uznajemy, ze nie da sie dojsc
        poz_krola += wynik;
        while(poz_krola != poz_fig){
            if((*this)(poz_krola) != nullptr){
                wynik = wspolrzedne(10,10);
                return wynik;
            }
            poz_krola += wynik;
        }
    }

    return wynik;
}