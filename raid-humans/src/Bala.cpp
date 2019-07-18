#include "../include/Bala.h"
#include <iostream>
#include <math.h>

#define BDMG 100
Bala::Bala(float posX, float posY)
{

    balaSprite.setTexture(mundo::getMundo()->balaTex);
    balaSprite.setTextureRect(IntRect(276,5,96,118));
    balaSprite.scale(0.5,0.5);
    balaSprite.setOrigin(sf::Vector2f(36,36));
    nextPosX = posX;
    nextPosY= posY;
    hitbox.setSize(Vector2f(15,40));
    hitbox.setFillColor(Color(255,0,0,155));
    hitbox.setOrigin(8,-5);
    hitbox.setPosition(Vector2f(nextPosX,nextPosY));
//cout<<"Creo una bala. " <<endl;
    viva=true;
}

void Bala::disparar(float time){

    float speed=100;

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

float Bala::setPos(sf::Vector2f newPos){
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
int Bala::getX(){
    return balaSprite.getPosition().x;
}
int Bala::getY(){
    return balaSprite.getPosition().y;
}
sf::FloatRect Bala::getGlobal(){
    return balaSprite.getGlobalBounds();
}
void Bala::colision(int j){
    if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->enemigosFuera->at(j).hitbox.getGlobalBounds())){
        viva=false;

       if(mundo::getMundo()->enemigosFuera->at(j).balaHit(BDMG)){
        mundo::getMundo()->enemigosFuera->erase(mundo::getMundo()->enemigosFuera->begin()+j);
       }

    }

}
void Bala::colision2(int j){
    if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->enemigosFuera2->at(j).hitbox.getGlobalBounds())){
        viva=false;

       if(mundo::getMundo()->enemigosFuera2->at(j).balaHit(BDMG)){
        mundo::getMundo()->enemigosFuera2->erase(mundo::getMundo()->enemigosFuera2->begin()+j);
       }

    }

}
void Bala::colisionboss(int j){

    if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->vectorBoss1->at(j).hitbox.getGlobalBounds())){
        viva=false;

       if(mundo::getMundo()->vectorBoss1->at(j).balaHit(BDMG)){
        mundo::getMundo()->vectorBoss1->erase(mundo::getMundo()->vectorBoss1->begin()+j);
       }

    }
}
void Bala::render(float ticks, sf::RenderWindow &Window){
    balaSprite.setPosition(xlast*(1-ticks) + x*ticks,ylast*(1-ticks)+y*ticks);

        Window.draw(balaSprite);

        if(mundo::getMundo()->getDebug()){
   Window.draw(hitbox);
}


}

Bala::~Bala()
{
    //delete balaSprite;
}
