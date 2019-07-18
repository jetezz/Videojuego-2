#ifndef BALAMISIL_H
#define BALAMISIL_H
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemigos.h"
#include <math.h>
#include <boss1.h>

class BalaMisil
{
    public:
        BalaMisil(float posX, float posY);
        sf::Vector2f direccion;
        bool viva;
        float nextPosX;
        float nextPosY;
        float x;
        float y;
        float xlast;
        float ylast;
        float angle;

        void disparar(float time);
        float setPos(sf::Vector2f newPos);
        sf::FloatRect getGlobal();
        void colision(int j);
        void colision2(int j);
        void render(float ticks, sf::RenderWindow &Window);
        void colisionboss1(int j);
        sf::RectangleShape hitbox;

        virtual ~BalaMisil();

    protected:

    private:
        sf::Sprite balaSprite;
};

#endif // BALAMISIL_H
