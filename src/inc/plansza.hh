#ifndef PLANSZA_HH
#define PLANSZA_HH

#include "wspolrzedne.hh"
#include "figura.hh"
#include "mozliwosc.hh"
#include "druzyna.hh"
#include "tablica_ruchow.hh"


#define ROZMIAR 8

class plansza{

    figura *pola[ROZMIAR][ROZMIAR]; // szachownica zawierajaca informacje o tym, kto zajmuje dane pole
    kolor tura; // -1 kolej bialych 1 kolej czarnych 0 jakis blad, nikt nie moze sie ruszyc
    druzyna *biel;
    druzyna *czern;
    // nie int zeby poza materialem moc pozycje na stole nagradzac 
    // biale chca jak najmniejszy czarne jak najwiekszy, poczatkowy to 0
    float wynik;

    public:
    plansza(); // ustawia obydwie druzyny, tura bialych
    kolor czyja_tura(); // zwraca czyja jest teraz kolej
    figura* zwroc_pole(wspolrzedne wsp); // zwraca kto jest na danym polu o wspolrzednych (x,y)
    bool czy_puste(wspolrzedne wsp) const; // sprawdza czy nikogo nie ma na danym polu
    void zmien_pole(wspolrzedne wsp, figura *fig); // zmienia wartosc pola o wspolrzednych (x,y)
    figura* operator ()(int _x, int _y) const;
    figura*& operator ()(int _x, int _y); // zwraca adres wskaznika na figure
    figura* operator ()(wspolrzedne wsp) const;
    figura*& operator ()(wspolrzedne wsp); // zwraca adres wskaznika na figure
    void rusz(wspolrzedne start, wspolrzedne koniec); // jesli jest to zgodne z zasadami rusza figure z pola start na pole koniec
    tablica_ruchow *mozliwe_ruchy(wspolrzedne start) const; // zwraca liste dostepnych ruchow z danego pola
    void wyswietl() const; // wyswietla plansze
    static bool czy_poza_plansza(wspolrzedne wsp); // sprawdza czy istnieje pole o takich wspolrzednych
    static bool czy_poza_plansza(int _x, int _y); // sprawdza czy istnieje pole o takich wspolrzednych

    private:
    // dodaje ruch do listy jesli nie jest to wbrew zasadom
    void mozliwy_po_wektorze(figura &fig,
        const mozliwosc &_mozliwosc, tablica_ruchow *tab_ruch) const;
    void zbij(figura *fig); // bije figure i aktualizuje wynik
    void aktualizuj_pola(const wspolrzedne &docelowe, figura &fig); // aktualizuje stan szachownicy po ruchu
    // zwraca mozliwe bicia pionkiem
    void mozliwe_bicia_pionkiem(pionek &pion, tablica_ruchow *tab_ruch) const;
    druzyna* zwroc_druzyne(kolor kol) const; // zwraca wskaznik na druzyne w danym kolorze 
    // sprawdza czy ruszajac sie nie spowodujemy szacha na wlasnym krolu
    // start to pole z ktorego sie ruszamy, wektor to wektor w jakim chcemy sie ruszyc
    // wektor poniewaz w jedna strone mozemy nie odslanic krola a w inna bedziemy odslaniac
    bool czy_bede_szachowany(wspolrzedne start, wspolrzedne wektor) const;
    bool czy_odsloni_krola(wspolrzedne start, wspolrzedne wektor) const; // wykorzystane w czy_bede_szachowany
    // sprawdza po jakim wektorze nalezy sie poruszac od krola do figury
    // jesli nie po skosie, wierszach lub kolumnach zwraca wspolrzedne(10,10)
    wspolrzedne wektor_od_krola(wspolrzedne poz_fig, wspolrzedne poz_krola) const;
    // sprawdza czy jesli krol sie rusza w dane miejsce to bedzie szachowany
    bool krol_sie_szachuje(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy krol w danym miejscy bedzie szachowany w wierszu lub kolumnie
    bool czy_szach_po_wier_lub_kol(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy krol w danym miejscy bedzie szachowany po przekatnej
    bool czy_szach_po_przekatnej(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy skoczek szachuje krol w danym miejscu
    bool czy_szach_przez_skoczka(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // sprawdza czy na danym polu jest wroga wieza lub hetman
    bool czy_wroga_w_lub_h(const int &x_wsp, const int &y_wsp, const kolor &moj_kol) const;
    // sprawdza czy na danym polu jest wrogi goniec lub hetman
    bool czy_wrogi_g_lub_h(const int &x_wsp, const int &y_wsp, const kolor &moj_kol) const;
    // sprawdza czy na danym polu jest wrogi skoczek
    bool czy_wrogi_s(const int &x_wsp, const int &y_wsp, const kolor &moj_kol) const;

};

#endif