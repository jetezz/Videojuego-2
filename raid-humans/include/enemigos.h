

#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include <iostream>
#include<SFML/Graphics.hpp>
#include <player.h>
#include <Torreta.h>
#include <math.h>

using namespace sf;
using namespace std;
class player;
class Torreta;
class enemigos {

public:
        enemigos(); //defecto
        enemigos(float x, float y); //parametros
        enemigos(const enemigos& E); //copia
        ~enemigos(); //destructor

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
        float velocidad = 50;
        float vida = 500;
        float money;
        bool ataca=false;
        bool atacaTorre=false;
        bool invulnerable=false;

         int        estado;    //0-> reposo ,1-> movimiento, 2-> ataque (para renderizar)


        sf::FloatRect getGlobal();
        void moveEnemy(float time, vector<enemigos>, vector<Torreta>, int a);
        void render(float ticks, RenderWindow& ventana);
        void colisionEnemigos(Vector2f ene);
        bool ataque(player * p, vector<Torreta> vecTor);
        void setObjetivo(Vector2f obj);
        void atacaTorretaCercana(vector<Torreta> vecTor);
        void atacaJugador(player &jugador);
        void movsprites();
        bool playerHit(float dano);
        bool balaHit(float dano);
        void invulnerabilidad();
        void danobala();
        void seleccionaAtaque(vector<Torreta> vecTor, player &jugador);


protected:
private:
     Clock timeInvul;
     Clock  timedanobala;
     Clock timeenemigo;



};

#endif // ENEMIGOS_H
