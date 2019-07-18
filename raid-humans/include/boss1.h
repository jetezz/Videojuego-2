#ifndef BOSS1_H
#define BOSS1_H


#include<SFML/Graphics.hpp>
#include <player.h>
#include <Torreta.h>
#include <math.h>

using namespace sf;
using namespace std;
class player;
class Torreta;



class boss1 {

public:
        boss1(); //defecto
        boss1(float x, float y); //parametros
        boss1(const boss1& E); //copia
        ~boss1(); //destructor

        RectangleShape hitbox;
        RectangleShape colision;

        Sprite    eSprite;
        float     x;
        float     y;
        float     xlast;
        float     ylast;

        Vector2f   vel;
        Vector2f objetivo;


        float velocidad = 60;
        float vida=500;
        float money;

        bool ataca=false;
        bool ataquerealizado=false;
        bool atacaTorre=false;
        bool invulnerable=false;

         int        estado;    //0-> reposo ,1-> movimiento, 2-> ataque (para renderizar)


        sf::FloatRect getGlobal();
        void moveEnemy(float time);
        void render(float ticks, RenderWindow& ventana);
        void colisionEnemigos(Vector2f ene);
        bool ataque();
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

#endif // BOSS1_H
