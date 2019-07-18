#include "boss1.h"


using namespace sf;
using namespace std;


#define DMG 100


boss1::boss1() {
    x=0;
    y=0;
    xlast=0;
    ylast=0;



}

boss1::boss1(const boss1& E) {


    eSprite=E.eSprite;
    hitbox=E.hitbox;
    colision=E.colision;
    x=E.x;
    y=E.y;
    xlast=E.xlast;
    ylast=E.ylast;
    vel=E.vel;
    objetivo=E.objetivo;

    estado=1;

    money=rand()%60;

}

boss1::boss1(float x2, float y2) {


    x=x2;
    y=y2;
    xlast=x2;
    ylast=y2;



    eSprite.setTexture(mundo::getMundo()->enemigobase);
    eSprite.setTextureRect(IntRect(1,395,120,184));
    eSprite.setOrigin(eSprite.getGlobalBounds().width/2,eSprite.getGlobalBounds().height/2);   // ahora es fija pero debera ser la que mande el spawn



    eSprite.scale(-0.5,0.5);
    eSprite.setPosition(x,y);


    hitbox.setSize(Vector2f(eSprite.getGlobalBounds().width,eSprite.getGlobalBounds().height));
    hitbox.setFillColor(Color(255,0,0,155));

    hitbox.setOrigin(hitbox.getGlobalBounds().width/2,hitbox.getGlobalBounds().height/2);
    hitbox.setPosition(Vector2f(xlast,ylast));


    int num = rand()%(int)mundo::getMundo()->castillo->hitbox.getGlobalBounds().height+(int)mundo::getMundo()->castillo->hitbox.getPosition().y;
    objetivo.y = num;
    objetivo.x=mundo::getMundo()->castillo->hitbox.getPosition().x;

}

boss1::~boss1() {

}


void boss1::moveEnemy(float time) {

    xlast=x;
    ylast=y;
    bool choca=false;
    Vector2f pos;

    if(atacaTorre==false) {
        /*for(int i=0; i<ene.size()&&choca==false; i++){
            //for(int j=0; i<torres.size()&&colision==false; i++){
                if(i!=a){
waif(colision.getGlobalBounds().intersects(ene.at(i).colision.getGlobalBounds())){
                        choca=true;
                    }
                    if(ene.at(i).atacaTorre==true) {
                        choca=true;
                    }
                }
            //}
        }*/
        if(choca==false && atacaTorre==false){
            if(x < objetivo.x && y < objetivo.y) {
            x=x+velocidad*time;
            y=y+velocidad*time;

            }
            if(x > objetivo.x && y < objetivo.y) {
                x=x-velocidad*time;
                y=y+velocidad*time;

            }
            if(x < objetivo.x && y > objetivo.y) {
                x=x+velocidad*time;
                y=y-velocidad*time;

            }
            if(x > objetivo.x && y > objetivo.y) {
                x=x-velocidad*time;
                y=y-velocidad*time;

            }
        }else{
            if (atacaTorre==false) {
                if(x < objetivo.x && y < objetivo.y) {
                    x=x-2*time;
                    y=y-3*time;

                }
                if(x > objetivo.x && y < objetivo.y) {
                    x=x+2*time;
                    y=y-3*time;

                }
                if(x < objetivo.x && y > objetivo.y) {
                    x=x-2*time;
                    y=y+3*time;


                }
                if(x > objetivo.x && y > objetivo.y) {
                    x=x+2*time;
                    y=y+3*time;

                }
            }
        }
        //eSprite.getGlobalBounds().top;

        /*Vector2f pos;
        pos.x=x;
        pos.y=y;*/
    }
        eSprite.setPosition(xlast,ylast);
        hitbox.setPosition(eSprite.getPosition());


        movsprites();
}

bool boss1::ataque(){

    if(ataca==false){
        if(hitbox.getGlobalBounds().intersects(mundo::getMundo()->castillo->hitbox.getGlobalBounds())){
            ataca=true;
            estado=2;
        }
    }
    else{
        if(!hitbox.getGlobalBounds().intersects(mundo::getMundo()->castillo->hitbox.getGlobalBounds())){
            ataca=false;
            estado=1;
        }
    }
    return ataca;
}

