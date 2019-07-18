#include "Castillo.h"

Castillo::Castillo()
{
    castilloSprite.setTexture(mundo::getMundo()->castilloTex);

    castilloSprite.setScale(0.6f,0.7f);
    //castilloSprite.setOrigin(sf::Vector2f(600/2,500/2));
    //castilloSprite.setRotation(90);
    castilloSprite.setPosition(Vector2f(545,250));
    vida=2000;

    hitbox.setSize(Vector2f(castilloSprite.getGlobalBounds().width,castilloSprite.getGlobalBounds().height));
    hitbox.setFillColor(Color(255,0,0,155));
    //hitbox.setOrigin(8,-5);
    hitbox.setPosition(Vector2f(545,250));
}

void Castillo::draw(sf::RenderWindow &Window){
    Window.draw(castilloSprite);
    if(mundo::getMundo()->getDebug()){
        Window.draw(hitbox);
    }
}
bool Castillo::enemigohit(float dano){

    bool muerto=false;


    if(vida-dano<=0) {
       // muere();

       muerto=true;
       vida=vida-dano;

    }
    else{
        vida=vida-dano;
        cout<<"vidaaaa"<<vida<<endl;

        }

    return muerto;
}

Castillo::~Castillo()
{
    //dtor
}
