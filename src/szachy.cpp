#include "inc/szachy.hh"

// TODO poprawic zeby bylo czytelniejsze
void szachy::czytaj_ruch(){
    std::cout << std::endl << "Podaj ruch, np A1 B6,\ngdzie A1 to pozycja startowa, B6 to pozycja koncowa" << std::endl;
    // pozycje startowe
    char kolumna_st;
    int wiersz_st;
    int kol_po_konw_st;
    std::cin >> kolumna_st;
    while(std::cin.fail() || ((kolumna_st < 'A' || kolumna_st > 'H')
     && (kolumna_st < 'a' || kolumna_st > 'h'))){

        std::cout << "Blad przy wczytywaniu kolumny startowej" << std::endl << "podaj litere A-H"<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> kolumna_st;
    }
    std::cin >> wiersz_st;
    while(std::cin.fail() || wiersz_st < 1 || wiersz_st > 8){
        std::cout << "Blad przy wczytywaniu wiersza startowego" << std::endl << "podaj cyfre 1-8" <<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> wiersz_st;
    }

    kolumna_st = toupper(kolumna_st); // jesli uzytkownik poda mala litere to nic to nie zmieni
    kol_po_konw_st = int(kolumna_st); // konwertujemy char na ASCII
    kol_po_konw_st -= 65; // zamienia A na 0, B na 1 itd
    // zamieni 1 na 0 itd, zeby program liczyl od 0 a uzytkownik operowal jak na szachownicy od 1
    --wiersz_st;

    char kolumna_kon;
    int wiersz_kon;
    int kol_po_konw_kon;
    std::cin >> kolumna_kon;
    while(std::cin.fail()|| ((kolumna_kon < 'A' || kolumna_kon > 'H')
     && (kolumna_kon < 'a' || kolumna_kon > 'h'))){
        std::cout << "Blad przy wczytywaniu kolumny koncowej" << std::endl << "podaj litere A-H"<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> kolumna_kon;
    }
    std::cin >> wiersz_kon;
    while(std::cin.fail() || wiersz_kon < 1 || wiersz_kon > 8){
        std::cout << "Blad przy wczytywaniu wiersza startowego" << std::endl << "podaj cyfre 1-8" <<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> wiersz_kon;
    }

    kolumna_kon = toupper(kolumna_kon); // jesli uzytkownik poda mala litere to nic to nie zmieni
    kol_po_konw_kon = int(kolumna_kon); // konwertujemy char na ASCII
    kol_po_konw_kon -= 65; // zamienia A na 0, B na 1 itd
    // zamieni 1 na 0 itd, zeby program liczyl od 0 a uzytkownik operowal jak na szachownicy od 1
    --wiersz_kon;
    this->ruch_gracza(wspolrzedne(kol_po_konw_st,wiersz_st), wspolrzedne(kol_po_konw_kon,wiersz_kon));
}

void szachy::wyswietl_stan_gry(){
    szachownica.wyswietl();
}

void szachy::ruch_gracza(wspolrzedne start, wspolrzedne koniec){
    this->szachownica.ruch_figura(start, koniec);
}

void szachy::cofnij(){
    this->szachownica.cofnij_ruch();
}

bool szachy::czy_koniec(kolor kol){
    if(this->szachownica.czy_mat_pat(kol) == true){
        return true;
    }
    return false;
}

void szachy::ruch_si(){
    ruch ruch_komputera = this->alfa_beta_zewn(GLEBOKOSC_SI);
    this->szachownica.ruch_figura(ruch_komputera.skad,ruch_komputera.docelowo);
}

