#ifndef BOMBA_H
#define BOMBA_H
#include <SFML/Graphics.hpp>
#include <mundo.h>
#include <enemigos.h>

class Bomba
{
    public:
        Bomba(float xPos, float yPos);
        bool explosion();
        bool viva;
        bool explotando;
        bool colision(int i);
        int getX();
        int getY();
        void render(sf::RenderWindow &Window);
        sf::Sprite bomba;
        sf::Clock timeExplosion;
        virtual ~Bomba();

    protected:

    private:

};

#endif // BOMBA_H
