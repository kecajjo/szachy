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

void GUI::rysuj(const plansza &szachownica, sf::RenderWindow &okienko, const kolor &kol_gracza){
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
                switch(szachownica(i,j)->zwroc_nazwe()){
                    case 'p':
                        this->figury_sp[5][kol].setPosition(i*this->siatka_x, j*this->siatka_y);
                        okienko.draw(this->figury_sp[5][kol]);
                     break;
                    case 's':
                        this->figury_sp[4][kol].setPosition(i*this->siatka_x, j*this->siatka_y);
                        okienko.draw(this->figury_sp[4][kol]);
                     break;
                    case 'g':
                        this->figury_sp[3][kol].setPosition(i*this->siatka_x, j*this->siatka_y);
                        okienko.draw(this->figury_sp[3][kol]);
                     break;
                    case 'w':
                        this->figury_sp[2][kol].setPosition(i*this->siatka_x, j*this->siatka_y);
                        okienko.draw(this->figury_sp[2][kol]);
                     break;
                    case 'h':
                        this->figury_sp[1][kol].setPosition(i*this->siatka_x, j*this->siatka_y);
                        okienko.draw(this->figury_sp[1][kol]);
                     break;
                    case 'k':
                        this->figury_sp[0][kol].setPosition(i*this->siatka_x, j*this->siatka_y);
                        okienko.draw(this->figury_sp[0][kol]);
                     break;
                    default: break;
                }
            }
        }
    }
    okienko.display();
}

wspolrzedne GUI::akcja_uzytkownika(sf::RenderWindow &okienko, const kolor &kol_gracza){
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
            std::cout << "kliknieto myszka " << std::endl;
                if(wydarzenie.mouseButton.button == sf::Mouse::Left){
                    std::cout << "kliknieto lewy przycisk " << std::endl;
                    kliknieto.x = wydarzenie.mouseButton.x/this->siatka_x;
                    kliknieto.y = wydarzenie.mouseButton.y/this->siatka_y;
                    // jesli kliknieto poza pola
                    if(kliknieto.x < 0 || kliknieto.x >=8
                     || kliknieto.y < 0 || kliknieto.y >=8){
                         kliknieto = wspolrzedne(10,10);
                    } else{ // jesli pliknieto na plansze, konczymy obieg petli
                        czy_koniec = true;
                        // tworzy prostokat o rozmiarach pola
                        sf::RectangleShape prostokat(sf::Vector2f(this->siatka_x,this->siatka_y));
                        prostokat.setPosition(kliknieto.x*this->siatka_x+4,kliknieto.y*this->siatka_y);
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
    return kliknieto;
}