void boss1::setObjetivo(Vector2f obj) {
    objetivo = mundo::getMundo()->castillo->castilloSprite.getPosition();
}
sf::FloatRect boss1::getGlobal(){
    return eSprite.getGlobalBounds();
}
void boss1::render(float ticks, RenderWindow &ventana) {

eSprite.setPosition(xlast*(1-ticks) + x*ticks,ylast*(1-ticks)+y*ticks);
ventana.draw(eSprite);
//ventana.draw(colision);
if(mundo::getMundo()->getDebug()){
   ventana.draw(hitbox);

}
//ventana.draw(hitbox);
//ventana.draw(colision);



}

//Hitplayer es cuando el jugador le ataca, devuelve true si muere
bool boss1::playerHit(float dano){

    bool muerto=false;


if(invulnerable==false){
    if(vida-dano<=0) {
       // muere();
        mundo::getMundo()->vectorMonedas->push_back(Moneda(x,y,money));
       muerto=true;
        vida=vida-dano;

    }
    else{
        vida=vida-dano;

        timeInvul.restart();
        invulnerabilidad();
        invulnerable = true;
        }
    }
    return muerto;
}

void boss1::invulnerabilidad(){


     if (invulnerable){
     eSprite.setColor(Color(255,0,0,155));

         if(timeInvul.getElapsedTime().asMilliseconds()>=200){

             eSprite.setColor(Color(255,255,255,255));
             invulnerable=false;
        }

    }

}

bool boss1::balaHit(float dano){

    bool muerto=false;


    if(vida-dano<=0) {
       mundo::getMundo()->vectorMonedas->push_back(Moneda(x,y,money));
       muerto=true;

    }
    else{
        vida=vida-dano;

        timedanobala.restart();
        eSprite.setColor(Color(255,0,0,155));
        }

    return muerto;
}

void boss1::danobala(){




         if(timedanobala.getElapsedTime().asMilliseconds()>=200 && invulnerable==false){

             eSprite.setColor(Color(255,255,255,255));

        }



}

void boss1:: movsprites(){

    if (atacaTorre==true) {
        estado=2;

    }






    switch (estado){





        case 1:

            if(timeenemigo.getElapsedTime().asMilliseconds()<100){
                    eSprite.setTextureRect(IntRect(1,395,120,184));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<200){
                    eSprite.setTextureRect(sf::IntRect(122,395,96,184));

             } else if(timeenemigo.getElapsedTime().asMilliseconds()<300){
                    eSprite.setTextureRect(sf::IntRect(219,395,96,184));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<400){
                    eSprite.setTextureRect(sf::IntRect(316,395,96,184));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<500){
                    eSprite.setTextureRect(sf::IntRect(413,395,80,184));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<600){
                    eSprite.setTextureRect(sf::IntRect(494,395,112,184));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<700){
                    eSprite.setTextureRect(sf::IntRect(219,395,96,184));
             }


              else{
             timeenemigo.restart();
             }
             break;

        case 2:

             if(timeenemigo.getElapsedTime().asMilliseconds()<200){
                    eSprite.setTextureRect(IntRect(1,1127,88,184));

             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<400){
                    eSprite.setTextureRect(sf::IntRect(90,1127,120,184));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<600){
                  //   eSprite.setOrigin(60,eSprite.getOrigin().y);
                     //hitbox.setOrigin(eSprite.getOrigin());


                    eSprite.setTextureRect(sf::IntRect(211,1127,136,184));

             }

             else if(timeenemigo.getElapsedTime().asMilliseconds()<800){

                    eSprite.setTextureRect(sf::IntRect(350,1127,216,160));


             }


             else if(timeenemigo.getElapsedTime().asMilliseconds()<1000){

                    eSprite.setTextureRect(sf::IntRect(565,1127,200,160));
                    if(ataquerealizado==false){

                        mundo::getMundo()->castillo->enemigohit(200);
                         ataquerealizado=true;
                    }



             }


             else if(timeenemigo.getElapsedTime().asMilliseconds()<1200){
                    eSprite.setTextureRect(sf::IntRect(766,1127,136,184));

             }

             else{
                      ataquerealizado=false;
                hitbox.setOrigin(eSprite.getGlobalBounds().width/2,eSprite.getGlobalBounds().height/2);


                  eSprite.setTextureRect(IntRect(3, 290, 59, 98));
                    eSprite.setOrigin(hitbox.getOrigin());
             timeenemigo.restart();

             }

           break;


    }

}
