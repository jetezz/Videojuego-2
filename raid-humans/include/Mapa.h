#ifndef MAPA_H
#define MAPA_H
#include "tinyxml2.h"
#include "SFML/Graphics.hpp"
using namespace tinyxml2;
using namespace std;
class Mapa{
    public:
        Mapa(char *archivo, string urlTiles);
        void        drawMapa(sf::RenderWindow &window);
        void        setActivateLayer(int layer);
    private:
        int         _width;
        int         _height;
        int         _tileWidth;
        int         _tileHeight;
        int         _tilesetWidth;
        int         _tilesetHeight;
        int         _imageWidth;
        int         _imageHeight;
        //XMLElement  *mapaXML;
        XMLDocument doc;
        XMLElement  *imageTileset;
        XMLElement  *imagen;
        XMLElement  *layers;
        int         _numLayers;
        int         filas;
        int         columnas;
        int         posicion;
        sf::Sprite  _tilesetSprite;
        sf::Texture _tilesetTexture;
        sf::Sprite  ****_tileMapSprite;
        int         gid;
        string      ficheroimg;
        int         _activeLayer;
        bool        **colisionMap;
};
#endif //MAPA_H
