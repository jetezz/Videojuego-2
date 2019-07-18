#include "../include/Torreta.h"

Torreta::Torreta()
{

    torretaSprite.setTexture(mundo::getMundo()->torretaTex);
    if(mundo::getMundo()->tipoTorreta==1){
        torretaSprite.setTextureRect(IntRect(0,0,128,128));
    }
    else if(mundo::getMundo()->tipoTorreta==2){
        torretaSprite.setTextureRect(IntRect(128*3,0,128,128));
    }
    torretaSprite.setScale(0.4f,0.4f);
    torretaSprite.setOrigin(sf::Vector2f(128/2,128/2));
    tipo=mundo::getMundo()->tipoTorreta;
}
int Torreta::getX(){
    return torretaSprite.getPosition().x;
}
int Torreta::getY(){
    return torretaSprite.getPosition().y;
}
void Torreta::draw(sf::RenderWindow &Window){
    Window.draw(torretaSprite);
}

void Torreta::dibujarSprite(){
    if(timeTorreta.getElapsedTime().asMilliseconds() < 200){
        if(tipo==1){
            torretaSprite.setTextureRect(IntRect(128,0,128,128));
        }
        else if(tipo==2){
            torretaSprite.setTextureRect(IntRect(0,128,128,128));
        }

    }
    else if(timeTorreta.getElapsedTime().asMilliseconds() < 400){
        if(tipo==1){
            torretaSprite.setTextureRect(IntRect(0,0,128,128));
        }
        else if(tipo==2){
            torretaSprite.setTextureRect(IntRect(128*3,0,128,128));
        }
    }
}

void Torreta::setPos(sf::Vector2f newPos){
    torretaSprite.setPosition(newPos.x,newPos.y);
}
void Torreta::rotarTorreta(float angle){
    torretaSprite.setRotation(angle*180/M_PI +90);

}
Torreta::~Torreta()
{
/*
Revisar Delete

*/


}
sf::Sprite Torreta::getSprite() {
    return torretaSprite;
}

bool Torreta:: enemigohit(float dano){

bool muerto=false;

    if(vida-dano<=0) {

       // muere();


       muerto=true;
    }
    else{
        vida=vida-dano;


    timedanoTorreta.restart();
        }
       torretaSprite.setColor(Color(255,0,0,155));
    return muerto;


}

void Torreta:: danoenemigo(){

     if(timedanoTorreta.getElapsedTime().asMilliseconds()>=200){
             torretaSprite.setColor(Color(255,255,255,255));


        }


}