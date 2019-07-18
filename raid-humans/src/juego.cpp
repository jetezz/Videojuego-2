#include "../include/juego.h"



#define SPAWN_SPEED 4000
#define SHOOT_SPEED 4000
#define UPDATE_TICK_TIME 1000/15
#define kVel 100
#define RONDAFINAL 2

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml2.h"
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

juego::juego(Vector2u resolucion)
{
    //ctor





//creo mapa


// ===== 2 MAPAS -------->>>>>>
    //mapa1_OK -- mapa1
    //mapa2    -- mapa2


 mapa = new Mapa("resources/mapa1_OK.tmx", "resources/PathAndObjects.png");
 ventana = new RenderWindow(VideoMode(resolucion.x, resolucion.y), "Raid humans");
 castillo = new Castillo();
 hud = new Hud();
 jugador= new player("resources/player2.png" ,500,400);
 mundo::getMundo()->enemigosEspera=&enemigosEspera;
 mundo::getMundo()->enemigosFuera=&enemigosFuera;
 mundo::getMundo()->enemigosEspera2=&enemigosEspera2;
 mundo::getMundo()->enemigosFuera2=&enemigosFuera2;
 mundo::getMundo()->vectorTorreta=&vectorTorreta;
 mundo::getMundo()->vectorMonedas=&vectorMonedas;
 mundo::getMundo()->vectorBalas=&vectorBalas;
 mundo::getMundo()->vectorBalasMisil=&vectorBalasMisil;
 mundo::getMundo()->castillo=castillo;
 mundo::getMundo()->vectorboss1Espera=&vectorboss1Espera;
 mundo::getMundo()->vectorBoss1=&vectorBoss1;
 mundo::getMundo()->vectorBombas=&vectorBombas;

portada.setTexture(mundo::getMundo()->splasTexture);
  menu.setTexture(mundo::getMundo()->splasmenu);
  boton.setTexture(mundo::getMundo()->botoninicio);

 portada.setScale((double)ventana->getSize().x/(double)portada.getTexture()->getSize().x,(double)ventana->getSize().y/(double)portada.getTexture()->getSize().y);
 menu.setScale((double)ventana->getSize().x/(double)menu.getTexture()->getSize().x,(double)ventana->getSize().y/(double)menu.getTexture()->getSize().y);
 boton.setPosition((double)ventana->getSize().x/2-(double)boton.getTexture()->getSize().x/2,(double)ventana->getSize().y/2);
titulo.setFont(mundo::getMundo()->font);
titulo.setCharacterSize(120);
titulo.setString("Raid Humans");
titulo.setColor(Color::Black);
titulo.setPosition((double)ventana->getSize().x/2 - (double)titulo.getGlobalBounds().width/2,(double)ventana->getSize().y*1/4 );

    torretaCompra1.setTexture(mundo::getMundo()->compratorreta1);
    torretaCompra2.setTexture(mundo::getMundo()->compratorreta2);
    espadaCompra.setTexture(mundo::getMundo()->compramejora);
    continuarRonda.setTexture(mundo::getMundo()->botoncambioestado);
    bombaCompra.setTexture(mundo::getMundo()->bombaCompra);

endtitulo.setFont(mundo::getMundo()->font);
endtitulo.setCharacterSize(120);
endtitulo.setString("GAME OVER");
endtitulo.setColor(Color::Black);
endtitulo.setPosition((double)ventana->getSize().x/2 - (double)titulo.getGlobalBounds().width/2,(double)ventana->getSize().y*1/4 );



 if(!tumbatext.loadFromFile("resources/tumbita.png")){
        std::cerr <<"Error al cargar la imagen";
        exit(0);
    }

tumba.setTexture(tumbatext);
tumba.setScale(0.5f,0.5f);
tumba.setPosition(250,400);


 if(!copawintext.loadFromFile("resources/copa.png")){
        std::cerr <<"Error al cargar la imagen";
        exit(0);
    }

copawin.setTexture(copawintext);
copawin.setScale(0.5f,0.5f);
copawin.setPosition(250,400);

 if(!tumbatext.loadFromFile("resources/tumbita.png")){
        std::cerr <<"Error al cargar la imagen";
        exit(0);
    }

tumba.setTexture(tumbatext);
tumba.setScale(0.5f,0.5f);
tumba.setPosition(250,400);






    torretaCompra1.setPosition(30,600);
    torretaCompra1.scale(0.8,0.8);
    torretaCompra2.setPosition(170, 600);
    torretaCompra2.scale(0.8,0.8);
    espadaCompra.setPosition(310,600);
    espadaCompra.scale(0.8,0.8);
    bombaCompra.setPosition(400,600);
    bombaCompra.scale(0.8,0.8);



    mundo::getMundo()->dinero.setPosition(ventana->getSize().x-ventana->getSize().x/8,ventana->getSize().y/9);
    mundo::getMundo()->dinero.setColor((sf::Color::Black));
    mundo::getMundo()->dinero.setCharacterSize(30);

    continuarRonda.setPosition(630,600);


    torretaFantasma.setTexture((mundo::getMundo()->torretaTex));
    torretaFantasma.setColor(Color(255,255,255,155));
    torretaFantasma.setTextureRect(IntRect(16,5,96,118));
    torretaFantasma.setScale(0.4f,0.4f);
    torretaFantasma.setOrigin(sf::Vector2f(96/2,118/2));




estado=new StateMachine();





 mundo::getMundo()->ventana=ventana;
 mundo::getMundo()->jugador=jugador;
 mundo::getMundo()->mapa=mapa;






 while(ventana->isOpen()){

     Event event;
    while (ventana->pollEvent(event))
    {

        if (event.type == Event::Closed) {

             delete jugador;
             delete mapa;
             ventana->close();
            delete ventana;
        }
         if (Keyboard::isKeyPressed(Keyboard::F6))
            {
                 mundo::getMundo()->toggleDebug();
                 mundo::getMundo()->test();
                 mundo::getMundo()->addCoins(500);
                 jugador->toggleInvul();
            }


    }
         if(clock.getElapsedTime().asMilliseconds() - tiempo.asMilliseconds() > UPDATE_TICK_TIME){


            update(updateCLock.restart().asSeconds());
            tiempo = clock.getElapsedTime();


         }




float timeElapsed=updateCLock.getElapsedTime().asMilliseconds();
float tiempoRefresco = UPDATE_TICK_TIME;                                   //Hay un bug que si utilizas el  UPDATE TIME directamente no hace la division bien

   float percentick=min(1.f,timeElapsed/tiempoRefresco);

    renderizar(percentick);



 }


}
/*
juego::~juego()
{
    //dtor


}
*/

