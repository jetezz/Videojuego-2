#include "player.h"

using namespace sf;
using namespace std;

#define TIEMPOINVULNERABLE 1000 //ms de tiempo invulnerable
#define BASEDMG 100
#define kVmax 300
player::player(string imgDirectory,float x2, float y2)
{


    if (!pTexture.loadFromFile(imgDirectory))
    {
        cerr << "Error cargando la imagen " << imgDirectory << endl;
        exit(0);

    }


    pSprite.setTexture(pTexture);
    pSprite.setTextureRect(sf::IntRect(4, 8, 40, 65));

    pSprite.setOrigin(pSprite.getGlobalBounds().width/2,pSprite.getGlobalBounds().height/2);

    x=x2;
    y=y2;
    xlast=x2;
    ylast=y2;

    hitbox.setSize(Vector2f(pSprite.getGlobalBounds().width,pSprite.getGlobalBounds().height));
    hitbox.setFillColor(Color(255,0,0,155));
    hitbox.setOrigin(pSprite.getOrigin());
    hitbox.setPosition(Vector2f(x,y));

    hitboxArma.setSize(Vector2f(pSprite.getGlobalBounds().width,pSprite.getGlobalBounds().height));
    hitboxArma.setFillColor(Color(255,255,0,155));
    hitboxArma.setOrigin(hitbox.getOrigin().x-hitbox.getGlobalBounds().width,hitbox.getOrigin().y);


    estado=0;



    pSprite.setPosition(x,y);
}

player::~player()
{
    //dtor
}


Vector2f player::movePlayer(Vector2f v , float time){
 //std::cout << "p--> x:"<< pos.x <<" y:"<< pos.y <<std::endl;
 // std::cout << "v--> x:"<< vel.x <<" y:"<< vel.y <<std::endl;
   // std::cout << "T--> "<< time <<" seg" <<std::endl;

xlast=x;
ylast=y;





    vel.x=v.x;
    vel.y=v.y;

    for(int i=0;i<mundo::getMundo()->enemigosFuera->size();i++){

    if(mundo::getMundo()->enemigosFuera->at(i).hitbox.getGlobalBounds().intersects(hitbox.getGlobalBounds())){

        if(vel.x!=0){
            vel.x=vel.x*0.7;
        }
         if(vel.y!=0){
            vel.y=vel.y*0.7;
        }
    }
}




    x=x+vel.x*time ;
    y=y +vel.y*time ;

if(x>mundo::getMundo()->ventana->getSize().x - mundo::getMundo()->jugador->hitbox.getGlobalBounds().width/2 || x<mundo::getMundo()->jugador->hitbox.getGlobalBounds().width/2){
    x=xlast;
}
if(y>mundo::getMundo()->ventana->getSize().y - mundo::getMundo()->jugador->hitbox.getGlobalBounds().height/2 || y<mundo::getMundo()->jugador->hitbox.getGlobalBounds().height/2){
    y=ylast;
}

if(x>mundo::getMundo()->castillo->hitbox.getPosition().x){
    if(ylast>mundo::getMundo()->castillo->hitbox.getPosition().y + 30 && ylast < mundo::getMundo()->castillo->hitbox.getPosition().y + mundo::getMundo()->castillo->hitbox.getGlobalBounds().height){
        x=xlast;
    }
}
if(y>mundo::getMundo()->castillo->hitbox.getPosition().y + 30 && y < mundo::getMundo()->castillo->hitbox.getPosition().y + mundo::getMundo()->castillo->hitbox.getGlobalBounds().height){
    if(x>mundo::getMundo()->castillo->hitbox.getPosition().x){
            y=ylast;
    }
}




Vector2f pos;
pos.x=xlast;
pos.y=ylast;


hitbox.setPosition(x,y);
hitboxArma.setPosition(x,y);
 pSprite.setPosition(pos);


    return pos;




     }

bool player::enemigohit(float dano){
cout << salud << endl;
bool muerto=false;

    if(!invulnerable){
         if(salud-dano<=0) {

           // muere();

           salud=salud-dano;
           muerto=true;
        }
        else{
            salud=salud-dano;
            invulnerable=true;
            timeinvul.restart();

        }
    }


    return muerto;


}


void player::invulnerabilidad(){


     if (invulnerable && !mundo::getMundo()->getDebug()){
     pSprite.setColor(Color(255,255,255,155));

         if(timeinvul.getElapsedTime().asMilliseconds()>=TIEMPOINVULNERABLE){

             pSprite.setColor(Color(255,255,255,255));
             invulnerable=false;
        }

    }

}


