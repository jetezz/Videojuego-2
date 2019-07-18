#ifndef TORRETA_H
#define TORRETA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <mundo.h>

class Torreta
{
    public:
        Torreta();
        int getX();
        int getY();
        float vida=500;
        int tipo;
        void setPos(sf::Vector2f newPos);
        void rotarTorreta(float angle);
        void draw(sf::RenderWindow &Window);
        void dibujarSprite();
        void danoenemigo();
        bool enemigohit(float dano);
        sf::Sprite getSprite();

        sf::Clock timeTorreta;
        sf::Clock timedanoTorreta;
        ~Torreta();
                sf::Sprite torretaSprite;

    private:



};

#endif // TORRETA_H
