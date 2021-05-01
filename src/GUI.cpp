#include "inc/GUI.hh"

GUI::GUI(){
    if(this->plansza_tex.loadFromFile("./obrazki/szachownica1.png") == false){
        std::cout << "BLAD podczas otwierania obrazka" <<std::endl;
        return;
    }
    this->plansza_sp.setTexture(this->plansza_tex);
    float x = this->plansza_tex.getSize().x;
    float y = this->plansza_tex.getSize().y;
    x = 720/x;
    y = 720/y;
    this->plansza_sp.setScale(x,y);

    std::string sciezka = "./obrazki/";
    std::string figura[6] = {
        "krol_",
        "hetman_",
        "wieza_",
        "goniec_",
        "skoczek_",
        "pionek_"
    };
    std::string kolor[2]={
        "bialy",
        "czarny"
    };

    for(int i=0;i<6;i++){
        for(int j=0;j<2;j++){
            if(this->figury_tex[i][j].loadFromFile(sciezka+figura[i]+kolor[j]+".png") == false){
                std::cout << "BLAD podczas otwierania obrazka" <<std::endl;
                return;
            }
            figury_tex[i][j].setSmooth(true);
            this->figury_sp[i][j].setTexture(this->figury_tex[i][j]);
            this->figury_sp[i][j].scale(1.5,1.5);
        }
    }

    this->siatka_x = 89; // ramka zajmuje kilka pikseli dlatego nie 90
    this->siatka_y = 89; // ramka zajmuje kilka pikseli dlatego nie 90
    
}

void GUI::wyswietl(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza){
    this->renderuj(szachownica, okienko, kol_gracza);
    okienko.display();
}

void GUI::renderuj(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza){
    okienko.clear();

    okienko.draw(this->plansza_sp);

    int kol;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(szachownica(i,j) != nullptr){
                if(szachownica(i,j)->ktora_druzyna() == biali){
                    // bedziemy uzywac bialych figur
                    kol = 0;
                } else{ // w przeciwnym razie beda czarne
                    kol = 1;
                }
                // pierwszy wiersz jest na dole nie na gorze
                switch(szachownica(i,j)->zwroc_nazwe()){
                    case 'p':
                        this->figury_sp[5][kol].setPosition(i*this->siatka_x, (7-j)*this->siatka_y);
                        okienko.draw(this->figury_sp[5][kol]);
                     break;
                    case 's':
                        this->figury_sp[4][kol].setPosition(i*this->siatka_x, (7-j)*this->siatka_y);
                        okienko.draw(this->figury_sp[4][kol]);
                     break;
                    case 'g':
                        this->figury_sp[3][kol].setPosition(i*this->siatka_x, (7-j)*this->siatka_y);
                        okienko.draw(this->figury_sp[3][kol]);
                     break;
                    case 'w':
                        this->figury_sp[2][kol].setPosition(i*this->siatka_x, (7-j)*this->siatka_y);
                        okienko.draw(this->figury_sp[2][kol]);
                     break;
                    case 'h':
                        this->figury_sp[1][kol].setPosition(i*this->siatka_x, (7-j)*this->siatka_y);
                        okienko.draw(this->figury_sp[1][kol]);
                     break;
                    case 'k':
                        this->figury_sp[0][kol].setPosition(i*this->siatka_x, (7-j)*this->siatka_y);
                        okienko.draw(this->figury_sp[0][kol]);
                     break;
                    default: break;
                }
            }
        }
    }
}