void player::toggleDebug(){

    if(debug){
        debug = false;
    }else{
    debug=true;
    }

}

void player::calcularVelocidadPlayer(vector<int> inputs,float time){

  sf::Vector2f v;
v.x=0;
v.y=0;



    for (int i=0; i< inputs.size();i++){

        switch (inputs[i]){



        case 8:


            v.y-=kVel;
             if(estado!=2)
            estado=1;

        break;
        case 4:

         pSprite.setScale(1,1);
            v.x-=kVel;
             if(estado!=2)
            estado=1;

        break;
        case 6 :

            pSprite.setScale(-1,1);                          //Escala por defecto
            v.x+=kVel;
             if(estado!=2)
            estado=1;
        break;
        case 2 :


            v.y+=kVel;
            if(estado!=2)
            estado=1;
        break;
        case 7 :
            hitboxArma.setScale(1,1);

            if(estado==2 || estado == 0){
            pSprite.setScale(-1,1);
            }
        break;
        case 9 :

            hitboxArma.setScale(-1,1);

            if(estado==2 || estado == 0){
           pSprite.setScale(1,1);
            }
        break;
        case 5 :
            if(estado!=2)
            timejugador.restart();
          estado=2;
          ataquePlayer();

        break;





        }




    }
     if(nivel==1){


        switch (estado){

        case 0:
            if(timejugador.getElapsedTime().asMilliseconds()<200){
                    pSprite.setTextureRect(sf::IntRect(4, 8, 41, 65));


            }else if(timejugador.getElapsedTime().asMilliseconds()<400){
                pSprite.setTextureRect(sf::IntRect(4+41, 8, 41, 65));
            }
            else if(timejugador.getElapsedTime().asMilliseconds()<600){
                    pSprite.setTextureRect(sf::IntRect(4+41*2, 8, 41, 65));

            }
            else if(timejugador.getElapsedTime().asMilliseconds()<800){
                    pSprite.setTextureRect(sf::IntRect(4+41*3, 8, 41, 65));
            }
            else if(timejugador.getElapsedTime().asMilliseconds()<1000){
                    pSprite.setTextureRect(sf::IntRect(4+41*2, 8, 41, 65));

            }

            else if(timejugador.getElapsedTime().asMilliseconds()<1200){
                pSprite.setTextureRect(sf::IntRect(4+41, 8, 41, 65));
            }else{
            timejugador.restart();
            }
            break;

            case 1:

                if(timejugador.getElapsedTime().asMilliseconds()<200){
                        pSprite.setTextureRect(sf::IntRect(276, 178, 41, 65));
                 }
                  else if(timejugador.getElapsedTime().asMilliseconds()<400){
                        pSprite.setTextureRect(sf::IntRect(276+47, 178, 41, 65));
                 }
                 else if(timejugador.getElapsedTime().asMilliseconds()<600){
                        pSprite.setTextureRect(sf::IntRect(276+47*2, 178, 41, 65));
                 }
                  else if(timejugador.getElapsedTime().asMilliseconds()<800){
                        pSprite.setTextureRect(sf::IntRect(276+47, 178, 41, 65));
                 }

                  else{
                 timejugador.restart();
                 }
                 break;

            case 2:

                if(timejugador.getElapsedTime().asMilliseconds()<100){
                        pSprite.setTextureRect(sf::IntRect(10, 98, 50, 65));

                 }
                 else if(timejugador.getElapsedTime().asMilliseconds()<200){
                        pSprite.setTextureRect(sf::IntRect(62, 98, 50, 65));
                 }

                 else if(timejugador.getElapsedTime().asMilliseconds()<300){
                        pSprite.setOrigin(60,pSprite.getOrigin().y);
                        pSprite.setTextureRect(sf::IntRect(226, 99, 60, 70));


                 }

                  else if(timejugador.getElapsedTime().asMilliseconds()<400){
                        pSprite.setTextureRect(sf::IntRect(294, 98, 50, 80));
                 }
                  else if(timejugador.getElapsedTime().asMilliseconds()<500){

                        pSprite.setTextureRect(sf::IntRect(353, 98, 50, 80));


                 }


                else{
                 pSprite.setTextureRect(sf::IntRect(4, 8, 41, 65));
                 pSprite.setOrigin(hitbox.getOrigin());
                 timejugador.restart();
                 estado=4;

                 }


        }
    }

    if(nivel==2){
         switch (estado){

        case 0:
            if(timejugador.getElapsedTime().asMilliseconds()<200){
                    pSprite.setTextureRect(sf::IntRect(10, 258, 41, 77));


            }else if(timejugador.getElapsedTime().asMilliseconds()<400){
                pSprite.setTextureRect(sf::IntRect(50, 258, 41, 77));
            }
            else if(timejugador.getElapsedTime().asMilliseconds()<600){
                    pSprite.setTextureRect(sf::IntRect(92, 258, 41, 77));

            }
            else if(timejugador.getElapsedTime().asMilliseconds()<800){
                    pSprite.setTextureRect(sf::IntRect(133, 258, 41, 77));
            }


            else if(timejugador.getElapsedTime().asMilliseconds()<1000){
                pSprite.setTextureRect(sf::IntRect(50, 258, 41, 77));

            }else{
            timejugador.restart();
            }
            break;

            case 1:

                if(timejugador.getElapsedTime().asMilliseconds()<200){
                        pSprite.setTextureRect(sf::IntRect(276, 258, 41, 77));
                 }
                  else if(timejugador.getElapsedTime().asMilliseconds()<400){
                        pSprite.setTextureRect(sf::IntRect(276+47, 258, 41, 77));
                 }
                 else if(timejugador.getElapsedTime().asMilliseconds()<600){
                        pSprite.setTextureRect(sf::IntRect(276+47*2, 258, 41, 77));
                 }
                  else if(timejugador.getElapsedTime().asMilliseconds()<800){
                        pSprite.setTextureRect(sf::IntRect(276+47, 258, 41, 77));
                 }

                  else{
                 timejugador.restart();
                 }
                 break;

            case 2:

                if(timejugador.getElapsedTime().asMilliseconds()<100){
                        pSprite.setTextureRect(sf::IntRect(5, 344, 54, 90));

                 }
                 else if(timejugador.getElapsedTime().asMilliseconds()<200){
                        pSprite.setTextureRect(sf::IntRect(65, 344, 54, 90));
                 }

                 else if(timejugador.getElapsedTime().asMilliseconds()<300){
                        pSprite.setOrigin(60,pSprite.getOrigin().y);
                        pSprite.setTextureRect(sf::IntRect(240, 371, 68, 66));


                 }

                  else if(timejugador.getElapsedTime().asMilliseconds()<400){
                        pSprite.setTextureRect(sf::IntRect(312, 371, 68, 66));
                 }
                  else if(timejugador.getElapsedTime().asMilliseconds()<500){

                        pSprite.setTextureRect(sf::IntRect(378, 371, 68, 66));


                 }


                else{
                pSprite.setTextureRect(sf::IntRect(10, 258, 41, 77));
                 pSprite.setOrigin(hitbox.getOrigin());
                 timejugador.restart();
                 estado=4;

                 }


        }

    }

    if(v.x==0 && v.y==0 && estado!=2)
        estado=0;

   movePlayer(v,time);


}