void juego:: inicializar() { //inicializar las variables del juego



    if (estado->getEstado() == 3 && estado->getModo()==false){

        enemigos ene1(0,(rand() % 200) + 200);
        enemigos ene2(0,(rand() % 200) + 200);
        enemigos ene3(0,(rand() % 200) + 200);
        enemigos ene4(0,(rand() % 200) + 200);
        enemigos ene5(0,(rand() % 200) + 200);
        enemigos ene6(0,(rand() % 200) + 200);
        enemigos ene7(0,(rand() % 200) + 200);
        enemigos ene8(0,(rand() % 200) + 200);
        enemigos ene9(0,(rand() % 200) + 200);
        enemigos ene10(0,(rand() % 200) + 200);
        enemigos ene11(0,(rand() % 200) + 200);
        enemigos ene12(0,(rand() % 200) + 200);
        enemigos ene13(0,(rand() % 200) + 200);
        enemigos ene14(0,(rand() % 200) + 200);
        enemigos ene15(0,(rand() % 200) + 200);
        enemigos ene16(0,(rand() % 200) + 200);

        enemigos2 ene21(0,(rand() % 200) + 200);
        enemigos2 ene22(0,(rand() % 200) + 200);


        boss1 bos1(0,(rand() % 200) + 200);
        boss1 bos2(0,(rand() % 200) + 200);
        boss1 bos3(0,(rand() % 200) + 200);
        boss1 bos4(0,(rand() % 200) + 200);
        boss1 bos5(0,(rand() % 200) + 200);
        boss1 bos6(0,(rand() % 200) + 200);
        boss1 bos7(0,(rand() % 200) + 200);
        boss1 bos8(0,(rand() % 200) + 200);



        vectorboss1Espera.push_back(bos1);
        vectorboss1Espera.push_back(bos2);
        vectorboss1Espera.push_back(bos4);
        vectorboss1Espera.push_back(bos3);
        vectorboss1Espera.push_back(bos6);
        vectorboss1Espera.push_back(bos5);
        vectorboss1Espera.push_back(bos7);
        vectorboss1Espera.push_back(bos8);

        enemigosEspera.push_back(ene1);
        enemigosEspera.push_back(ene2);
        enemigosEspera.push_back(ene3);
        enemigosEspera.push_back(ene4);
        enemigosEspera.push_back(ene5);
        enemigosEspera.push_back(ene6);
        enemigosEspera.push_back(ene7);
        enemigosEspera.push_back(ene8);
        enemigosEspera.push_back(ene9);
        enemigosEspera.push_back(ene10);
        enemigosEspera.push_back(ene11);
        enemigosEspera.push_back(ene12);
        enemigosEspera.push_back(ene13);
        enemigosEspera.push_back(ene14);
        enemigosEspera.push_back(ene15);
        enemigosEspera.push_back(ene16);

        enemigosEspera2.push_back(ene21);
        enemigosEspera2.push_back(ene22);

        numEnemigosFuera=0;
        numEnemigos = (rand() % 4) + 5;

        numEnemigosFuera2=0;
        numEnemigos2 = (rand() % 3) + 2;

        numEnemigosFuera1=0;
        numEnemigos1 = (rand() % 3) + 2;

    }

}


