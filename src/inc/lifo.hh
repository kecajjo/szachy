#ifndef LIFO_HH
#define LIFO_HH

#include <iostream>
// statyczny rozmiar pozwala zaoszczedzic czas na alokowanie pamieci
// w grze bedzie tylko 1 taka struktura o niewielkim rozmiarze
template <typename typ, int maks_rozmiar>
struct lifo{
    private:
    typ elementy[maks_rozmiar]; // wskaznik na dodawane elementy
    int rozmiar;
    int aktualny_elem;
    public:
    lifo();
    void dodaj_elem(typ);
    typ sciagnij_elem(); // sciaga element z gory i usuwa go
    typ sprawdz_gore(); // zwraca element z gory, ale nie usuwa go
    int zwroc_rozmiar(); // zwraca rozmiar
};

template <typename typ, int maks_rozmiar>
lifo<typ, maks_rozmiar>::lifo(){
    this->rozmiar = 0;
    aktualny_elem = -1;
}

template <typename typ, int maks_rozmiar>
void lifo<typ, maks_rozmiar>::dodaj_elem(typ _typ){
    this->aktualny_elem += 1;
    // jesli zapelnimy strukture to zacznie tracic pamiec o najstarszych elementach na rzecz nowych
    this->aktualny_elem %= maks_rozmiar;
    this->elementy[aktualny_elem] = _typ;
    // musimy znac rozmiar, zeby potem nie probowac sciagac z pustej struktury
    if(this->rozmiar < maks_rozmiar){
        this->rozmiar += 1;
    }
}

template <typename typ, int maks_rozmiar>
typ lifo<typ, maks_rozmiar>::sciagnij_elem(){
    if(this->rozmiar < 1){
        std::cout << "struktura pusta, nie mozna sciagnac elementu" << std::endl;
        return this->elementy[0];
    }
    typ zwroc = this->elementy[aktualny_elem];
    // w ten sposob modulo zawsze zwroci poprzedni element
    aktualny_elem += maks_rozmiar-1;
    aktualny_elem %= maks_rozmiar;
    this->rozmiar -= 1;
    return zwroc;
}

template <typename typ, int maks_rozmiar>
typ lifo<typ, maks_rozmiar>::sprawdz_gore(){
    if(this->rozmiar < 1){
        std::cout << "struktura pusta, nie mozna sprawdzic elementu" << std::endl;
        return this->elementy[0];
    }
    return this->elementy[aktualny_elem];
}

template <typename typ, int maks_rozmiar>
int lifo<typ, maks_rozmiar>::zwroc_rozmiar(){
    return this->rozmiar;
}

#endif