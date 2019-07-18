#include "Hud.h"

Hud::Hud()
{
   // nvida = mundo::getMundo()->jugador->salud;
    corazon.setTexture(mundo::getMundo()->corazontext);
    corazon.setPosition(55,76);
    corazon.setScale(0.1f,0.1f);

    if(!font.loadFromFile("resources/fonti"))
        cout<<"err"<<endl;

    vidap.setFont(font);
    vidap.setString("Avast Call");
    vidap.setColor(sf::Color::White);
    vidap.setPosition(Vector2f(100,81));
    vidap.setCharacterSize(20);
    vidap.setStyle(sf::Text::Bold);

    vidac.setFont(font);
    vidac.setString("Castillo");
    vidac.setColor(sf::Color::White);
    vidac.setPosition(Vector2f(570,280.5f));
    vidac.setCharacterSize(20);
    vidac.setStyle(sf::Text::Bold);

    corazonc.setTexture(mundo::getMundo()->corazontext);
    corazonc.setPosition(521,276);
    corazonc.setScale(0.1f,0.1f);

    monedilla.setTexture(mundo::getMundo()->monedatext);
    monedilla.setPosition(645,35.0f);
    monedilla.setScale(0.41f,0.4f);

    cajavida.setSize(Vector2f(240,20));
    cajavida.setFillColor(Color(255,0,0,255));
    cajavida.setPosition(Vector2f(74,82.5f));

    cajavidabackground.setSize(Vector2f(245,30));
    cajavidabackground.setFillColor(Color(0,0,0,255));
    cajavidabackground.setPosition(Vector2f(74,77.5f));

    cajavidac.setSize(Vector2f(240,20));
    cajavidac.setFillColor(Color(255,0,0,255));
    cajavidac.setPosition(Vector2f(540,282.5f));

    cajavidabackgroundc.setSize(Vector2f(245,30));
    cajavidabackgroundc.setFillColor(Color(0,0,0,255));
    cajavidabackgroundc.setPosition(Vector2f(540,277.5f));

}

void Hud::draw(sf::RenderWindow &Window){

    Window.draw(cajavidabackground);
    Window.draw(cajavida);
    Window.draw(corazon);
    Window.draw(cajavidabackgroundc);
    Window.draw(cajavidac);
    Window.draw(corazonc);
    Window.draw(monedilla);
    Window.draw(vidap);
    Window.draw(vidac);
}
void Hud::updateHud(){
    int health = mundo::getMundo()->jugador->salud;
    int healthc = mundo::getMundo()->castillo->vida;
    cajavida.setSize(Vector2f((health*240)/500,20));
    cajavidac.setSize(Vector2f((healthc*240)/2000,20));
}
Hud::~Hud()
{
    //dtor
}