void juego:: update(float elapsedTime){

//cout << "modo-> " << estado->getModo() << endl;
//cout << "estado-> " << estado->getEstado() << endl;

    if(estado->getEstado()==1){
            /////////////////////////////
    //////////INTRODUCCION///////////
    ///////////////////////////

    if(clock.getElapsedTime().asSeconds()>5){

        estado->setEstado(2);
    }



    }else if(estado->getEstado()==2){


     ////////////////////////////////////////
    //////////MENU INICIAL DEL JUEGO///////////
    //////////////////////////////////////



        if(IsSpriteCLicker (boton)){

                clockSpawn.restart();

                clockBala.restart();

                clockAttack.restart();

                 estado->setEstado(3);


        }




    }else if (estado->getEstado()==3){
     ////////////////////////////////////////
    //////////INGAME///////////
    //////////////////////////////////////
    std::stringstream ss;
    ss << mundo::getMundo()->getCoins();

    hud->updateHud();
    mundo::getMundo()->dinero.setString(ss.str());

   //cout << mundo::getMundo()->getCoins() << endl;

                for(int i=0; i<vectorBalas.size(); i++){
                   vectorBalas[i].disparar(elapsedTime);
                    for (int j=0;j<enemigosFuera.size();j++) {
                        vectorBalas[i].colision(j);

                    }
                    for (int j=0;j<enemigosFuera2.size();j++) {
                        vectorBalas[i].colision2(j);

                    }
                    for (int j=0;j<vectorBoss1.size();j++) {
                        vectorBalas[i].colisionboss(j);

                    }
                    if(!vectorBalas[i].viva){
                        vectorBalas.erase(vectorBalas.begin()+i);
                    }
            //cout<<"Tamano vectorBalas: " <<vectorBalas.size() <<endl;
                }
                for(int i=0; i<vectorBalasMisil.size(); i++){
                    vectorBalasMisil[i].disparar(elapsedTime);
                    for (int j=0;j<enemigosFuera.size();j++) {
                        vectorBalasMisil[i].colision(j);

                    }
                    for (int j=0;j<enemigosFuera2.size();j++) {
                        vectorBalasMisil[i].colision2(j);

                    }
                    for (int j=0;j<vectorBoss1.size();j++) {
                        vectorBalasMisil[i].colisionboss1(j);

                    }
                    if(!vectorBalasMisil[i].viva){
                        vectorBalasMisil.erase(vectorBalasMisil.begin()+i);
                    }
                }

                for(int i=0; i<vectorBombas.size();i++){
                    for(int j=0; j<enemigosFuera.size(); j++){
                            if(vectorBombas[i].colision(j)){
                                vectorBombas.erase(vectorBombas.begin()+i);
                            }
                    }

                }

        checkGameover();


        if(estado->getModo()==true){

            ////////////////////
            ////MODO COMPRA/////
            ////////////////////

            vector<int> inputs= getInputs();                //Funcion para coger los botones que se pulsan
            jugador->calcularVelocidadPlayer(inputs,elapsedTime); //Calculamos la posicion inicial y final deljugador y lo movemos
            recogerMoneda();

                    for(int i=0; i<vectorMonedas.size(); i++){
                        if(vectorMonedas.at(i).checkMuerte()){
                            vectorMonedas.erase(vectorMonedas.begin()+i);
                        }

                    }
            //Pintar candado cuando no se puede comprar

           if(mundo::getMundo()->getCoins()>=100){
                torretaCompra1.setTexture(mundo::getMundo()->compratorreta1);
           }else{
                torretaCompra1.setTexture(mundo::getMundo()->compratorreta1no);
           }

           if(mundo::getMundo()->getCoins()>=200){
                torretaCompra2.setTexture(mundo::getMundo()->compratorreta2);
           }else{
                torretaCompra2.setTexture(mundo::getMundo()->compratorreta2no);
           }

           if(mundo::getMundo()->getCoins()>=500 && mundo::getMundo()->jugador->nivel<2){
                espadaCompra.setTexture(mundo::getMundo()->compramejora);
           }else{
                espadaCompra.setTexture(mundo::getMundo()->compramejorano);
           }

           if(mundo::getMundo()->getCoins()>=300){
                bombaCompra.setTexture(mundo::getMundo()->bombaCompra);
           }else{
                bombaCompra.setTexture(mundo::getMundo()->bombaCompraNo);
           }

            //Colocar torreta
           if(estado->getColocando() && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(!IsSpriteCLicker(mundo::getMundo()->castillo->castilloSprite) && !addTorreta()){
                    estado->comprando();
                    sf::sleep(seconds(0.100));
                }

           }

           //Hacer clic en el boton de compra de torreta 1
           if(IsSpriteCLicker (torretaCompra1)  && !estado->getColocando()){
                if(mundo::getMundo()->gastaCoins(100)){
                    estado->colocando();
                    sf::sleep(seconds(0.100));
                    mundo::getMundo()->cambiarTipoTorreta(1);
                    torretaFantasma.setTexture(mundo::getMundo()->torretaTex);
                    torretaFantasma.setTextureRect(IntRect(128,0,128,128));
                }
           }


           //hacer clic en el boton de compra 2
           else if(IsSpriteCLicker (torretaCompra2) && !estado->getColocando()){
                  if(mundo::getMundo()->gastaCoins(200)){
                    estado->colocando();
                    sf::sleep(seconds(0.100));
                    mundo::getMundo()->cambiarTipoTorreta(2);
                    torretaFantasma.setTexture(mundo::getMundo()->torretaTex);
                    torretaFantasma.setTextureRect(IntRect(0,128,128,128));
                  }

            //Hacer clic en el boton de mejora de arma
           }else if  (IsSpriteCLicker(espadaCompra) && mundo::getMundo()->jugador->nivel<2){
               if(mundo::getMundo()->gastaCoins(500)){
                  mundo::getMundo()->jugador->nivel=2;
               }


           }
           else if(IsSpriteCLicker (bombaCompra) && !estado->getColocando()){
                if(mundo::getMundo()->gastaCoins(200)){
                    estado->colocando();
                    sf::sleep(seconds(0.100));
                    mundo::getMundo()->cambiarTipoTorreta(3);
                    torretaFantasma.setTexture(mundo::getMundo()->bombaTex);
                    torretaFantasma.setScale(0.2,0.2);
                    torretaFantasma.setTextureRect(IntRect(0,0,128,128));
                }
           }


            //Mover botones para que no se buguee
           if(estado->getColocando()){
            torretaCompra1.setPosition(-200,-200);
            torretaCompra2.setPosition(-200, -200);
            espadaCompra.setPosition(-200,-200);
            continuarRonda.setPosition(-200,-200);
            bombaCompra.setPosition(-200,-200);

           }else{


            torretaCompra1.setPosition(30,600);
            torretaCompra2.setPosition(190, 600);
            bombaCompra.setPosition(350,600);
            espadaCompra.setPosition(510,600);
            continuarRonda.setPosition(630,600);
           }




          if(IsSpriteCLicker (continuarRonda)){
                if(estado->getColocando()){
                    estado->comprando();
                }else{
                    estado->toggleModo();
                    inicializar();
                }

          }



        }else{

            ////////////////////
            ////MODO BATALLA/////
            ////////////////////




            vector<int> inputs= getInputs();                //Funcion para coger los botones que se pulsan
            jugador->calcularVelocidadPlayer(inputs,elapsedTime); //Calculamos la posicion inicial y final deljugador y lo movemos



            jugador->invulnerabilidad();

            //movimiento enemigo
            if (enemigosFuera.empty()==false) {
                for (int i=0;i<enemigosFuera.size();i++) {
                    enemigosFuera.at(i).moveEnemy(elapsedTime, enemigosFuera, vectorTorreta, i);
                    enemigosFuera.at(i).invulnerabilidad();
                    enemigosFuera.at(i).danobala();

                        /*dSprite.setTexture(dTexture);
                        dSprite.setOrigin(17,48/2);
                        dSprite.setTextureRect(IntRect(0.1*35, 2.63*50, 28, 27));
                        dSprite.setPosition(jugador->xlast,jugador->ylast+25);*/
                    }
            }
            if (enemigosFuera2.empty()==false) {
                for (int i=0;i<enemigosFuera2.size();i++) {
                    enemigosFuera2.at(i).moveEnemy(elapsedTime, enemigosFuera2, i);
                    enemigosFuera2.at(i).invulnerabilidad();
                    enemigosFuera2.at(i).danobala();
                    }
            }
            if (vectorBoss1.empty()==false) {
                for (int i=0;i<vectorBoss1.size();i++) {
                    vectorBoss1.at(i).moveEnemy(elapsedTime);
                    vectorBoss1.at(i).invulnerabilidad();
                    vectorBoss1.at(i).ataque();
                    vectorBoss1.at(i).movsprites();
                    vectorBoss1.at(i).danobala();

                        /*dSprite.setTexture(dTexture);
                        dSprite.setOrigin(17,48/2);
                        dSprite.setTextureRect(IntRect(0.1*35, 2.63*50, 28, 27));
                        dSprite.setPosition(jugador->xlast,jugador->ylast+25);*/
                    }
            }

            recogerMoneda();

            for(int i = 0; i < vectorTorreta.size(); i++){
                vectorTorreta[i].dibujarSprite();
                vectorTorreta[i].danoenemigo();
            }


                     //temporizador para generar enemigos
                     if(clockSpawn.getElapsedTime() > tiempoSpawn && estado->getRonda() == 1){

                        clockSpawn.restart();

                        if (enemigosEspera.empty()==false && (numEnemigos != numEnemigosFuera)) {
                            numEnemigosFuera++;
                            enemigosFuera.push_back(enemigosEspera.at(enemigosEspera.size()-1));
                            enemigosEspera.pop_back();
                        }
                        if (enemigosEspera2.empty()==false && (numEnemigos2 != numEnemigosFuera2)) {
                            numEnemigosFuera2++;
                            enemigosFuera2.push_back(enemigosEspera2.at(enemigosEspera2.size()-1));
                            enemigosEspera2.pop_back();
						}
                        if (vectorboss1Espera.empty()==false && (numEnemigos1 != numEnemigosFuera1)) {
                            numEnemigosFuera1++;
                            vectorBoss1.push_back(vectorboss1Espera.at(vectorboss1Espera.size()-1));
                            vectorboss1Espera.pop_back();
                        }
                        if (enemigosFuera.empty()==false) {
                            for (int i=0;i<enemigosFuera.size()&&i<4;i++) {
                                enemigosFuera.at(i).seleccionaAtaque(vectorTorreta, *jugador);
                            }
                        }
                        if (enemigosFuera2.empty()==false) {
                            for (int i=0;i<enemigosFuera2.size()&&i<4;i++) {
                                enemigosFuera2.at(i).atacaJugador(jugador);
                                enemigosFuera2.at(i).ataque(jugador, vectorTorreta);
                            }
                        }


                        //le damos un objetivo al enemigo


                     }
                     else if(clockSpawn.getElapsedTime() > tiempoSpawn2 && estado->getRonda() == 2){
                        clockSpawn.restart();

                        if (enemigosEspera.empty()==false && (numEnemigos != numEnemigosFuera)) {
                            numEnemigosFuera++;
                            enemigosFuera.push_back(enemigosEspera.at(enemigosEspera.size()-1));
                            enemigosEspera.pop_back();
                        }
                        if (enemigosEspera2.empty()==false && (numEnemigos2 != numEnemigosFuera2)) {
                            numEnemigosFuera2++;
                            enemigosFuera2.push_back(enemigosEspera2.at(enemigosEspera2.size()-1));
                            enemigosEspera2.pop_back();
                        }
                        if (vectorboss1Espera.empty()==false && (numEnemigos1 != numEnemigosFuera1)) {
                            numEnemigosFuera1++;
                            vectorBoss1.push_back(vectorboss1Espera.at(vectorboss1Espera.size()-1));
                            vectorboss1Espera.pop_back();
                        }
                        if (enemigosFuera.empty()==false) {
                            for (int i=0;i<enemigosFuera.size()&&i<4;i++) {
                                enemigosFuera.at(i).seleccionaAtaque(vectorTorreta, *jugador);
                            }
                        }
                        if (enemigosFuera2.empty()==false) {
                            for (int i=0;i<enemigosFuera2.size()&&i<4;i++) {
                                enemigosFuera2.at(i).atacaJugador(jugador);
                            }
                        }
                        //le damos un objetivo al enemigo
                     }


                      // los enemigos comprueban el ataque
                     if(clockAttack.getElapsedTime() > tiempoAttack){

                        clockAttack.restart();

                        if (enemigosFuera.empty()==false) {
                            for (int i=0;i<enemigosFuera.size();i++) {
                                enemigosFuera.at(i).seleccionaAtaque(vectorTorreta, *jugador);
                                if(enemigosFuera.at(i).ataca==true){
                                   // if (!dTexture.loadFromFile("resources/hit.png")){
                                     //   cerr << "Error cargando la imagen del golpe resources/sprites.png" << endl;
                                     //   exit(0);
                                  //  }
                                  //enemigosFuera.at(i).eSprite.setColor(Color(255,0,0,155));

                                }else{
                                  //enemigosFuera.at(i).eSprite.setColor(Color(255,255,255,255));
                                }
                            }
                        }
                        if (enemigosFuera2.empty()==false) {
                            for (int i=0;i<enemigosFuera2.size();i++) {
                                enemigosFuera2.at(i).atacaJugador(jugador);
                                if(enemigosFuera2.at(i).ataca==true){


                                }else{

                                }
                            }
                        }

                     }

                    //temporizador para generar balas
                     if(clockBala.getElapsedTime().asMilliseconds() - tiempoBala.asMilliseconds() > SHOOT_SPEED){
                        tiempoBala = clockBala.getElapsedTime();
                        disparar();
                     }



                    for(int i=0; i<vectorMonedas.size(); i++){
                        if(vectorMonedas.at(i).checkMuerte()){
                            vectorMonedas.erase(vectorMonedas.begin()+i);
                        }

                    }
   if((numEnemigos==numEnemigosFuera) && enemigosFuera.size()==0 && (numEnemigos1==numEnemigosFuera1) && vectorBoss1.size()==0 /*&& (numEnemigos2==numEnemigosFuera2) && enemigosFuera2.size()==0*/){
        cout <<"CAMBIO DE RONDA DIN DIN DIN" << endl;

         mundo::getMundo()->vectorMonedas->push_back(Moneda(400,400,50*estado->getRonda()));
        mundo::getMundo()->castillo->vida=2000;
        estado->toggleModo();


   }

        }


    }else if(estado->getEstado()==4){
     ////////////////////////////////////////
    //////////GAME OVER//////////
    //////////////////////////////////////


        if (enemigosFuera.empty()==false) {
            for (int i=0;i<enemigosFuera.size();i++) {
               enemigosFuera.erase(enemigosFuera.begin()+i);
            }
        }

        if (enemigosFuera2.empty()==false) {
            for (int i=0;i<enemigosFuera2.size();i++) {
               enemigosFuera2.erase(enemigosFuera2.begin()+i);
            }
        }


        if (vectorMonedas.empty()==false) {
            for (int i=0;i<vectorMonedas.size();i++) {
               vectorMonedas.erase(vectorMonedas.begin()+i);
            }
        }

        if (vectorTorreta.empty()==false) {
            for (int i=0;i<vectorTorreta.size();i++) {
               vectorTorreta.erase(vectorTorreta.begin()+i);
            }
        }


        if (vectorBalasMisil.empty()==false) {
            for (int i=0;i<vectorBalasMisil.size();i++) {
              vectorBalasMisil.erase(vectorBalasMisil.begin()+i);
            }
        }


        if (enemigosEspera.empty()==false) {
            for (int i=0;i<enemigosEspera.size();i++) {
               enemigosEspera.erase(enemigosEspera.begin()+i);
            }
        }

        if (enemigosEspera2.empty()==false) {
            for (int i=0;i<enemigosEspera2.size();i++) {
               enemigosEspera2.erase(enemigosEspera2.begin()+i);
            }
        }

        if(vectorBombas.empty()==false){
            for(int i=0; i<vectorBombas.size(); i++){
                vectorBombas.erase(vectorBombas.begin()+i);
            }
        }

        titulo.setString("GG ez");



    }







}
//ataque de los enemigos


