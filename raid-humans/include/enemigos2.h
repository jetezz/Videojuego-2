

#ifndef ENEMIGOS2_H
#define ENEMIGOS2_H
#include <iostream>
#include<SFML/Graphics.hpp>
#include <player.h>
#include <Torreta.h>
#include <math.h>

using namespace sf;
using namespace std;
class player;
class Torreta;
class enemigos2 {

public:
        enemigos2(); //defecto
        enemigos2(float x, float y); //parametros
        enemigos2(const enemigos2& E); //copia
        ~enemigos2(); //destructor

        RectangleShape hitbox;
        RectangleShape colision;

        Sprite    eSprite;
        float     x;
        float     y;
        float     xlast;
        float     ylast;

        Vector2f   vel;
        Vector2f objetivo;
        float saludEnemigo;
        float danioEnemigo;
        float velocidad = 75;
        float vida = 50;
        float money;
        bool ataca=false;
        bool invulnerable=false;

         int        estado;    //0-> reposo ,1-> movimiento, 2-> ataque (para renderizar)


        sf::FloatRect getGlobal();
        void moveEnemy(float time, vector<enemigos2>, int a);
        void render(float ticks, RenderWindow& ventana);
        void colisionEnemigos(Vector2f ene);
        bool ataque(player * p, vector<Torreta> vecTor);
        void setObjetivo(Vector2f obj);
        void atacaJugador(player *jugador);
        void movsprites();
        bool playerHit(float dano);
        bool balaHit(float dano);
        void invulnerabilidad();
        void danobala();


protected:
private:
     Clock timeInvul;
     Clock  timedanobala;
     Clock timeenemigo;



};

#endif // ENEMIGOS_H
