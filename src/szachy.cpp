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

void ruch_si(){
    // TODO
}