void juego:: renderizar(float percentick){
ventana->clear();


 if(estado->getEstado()==1){
            /////////////////////////////
    //////////INTRODUCCION///////////
    ///////////////////////////

    ventana->draw(portada);




    }else if(estado->getEstado()==2){


     ////////////////////////////////////////
    //////////MENU INICIAL DEL JUEGO///////////
    //////////////////////////////////////


     ventana->draw(menu);
     ventana->draw(boton);
     ventana->draw(titulo);


    }else if (estado->getEstado()==3){
     ////////////////////////////////////////
    //////////INGAME///////////
    //////////////////////////////////////







       mapa->setActivateLayer(0);
       mapa->drawMapa(*ventana);


//Recorrer el vector de torretas y dibujar las torretas

for(int i=0; i<vectorTorreta.size(); i++)
    vectorTorreta[i].draw(*ventana);

jugador->render(percentick, *ventana);

if (enemigosFuera.empty()==false) {
    for (int i=0;i<enemigosFuera.size();i++) {
        enemigosFuera.at(i).render(percentick, *ventana);
    }
}
if (enemigosFuera2.empty()==false) {
    for (int i=0;i<enemigosFuera2.size();i++) {
        enemigosFuera2.at(i).render(percentick, *ventana);
    }
}
if (vectorBoss1.empty()==false) {
    for (int i=0;i<vectorBoss1.size();i++) {
        vectorBoss1.at(i).render(percentick, *ventana);
    }
}

if (enemigosFuera.size()>0) {
    for (int i=0;i<enemigosFuera.size();i++) {
        if(enemigosFuera.at(i).ataca==true){
            ventana->draw(dSprite);
        }
    }
}
if (enemigosFuera2.size()>0) {
    for (int i=0;i<enemigosFuera2.size();i++) {
        if(enemigosFuera2.at(i).ataca==true){
            ventana->draw(dSprite);
        }
    }
}


for(int i=0; i<vectorBalas.size(); i++){
    vectorBalas[i].render(percentick, *ventana);
}
for(int i=0; i<vectorBalasMisil.size(); i++){
    vectorBalasMisil[i].render(percentick, *ventana);
}

for(int i=0; i<vectorMonedas.size(); i++){
    vectorMonedas[i].render(*ventana);
}
for(int i=0; i<vectorBombas.size(); i++){
    vectorBombas[i].render(*ventana);
}






                    if(estado->getModo()==true){

                        ////////////////////
                        ////MODO COMPRA/////
                        ////////////////////
                        if(estado->getColocando()){
                             dibujarSelector();

                        }else{
                            jugador->render(percentick, *ventana);
                            ventana->draw(torretaCompra1);
                            ventana->draw(torretaCompra2);
                            ventana->draw(espadaCompra);
                            ventana->draw(continuarRonda);
                            ventana->draw(bombaCompra);


                        }

                    }

castillo->draw(*ventana);
hud->draw(*ventana);
      ventana->draw(mundo::getMundo()->dinero);

    }


    else if(estado->getEstado()==5){
     ////////////////////////////////////////
    //////////GAME OVER//////////
    //////////////////////////////////////
        endtitulo.setColor(Color::White);
        ventana->draw(endtitulo);
        //if(mundo::mundo())
        if(mundo::getMundo()->jugador->salud <= 0 || mundo::getMundo()->castillo->vida <= 0){
          //  if(mundo::getMundo()->jugador->salud <= 0){
                ventana->draw(tumba);
           // }
           /* if(mundo::getMundo()->castillo->vida == 0){
                ventana->draw(castillolose);
            }*/
        }else{
            endtitulo.setString("GAME OVER");
            ventana->draw(copawin);
        }

/*
     ventana->draw(boton);
 if(IsSpriteCLicker (boton)){

                clockSpawn.restart();

                clockBala.restart();

                clockAttack.restart();

                 estado->setEstado(1);


        }*/

    }





ventana->display();


}

