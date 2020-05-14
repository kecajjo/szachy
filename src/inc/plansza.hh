#ifndef PLANSZA_HH
#define PLANSZA_HH

#include <list>
#include <vector>
#include "wspolrzedne.hh"
#include "figura.hh"
#include "mozliwosc.hh"
#include "druzyna.hh"

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
    bool czy_puste(wspolrzedne wsp); // sprawdza czy nikogo nie ma na danym polu
    void zmien_pole(wspolrzedne wsp, figura *fig); // zmienia wartosc pola o wspolrzednych (x,y)
    figura* operator ()(int _x, int _y) const;
    figura*& operator ()(int _x, int _y); // zwraca adres wskaznika na figure
    figura* operator ()(wspolrzedne wsp) const;
    figura*& operator ()(wspolrzedne wsp); // zwraca adres wskaznika na figure
    void rusz(wspolrzedne start, wspolrzedne koniec); // jesli jest to zgodne z zasadami rusza figure z pola start na pole koniec
    std::vector<wspolrzedne> *mozliwe_ruchy(wspolrzedne start); // zwraca liste dostepnych ruchow z danego pola
    void wyswietl(); // wyswietla plansze
    static bool czy_poza_plansza(wspolrzedne wsp); // sprawdza czy istnieje pole o takich wspolrzednych

    private:
    // dodaje ruch do listy jesli nie jest to wbrew zasadom
    void mozliwy_po_wektorze(figura &fig,
        const mozliwosc &_mozliwosc, std::vector<wspolrzedne> *lista_ruchow);
    void zbij(figura *fig); // bije figure i aktualizuje wynik
    void aktualizuj_pola(const wspolrzedne &docelowe, figura &fig); // aktualizuje stan szachownicy po ruchu
    // zwraca mozliwe bicia pionkiem
    void mozliwe_bicia_pionkiem(pionek &pion, std::vector<wspolrzedne> *lista_ruchow);
};

#endif