ruch szachy::alfa_beta_zewn(int glebokosc){
    if(glebokosc == 0){
        return ruch();
    }
    tablica_ruchow **wszystkie_ruchy = new tablica_ruchow*[16];
    this->szachownica.ruchy_druzyny(this->szachownica.czyja_tura(), wszystkie_ruchy);
    if(this->szachownica.czy_mat_pat(wszystkie_ruchy)){
        this->usun_tab_wsz_ruch(wszystkie_ruchy);
        // nie mozna wykonac ruchu jesli jest juz mat/pat
        return ruch();
    }

    ruch najlepszy_ruch;
    float najlepszy_wynik;
    wspolrzedne docelowo;
    kolor kol = this->szachownica.czyja_tura();
    druzyna *dr = this->szachownica.zwroc_druzyne(kol);

    if(kol == biali){
        najlepszy_wynik = 1000000; // liczba znacznie wieksza niz jakikolwiek mozliwy do uzyskania wynik
    } else{
        najlepszy_wynik = -1000000; // liczba znacznie mniejsza niz jakikolwiek mozliwy do uzyskania wynik
    }
    for(int i=15;i>-1;i--){ // bedzie preferowac ruch pionkami
        // jesli wszystkie ruchy wskazuja na nullptr to pomijamy figure
        if(wszystkie_ruchy[i] != nullptr){
            int ile_ruchow_fig = wszystkie_ruchy[i]->rozmiar;
            figura *aktualna_fig = (*dr)[i];
            for(int j=0; j<ile_ruchow_fig; j++){
                docelowo = (*wszystkie_ruchy[i])[j];
                // ruszamy sie, by rozwazyc dana mozliwosc
                // jako ze sprawdzamy tylko mozlwie ruchy mozemy od razu aktualizowac plansze
                this->szachownica.aktualizuj_stan_gry(docelowo, aktualna_fig);
                float wynik_ruchu;
                if(kol == biali){
                    wynik_ruchu = this->alfa_beta_wewn(glebokosc-1, -1000000, najlepszy_wynik, czarni);
                    // cofamy sie do poprzedniego ustawienia szachownicy
                    this->cofnij();
                    if(wynik_ruchu < najlepszy_wynik){
                        najlepszy_wynik = wynik_ruchu;
                        // jako docelowo ustawia wpolrzedne koncowe ktore sprawdzilismy w ruchu
                        najlepszy_ruch.ustaw_docelowo(docelowo);
                        // jako skad ustawia pozycje figury, ktora ruszalismy
                        najlepszy_ruch.ustaw_skad(aktualna_fig->aktualna_pozycja());
                    }
                } else{
                    wynik_ruchu = this->alfa_beta_wewn(glebokosc-1, najlepszy_wynik, 1000000, biali);
                    // cofamy sie do poprzedniego ustawienia szachownicy
                    this->cofnij();
                    if(wynik_ruchu > najlepszy_wynik){
                        najlepszy_wynik = wynik_ruchu;
                        // jako docelowo ustawia wpolrzedne koncowe ktore sprawdzilismy w ruchu
                        najlepszy_ruch.ustaw_docelowo(docelowo);
                        // jako skad ustawia pozycje figury, ktora ruszalismy
                        najlepszy_ruch.ustaw_skad(aktualna_fig->aktualna_pozycja());
                    }
                }
            }
        }
    }
    this->usun_tab_wsz_ruch(wszystkie_ruchy);

    return najlepszy_ruch;
}