vector<int> juego::getInputs(){



vector<int> data;



            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                   data.push_back(4);                               //IZQUIERDA --> 4
            }
            if (Keyboard::isKeyPressed(Keyboard::D))    //DEREZHA --> 6
            {
                  data.push_back(6);
            }
            if (Keyboard::isKeyPressed(Keyboard::W))       //ARRIBA --> 8
            {
                 data.push_back(8);
            }
            if (Keyboard::isKeyPressed(Keyboard::S))     //ABAJO --> 2
            {
                data.push_back(2);
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))    //ESCAPE --> 0
            {
                data.push_back(0);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

                data.push_back(5);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
               if(mundo::getMundo()->getDebug()) addTorreta();
            }


            Vector2i position = Mouse::getPosition(*ventana);

            if(position.x > jugador->x){         //RATON MIRA DERECHA
               data.push_back(7);

            }else{
               data.push_back(9);                   //RATON MIRA IZQUIERDA
            }


    return data;
}


void juego::dibujarSelector(){
    //Dibujar selector en el mapa para poner la torreta donde marque

    //definir rectangulo, para selector
    sf::RectangleShape selector(sf::Vector2f(32.f, 32.f));
    sf::Color trasnparente(0, 0, 0, 1); //Cuadrado transparente
    selector.setFillColor(trasnparente);
    //Pintar borde del rectangulo, que sera e selector
    selector.setOutlineThickness(2.f);
    selector.setOutlineColor(sf::Color(255, 255, 255)); //Color blanco

        //Obtener coordenadas de la ventana
        sf::Vector2i localPosition = sf::Mouse::getPosition(*ventana);
        int posicionX = localPosition.x;
        int posicionY = localPosition.y;

        //Obtener parte entera de la division
        int i = (posicionX/32);
        int j = (posicionY/32);

        //Dibujar el selector en el cuadrado de la matriz
        selector.setPosition(i*32.f ,j*32.f);
        torretaFantasma.setPosition(i*32.f+10.f ,j*32.f+14.f);
        ventana->draw(selector);
        ventana->draw(torretaFantasma);


}

