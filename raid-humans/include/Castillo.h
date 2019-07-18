#ifndef CASTILLO_H
#define CASTILLO_H
#include <SFML/Graphics.hpp>
#include <mundo.h>

class Castillo
{
    public:
        Castillo();
        float vida;
        bool invulnerable=false;
        void draw(sf::RenderWindow &Window);
        bool enemigohit(float dano);
        virtual ~Castillo();
        sf::Sprite castilloSprite;
        sf::RectangleShape hitbox;



    protected:

    private:
};

#endif // CASTILLO_H
