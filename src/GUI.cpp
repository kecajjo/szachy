#include "inc/GUI.hh"

// otwiera okno
GUI::GUI() : okno(sf::VideoMode(800, 800), "szachy"){
    this->okno.display();
}

void GUI::wyswietl(const plansza &szachownica){

}

void GUI::sprawdzaj_wydarzenia(){
    while(this->okno.pollEvent(this->wydarzenie)){
        if(this->wydarzenie.type == sf::Event::Closed){
            // zamyka okno
            this->okno.close();
            // zamyka aplikacje
            std::exit(0);
        }
    }
}