#ifndef PLANSZA_HH
#define PLANSZA_HH

#include "wspolrzedne.hh"
#include "figura.hh"
#include "mozliwosc.hh"
#include "druzyna.hh"
#include "tablica_ruchow.hh"
#include "blokada_szacha.hh"
#include "lifo.hh"
#include "ruch.hh"
#include <iostream>

#define PAMIEC_WSTECZ 10

#define ROZMIAR 8

class plansza{

    figura *pola[ROZMIAR][ROZMIAR]; // szachownica zawierajaca informacje o tym, kto zajmuje dane pole
    kolor tura; // -1 kolej bialych 1 kolej czarnych 0 jakis blad, nikt nie moze sie ruszyc
    druzyna *biel;
    druzyna *czern;
    // nie int zeby poza materialem moc pozycje na stole nagradzac 
    // biale chca jak najmniejszy czarne jak najwiekszy, poczatkowy to 0
    float wynik;
    lifo<ruch, PAMIEC_WSTECZ> poprzednie_ruchy;

    public:
    plansza(); // ustawia obydwie druzyny, tura bialych
    ~plansza();
    kolor czyja_tura(); // zwraca czyja jest teraz kolej
    bool czy_puste(wspolrzedne wsp) const; // sprawdza czy nikogo nie ma na danym polu
    figura* operator ()(const int &_x, const int &_y) const;
    figura*& operator ()(const int &_x, const int &_y); // zwraca adres wskaznika na figure
    figura* operator ()(const wspolrzedne &wsp) const;
    figura*& operator ()(const wspolrzedne &wsp); // zwraca adres wskaznika na figure
    // zwraca tablice wskaznikow na tablic_ruchow zawierajaca wszystkie mozliwe ruchy danej druzyny
    // trzeba pamietac o zwolnieniu z pamieci wszystkich elementow
    void ruchy_druzyny(kolor kol, tablica_ruchow **wszystkie_ruchy);
    // zwraca strukture majaca tablice dostepnych ruchow z danego pola
    tablica_ruchow *mozliwe_ruchy(wspolrzedne start, blokada_szacha *tab_blok);
    // pozwala cofnac ruch
    void cofnij_ruch();
    // sprawdza czy juz koniec gry, sprawdza czy ktorakolwiek figura moze wykonac ruch
    // standardowo jest 16 figur stad rozmiar = 16
    bool czy_mat_pat(tablica_ruchow **wszystkie_ruchy, const int &rozmiar = 16);
    // czy dana druzyna przegrala/zremisowala(pat)
    bool czy_mat_pat(kolor kol);
    void wyswietl() const; // wyswietla plansze
    static bool czy_poza_plansza(const wspolrzedne &wsp); // sprawdza czy istnieje pole o takich wspolrzednych
    static bool czy_poza_plansza(const int &_x, const int &_y); // sprawdza czy istnieje pole o takich wspolrzednych
    druzyna* zwroc_druzyne(const kolor &kol) const; // zwraca wskaznik na druzyne w danym kolorze 
    // zmiana osoby, ktora sie rusza
    void zmien_ture();
    // sprawdza na ktore pola mozna sie ruszyc figura inna niz krol, zeby powstrzymac szacha i zapisuej je w blokadzie_szacha
    void mozliwe_blokowanie_szacha(wspolrzedne kr, const wspolrzedne &szachujaca, blokada_szacha *tab_blok) const;
    void zbij(figura *fig); // bije figure i aktualizuje wynik
    void aktualizuj_stan_gry(const wspolrzedne &docelowe, const wspolrzedne &poczatkowe); // aktualizuje stan szachownicy po ruchu
    // rusza wybrana figura jesli jest to dozwolone
    void ruch_figura(wspolrzedne start, wspolrzedne koniec);
    float zwroc_wynik(); // zwraca aktualny wynik

    private:
    // dodaje ruch do listy jesli nie jest to wbrew zasadom
    void mozliwy_po_wektorze(figura &fig, const mozliwosc &_mozliwosc,
        tablica_ruchow *tab_ruch, blokada_szacha *tab_blok);
    // zwraca mozliwe bicia pionkiem
    void mozliwe_bicia_pionkiem(pionek &pion, tablica_ruchow *tab_ruch, blokada_szacha *tab_blok);
    // sprawdza czy ruszajac sie nie spowodujemy szacha na wlasnym krolu
    // start to pole z ktorego sie ruszamy, wektor to wektor w jakim chcemy sie ruszyc
    // wektor poniewaz w jedna strone mozemy nie odslanic krola a w inna bedziemy odslaniac
    bool czy_bede_szachowany(wspolrzedne start, wspolrzedne wektor);
    // wykorzystane w czy_bede_szachowany
    bool czy_odsloni_krola(wspolrzedne start, wspolrzedne wektor) const;
    // sprawdza po jakim wektorze nalezy sie poruszac od krola do figury
    // jesli nie po skosie, wierszach lub kolumnach zwraca wspolrzedne(10,10)
    wspolrzedne wektor_od_krola(wspolrzedne poz_fig, wspolrzedne poz_krola) const;
    // sprawdza czy krol w danym miejscu bylby szachowany, zwraca nullptr jesli nie
    figura* czy_szach(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy krol w danym miejscy bedzie szachowany w wierszu lub kolumnie, zwraca nullptr, jesli brak szacha
    figura* czy_szach_po_wier_lub_kol(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy krol w danym miejscy bedzie szachowany po przekatnej, zwraca nullptr, jesli brak szacha
    figura* czy_szach_po_przekatnej(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy skoczek szachuje krol w danym miejscu, zwraca nullptr, jesli brak szacha
    figura* czy_szach_przez_skoczka(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // czy pionek szachuje krol w danym miejscu, zwraca nullptr jesli brak szacha
    figura* czy_szach_przez_pionka(const wspolrzedne &pol_krola, const kolor &kol_krola) const;
    // sprawdza czy dana figura to wroga wieza lub hetman
    bool czy_wroga_w_lub_h(const figura &fig, const kolor &moj_kol) const;
    // sprawdza czy dana figura to wrogi goniec lub hetman
    bool czy_wrogi_g_lub_h(const figura &fig, const kolor &moj_kol) const;
    // sprawdza czy dana figura to wrogi skoczek
    bool czy_wrogi_s(const figura &fig, const kolor &moj_kol) const;
    // sprawdza czy dana figura to wrogi pionek
    bool czy_wrogi_p(const figura &fig, const kolor &moj_kol) const;
    // sprawdza czy cos jest pomiedzy figurami na polach start i koniec, potrzebuje wektor w ktorym sie przemieszcza
    bool czy_cos_na_drodze(wspolrzedne start, const wspolrzedne &koniec, const wspolrzedne &wektor) const;
    // sprawdza czy druzyna jest w podwojnym szachu
    bool czy_podwojny_szach(kolor kol) const;
    // probuje zrobic roszade w danej druzynie
    void roszada_mozliwa(const kolor &kol, tablica_ruchow *tab_ruch);
    // sprawdza czy nastapila roszada, jesli tak to aktualizuje wieze
    void aktualizuj_roszada(const wspolrzedne &docelowe, figura *fig, ruch &obecny_ruch);
    // aktualizuj pionka na figure podczas promocji
    void aktualizuj_promocja(figura *&fig, const char &na_co_prom = 'h');
    // wylicza wynik na podstawie obecnej sytuacji na planszy
    void wylicz_wynik();
};

#endif