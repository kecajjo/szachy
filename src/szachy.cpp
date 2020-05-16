#include "inc/szachy.hh"

// TODO dokonczyc wczytywanie ruchu z klawiatury i poprawic calosc
void szachy::czytaj_ruch(){
    // pozycje startowe
    char kolumna_st;
    int wiersz_st;
    int kol_po_konw_st;
    std::cin >> kolumna_st;
    std::cin >> wiersz_st;

    kolumna_st = toupper(kolumna_st); // jesli uzytkownik poda mala litere to nic to nie zmieni
    kol_po_konw_st = int(kolumna_st); // konwertujemy char na ASCII
    kol_po_konw_st -= 65; // zamienia A na 0, B na 1 itd
    // zamieni 1 na 0 itd, zeby program liczyl od 0 a uzytkownik operowal jak na szachownicy od 1
    --wiersz_st;

    char kolumna_kon;
    int wiersz_kon;
    int kol_po_konw_kon;
    std::cin >> kolumna_kon;
    std::cin >> wiersz_kon;

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
    if(this->szachownica(start) == nullptr){
        std::cout << " Pole puste, nie mozna sie stad ruszyc" << std::endl;
        return;
    }

    kolor tura = this->szachownica.czyja_tura();
    if(this->szachownica(start)->ktora_druzyna() != tura){
        std::cout << "Blad: Proba ruchu figura przeciwnika!" << std::endl;
        return;
    }

    blokada_szacha *tab_blok;
    druzyna *gracz = this->szachownica.zwroc_druzyne(tura);
    // jesli gracz nie jest szachowany
    if(gracz->czy_szach() == nullptr){
        tab_blok = nullptr;
    } else{ // jesli gracz jest szachowany
        tab_blok = new blokada_szacha;
        this->szachownica.mozliwe_blokowanie_szacha((*gracz)[0]->aktualna_pozycja(), gracz->czy_szach()->aktualna_pozycja(), tab_blok);
    }

    tablica_ruchow *mozliwe_pola_koncowe = this->szachownica.mozliwe_ruchy(start, tab_blok);
    // jesli nie mozna sie ruszyc na zadne pole konczy dzialanie funkcji
    if(mozliwe_pola_koncowe == nullptr){
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
            // jesli ruszamy sie na pole, ktore nie jest puste
            if(this->szachownica(koniec) != nullptr){
                // bijemy figure na polu docelowym
                this->szachownica.zbij(this->szachownica(koniec));
            }
            // zwolnienie pamieci
            if(tab_blok != nullptr){
                delete tab_blok;
            }
            delete mozliwe_pola_koncowe;
            // aktualizuje pole i konczy dzialanie funkcji
            this->szachownica.aktualizuj_stan_gry(koniec, this->szachownica(start));
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
