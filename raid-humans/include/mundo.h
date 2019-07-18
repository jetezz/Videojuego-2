#ifndef MUNDO_H
#define MUNDO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include <Mapa.h>
#include <enemigos.h>
#include <enemigos2.h>
#include <vector>
#include <Torreta.h>
#include <Bala.h>
#include <Moneda.h>
#include <BalaMisil.h>
#include <boss1.h>
#include <Castillo.h>
#include <Bomba.h>

using namespace sf;
class enemigos;
class enemigos2;
class player;
class Mapa;
class Moneda;
class Bala;
class BalaMisil;
class Castillo;
class boss1;
class Bomba;

class mundo
{
    public:
        mundo();
        virtual ~mundo();

        static mundo* getMundo(); //Singleton

        void toggleDebug();
        bool getDebug();
        void test();
        void cambiarTipoTorreta(int tipo);
        int getCoins();
        bool gastaCoins(int coins);
        void addCoins(int coins);
        Mapa *mapa;
        RenderWindow * ventana;
        Castillo *castillo;
        player * jugador;



        sf::Texture torretaTex;
        sf::Texture castilloTex;
        sf::Texture eTexture;
        sf::Texture eTexture2;
        sf::Texture balaTex;
        sf::Texture coinTex;
        sf::Texture splasTexture;
        sf::Texture splasmenu;
        sf::Texture botoninicio;
        sf::Texture compratorreta1;
        sf::Texture compratorreta2;
        sf::Texture compramejora;
        sf::Texture botoncambioestado;
        sf::Texture compratorreta1no;
        sf::Texture compratorreta2no;
        sf::Texture compramejorano;
        sf::Texture corazonctext;
        sf::Texture corazontext;
        sf::Texture monedatext;
        sf::Texture enemigobase;
        sf::Texture bombaCompra;
        sf::Texture bombaCompraNo;
        sf::Texture bombaTex;
        sf::Texture explosionTex;

        sf::Text dinero;
        sf::Font font;
        int tipoTorreta;
        int monedas;

        vector<enemigos> * enemigosFuera; //vector de enemigos que se encuentran en pantalla
        vector<enemigos> * enemigosEspera;
        vector<enemigos2> * enemigosFuera2;
        vector<enemigos2> * enemigosEspera2;
        vector<Torreta> * vectorTorreta;
        vector<Bala> * vectorBalas;
        vector<BalaMisil> * vectorBalasMisil;
        vector<Moneda> * vectorMonedas;
        vector<boss1> * vectorboss1Espera;
        vector<boss1> * vectorBoss1;
        vector<Bomba> * vectorBombas;


    protected:

    private:
        static mundo* _instancia;
        bool debug = false;

};

#endif // MUNDO_H
