#include "Moneda.h"
#include <iostream>
using namespace sf;
Moneda::Moneda(float x, float y, int valorPasado)
{

    mSprite.setTexture(mundo::getMundo()->coinTex);


valor=valorPasado;
    //Max 3000coins  min 100
    if(valor<=5){ //Monton pequenio
        mSprite.setTextureRect(sf::IntRect(16*2, 0, 16, 16));
    }
    else if(valor<=10){ //Monton grande
        mSprite.setTextureRect(sf::IntRect(16*3, 0, 16, 16));
    }
    else if(valor<=50){ //Monton enorme
        mSprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
    }
    else{ //Lingotes
        mSprite.setTextureRect(sf::IntRect(16*2, 16, 16, 16));
    }
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
    mSprite.setPosition(x,y);
    mSprite.scale((1.5),(1.5));

    hitbox.setSize(sf::Vector2f(mSprite.getGlobalBounds().width*4, mSprite.getGlobalBounds().height*4));
    hitbox.setOrigin(hitbox.getGlobalBounds().width/2,hitbox.getGlobalBounds().height/2);
    hitbox.setFillColor(sf::Color(255,0,0,155));
    hitbox.setPosition(sf::Vector2f(x,y));




}


bool Moneda::checkMuerte(){


    if(timeMoneda.getElapsedTime().asSeconds()>tiempoParpadeo.asSeconds()){

        if(parpadeo.getElapsedTime().asSeconds()>tiempoentreparpadeo.asSeconds()){

            mSprite.setColor(Color(255,255,255,0));
            parpadeo.restart();

        }else{

            mSprite.setColor(Color(255,255,255,255));
        }

    }
    if(timeMoneda.getElapsedTime().asSeconds() > tiempomuerte.asSeconds()){

        return true;

    }
return false;
}




bool Moneda::movimiento(float xJugador, float yJugador){

    float angle = atan2(yJugador - mSprite.getPosition().y, xJugador - mSprite.getPosition().x);
    sf::Vector2f newpos((cos(angle))*2, (sin(angle))*2);
    mSprite.move(newpos.x*2, newpos.y*2);
    hitbox.move(newpos.x*2, newpos.y*2);

    if(abs(int(xJugador - mSprite.getPosition().x)) <=8 && abs(int(yJugador - mSprite.getPosition().y)) <=8){
        return true;
    }
    else
        return false;


}

void Moneda::render(sf::RenderWindow &Window){
    Window.draw(mSprite);
    if(mundo::getMundo()->getDebug()){
        Window.draw(hitbox);
    }
}

Moneda::~Moneda()
{
    //dtor
}