void player:: render(float ticks, RenderWindow &ventana){



pSprite.setPosition(xlast*(1-ticks) + x*ticks,ylast*(1-ticks)+y*ticks);
ventana.draw(pSprite);
if(mundo::getMundo()->getDebug()){
    ventana.draw(hitbox);
    ventana.draw(hitboxArma);
}


}



void player::ataquePlayer(){

for(int i=0;i<mundo::getMundo()->enemigosFuera->size();i++){
    if(mundo::getMundo()->enemigosFuera->at(i).hitbox.getGlobalBounds().intersects(hitboxArma.getGlobalBounds())){
       if(mundo::getMundo()->enemigosFuera->at(i).playerHit(BASEDMG*nivel)){
            //Hitplayer es cuando el jugador le ataca, devuelve true si muere
         mundo::getMundo()->enemigosFuera->erase(mundo::getMundo()->enemigosFuera->begin()+i);
       }
    }
}

for(int i=0;i<mundo::getMundo()->vectorBoss1->size();i++){
    if(mundo::getMundo()->vectorBoss1->at(i).hitbox.getGlobalBounds().intersects(hitboxArma.getGlobalBounds())){
       if(mundo::getMundo()->vectorBoss1->at(i).playerHit(BASEDMG*nivel)){
            //Hitplayer es cuando el jugador le ataca, devuelve true si muere
         mundo::getMundo()->vectorBoss1->erase(mundo::getMundo()->vectorBoss1->begin()+i);
       }
    }
}

}

void player::toggleInvul(){

if(invulnerable){
    invulnerable=false;
}else{
    invulnerable=true;
}

}






