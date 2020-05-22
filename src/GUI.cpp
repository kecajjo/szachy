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

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            // 7-j, zeby wyswietlalo od dolu
            this->pola[i][j] = sf::Vector2f(i*89,(7-j)*89);
        }
    }
    std::cout << "rozmiar planszy " << x*this->plansza_tex.getSize().x << " " << y*this->plansza_tex.getSize().y << std::endl;
    std::cout << "rozmiar figury: " << this->figury_tex[0][0].getSize().x << " " << this->figury_tex[0][0].getSize().y<< std::endl;
    
}

void GUI::rysuj(const plansza &szachownica, sf::RenderWindow &okienko){
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
                        this->figury_sp[5][kol].setPosition(this->pola[i][j]);
                        okienko.draw(this->figury_sp[5][kol]);
                     break;
                    case 's':
                        this->figury_sp[4][kol].setPosition(this->pola[i][j]);
                        okienko.draw(this->figury_sp[4][kol]);
                     break;
                    case 'g':
                        this->figury_sp[3][kol].setPosition(this->pola[i][j]);
                        okienko.draw(this->figury_sp[3][kol]);
                     break;
                    case 'w':
                        this->figury_sp[2][kol].setPosition(this->pola[i][j]);
                        okienko.draw(this->figury_sp[2][kol]);
                     break;
                    case 'h':
                        this->figury_sp[1][kol].setPosition(this->pola[i][j]);
                        okienko.draw(this->figury_sp[1][kol]);
                     break;
                    case 'k':
                        this->figury_sp[0][kol].setPosition(this->pola[i][j]);
                        okienko.draw(this->figury_sp[0][kol]);
                     break;
                    default: break;
                }
            }
        }
    }
    okienko.display();
}