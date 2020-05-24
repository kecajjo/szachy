#include "inc/plansza.hh"

plansza::plansza(){

this->czas1 = 0;
this->czas2 = 0;
this->ilosc_przebiegow = 0;

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

plansza::~plansza(){
    delete this->biel;
    delete this->czern;
}

kolor plansza::czyja_tura(){
    return tura;
}

bool plansza::czy_puste(wspolrzedne wsp) const{
    if(this->pola[wsp.y][wsp.x] == nullptr){
        return true; // nikogo nie ma
    }
    return false; // pole zajete
}

figura* plansza::operator ()(const int &_x, const int &_y) const{
    if(_x < ROZMIAR && _y < ROZMIAR){
        return this->pola[_y][_x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

figura*& plansza::operator ()(const int &_x, const int &_y){
    if(_x < ROZMIAR && _y < ROZMIAR){
        return this->pola[_y][_x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

figura* plansza::operator ()(const wspolrzedne &wsp) const{
    if(wsp.x < ROZMIAR && wsp.y < ROZMIAR){
        return this->pola[wsp.y][wsp.x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

figura*& plansza::operator ()(const wspolrzedne &wsp){
    if(wsp.x < ROZMIAR && wsp.y < ROZMIAR){
        return this->pola[wsp.y][wsp.x];
    }
    else{
        std::cout << "przekroczono zakres szachownicy" << std::endl;
    }
    return this->pola[0][0];
}

void plansza::ruchy_druzyny(kolor kol, tablica_ruchow **wszystkie_ruchy){
std::clock_t start_cz = clock();
    druzyna *_druzyna = this->zwroc_druzyne(kol);
    figura *fig;
    if(_druzyna->czy_podwojny_szach() == true){
        fig = (*_druzyna)[0];
        // jesli jest podwojny szach to blokada_szacha i tak nie jest rozpatrywana,
        // bo moze sie ruszac tylko krol
        blokada_szacha *tab_blok = nullptr;
        // wpisuje w dany element wszystkie mozliwe dla danej figury ruchy
        this->mozliwe_ruchy(fig->aktualna_pozycja(), tab_blok, wszystkie_ruchy[0]);
        // jesli jest podwojny szach to tylko krol sie moze ruszac
        for(int i=1;i<16;i++){
            wszystkie_ruchy[i]->oproznij();
        }
    } else{
        blokada_szacha *tab_blok = nullptr;
        // fakt szachowania druzyny nie jest zalezny od uzycia konkretnej figury
        // jesli nie ma szacha blokada_szacha powinna wskazywac na nullptr
        if(_druzyna->czy_szach() != nullptr){
            tab_blok = new blokada_szacha;
            wspolrzedne poz_kr = (*_druzyna)[0]->aktualna_pozycja();
            wspolrzedne poz_szach = _druzyna->czy_szach()->aktualna_pozycja();
            this->mozliwe_blokowanie_szacha(poz_kr, poz_szach, tab_blok);
        }
        // kazdej figurze tworzymy tablice_ruchow
        for(int i=0;i<16;i++){ // druzyna ma zawsze 16 figur
            fig = (*_druzyna)[i];
            // jesli figura zostala zbita nie jest brana pod uwage
            if(fig->czy_aktywna() == true){
                // wpisuje w dany element wszystkie mozliwe dla danej figury ruchy
this->ilosc_przebiegow +=1;
std::clock_t start = std::clock();
                this->mozliwe_ruchy(fig->aktualna_pozycja(), tab_blok, wszystkie_ruchy[i]);
std::clock_t koniec = std::clock();
this->czas2 += (double)(koniec-start)/CLOCKS_PER_SEC;
            } else{ // jesli figura byla zbita czysci wszystkie ruchy[i]
                wszystkie_ruchy[i]->oproznij();
            }
        }
        if(tab_blok != nullptr){
            delete tab_blok;
        }
    }
std::clock_t koniec_cz = clock();
this->czas1 += (double)(koniec_cz-start_cz)/CLOCKS_PER_SEC;
}

void plansza::mozliwe_ruchy(wspolrzedne start, blokada_szacha *tab_blok, tablica_ruchow *tab_ruch){

    // jesli podano pozycje startowa spoza szachownicy zwraca nullptr
    if(plansza::czy_poza_plansza(start)){
        std::cout << "Proba ruchu z pola poza plansza: " << start.x << " " << start.y << std::endl;
        tab_ruch->oproznij();
        return;
    }

    // jesli proba ruchu nastepuje z pustego pola zwraca nullptr
    if((*this)(start) == nullptr){
        std::cout << " Pole puste, nie mozna sie stad ruszyc: " << start.x << " " << start.y << std::endl;
        tab_ruch->oproznij();
        return;
    }
    figura *fig = (*this)(start);
    // przechowuje wektory w jakich moze sie poruszac figura
    mozliwosc *wektory_ruchu = fig->zasady_ruchu();

    int rozmiar_listy;
    char rodzaj_fig = fig->zwroc_nazwe();
    if(rodzaj_fig == 'h' || rodzaj_fig == 'k' || rodzaj_fig == 's'){
        rozmiar_listy = 8;
    } else{
        if(rodzaj_fig == 'g' || rodzaj_fig == 'w'){
            rozmiar_listy = 4;
        } else{ // pionek
            rozmiar_listy = 1;
        }
    }

    for(int i=0;i<rozmiar_listy;i++){
        // dodaje do listy ruchy ktore mozna wykonac po danym wektorze
        this->mozliwy_po_wektorze(*fig, wektory_ruchu[i], tab_ruch, tab_blok);
    }

    // uwzglednienie bicia przez pionki
    switch(fig->zwroc_nazwe()){
        case 'p':{
            pionek *pion = dynamic_cast<pionek*>(fig);
            mozliwe_bicia_pionkiem(*pion, tab_ruch, tab_blok);
            mozliwe_bicie_w_przelocie(fig, tab_ruch);
            break;
        }
        case 'k':
            this->roszada_mozliwa(fig->ktora_druzyna(), tab_ruch);
            break;
        default: break;
    }
}

void plansza::cofnij_ruch(){
    ruch poprzedni = this->poprzednie_ruchy.sciagnij_elem();
    this->wynik = poprzedni.zwroc_wynik();
    // ustawiamy figure z pozycji docelowej na poprzednia pozycje
    (*this)(poprzedni.zwroc_skad()) = (*this)(poprzedni.zwroc_docelowo());
    // jesli faktycznie cos zbilismy, trzeba aktywowac zbita figure
    // i przywrocic ja na miejsce
    if(poprzedni.zwroc_zbito() != nullptr){
        poprzedni.zwroc_zbito()->zmien_na_aktywna();
        (*this)(poprzedni.zwroc_docelowo()) = poprzedni.zwroc_zbito();
    }else{ // jesli nie bilismy, ustawiamy koncowe pole na nullptr
        (*this)(poprzedni.zwroc_docelowo()) = nullptr;
    }
    figura *fig = (*this)(poprzedni.zwroc_skad());
    fig->przesun(poprzedni.zwroc_skad());

    // jako ze tury sa na zmiane to zamiast cofac,
    // mozna zmienic na nastepna (nie liczymy ich)
    this->zmien_ture();
    druzyna *dr = this->zwroc_druzyne(this->czyja_tura());
    dr->ustaw_szach(poprzedni.zwroc_szach());
    dr->ustaw_podwojny_szach(poprzedni.czy_podw_szach());

    if(poprzedni.czy_pier_ruch() == true){
        switch(fig->zwroc_nazwe()){
            case 'p':
                dynamic_cast<pionek*>(fig)->ustaw_nie_ruszono();
             break;
            case 'w':
                dynamic_cast<wieza*>(fig)->ustaw_nie_ruszono();
             break;
            case 'k':
                dynamic_cast<krol*>(fig)->ustaw_nie_ruszono();
             break;
            default:
                std::cout << "BLAD: zle dodany ruch, ktory probuje sie cofnac" << std::endl;
             break;
        }
    } 
    switch(poprzedni.zwroc_ruch_spec()){
        case 'r':{
            // dluga roszada
            int y = poprzedni.zwroc_docelowo().y;
            if(poprzedni.zwroc_docelowo().x == 2){
                wieza *w = dynamic_cast<wieza*>((*this)(3,y));
                (*this)(0,y) = w;
                (*this)(3,y) = nullptr;
                w->ustaw_nie_ruszono();
                w->przesun(wspolrzedne(0,y));
            } else{ // krotka roszada
                wieza *w = dynamic_cast<wieza*>((*this)(5,y));
                (*this)(7,y) = w;
                (*this)(5,y) = nullptr;
                w->ustaw_nie_ruszono();
                w->przesun(wspolrzedne(7,y));
            }
            break;
        }
        case 'p':{
            druzyna *dr = this->zwroc_druzyne(this->czyja_tura());
            // tylko figury z tego zakresu moga byc po promocy
            wspolrzedne pomocnicze = fig->aktualna_pozycja();
            for(int i=8;i<16;i++){
                if((*dr)[i]->aktualna_pozycja() == pomocnicze){
                    delete (*dr)[i];
                    pionek *pion = new pionek(dr->sprawdz_kolor(), pomocnicze);
                    pion->ruszono();
                    (*dr)[i] = pion;
                    (*this)(pomocnicze) = pion;
                    break;
                }
            }
            break;
        }
        case 'b':{
            druzyna *dr;
            if(this->czyja_tura() == biali){
                dr = this->zwroc_druzyne(czarni);
            } else{
                dr = this->zwroc_druzyne(biali);
            }
            wspolrzedne pomocnicze(poprzedni.zwroc_docelowo().x,
                                poprzedni.zwroc_skad().y);
            for(int i=8;i<16;i++){
                if((*dr)[i]->aktualna_pozycja() == pomocnicze){
                    (*dr)[i]->zmien_na_aktywna();
                    (*this)(pomocnicze) = (*dr)[i];
                }
            }
        }
        default: break;
    }
}

bool plansza::czy_mat_pat(tablica_ruchow **wszystkie_ruchy, const int &rozmiar){
    for(int i=0;i<rozmiar;i++){
        // jesli istnieje przynajmniej jeden ruch nie ma mata
        if(wszystkie_ruchy[i]->rozmiar != 0){
            return false;
        }
    }
    // jesli nie znaleziono zadnego ruchu to mat
    return true;
}

bool plansza::czy_mat_pat(kolor kol){
    tablica_ruchow **wszystkie_ruchy = new tablica_ruchow*[16];
    for(int i=0;i<16;i++){
        wszystkie_ruchy[i] = new tablica_ruchow;
    }
    this->ruchy_druzyny(kol, wszystkie_ruchy);
    bool wynik = this->czy_mat_pat(wszystkie_ruchy);
    for(int i=0;i<16;i++){
        delete wszystkie_ruchy[i];
    }
    delete [] wszystkie_ruchy;
    return wynik;
}

void plansza::wyswietl() const{
    
    char pomocniczy = '\0';

    // wyswietla numery kolumn
    std::cout << std::endl << "    ";
    for(char i='A';i<'I';i++){
        std::cout << i << " ";
    }
    std::cout << std::endl <<std::endl;

    for(int i=ROZMIAR-1;i>=0;i--){
        //wyswietla numery wierszy
        std::cout << i+1 << "   ";

        // wyswietla ulozenie figur, "+" oznacza puste pole
        for(int j=0;j<ROZMIAR;j++){
            if((*this)(j,i) == nullptr){
                std::cout << "x ";
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
        std::cout << "  " << i+1;
        std::cout << std::endl;
    }
    // wyswietla numery kolumn
    std::cout << std::endl << "    ";
    for(char i='A';i<'I';i++){
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl << std::endl;
}

bool plansza::czy_poza_plansza(const wspolrzedne &wsp){
    if(wsp.x < 0 || wsp.x >= ROZMIAR || wsp.y < 0 || wsp.y >= ROZMIAR){
        return true;
    }
    return false;
}

bool plansza::czy_poza_plansza(const int &_x, const int &_y){
    if(_x < 0 || _x >= ROZMIAR || _y < 0 || _y >= ROZMIAR){
        return true;
    }
    return false;
}

druzyna* plansza::zwroc_druzyne(const kolor &kol) const{
    if(kol == biali){
        return this->biel;
    }
    if(kol == czarni){
        return this->czern;
    }
    std::cout << "NIE MA TAKIEJ DRUZYNY" << std::endl;
    return nullptr;
}

void plansza::zmien_ture(){
    // w razie gdyby nie byla niczyja tura (mat/pat)
    if(this->tura == biali){
        this->tura = czarni;
    } else{
        if(this->tura == czarni){
            this->tura = biali;
        }
    }
}

void plansza::mozliwe_blokowanie_szacha(wspolrzedne kr, const wspolrzedne &szachujaca, blokada_szacha *tab_blok) const{
    // funkcja powinna byc uzywana tylko jesli jest szach, inaczej wyrzuci bledy
    
    wspolrzedne wektor = this->wektor_od_krola(szachujaca, kr);
    // wspolrzedne swiadczace o braku wspolnej kolumny, wiersza lub przekatnej
    if(wektor == (wspolrzedne(10,10))){
        figura *fig;
        fig = czy_szach_przez_skoczka(kr,(*this)(kr)->ktora_druzyna());
        // jesli skoczek grozi krolowi to mozna jedynie ruszyc krola albo zbic skoczka
        tab_blok->dodaj_elem(fig->aktualna_pozycja());
    } else{
        while(kr != szachujaca){
            // pomija pozycje krola
            // doda sie jeszcze pozycja figury szachujacej
            kr += wektor;
            tab_blok->dodaj_elem(kr);
        }
    }
}

void plansza::zbij(figura *fig){
    fig->zbito();
}

void plansza::aktualizuj_stan_gry(const wspolrzedne &docelowe, const wspolrzedne &poczatkowe){

    figura *fig = (*this)(poczatkowe);
    ruch obecny_ruch(this->wynik, poczatkowe, docelowe, (*this)(docelowe));
    // jesli ruszamy sie na pole, ktore nie jest puste
    if((*this)(docelowe) != nullptr){
        // bijemy figure na polu docelowym
        this->zbij((*this)(docelowe));
    }

    // sprawdzenie czy to moze byc roszada
    if(fig->zwroc_nazwe() == 'k'){
        aktualizuj_roszada(docelowe, fig, obecny_ruch);
    }

    // promocja i bicie w przelocie
    if(fig->zwroc_nazwe() == 'p'){
        // jesli pionek znajdzie sie w pierwszym lub ostatnim rzedzie
        // jest promowany
        if(docelowe.y == 0 || docelowe.y == 7){
            this->aktualizuj_promocja(fig);
            obecny_ruch.ustaw_ruch_spec('p');
        }
        // jesli pinoke poruszyl sie po skosie (bil) na puste pole
        // to wystapilo bicie w przelocie
        if(((*this)(docelowe) == nullptr) && (docelowe.x != poczatkowe.x)){
            obecny_ruch.ustaw_ruch_spec('b');
            // bity pionek jest na przecieciu poczatkowego wiersza 
            // i koncowej kolumny ruszanego pionka
            this->zbij((*this)(docelowe.x, poczatkowe.y));
            (*this)(docelowe.x,poczatkowe.y) = nullptr;
        }
    }

    (*this)(fig->aktualna_pozycja()) = nullptr;
    fig->przesun(docelowe);
    (*this)(docelowe) = fig;

    kolor moj_kolor = fig->ktora_druzyna();
    obecny_ruch.ustaw_szach(this->zwroc_druzyne(moj_kolor)->czy_szach());
    obecny_ruch.ustaw_podw_szach(this->zwroc_druzyne(moj_kolor)->czy_podwojny_szach());

    // po ruchu nigdy nie bede szachowany
    this->zwroc_druzyne(moj_kolor)->ustaw_szach(nullptr);
    this->zwroc_druzyne(moj_kolor)->ustaw_podwojny_szach(false);

    char nazwa = fig->zwroc_nazwe();
    switch(nazwa){
        case 'p':{
            pionek *pion = dynamic_cast<pionek*>(fig);
            if(pion->czy_pierwszy() == true){
                obecny_ruch.wykon_pierw_ruch();
            }
            pion->ruszono();
            break;
        } case 'k':{
            krol *kr = dynamic_cast<krol*>(fig);
            if(kr->czy_pierwszy() == true){
                obecny_ruch.wykon_pierw_ruch();
            }
            kr->ruszono();
            break;
        } case 'w':{
            wieza *wi = dynamic_cast<wieza*>(fig);
            if(wi->czy_pierwszy()){
                obecny_ruch.wykon_pierw_ruch();
            }
            wi->ruszono();
        } default: break;
    }
    this->zmien_ture();
    moj_kolor = this->czyja_tura();
    // sprawdza czy po ruchu przeciwna druzyna jest w szachu
    // i ustawia wlasciwa zmienna
    figura *krol = (*this->zwroc_druzyne(moj_kolor))[0];
    figura *szachuje = this->czy_szach(krol->aktualna_pozycja(), moj_kolor);
    druzyna *dr = this->zwroc_druzyne(moj_kolor);
    dr->ustaw_szach(szachuje);
    // sprawdza czy jest podwojny szach i ustawia zmienna w druzynie
    dr->ustaw_podwojny_szach(this->czy_podwojny_szach(moj_kolor));
    this->poprzednie_ruchy.dodaj_elem(obecny_ruch);

    this->wylicz_wynik();
}

void plansza::ruch_figura(wspolrzedne start, wspolrzedne koniec){

    // jesli podano pozycje startowa spoza szachownicy konczy dzialanie funkcji
    if(plansza::czy_poza_plansza(start)){
        std::cout << "Proba ruchu z pola poza plansza: " << start.x << " " << start.y << std::endl;
        return;
    }

    // jesli podano pole docelowe spoza szachownicy konczy dzialanie funkcji
    if(plansza::czy_poza_plansza(koniec)){
        std::cout << "Proba ruchu na pole poza plansza: " << koniec.x << " " << koniec.y << std::endl;
        return;
    }

    // jesli proba ruchu nastepuje z pustego pola konczy dzialanie funkcji
    if((*this)(start) == nullptr){
        std::cout << " Pole puste, nie mozna sie stad ruszyc: " << start.x << " " << start.y << std::endl;
        return;
    }

    kolor tura = this->czyja_tura();
    if((*this)(start)->ktora_druzyna() != tura){
        std::cout << "Blad: Proba ruchu figura przeciwnika!" << std::endl;
        return;
    }

    blokada_szacha *tab_blok;
    druzyna *gracz = this->zwroc_druzyne(tura);

    // jesli gracz jest w podwojnym szachu to moze sie ruszyc tylko krolem
    if(gracz->czy_podwojny_szach() == true){
        if((*this)(start)->zwroc_nazwe() != 'k'){
            std::cout << "RUCH NIEDOZWOLONY" << std::endl;
            return;
        }
    }

    // jesli gracz nie jest szachowany
    if(gracz->czy_szach() == nullptr){
        tab_blok = nullptr;
    } else{ // jesli gracz jest szachowany
        tab_blok = new blokada_szacha;
        this->mozliwe_blokowanie_szacha((*gracz)[0]->aktualna_pozycja(), gracz->czy_szach()->aktualna_pozycja(), tab_blok);
    }

    tablica_ruchow *mozliwe_pola_koncowe = new tablica_ruchow;
    this->mozliwe_ruchy(start, tab_blok, mozliwe_pola_koncowe);
    // jesli nie mozna sie ruszyc na zadne pole konczy dzialanie funkcji
    if(mozliwe_pola_koncowe->rozmiar == 0){
        if(tab_blok != nullptr){
            delete tab_blok;
        }
        std::cout << "RUCH NIEDOZWOLONY" << std::endl;
        return;
    }

    int rozmiar = mozliwe_pola_koncowe->rozmiar;
    for(int i=0;i<rozmiar;i++){
        // czy chcemy sie ruszyc na dostepne dla figury pole
        if(koniec == (*mozliwe_pola_koncowe)[i]){
            // zwolnienie pamieci
            if(tab_blok != nullptr){
                delete tab_blok;
            }
            delete mozliwe_pola_koncowe;
            // aktualizuje stan gry i konczy dzialanie funkcji
            this->aktualizuj_stan_gry(koniec, start);
            return;
        }
    }
    // zwolnienie pamieci
    if(tab_blok != nullptr){
        delete tab_blok;
    }
    delete mozliwe_pola_koncowe;

    // nie mozna sie tak ruszyc
    std::cout << "RUCH NIEDOZWOLONY" << std::endl;
}

float plansza::zwroc_wynik(){
    return this->wynik;
}

void plansza::mozliwy_po_wektorze(figura &fig, const mozliwosc &_mozliwosc,
        tablica_ruchow *tab_ruch, blokada_szacha *tab_blok){

    // ile razy mozna powtorzyc rucho o wektor
    int powtorzen = _mozliwosc.zasieg;
    // wektor jakim sie poruszamy
    wspolrzedne wektor = _mozliwosc.wektor;
    // zmienna okreslajaca koncowe pole na ktore mozna sie ruszyc
    wspolrzedne mozliwy_ruch = fig.aktualna_pozycja();
    
    if(plansza::czy_poza_plansza(mozliwy_ruch+wektor)){
        return;
    }
    // jesli bede szachowany po ruchu w tym wektorze, to jest on zakazany
    bool bede_szach = this->czy_bede_szachowany(mozliwy_ruch, wektor);
    if(bede_szach == true){
        return;
    }

    int t_b_rozmiar = 0;
    if(tab_blok != nullptr){
        t_b_rozmiar = tab_blok->rozmiar;
    }

    char nazwa_fig = fig.zwroc_nazwe();
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
                if(nazwa_fig == 'p'){
                    return;
                } else{// mozna bic, ale dalej sie nie ruszymy
                    // trzeba sprawdzic czy akurat nie jestesmy szachowani
                    // jesli jestesmy to krol dalej sie porusza jak poprzednio
                    if(tab_blok != nullptr && nazwa_fig != 'k'){
                        // jesli tak to sprawdzamy dostepne mozliwosci
                        for(int j=0;j<t_b_rozmiar;j++){
                            if((*tab_blok)[j] == mozliwy_ruch){
                                tab_ruch->dodaj_elem(mozliwy_ruch);
                                return;
                            }
                        }
                    } else{
                        tab_ruch->dodaj_elem(mozliwy_ruch);
                        return;
                    }
                }
            }
        }
        // nie ma na drodze zadnych przeszkod
        // trzeba sprawdzic czy akurat nie jestesmy szachowani
        // jesli jestesmy to krol dalej sie porusza jak poprzednio
        if(tab_blok != nullptr && nazwa_fig != 'k'){
            // jesli tak to sprawdzamy dostepne mozliwosci
            for(int j=0;j<t_b_rozmiar;j++){
                if((*tab_blok)[j] == mozliwy_ruch){
                    tab_ruch->dodaj_elem(mozliwy_ruch);
                }
            }
        } else{
            tab_ruch->dodaj_elem(mozliwy_ruch);
        }
    }
}

void plansza::mozliwe_bicia_pionkiem(const pionek &pion, tablica_ruchow *tab_ruch, blokada_szacha *tab_blok){
    
    wspolrzedne wektory_bicia[2];
    pion.zasady_bicia(wektory_bicia);
    wspolrzedne pozycja_piona = pion.aktualna_pozycja();

    int t_b_rozmiar = 0;
    if(tab_blok != nullptr){
        t_b_rozmiar = tab_blok->rozmiar;
    }

    for(int i=0;i<2;i++){ // mozna bic na 2 sposoby
        wspolrzedne proba_bicia = pozycja_piona + wektory_bicia[i];
        if(plansza::czy_poza_plansza(proba_bicia) == false){ // czy pole znajduje sie na planszy
            if(czy_bede_szachowany(pozycja_piona, wektory_bicia[i]) == false){
                // if chroni przed proba sprawdzenia koloru jesli pole wskazuje na nullptr
                if((*this)(proba_bicia) != nullptr){
                    if((*this)(proba_bicia)->ktora_druzyna() != pion.ktora_druzyna()){ // jesli pole jest zajete przez przeciwnika
                        // trzeba sprawdzic czy akurat nie jestesmy szachowani
                        if(tab_blok != nullptr){
                            // jesli tak to sprawdzamy dostepne mozliwosci
                            for(int j=0;j<t_b_rozmiar;j++){
                                if((*tab_blok)[j] == proba_bicia){
                                    tab_ruch->dodaj_elem(proba_bicia);
                                }
                            }
                        } else{
                            tab_ruch->dodaj_elem(proba_bicia);
                        }
                    }
                }
            }
        }
    }
}

void plansza::mozliwe_bicie_w_przelocie(figura *&fig, tablica_ruchow *tab_ruch){
    // tylko z tego wiersza biali moga bic w przelocie
    if(fig->aktualna_pozycja().y == 4 && fig->ktora_druzyna() == biali){
        this->w_przelocie_biali(fig, tab_ruch);
    } else{
        // tylko z tego wiersza czarni moga bic w przelocie
        if(fig->aktualna_pozycja().y == 3 && fig->ktora_druzyna() == czarni){
            this->w_przelocie_czarni(fig, tab_ruch);
        }
    }
}

void plansza::w_przelocie_biali(figura *&fig, tablica_ruchow *tab_ruch){
    int x = fig->aktualna_pozycja().x + 1;
    if(x<8){
        if((*this)(x,4) != nullptr){
            // w przelocie mozna bic tylko pionka
            if(this->czy_wrogi_p(*(*this)(x,4),biali) == true){
                ruch _ruch = this->poprzednie_ruchy.sprawdz_gore();
                // pionek musial ruszyc sie o 2 pola
                if(_ruch.zwroc_skad() == wspolrzedne(x,6)
                && _ruch.zwroc_docelowo() == wspolrzedne(x,4)){
                    // ciezko przewidziec wszystkie wyjatki,
                    // wiec symulujemy ruch i sprawdzamy czy krol bedzie szachowany
                    figura *bity = (*this)(x,4);
                    (*this)(x,4) = nullptr;
                    (*this)(x-1,4) = nullptr;
                    (*this)(x,5) = fig;
                    figura *szach = czy_szach((*this->zwroc_druzyne(biali))[0]->aktualna_pozycja(), biali);
                    // cofamy symulacje
                    (*this)(x,4) = bity;
                    (*this)(x,5) = nullptr;
                    (*this)(x-1,4) = fig;
                    if(szach == nullptr){
                        tab_ruch->dodaj_elem(wspolrzedne(x,5));
                    } 
                }
            }
        }
    }
    x -= 2;
    if(x>=0){
        if((*this)(x,4) != nullptr){
            // w przelocie mozna bic tylko pionka
            if(this->czy_wrogi_p(*(*this)(x,4),biali) == true){
                ruch _ruch = this->poprzednie_ruchy.sprawdz_gore();
                // pionek musial ruszyc sie o 2 pola
                if(_ruch.zwroc_skad() == wspolrzedne(x,6)
                && _ruch.zwroc_docelowo() == wspolrzedne(x,4)){
                    // ciezko przewidziec wszystkie wyjatki,
                    // wiec symulujemy ruch i sprawdzamy czy krol bedzie szachowany
                    figura *bity = (*this)(x,4);
                    (*this)(x,4) = nullptr;
                    (*this)(x+1,4) = nullptr;
                    (*this)(x,5) = fig;
                    figura *szach = czy_szach((*this->zwroc_druzyne(biali))[0]->aktualna_pozycja(), biali);
                    // cofamy symulacje
                    (*this)(x,4) = bity;
                    (*this)(x,5) = nullptr;
                    (*this)(x+1,4) = fig;
                    if(szach == nullptr){
                        tab_ruch->dodaj_elem(wspolrzedne(x,5));
                    } 
                }
            }
        }
    }
}

void plansza::w_przelocie_czarni(figura *&fig, tablica_ruchow *tab_ruch){
    int x = fig->aktualna_pozycja().x + 1;
    if(x<8){
        if((*this)(x,3) != nullptr){
            // w przelocie mozna bic tylko pionka
            if(this->czy_wrogi_p(*(*this)(x,3),czarni) == true){
                ruch _ruch = this->poprzednie_ruchy.sprawdz_gore();
                // pionek musial ruszyc sie o 2 pola
                if(_ruch.zwroc_skad() == wspolrzedne(x,1)
                && _ruch.zwroc_docelowo() == wspolrzedne(x,3)){
                    // ciezko przewidziec wszystkie wyjatki,
                    // wiec symulujemy ruch i sprawdzamy czy krol bedzie szachowany
                    figura *bity = (*this)(x,3);
                    (*this)(x,3) = nullptr;
                    (*this)(x-1,3) = nullptr;
                    (*this)(x,2) = fig;
                    figura *szach = czy_szach((*this->zwroc_druzyne(czarni))[0]->aktualna_pozycja(), czarni);
                    // cofamy symulacje
                    (*this)(x,3) = bity;
                    (*this)(x,2) = nullptr;
                    (*this)(x-1,3) = fig;
                    if(szach == nullptr){
                        tab_ruch->dodaj_elem(wspolrzedne(x,2));
                    } 
                }
            }
        }
    }
    x -= 2;
    if(x>=0){
        if((*this)(x,3) != nullptr){
            // w przelocie mozna bic tylko pionka
            if(this->czy_wrogi_p(*(*this)(x,3),czarni) == true){
                ruch _ruch = this->poprzednie_ruchy.sprawdz_gore();
                // pionek musial ruszyc sie o 2 pola
                if(_ruch.zwroc_skad() == wspolrzedne(x,1)
                && _ruch.zwroc_docelowo() == wspolrzedne(x,3)){
                    // ciezko przewidziec wszystkie wyjatki,
                    // wiec symulujemy ruch i sprawdzamy czy krol bedzie szachowany
                    figura *bity = (*this)(x,3);
                    (*this)(x,3) = nullptr;
                    (*this)(x+1,3) = nullptr;
                    (*this)(x,2) = fig;
                    figura *szach = czy_szach((*this->zwroc_druzyne(czarni))[0]->aktualna_pozycja(), czarni);
                    // cofamy symulacje
                    (*this)(x,3) = bity;
                    (*this)(x,2) = nullptr;
                    (*this)(x+1,3) = fig;
                    if(szach == nullptr){
                        tab_ruch->dodaj_elem(wspolrzedne(x,2));
                    } 
                }
            }
        }
    }
}

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
    } else{
        // zeby nie bylo klopotu jak krol sie odsunie o pole od szachujacej figury
        // trzeba rozpatrzyc jakby jego obecna pozycja byla rowna nullptr
        figura *kr = (*this)(start);
        (*this)(start) = nullptr;

        fig = this->czy_szach(start+wektor, fig->ktora_druzyna());
        bool obok_kr = this->czy_obok_krola(start+wektor);
        // sprawdza czy 2 krole nie beda obok siebie
        // po rozpatrzeniu ponownie umieszczamy krola na planszy
        (*this)(start) = kr;
        if(fig != nullptr){
            return true;
        }

        if(obok_kr == true){
            return true;
        }
    }
    return false;
}

bool plansza::czy_odsloni_krola(wspolrzedne start, wspolrzedne wektor) const{

    figura *fig = (*this)(start);
    kolor kol = fig->ktora_druzyna();
    figura *kr = (*(this->zwroc_druzyne(kol)))[0]; // druzyna[0] zwraca krola z tej druzyny
    wspolrzedne poz_krola = kr->aktualna_pozycja();
    wspolrzedne mozliwy_atak(10,10); // jesli nie zostanie zmienione to na pewno wyjdzie poza plansze
    mozliwy_atak = wektor_od_krola(start, poz_krola);
    if(mozliwy_atak != wspolrzedne(10,10)){
        if(this->czy_cos_na_drodze(poz_krola, start, mozliwy_atak)){
           return false;
        }
    }

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
    if(wektor == mozliwy_atak || wektor == mozliwy_atak*(-1)){
        return false;
    } else{ // sprawdzamy tylko od miejsca za miejscem z ktorego chcemy sie ruszyc
        start += mozliwy_atak;
        while(plansza::czy_poza_plansza(start) == false){
            // jesli jakies pole jest zajete
            if((*this)(start) != nullptr){
                fig = (*this)(start);
                char nazwa_fig = fig->zwroc_nazwe();
                if(po_przekatnej == true){
                    // jesli zajmuje je goniec albo hetman
                    if(nazwa_fig == 'g' || nazwa_fig == 'h'){
                        // jesli jest przeciwnego koloru
                        if(fig->ktora_druzyna() != kol){
                            return true;
                        }
                    }
                    // na drodze byla juz jakas figura, wiec zwracamy false
                    return false;
                } else{
                    // jesli zajmuje je wieza albo hetman
                    if(nazwa_fig == 'w' || nazwa_fig == 'h'){
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

wspolrzedne plansza::wektor_od_krola(wspolrzedne poz_fig, wspolrzedne poz_krola) const{

    wspolrzedne wynik(10,10);
    int xfig = poz_fig.x;
    int xkrol = poz_krola.x;
    int yfig = poz_fig.y;
    int ykrol = poz_krola.y;

    // jesli roznica x i y jest taka sama
    // to ruszana figura jest pod skosem do krola
    int roznica_x = xfig - xkrol;
    int roznica_y = yfig - ykrol;
    if(roznica_x == roznica_y){
        // figura jest po przekatnej na polnocny wschod od krola
        if(xfig > xkrol){
            wynik = wspolrzedne(1,1);
        } else{ // figura jest na poludniowy zachod od krola
            wynik = wspolrzedne(-1,-1);
        }
    } else{
        // jesli roznica a.x - b.x == b.y -a.y
        // to ruszana figura jest pod skosem do krola
        roznica_x = xfig - xkrol;
        roznica_y = ykrol - yfig;
        if(roznica_x == roznica_y){
            // figura jest po przekatnej na poludniowy wschod od krola
            if(xfig > xkrol){
                wynik = wspolrzedne(1,-1);
            } else{ // figura jest na polnocny zachod od krola
                wynik = wspolrzedne(-1,1);
            }
        } else{
            // jesli krol i figura sa w tej samej kolumnie
            if(xfig == xkrol){
                // figura jest na polnoc
                if(yfig > ykrol){
                    wynik = wspolrzedne(0,1);
                } else{ // figura jest na poludnie
                    wynik = wspolrzedne(0,-1);
                }
            } else{
                // jesli krol i figura sa w tym samym wierszu
                if(yfig == ykrol){
                    // figura jest na wschod
                    if(xfig > xkrol){
                        wynik = wspolrzedne(1,0);
                    } else{
                        wynik = wspolrzedne(-1,0);
                    }
                }
            }
        }
    }
    return wynik;
}

figura* plansza::czy_szach(const wspolrzedne &pol_krola, const kolor &kol_krola) const{
    
    figura *fig = czy_szach_po_przekatnej(pol_krola, kol_krola);
    if(fig != nullptr){
        return fig;
    }
    fig = czy_szach_po_wier_lub_kol(pol_krola, kol_krola);
    if(fig != nullptr){
        return fig;
    }
    fig = czy_szach_przez_skoczka(pol_krola, kol_krola);
    if(fig != nullptr){
        return fig;
    }
    fig = czy_szach_przez_pionka(pol_krola, kol_krola);
    if(fig != nullptr){
        return fig;
    }
    return fig;
}

figura* plansza::czy_szach_po_wier_lub_kol(const wspolrzedne &pol_krola, const kolor &kol_krola) const{
    int xkrola = pol_krola.x;
    int ykrola = pol_krola.y;
    int i;
    figura *fig;

    for(i = xkrola-1;i>-1;i--){
        fig = (*this)(i, ykrola);
        if(fig != nullptr){
            // jesli pola na lewo od krola nie sa puste
            if(czy_wroga_w_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
    }

    for(i = xkrola+1;i<8;i++){
        fig = (*this)(i, ykrola);
        if(fig != nullptr){
            // jesli pola na prawo od krola nie sa puste
            if(czy_wroga_w_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
    }

    for(i = ykrola-1;i>-1;i--){
        fig = (*this)(xkrola, i);
        if(fig != nullptr){
            // jesli pola pod krolem nie sa puste
            if(czy_wroga_w_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
    }
    for(i = ykrola+1;i<8;i++){
        fig = (*this)(xkrola, i);
        if(fig != nullptr){
            // jesli pola nad krolem nie sa puste
            if(czy_wroga_w_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
    }
    return nullptr;
}

figura* plansza::czy_szach_po_przekatnej(const wspolrzedne &pol_krola, const kolor &kol_krola) const{
    int xkrola = pol_krola.x;
    int ykrola = pol_krola.y;
    int i, j;
    figura *fig;
    
    // na poludniowy zachod od krola
    i = xkrola-1;
    j = ykrola-1;
    while(i>-1 && j>-1){
        fig = (*this)(i, j);
        if(fig != nullptr){
            if(czy_wrogi_g_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
        --i;
        --j;
    }
    // na polnocny zachod od krola
    i = xkrola-1;
    j = ykrola+1;
    while(i>-1 && j<8){
        fig = (*this)(i, j);
        if(fig != nullptr){
            if(czy_wrogi_g_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
        --i;
        ++j;
    }
    // na polnocny wschod od krola
    i = xkrola+1;
    j = ykrola+1;
    while(i<8 && j<8){
        fig = (*this)(i, j);
        if(fig != nullptr){
            if(czy_wrogi_g_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
        ++i;
        ++j;
    }
    // na poludniowy wschod od krola
    i = xkrola+1;
    j = ykrola-1;
    while(i<8 && j>-1){
        fig = (*this)(i, j);
        if(fig != nullptr){
            if(czy_wrogi_g_lub_h(*fig, kol_krola) == true){
                return fig;
            }
            break; // wychodzi z petli bo na drodze jest inna figura
        }
        ++i;
        --j;
    }

    return nullptr;
}

figura* plansza::czy_szach_przez_skoczka(const wspolrzedne &pol_krola, const kolor &kol_krola) const{
    int x = pol_krola.x;
    int y = pol_krola.y;
    figura *fig;
    // wszystkie mozliwe ustawienia skoczka
    x -= 2; y -= 1;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    y +=2;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    x += 1; y += 1;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    x += 2;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    x += 1; y -= 1;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    y -= 2;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    x -= 1; y -= 1;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    x -=2;
    if(plansza::czy_poza_plansza(x,y) == false){
        fig = (*this)(x,y);
        if(fig != nullptr){
            if(czy_wrogi_s(*fig, kol_krola)){
                return fig;
            }
        }
    }
    return nullptr;
}

figura* plansza::czy_szach_przez_pionka(const wspolrzedne &pol_krola, const kolor &kol_krola) const{
    
    // pionek bez wzgledu na kolor musi byc przesuniety na x o 1
    int x1 = pol_krola.x - 1;
    int x2 = pol_krola.x + 1;
    int y = pol_krola.y;
    figura *fig;
    // jesli biali to czarny pionek
    if(kol_krola == biali){
        // pionek musi byc nad krolem
        ++y;
        if(y<8){
            if(x1>=0){
                fig = (*this)(x1,y);
                if(fig != nullptr){
                    if(fig->zwroc_nazwe() == 'p'){
                        if(fig->ktora_druzyna() == czarni){
                            return fig;
                        }
                    }
                }
            }
            if(x2<8){
                fig = (*this)(x2,y);
                if(fig != nullptr){
                    if(fig->zwroc_nazwe() == 'p'){
                        if(fig->ktora_druzyna() == czarni){
                            return fig;
                        }
                    }
                }
            }
        }
    } else{ // jesli czarni to bialy pionek
        // pionek musi byc pod krolem
        --y;
        if(y>=0){
            if(x1>=0){
                fig = (*this)(x1,y);
                if(fig != nullptr){
                    if(fig->zwroc_nazwe() == 'p'){
                        if(fig->ktora_druzyna() == biali){
                            return fig;
                        }
                    }
                }
            }
            if(x2<8){
                fig = (*this)(x2,y);
                if(fig != nullptr){
                    if(fig->zwroc_nazwe() == 'p'){
                        if(fig->ktora_druzyna() == biali){
                            return fig;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

bool plansza::czy_wroga_w_lub_h(const figura &fig, const kolor &moj_kol) const{
    char nazwa = fig.zwroc_nazwe();
    if(nazwa == 'w' || nazwa == 'h'){
        if(fig.ktora_druzyna() != moj_kol){
            // wroga wieza lub hetman
            return true;
        }
    }
    return false;
}

bool plansza::czy_wrogi_g_lub_h(const figura &fig, const kolor &moj_kol) const{
    char nazwa = fig.zwroc_nazwe();
    if(nazwa == 'g' || nazwa == 'h'){
        if(fig.ktora_druzyna() != moj_kol){
            // wrogi goniec lub hetman
            return true;
        }
    }
    return false;
}

bool plansza::czy_wrogi_s(const figura &fig, const kolor &moj_kol) const{
    if(fig.zwroc_nazwe() == 's'){
        if(fig.ktora_druzyna() != moj_kol){
            // wrogi skoczek
            return true;
        }
    }
    return false;
}

bool plansza::czy_wrogi_p(const figura &fig, const kolor &moj_kol) const{
    if(fig.zwroc_nazwe() == 'p'){
        if(fig.ktora_druzyna() != moj_kol){
            // wrogi pionek
            return true;
        }
    }
    return false;
}

bool plansza::czy_cos_na_drodze(wspolrzedne start, const wspolrzedne &koniec, const wspolrzedne &wektor) const{
    start += wektor;
    while(start != koniec){
        if(plansza::czy_poza_plansza(start)){
            // std::cout << "proba sprawdzenia czy cos jest na drodze, wyszla poza plansze" << std::endl;
            return false;
        }
        if((*this)(start) != nullptr){
            return true;
        }
        start += wektor;
    }
    return false;
}

bool plansza::czy_podwojny_szach(kolor kol) const{
    
    druzyna *_druzyna = this->zwroc_druzyne(kol);
    // podwojny szach moze byc tylko jesli jest szach
    // nie da sie spowodowac 2 chachow po przekatnej badz 2 po wierszach lub kolumnach itd
    if(_druzyna->czy_szach() != nullptr){
        wspolrzedne wsp_krola = (*_druzyna)[0]->aktualna_pozycja();
        bool szach1 = false;
        if(czy_szach_po_wier_lub_kol(wsp_krola, kol) != nullptr){
            szach1 = true;
        }
        bool szach2 = false;
        if(czy_szach_po_przekatnej(wsp_krola, kol) != nullptr){
            szach2 = true;
        }
        if(szach1 && szach2){
            return true;
        }
        bool szach3 = false;
        if(czy_szach_przez_skoczka(wsp_krola, kol) != nullptr){
            szach3 = true;
        }
        if((szach1 && szach3) || (szach2 && szach3)){
            return true;
        }
        bool szach4 = false;
        if(czy_szach_przez_pionka(wsp_krola, kol) != nullptr){
            szach4 = true;
        }
        if((szach1 && szach4) || (szach2 && szach4) || (szach3 && szach4)){
            return true;
        }
    }
    return false;
}

void plansza::roszada_mozliwa(const kolor &kol, tablica_ruchow *tab_ruch){
    druzyna *dr = this->zwroc_druzyne(kol);
    if(dynamic_cast<krol*>((*dr)[0])->czy_pierwszy() == true){
        int y = (*dr)[0]->aktualna_pozycja().y; // jesli krol sie nie ruszyl to zawsze bedzie albo w 0 albo 7 wierszu
        if(dr->czy_szach() == nullptr){
            figura *fig = (*this)(0,y);
            if(fig != nullptr && (*this)(1,y) == nullptr
            && (*this)(2,y) == nullptr && (*this)(3,y) == nullptr){
                if(fig->zwroc_nazwe() == 'w'){
                    if(dynamic_cast<wieza*>(fig)->czy_pierwszy() == true){
                        // nie trzeba usuwac krola przed sprawdzeniem szacha,
                        // nie jest szachowany obecnie, wiec w wierszu nie ma wrogiej wiezy lub hetmana
                        if(this->czy_szach(wspolrzedne(3,y),kol) == nullptr
                        && this->czy_szach(wspolrzedne(2,y),kol) == nullptr){
                            tab_ruch->dodaj_elem(wspolrzedne(2,y)); // dodaje dluga roszade        
                        }
                    }
                }
            }
            fig = (*this)(7,y);
            if(fig != nullptr && (*this)(6,y) == nullptr
            && (*this)(5,y) == nullptr){
                if(fig->zwroc_nazwe() == 'w'){
                    if(dynamic_cast<wieza*>(fig)->czy_pierwszy() == true){
                        // nie trzeba usuwac krola przed sprawdzeniem szacha,
                        // nie jest szachowany obecnie, wiec w wierszu nie ma wrogiej wiezy lub hetmana
                        if(this->czy_szach(wspolrzedne(5,y),kol) == nullptr
                        && this->czy_szach(wspolrzedne(6,y),kol) == nullptr){
                            tab_ruch->dodaj_elem(wspolrzedne(6,y)); // dodaje krotka roszade        
                        }
                    }
                }
            }
        }
    }
}

void plansza::aktualizuj_roszada(const wspolrzedne &docelowe, figura *fig, ruch &obecny_ruch){
    // dluga roszada 
    if((fig->aktualna_pozycja().x - docelowe.x) == 2){
        // tylko uaktualnic wieze, dalsza czesc kodu uaktualni krola
        figura *wieza = (*this)(0,docelowe.y);
        (*this)(wieza->aktualna_pozycja()) = nullptr;
        wieza->przesun(wspolrzedne(3,docelowe.y));
        (*this)(3,docelowe.y) = wieza;
        obecny_ruch.ustaw_ruch_spec('r');
    } else{// krotka roszada
        if(fig->aktualna_pozycja().x - docelowe.x == -2){
            // tylko uaktualnic wieze, dalsza czesc kodu uaktualnia krola
            figura *wieza = (*this)(7,docelowe.y);
            (*this)(wieza->aktualna_pozycja()) = nullptr;
            wieza->przesun(wspolrzedne(5,docelowe.y));
            (*this)(5,docelowe.y) = wieza;
            obecny_ruch.ustaw_ruch_spec('r');
        }
    }
}

void plansza::aktualizuj_promocja(figura *&fig, const char &na_co_prom){
    kolor kol = fig->ktora_druzyna();
    wspolrzedne wsp = fig->aktualna_pozycja();
    druzyna* dr = this->zwroc_druzyne(kol);
    // pionki sa na miejscach 8-15
    for(int i=8;i<16;i++){
        if((*dr)[i]->aktualna_pozycja() == wsp){
            delete (*dr)[i];
            switch(na_co_prom){
                case 'h':{
                    (*dr)[i] = new hetman(kol, wsp);
                    break;
                }
                case 's':{
                    (*dr)[i] = new skoczek(kol, wsp);
                    break;
                }
                case 'w':{
                    (*dr)[i] = new wieza(kol, wsp);
                    break;
                }
                case 'g':{
                    (*dr)[i] = new goniec(kol, wsp);
                    break;
                }
                default:{
                    std::cout << "bledna nazwa figury przy promocji" <<std::endl;
                    return;
                    break;
                }
            }
            (*this)(wsp) = (*dr)[i];
            fig = (*dr)[i];
            return;
        }
    }
}

void plansza::wylicz_wynik(){
    float _wynik = 0;
    druzyna *dr = this->zwroc_druzyne(biali);
    // jesli druzyna jest w szachy ma mniej punktow
    if(dr->czy_szach() != nullptr){
        _wynik += 0.7;
    }
    for(int i=0;i<16;i++){
        if((*dr)[i]->czy_aktywna() == true){
            switch((*dr)[i]->zwroc_nazwe()){
                case 'p': _wynik -= 1*((*dr)[i]->aktualna_pozycja().y*1.4+10)*0.1; break;
                case 'g': _wynik -= 3*((*dr)[i]->aktualna_pozycja().y*0.5+10)*0.1; break;
                case 's': _wynik -= 3*((*dr)[i]->aktualna_pozycja().y*0.5+10)*0.1; break;
                case 'w': _wynik -= 5*((*dr)[i]->aktualna_pozycja().y*0.3+10)*0.1; break;
                case 'h': _wynik -= 9*((*dr)[i]->aktualna_pozycja().y*0.2+10)*0.1; break;
                case 'k': _wynik -= 100; break;
                default: std::cout << "niedozwolona nazwa w druzynie" << std::endl;
                break;
            }
        }
    }
    // 17-y dla czarnych dziala tak jak y+10 dla bialych
    dr = this->zwroc_druzyne(czarni);
    for(int i=0;i<16;i++){
        if((*dr)[i]->czy_aktywna() == true){
            switch((*dr)[i]->zwroc_nazwe()){
                case 'p': _wynik += 1*((7-(*dr)[i]->aktualna_pozycja().y)*1.4+10)*0.1; break;
                case 'g': _wynik += 3*((7-(*dr)[i]->aktualna_pozycja().y)*0.5+10)*0.1; break;
                case 's': _wynik += 3*((7-(*dr)[i]->aktualna_pozycja().y)*0.5+10)*0.1; break;
                case 'w': _wynik += 5*((7-(*dr)[i]->aktualna_pozycja().y)*0.3+10)*0.1; break;
                case 'h': _wynik += 9*((7-(*dr)[i]->aktualna_pozycja().y)*0.2+10)*0.1; break;
                case 'k': _wynik += 100; break;
                default: std::cout << "niedozwolona nazwa w druzynie" << std::endl;
                break;
            }
        }
    }
    // jesli druzyna jest w szachy ma mniej punktow
    if(dr->czy_szach() != nullptr){
        _wynik -= 0.7;
    }

    // bonus za kontrole centrum
    for(int i=3;i<4;i++){
        for(int j=3;j<4;j++){
            if((*this)(j,i) != nullptr){
                if((*this)(j,i)->ktora_druzyna() == biali){
                    _wynik -= -0.12;
                } else{
                    _wynik += 0.12;
                }
            }
        }
    }
    this->wynik = _wynik;
}

bool plansza::czy_obok_krola(const wspolrzedne &wsp){
    if(wsp.x != 7){ // jesli nie jest w ostatniej kolumnie
        if((*this)(wsp.x+1,wsp.y) != nullptr){
            if((*this)(wsp.x+1,wsp.y)->zwroc_nazwe() == 'k'){
                return true;
            }
        }
        if(wsp.y != 7){ // jesli nie naroznik
            if((*this)(wsp.x+1,wsp.y+1) != nullptr){
                if((*this)(wsp.x+1,wsp.y+1)->zwroc_nazwe() == 'k'){
                    return true;
                }
            }
        }
        if(wsp.y != 0){ // jesli nie drugi naroznik
            if((*this)(wsp.x+1,wsp.y-1) != nullptr){
                if((*this)(wsp.x+1,wsp.y-1)->zwroc_nazwe() == 'k'){
                    return true;
                }
            }
        }
    }
    if(wsp.x != 0){ // jesli nie w pierwszej kolumnie
        if((*this)(wsp.x-1,wsp.y) != nullptr){
            if((*this)(wsp.x-1,wsp.y)->zwroc_nazwe() == 'k'){
                return true;
            }
        }
        if(wsp.y != 7){ // jesli nie trzeci naroznik
            if((*this)(wsp.x-1,wsp.y+1) != nullptr){
                if((*this)(wsp.x-1,wsp.y+1)->zwroc_nazwe() == 'k'){
                    return true;
                }
            }
        }
        if(wsp.y != 0){ // jesli nie czwarty naroznik
            if((*this)(wsp.x-1,wsp.y-1) != nullptr){
                if((*this)(wsp.x-1,wsp.y-1)->zwroc_nazwe() == 'k'){
                    return true;
                }
            }
        }
    }
    if(wsp.y != 7){ // jesli nie w ostatnim wierszu
        if((*this)(wsp.x,wsp.y+1) != nullptr){
            if((*this)(wsp.x,wsp.y+1)->zwroc_nazwe() == 'k'){
                return true;
            }
        }
    }
    if(wsp.y != 0){ // jesli nie w ostatniej kolumnie
        if((*this)(wsp.x,wsp.y-1) != nullptr){
            if((*this)(wsp.x,wsp.y-1)->zwroc_nazwe() == 'k'){
                return true;
            }
        }
    }
    return false;
}
