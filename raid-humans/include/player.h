#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include<SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <mundo.h>

#define kVel 100

using namespace sf;
using namespace std;



class player
{
    public:

        player();
        player(string imgDirectory, float x, float y);
        virtual ~player();

        RectangleShape hitbox;
        RectangleShape hitboxArma;

        Texture   pTexture;
        Sprite    pSprite;
        float     x;
        float     y;
        float     xlast;
        float     ylast;
        Vector2f   vel;
        int        estado;    //0-> reposo ,1-> movimiento, 2-> ataque (para renderizar)
        int nivel=1;
        int salud=500;





    Vector2f movePlayer(Vector2f a, float time);

    void render(float ticks, RenderWindow& ventana);
    void calcularVelocidadPlayer(vector<int> inputs,float time);
    void toggleDebug();
    void ataquePlayer();
    void invulnerabilidad();
    bool enemigohit(float dano);
    void toggleInvul();
    protected:
    private:

    Clock timejugador;
    Clock timeinvul;
    bool debug = false;
    bool invulnerable;


};



#endif // PLAYER_H

