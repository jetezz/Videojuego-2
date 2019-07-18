#ifndef MONEDA_H
#define MONEDA_H
#include <SFML/Graphics.hpp>
#include <mundo.h>
#include <math.h>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#define TIEMPO_PARPADEO 10
#define TIEMPO_ENTRE_PARPADEO 1
#define TIEMPO_MUERTE 15


using namespace sf;
class Moneda
{
    public:
        Moneda(float x, float y, int valor);
        int valor;
        bool movimiento(float xJugador, float yJugador);
        void render(sf::RenderWindow &Window);
        bool checkMuerte();
        sf::RectangleShape hitbox;
        sf::Sprite mSprite;
        virtual ~Moneda();
        sf::Clock timeMoneda;
        sf::Clock parpadeo;
    protected:

    private:

    sf::Time tiempoParpadeo = seconds(10);
        sf::Time tiempoentreparpadeo = seconds(1);
            sf::Time tiempomuerte = seconds(15);


};

#endif // MONEDA_H
