#include "BalaMisil.h"

#define B2DMG 250
BalaMisil::BalaMisil(float posX, float posY)
{
    balaSprite.setTexture(mundo::getMundo()->balaTex);
    balaSprite.setTextureRect(IntRect(128,128,128,128));
    balaSprite.scale(0.5,0.5);
    balaSprite.setOrigin(sf::Vector2f(65,36));
    nextPosX = posX;
    nextPosY= posY;
    hitbox.setSize(Vector2f(16,44));
    hitbox.setFillColor(Color(255,0,0,155));
    hitbox.setOrigin(9,0);
    hitbox.setPosition(Vector2f(nextPosX,nextPosY));

    viva=true;
}

void BalaMisil::disparar(float time){

    float speed=50;

    sf::Vector2f newpos((cos(angle))*2, (sin(angle))*2);
    direccion = newpos;

    xlast = x;
    ylast = y;
    //Avanzar a la siguiente posicion
    x=x+direccion.x*speed*time;
    y=y+direccion.y*speed*time;

    hitbox.setPosition(Vector2f(x,y));

   if(x<0 || y < 0 || x>mundo::getMundo()->ventana->getSize().x|| y>mundo::getMundo()->ventana->getSize().y){
        viva = false;
    }

}

float BalaMisil::setPos(sf::Vector2f newPos){
    balaSprite.setPosition(newPos);
    x=newPos.x;
    y=newPos.y;
    xlast=newPos.x;
    ylast=newPos.y;
    //Calcular angulo hacia el que ira la bala
    angle = atan2(nextPosY - y, nextPosX - x);
    balaSprite.setRotation(angle*180/M_PI +90);//Direccion de la bala
    hitbox.setRotation(angle*180/M_PI +90);
    return angle;
}

sf::FloatRect BalaMisil::getGlobal(){
    return balaSprite.getGlobalBounds();
}
void BalaMisil::colision(int j){
    if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->enemigosFuera->at(j).hitbox.getGlobalBounds())){
        viva=false;

       if(mundo::getMundo()->enemigosFuera->at(j).balaHit(B2DMG)){
        mundo::getMundo()->enemigosFuera->erase(mundo::getMundo()->enemigosFuera->begin()+j);
       }

    }
}
void BalaMisil::colision2(int j){
    if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->enemigosFuera2->at(j).hitbox.getGlobalBounds())){
        viva=false;

       if(mundo::getMundo()->enemigosFuera2->at(j).balaHit(B2DMG)){
        mundo::getMundo()->enemigosFuera2->erase(mundo::getMundo()->enemigosFuera2->begin()+j);
       }

    }
}
void BalaMisil::colisionboss1(int j){
    if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->vectorBoss1->at(j).hitbox.getGlobalBounds())){
        viva=false;

       if(mundo::getMundo()->vectorBoss1->at(j).balaHit(B2DMG)){
        mundo::getMundo()->vectorBoss1->erase(mundo::getMundo()->vectorBoss1->begin()+j);
       }

    }
}
void BalaMisil::render(float ticks, sf::RenderWindow &Window){
    balaSprite.setPosition(xlast*(1-ticks) + x*ticks,ylast*(1-ticks)+y*ticks);

        Window.draw(balaSprite);

        if(mundo::getMundo()->getDebug()){
           Window.draw(hitbox);
        }
}

BalaMisil::~BalaMisil()
{
    //dtor
}