float szachy::alfa_beta_wewn(int glebokosc, float alfa, float beta, kolor kol){
    
    tablica_ruchow **wszystkie_ruchy = new tablica_ruchow*[16];
    this->szachownica.ruchy_druzyny(this->szachownica.czyja_tura(), wszystkie_ruchy);
    if(this->szachownica.czy_mat_pat(wszystkie_ruchy) == true){
        // nie mozna wykonac ruchu jesli jest juz mat/pat
        if(this->szachownica.czyja_tura() == biali){
            if(this->szachownica.zwroc_druzyne(biali)->czy_szach() != nullptr){
                this->usun_tab_wsz_ruch(wszystkie_ruchy);
                // czarne wygraly, zwracamy duzy wynik
                return 1000000;
            } else{ // pat czyli remis
                this->usun_tab_wsz_ruch(wszystkie_ruchy);
                return 0;
            }
        } else{
            if(this->szachownica.zwroc_druzyne(czarni)->czy_szach() != nullptr){
                this->usun_tab_wsz_ruch(wszystkie_ruchy);
                // biale wygraly, zwracamy maly wynik
                return -1000000;
            } else{ // pat czyli remis
                this->usun_tab_wsz_ruch(wszystkie_ruchy);
                return 0;
            }
        }
    }
    
    // jesli doszlismy do konca rekurencji zwracamy wynik
    if(glebokosc == 0){
        this->usun_tab_wsz_ruch(wszystkie_ruchy);
        return this->szachownica.zwroc_wynik();
    }


    float najlepszy_wynik;
    wspolrzedne docelowo;
    druzyna *dr = this->szachownica.zwroc_druzyne(kol);

    if(kol == biali){
        najlepszy_wynik = 1000000; // liczba znacznie wieksza niz jakikolwiek mozliwy do uzyskania wynik
    } else{
        najlepszy_wynik = -1000000; // liczba znacznie mniejsza niz jakikolwiek mozliwy do uzyskania wynik
    }

    for(int i=15;i>-1;i--){ // bedzie preferowac ruch pionkami
        // jesli wszystkie ruchy wskazuja na nullptr to pomijamy figure
        if(wszystkie_ruchy[i] != nullptr){
            int ile_ruchow_fig = wszystkie_ruchy[i]->rozmiar;
            figura *aktualna_fig = (*dr)[i];
            for(int j=0; j<ile_ruchow_fig; j++){
                docelowo = (*wszystkie_ruchy[i])[j];
                // ruszamy sie, by rozwazyc dana mozliwosc
                // jako ze sprawdzamy tylko mozlwie ruchy mozemy od razu aktualizowac plansze
                this->szachownica.aktualizuj_stan_gry(docelowo, aktualna_fig);
                float wynik_ruchu;
                if(kol == biali){
                    wynik_ruchu = this->alfa_beta_wewn(glebokosc-1, alfa, beta, czarni);
                    if(wynik_ruchu < najlepszy_wynik){
                        najlepszy_wynik = wynik_ruchu;
                    }
                    if(beta < wynik_ruchu){
                        beta = wynik_ruchu;
                    }
                } else{
                    wynik_ruchu = this->alfa_beta_wewn(glebokosc-1, alfa, beta, biali);
                    if(wynik_ruchu > najlepszy_wynik){
                        najlepszy_wynik = wynik_ruchu;
                    }
                    if(alfa > wynik_ruchu){
                        alfa = wynik_ruchu;
                    }
                }
                // cofamy sie do poprzendiego ustawienia szachownicy
                this->cofnij();
                // usuwanie mozliwosci, ktore nie wplywaja na wynik
                if(beta <= alfa){
                    this->usun_tab_wsz_ruch(wszystkie_ruchy);
                    return najlepszy_wynik;
                }
            }
        }
    }
    this->usun_tab_wsz_ruch(wszystkie_ruchy);
    return najlepszy_wynik;
}

void szachy::usun_tab_wsz_ruch(tablica_ruchow **usun){
    if(usun != nullptr){
        for(int i=0;i<16;i++){
            if(usun[i] != nullptr){
                delete usun[i];
            }
        }
        delete [] usun;
    }
}

void szachy::graj_przeciw_komputerowi(const kolor &kol_gracza){
    while(this->czy_koniec(biali) == false && this->czy_koniec(czarni) == false){
        this->wyswietl_stan_gry();
        if(this->szachownica.czyja_tura() == kol_gracza){
            this->czytaj_ruch();
        } else{
            std::clock_t start = std::clock();
            this->ruch_si();
            std::clock_t koniec = std::clock();
            double czas = (double)(koniec-start)/CLOCKS_PER_SEC;
            std::cout << "czas liczenia przez AI: " << czas << std::endl;
        }
    }
    if(this->czy_koniec(biali) == true){
        std::cout << "Czarni wygrali" << std::endl;
    }
    if(this->czy_koniec(czarni) == true){
        std::cout << "biali wygrali" << std::endl;
    }
}
