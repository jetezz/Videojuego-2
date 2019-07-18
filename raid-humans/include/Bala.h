#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemigos.h"
#include <boss1.h>
#include <math.h>

class enemigos;
class Torreta;
class player;
class Bala
{
    public:
        sf::Vector2f direccion;
        bool viva;
        float nextPosX;
        float nextPosY;
        float x;
        float y;
        float xlast;
        float ylast;
        float angle;
        Bala(float posX, float posY);
        void disparar(float time);
        float setPos(sf::Vector2f newPos);
        int getY();
        int getX();
        sf::FloatRect getGlobal();
        void colision(int j);
        void colision2(int j);
        void colisionboss(int j);
        void render(float ticks, sf::RenderWindow &Window);
        virtual ~Bala();
        sf::RectangleShape hitbox;
    private:

        sf::Sprite balaSprite;
};

#endif // BALA_H