wspolrzedne GUI::akcja_uzytkownika(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza){
    // petla bedzie dzialac do momentu wykonania jednej z wymienionych akcji
    bool czy_koniec = false;
    wspolrzedne kliknieto(10,10);
    sf::Event wydarzenie;
    while(czy_koniec == false){
        okienko.waitEvent(wydarzenie);
        switch(wydarzenie.type){
            case sf::Event::Closed:
                czy_koniec = true;
             break;
            case sf::Event::MouseButtonPressed:
                if(wydarzenie.mouseButton.button == sf::Mouse::Left){
                    kliknieto.x = wydarzenie.mouseButton.x/this->siatka_x;
                    kliknieto.y = wydarzenie.mouseButton.y/this->siatka_y;
                    // jesli kliknieto poza pola
                    if(kliknieto.x < 0 || kliknieto.x >=8
                     || kliknieto.y < 0 || kliknieto.y >=8){
                        kliknieto = wspolrzedne(10,10);
                    } else{ // jesli pliknieto na plansze, konczymy obieg petli
                        czy_koniec = true;
                        this->renderuj(szachownica, okienko, kol_gracza);
                        // tworzy prostokat o rozmiarach pola
                        sf::RectangleShape prostokat(sf::Vector2f(this->siatka_x,this->siatka_y));
                        // pierwsze pole jest na dole
                        prostokat.setPosition(kliknieto.x*this->siatka_x,kliknieto.y*this->siatka_y+3);
                        // jedynie kontury beda widoczne
                        prostokat.setFillColor(sf::Color::Transparent);
                        prostokat.setOutlineColor(sf::Color::Green);
                        prostokat.setOutlineThickness(5);
                        okienko.draw(prostokat);
                        okienko.display();
                    }
                }
             break;
            default: break;
        }
    }
    // pierwszy wiersza jest na dole
    if(kliknieto != wspolrzedne(10,10)){
        kliknieto.y = 7-kliknieto.y;
    }
    return kliknieto;
}
void GUI::koniec(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza, const kolor &kol_zwyciezcy){
    this->renderuj(szachownica, okienko, kol_gracza);
    
    sf::Text tekst;
    sf::Font czcionka;
    sf::Color kolor_tekstu(0,80,150,255);
    czcionka.loadFromFile("./obrazki/Arialn.ttf");
    tekst.setFont(czcionka);
    if(kol_zwyciezcy == biali){
        tekst.setString("BIALI WYGRALI");
    }
    if(kol_zwyciezcy == czarni){
        tekst.setString("CZARNI WYGRALI");
    }
    if(kol_zwyciezcy == nikt){
        tekst.setString("REMIS");
    }
    tekst.setCharacterSize(90); // wielkosc w pikselach
    tekst.setFillColor(kolor_tekstu);
    tekst.setStyle(sf::Text::Bold);
    float szerokosc = tekst.getGlobalBounds().width;
    float wysokosc = tekst.getGlobalBounds().height;
    // mamy podzial 8x8, wiec srodek bedzie przy 4
    // wskazujemy na lewy gorny rog, wiec musimy odjac polowe szerokosci napisu
    // zeby napis byl ponad srodkiem odejmuejmy cala wysokosc
    tekst.setPosition(this->siatka_x*4-szerokosc/2, this->siatka_y*4-wysokosc);
    okienko.draw(tekst);

    // informacja jak zakonczyc program
    sf::Text jak_zakonczyc;
    jak_zakonczyc.setFont(czcionka);
    jak_zakonczyc.setString("wcisnij spacje zeby zakonczyc");
    jak_zakonczyc.setCharacterSize(30);
    jak_zakonczyc.setFillColor(kolor_tekstu);
    szerokosc = jak_zakonczyc.getGlobalBounds().width;
    wysokosc = jak_zakonczyc.getGlobalBounds().height;
    jak_zakonczyc.setPosition(this->siatka_x*4-szerokosc/2, this->siatka_y*8-wysokosc-30);
    okienko.draw(jak_zakonczyc);

    okienko.display();

    // konczy dzialanie programu jesli uzytkownik wcisnie spacje
    sf::Event wydarzenie;
    while(1){
        while (okienko.waitEvent(wydarzenie)){
            switch(wydarzenie.type){
                case sf::Event::Closed: // jesli okno zostalo zamkniete
                    okienko.close();
                    //konczy dzialanie funkcji
                    return;
                 break;
                case sf::Event::KeyPressed:
                    // wcisnieto spacje
                    if(wydarzenie.key.code == sf::Keyboard::Key::Space){
                        okienko.close();
                        // konczy dzialanie funkcji
                        return;
                    }
                 break;
                default: break;
            }
        }
    }
}

kolor GUI::wybierz_kolor(){

    kolor kol;
    float szerokosc_ok = 500;
    float wysokosc_ok = 300;
    sf::RenderWindow okienko(sf::VideoMode(szerokosc_ok, wysokosc_ok), "menu", sf::Style::Titlebar | sf::Style::Close);
    sf::Texture tlo_tex;
    if(tlo_tex.loadFromFile("./obrazki/tlo.png") == false){
        std::cout << "BLAD podczas otwierania obrazka" <<std::endl;
        return nikt; // blad, nie zaladowano obrazka
    }
    sf::Sprite tlo_sp;
    tlo_sp.setTexture(tlo_tex);
    okienko.draw(tlo_sp);

    sf::Text tekst;
    sf::Font czcionka;
    sf::Color kolor_tekstu(sf::Color::Black);
    czcionka.loadFromFile("./obrazki/Arialn.ttf");
    tekst.setFont(czcionka);
    tekst.setString("Wybierz kolor:");
    tekst.setCharacterSize(50); // wielkosc w pikselach
    tekst.setFillColor(kolor_tekstu);
    tekst.setStyle(sf::Text::Bold);
    float szerokosc = tekst.getGlobalBounds().width;
    float wysokosc = tekst.getGlobalBounds().height;
    tekst.setPosition(szerokosc_ok/2 - szerokosc/2, 10);
    okienko.draw(tekst);

    tekst.setString("graj bialymi - wcisnij enter");
    tekst.setCharacterSize(40); // wielkosc w pikselach
    szerokosc = tekst.getGlobalBounds().width;
    wysokosc = tekst.getGlobalBounds().height;
    tekst.setPosition(szerokosc_ok/2 - szerokosc/2, wysokosc_ok/2 - (wysokosc + 10));
    okienko.draw(tekst);

    tekst.setString("graj czarnymi - wcisnij spacje");
    tekst.setCharacterSize(40); // wielkosc w pikselach
    szerokosc = tekst.getGlobalBounds().width;
    wysokosc = tekst.getGlobalBounds().height;
    tekst.setPosition(szerokosc_ok/2 - szerokosc/2, wysokosc_ok/2 + wysokosc);
    okienko.draw(tekst);
    okienko.display();

    sf::Event wydarzenie;
    while(okienko.isOpen()){
        okienko.waitEvent(wydarzenie);
        switch(wydarzenie.type){
            case sf::Event::Closed:
                kol = nikt;
                okienko.close();
             break;
            case sf::Event::KeyPressed:
                if(wydarzenie.key.code == sf::Keyboard::Key::Enter){
                    kol = biali;
                    okienko.close();
                } else{
                    if(wydarzenie.key.code == sf::Keyboard::Key::Space){
                        kol = czarni;
                        okienko.close();
                    }
                }
             break;
            default: break;
        }
    }
    return kol;
}