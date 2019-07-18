#include "../include/enemigos2.h"

using namespace sf;
using namespace std;


#define DMG 25
enemigos2::enemigos2() {
    x=0;
    y=0;
    xlast=0;
    ylast=0;
    saludEnemigo=0;
    danioEnemigo=0;




}

enemigos2::enemigos2(const enemigos2& E) {


    eSprite=E.eSprite;
    hitbox=E.hitbox;
    colision=E.colision;
    x=E.x;
    y=E.y;
    xlast=E.xlast;
    ylast=E.ylast;
    vel=E.vel;
    saludEnemigo=E.saludEnemigo;
    danioEnemigo=E.danioEnemigo;
    estado=1;

    money=rand()%60;

}

enemigos2::enemigos2(float x2, float y2) {



    eSprite.setTexture(mundo::getMundo()->eTexture2);

    eSprite.setOrigin(17,48/2);   // ahora es fija pero debera ser la que mande el spawn
    eSprite.setTextureRect(IntRect(335, 7, 35, 55));



    x=x2;
    y=y2;
    xlast=x2;
    ylast=y2;


    hitbox.setSize(Vector2f(59,88));
    hitbox.setFillColor(Color(255,0,0,155));
    hitbox.setOrigin(eSprite.getGlobalBounds().width/2-17,eSprite.getGlobalBounds().height/2-24);
    hitbox.setPosition(Vector2f(x,y));

    colision.setSize(Vector2f(15,10));
    colision.setFillColor(Color(255,255,0,155));
    colision.setOrigin(eSprite.getGlobalBounds().width/2,eSprite.getGlobalBounds().height/2-50);
    colision.setPosition(Vector2f(x,y));


    eSprite.setPosition(x,y);

}

enemigos2::~enemigos2() {

}


void enemigos2::moveEnemy(float time, vector<enemigos2> ene, int a) {

    xlast=x;
    ylast=y;
    bool choca=false;
    Vector2f pos;
    //if(ataca==false) {
        for(int i=0; i<ene.size()&&choca==false; i++){
            //for(int j=0; i<torres.size()&&colision==false; i++){
                if(i!=a){
                    if(colision.getGlobalBounds().intersects(ene.at(i).colision.getGlobalBounds())){
                        choca=true;
                    }
                    if(ene.at(i).ataca==true) {
                        choca=true;
                    }
                }
            //}
        }
        //if(choca==false && ataca==false){
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
        /*}else{
            if ((ataca==false && choca==true) || (ataca==true && choca==true)) {
                    cout<< "caca" <<endl;
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
        }*/
        //eSprite.getGlobalBounds().top;

        /*Vector2f pos;
        pos.x=x;
        pos.y=y;*/
    //}
        eSprite.setPosition(x,y);
        hitbox.setScale(eSprite.getScale());
        hitbox.setPosition(x,y);
        colision.setPosition(x,y);

        movsprites();
}

void enemigos2::colisionEnemigos(Vector2f ene){

}

bool enemigos2::ataque(player * p, vector<Torreta> torres){
    if(ataca==false){
        if(hitbox.getGlobalBounds().intersects(p->hitbox.getGlobalBounds())){
            ataca=true;
        }
        if (ataca==false) {
            if (torres.empty()==false) {
                for(int i=0;i<torres.size();i++) {
                    if (hitbox.getGlobalBounds().intersects(torres.at(i).getSprite().getGlobalBounds())) {
                        ataca=true;
                    }

                }
            }
        }
    }
    else{
        if(!hitbox.getGlobalBounds().intersects(p->hitbox.getGlobalBounds())){
            ataca=false;
        }
    }
    return ataca;
}

void enemigos2::setObjetivo(Vector2f obj) {
    objetivo = obj;
}
sf::FloatRect enemigos2::getGlobal(){
    return eSprite.getGlobalBounds();
}
void enemigos2::render(float ticks, RenderWindow &ventana) {

eSprite.setPosition(xlast*(1-ticks) + x*ticks,ylast*(1-ticks)+y*ticks);
ventana.draw(eSprite);
//ventana.draw(colision);
if(mundo::getMundo()->getDebug()){
   ventana.draw(hitbox);

}
//ventana.draw(hitbox);
//ventana.draw(colision);



}

void enemigos2::atacaJugador(player *jugador) {
    objetivo=jugador->pSprite.getPosition();
    if (hitbox.getGlobalBounds().intersects(jugador->pSprite.getGlobalBounds())) {

     mundo::getMundo()->jugador->enemigohit(DMG) && timeenemigo.getElapsedTime().asMilliseconds()>600;

        estado=2;
    }
    else {
        estado=1;
    }
}
//Hitplayer es cuando el jugador le ataca, devuelve true si muere
bool enemigos2::playerHit(float dano){

    bool muerto=false;

if(invulnerable==false){
    if(vida-dano<=0) {
       // muere();
        mundo::getMundo()->vectorMonedas->push_back(Moneda(x,y,money));
       muerto=true;

    }
    else{
        vida=vida-dano;
        cout<<"vidaaaa"<<vida<<endl;
        timeInvul.restart();
        invulnerabilidad();
        invulnerable = true;
        }
    }
    return muerto;
}

void enemigos2::invulnerabilidad(){


     if (invulnerable){
     eSprite.setColor(Color(255,0,0,155));

         if(timeInvul.getElapsedTime().asMilliseconds()>=200){

             eSprite.setColor(Color(255,255,255,255));
             invulnerable=false;
        }

    }

}

bool enemigos2::balaHit(float dano){

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

void enemigos2::danobala(){




         if(timedanobala.getElapsedTime().asMilliseconds()>=200 && invulnerable==false){

             eSprite.setColor(Color(255,255,255,255));

        }



}

void enemigos2:: movsprites(){

    if (ataca==true) {
        estado=2;
    }






    switch (estado){

    case 0:

        break;

        case 1:

            if(timeenemigo.getElapsedTime().asMilliseconds()<200){
                    eSprite.setTextureRect(IntRect(335, 7, 35, 55));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<400){
                    eSprite.setTextureRect(sf::IntRect(230, 14, 35, 40));
             }


              else{
             timeenemigo.restart();
             }
             break;

        case 2:

            if(timeenemigo.getElapsedTime().asMilliseconds()<200){
                    eSprite.setTextureRect(IntRect(335, 7, 35, 55));
             }
              else if(timeenemigo.getElapsedTime().asMilliseconds()<400){
                    eSprite.setTextureRect(sf::IntRect(230, 14, 35, 40));
             }


              else{
             timeenemigo.restart();
             }

           break;


    }

}
