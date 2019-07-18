#ifndef JUEGO_H
#define JUEGO_H


#include <SFML/System/Clock.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "player.h"
#include "Bala.h"
#include "Torreta.h"
#include "enemigos.h"
#include "enemigos2.h"
#include "Moneda.h"
#include <vector>
#include <Mapa.h>
#include <StateMachine.h>
#include <BalaMisil.h>
#include <Castillo.h>
#include <Bomba.h>
#include <sstream>
#include "Hud.h"
#include <boss1.h>
using namespace sf;


class juego
{
    public:
        juego(Vector2u resolucion);
        void inicializar();      //inicializar las variables del juego
        void update(float elapsedTime);
         void colisionEE();
        void renderizar(float percentick);
        vector<int> getInputs();
        Vector2f calcularVelocidadPlayer(vector<int> inputs);
        void dibujarSelector();
        bool addTorreta();
        void disparar();
        void recogerMoneda();
        void checkGameover();
        vector<Torreta> getTorretas();
        bool IsSpriteCLicker(sf::Sprite es);
        void togleInvul();
         //numero de enemigos que apareceran en la oleada
        int numEnemigos = 0;
        //numero de enemigos que ya han aparecido
        int numEnemigosFuera = 0;
         //numero de enemigos que apareceran en la oleada
        int numEnemigos1 = 0;
        //numero de enemigos que ya han aparecido
        int numEnemigosFuera1 = 0;
         //numero de enemigos que apareceran en la oleada
        int numEnemigos2 = 0;
        //numero de enemigos que ya han aparecido
        int numEnemigosFuera2 = 0;


    protected:

    private:
        Mapa *mapa;
        RenderWindow * ventana;
        player * jugador;
        StateMachine * estado;
        Castillo * castillo;
        vector<Torreta> vectorTorreta;
        vector<Bala> vectorBalas;
        vector<Moneda> vectorMonedas;
        vector<enemigos> enemigosFuera; //vector de enemigos que se encuentran en pantalla
        vector<enemigos>enemigosEspera; //vector de enemigos para hacer spawn*/
        vector<enemigos2> enemigosFuera2;
        vector<enemigos2> enemigosEspera2;
        vector<BalaMisil> vectorBalasMisil;
        vector<boss1> vectorboss1Espera;
        vector<boss1> vectorBoss1;
        vector<Bomba> vectorBombas;
        Sprite dSprite;
        Texture dTexture;
        sf::Text titulo;
        sf::Text endtitulo;
        Sprite tumba;
        Sprite copawin;
        Texture tumbatext;
        Texture copawintext;
        Clock clock;
        Clock updateCLock;
        Time tiempo = clock.getElapsedTime();


        //variables de tiempo para el spawn
        Clock clockSpawn;
        Time tiempoSpawn =  seconds(5.f);
        Time tiempoSpawn2= seconds(3.f);

        //variables de tiempo para la bala
        Clock clockBala;
        Time tiempoBala = clock.getElapsedTime();

        //variables de tiempo para el ataque
        Clock clockAttack;
        Time tiempoAttack = seconds(1.f);


        sf::Sprite portada;
        sf::Sprite menu;
        sf::Sprite boton;
        sf::Sprite torretaCompra1;
        sf::Sprite torretaCompra2;
        sf::Sprite espadaCompra;
        sf::Sprite bombaCompra;

        sf::Sprite continuarRonda;

        sf::Sprite torretaFantasma; //la que te sigue al comprar

        Hud * hud;
};
#endif // JUEGO_H