bool juego::addTorreta(){

    //Obtener coordenadas de la ventana
    sf::Vector2i localPosition = sf::Mouse::getPosition(*ventana);
    int posicionX = localPosition.x;
    int posicionY = localPosition.y;
    bool existe = false;

    //Obtener parte entera de la division
    int i = (posicionX/32);
    int j = (posicionY/32);

    for(int k = 0; k < vectorTorreta.size();k++){
        if(vectorTorreta[k].getX()/32 == i && vectorTorreta[k].getY()/32 == j){
            existe = true;
        }
    }
    for(int k=0; k<vectorBombas.size(); k++){
        if(vectorBombas[k].getX()/32 == i && vectorBombas[k].getY()/32 == j){
            existe = true;
        }
    }

    //CAMBIAR CUANDO TENGAMOS EL MAPA
    if(i >= 0 && j >= 0 && i <= 25 && j <= 25 && !existe){
            if(mundo::getMundo()->tipoTorreta==3){
                Bomba bomba(i*32.f+16 ,j*32.f+16);
                vectorBombas.push_back(bomba);
            }
            else{
                //Crea la clase torreta dandole un tamanio
                Torreta* torreta = new Torreta();
                //Coloca la torreta en una posicion llamando a una funcion que hemos creado en la clase torreta setPos
                torreta->setPos(sf::Vector2f(i*32.f+16 ,j*32.f+16));
                //Anade la torreta creada al vector de torretas
               vectorTorreta.push_back(*torreta);
            }

    }
    return existe;

}


