#include "Bomba.h"

Bomba::Bomba(float xPos, float yPos)
{
    bomba.setTexture(mundo::getMundo()->bombaTex);
    bomba.setScale(0.15f,0.15f);
    bomba.setOrigin(sf::Vector2f(bomba.getLocalBounds().width/2,bomba.getLocalBounds().height/2));
    bomba.setPosition(xPos,yPos);
    viva=true;
    explotando=false;
}
bool Bomba::explosion(){
    bool hecho=false;
    explotando=true;
    while(!hecho){
    if(timeExplosion.getElapsedTime().asMilliseconds()<100){
            bomba.setTexture(mundo::getMundo()->explosionTex);
            bomba.setScale(3.f,3.f);
            bomba.setTextureRect(IntRect(0, 0, 128, 128));
            cout<<"bum1"<<endl;

     }
      else if(timeExplosion.getElapsedTime().asMilliseconds()<200){
            bomba.setTextureRect(sf::IntRect(128, 0, 128, 128));
            cout<<"bum2"<<endl;
     }
    else if(timeExplosion.getElapsedTime().asMilliseconds()<300){
            bomba.setTextureRect(sf::IntRect(128*2, 0, 128, 128));
            cout<<"bum3"<<endl;
     }
      else{
        hecho=true;
        timeExplosion.restart();
        cout<<"fin bum "<<endl;
     }
    }

     return hecho;

}
bool Bomba::colision(int i){

bool colisiona=false;
    if(bomba.getGlobalBounds().intersects(mundo::getMundo()->enemigosFuera->at(i).hitbox.getGlobalBounds())){
        viva=false;
        colisiona=true;
        mundo::getMundo()->enemigosFuera->at(i).playerHit(1000);
        mundo::getMundo()->enemigosFuera->erase(mundo::getMundo()->enemigosFuera->begin()+i);
    }

return colisiona;
}
int Bomba::getX(){
return bomba.getPosition().x;
}
int Bomba::getY(){
return bomba.getPosition().y;
}
void Bomba::render(sf::RenderWindow &Window){
    if(viva)
        Window.draw(bomba);
}
Bomba::~Bomba()
{
    //dtor
}