void juego::disparar(){

    //Recorro el vector de torretas, las cuales dispararan al enemigo mas cercano
    for(int i=0; i<vectorTorreta.size(); i++){
        float angle=0;
        float enemigoX=0;//Variables para pasar a la nueva bala, con la pos del enemigo mas cercano
        float enemigoY=0;
        float dist=10000;
        /*FUNCION PARA CALCULAR EL ENEMIGO MAS CERCANO cogiendo el vector de los enemigos Y PASARLE LA POSICION A LA NUEVA BALA
          IF HAY ALGUN ENEMIGO le paso la posicion ELSE no creo la bala */
        if(!enemigosFuera.empty() || !vectorBoss1.empty() || !enemigosFuera2.empty()){//Si hay enemigos
            for(int j=0; j<enemigosFuera.size(); j++){//Recorro el vector de enemigos
                if(enemigosFuera[j].x>0){//Si en esa pos del vector hay un enemigo
                    //Calcular distancia entre enemigo y torreta
                    float newDist=sqrt(pow(vectorTorreta[i].getX()-enemigosFuera[j].x,2) + pow(vectorTorreta[i].getY()-enemigosFuera[j].y,2));
                    if(newDist < dist){
                        dist=newDist;//si la nueva distancia es menor que la anterior, sera la nueva distancia
                    if(dist<=300){

                        enemigoX=enemigosFuera[j].x;//Asignamos las coordenadas de ese enemigo a nuestras variables
                        enemigoY=enemigosFuera[j].y;
                    }
                    }
                }
            }
            for(int j=0; j<enemigosFuera2.size(); j++){//Recorro el vector de enemigos
                if(enemigosFuera2[j].x>0){//Si en esa pos del vector hay un enemigo
                    //Calcular distancia entre enemigo y torreta
                    float newDist=sqrt(pow(vectorTorreta[i].getX()-enemigosFuera2[j].x,2) + pow(vectorTorreta[i].getY()-enemigosFuera2[j].y,2));
                    if(newDist < dist){
                        dist=newDist;//si la nueva distancia es menor que la anterior, sera la nueva distancia
                    if(dist<=300){

                        enemigoX=enemigosFuera2[j].x;//Asignamos las coordenadas de ese enemigo a nuestras variables
                        enemigoY=enemigosFuera2[j].y;
                    }
                    }
                }
            }
            for(int j=0; j<vectorBoss1.size(); j++){//Recorro el vector de enemigos
                if(vectorBoss1[j].x>0){//Si en esa pos del vector hay un enemigo
                    //Calcular distancia entre enemigo y torreta
                    float newDist=sqrt(pow(vectorTorreta[i].getX()-vectorBoss1[j].x,2) + pow(vectorTorreta[i].getY()-vectorBoss1[j].y,2));
                    if(newDist < dist){
                        dist=newDist;//si la nueva distancia es menor que la anterior, sera la nueva distancia
                    if(dist<=300){

                        enemigoX=vectorBoss1[j].x;//Asignamos las coordenadas de ese enemigo a nuestras variables
                        enemigoY=vectorBoss1[j].y;
                    }
                    }
                }
            }
            if(dist<=300){
                if(vectorTorreta[i].tipo == 1){
                    Bala * nuevaBala = new Bala(enemigoX, enemigoY);
                    angle = nuevaBala->setPos(sf::Vector2f(vectorTorreta[i].getX(), vectorTorreta[i].getY()));
                    vectorBalas.push_back(*nuevaBala);
                    vectorTorreta[i].rotarTorreta(angle);
                    vectorTorreta[i].timeTorreta.restart(); //reseteo el sprite de torreta si dispara
                }
                else if(vectorTorreta[i].tipo==2){
                    BalaMisil * nuevaBala = new BalaMisil(enemigoX, enemigoY);
                    angle = nuevaBala->setPos(sf::Vector2f(vectorTorreta[i].getX(), vectorTorreta[i].getY()));
                    vectorBalasMisil.push_back(*nuevaBala);
                    vectorTorreta[i].rotarTorreta(angle);
                    vectorTorreta[i].timeTorreta.restart(); //reseteo el sprite de torreta si dispara
                }

            }
        }

    }

}
void juego::recogerMoneda(){
    for(int i=0; i<vectorMonedas.size(); i++){
        if(vectorMonedas[i].hitbox.getGlobalBounds().intersects(jugador->hitbox.getGlobalBounds())){

            if(vectorMonedas[i].movimiento(jugador->x, jugador->y)){
                 mundo::getMundo()->addCoins(vectorMonedas[i].valor);
                vectorMonedas.erase(vectorMonedas.begin()+i);
            }

        }
    }


}
vector<Torreta> juego::getTorretas() {
    return vectorTorreta;
}



bool juego:: IsSpriteCLicker (sf::Sprite es){
    bool pulsado=false;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::IntRect rectangudobon (es.getPosition().x,es.getPosition().y,es.getGlobalBounds().width,es.getGlobalBounds().height);
        if(rectangudobon.contains(sf::Mouse::getPosition(*ventana)))
            pulsado=true;

    }
    return pulsado;

}

void juego::checkGameover(){

    if(jugador->salud <= 0 || mundo::getMundo()->castillo->vida<=0 || estado->getRonda()>RONDAFINAL){

                estado->setEstado(5);

    }



}
