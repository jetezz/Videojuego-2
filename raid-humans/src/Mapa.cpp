#include "../include/Mapa.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
using namespace tinyxml2;
using namespace std;
using namespace sf;




Mapa::Mapa(char *archivo, string urlTiles){
    //leemos el tmx y cagamos el mapa
    _numLayers = 0;
    _width = 0;
    _height = 0;
        cout<<"1) Leemos XML. Archivo: "<<archivo<<" | "<<urlTiles<<endl;
    doc.LoadFile(archivo);

        if(doc.LoadFile(archivo))
            cout<<" -- ok"<<endl;
        else
            cout<<" -- x"<<endl;

    //empezamos a cargar sus params, map es lo 1o que nos encontramos en el xml
        cout<<"2) Leemos y asignamos width y height al mapa: "<< doc.FirstChildElement("map") <<endl;
    XMLElement* mapaXML = doc.FirstChildElement("map");
        if(doc.FirstChildElement("map"))
            cout<<" -- ok"<<endl;
        else
            cout<<" -- x"<<endl;

    _tileHeight = 0;
    _tileWidth  = 0;

    //leemos anchura y altura del mapa y los tiles
        cout<<"3) Leemos anchura y altura del mapa y los tiles"<<endl;
    mapaXML->QueryIntAttribute("width",&_width);
    mapaXML->QueryIntAttribute("height",&_height);
    mapaXML->QueryIntAttribute("tilewidth",&_tileWidth);
    mapaXML->QueryIntAttribute("tileheight",&_tileHeight);
        if(doc.FirstChildElement("map"))
            cout<<" -- ok --"<<"width: "<<_width<<" height: "<<_height<<" tileW: "<<_tileWidth<<" tileH: "<<_tileHeight<<endl;
        else
            cout<<" -- x"<<endl;

    cout<<"4) Obtenemos los tiles"<<endl;
    // obtenemos tiles
    imageTileset = mapaXML->FirstChildElement("tileset");
    imageTileset->QueryIntAttribute("tilewidth", &_tilesetWidth);
    imageTileset->QueryIntAttribute("tileheight", &_tilesetHeight);
    cout<<"-- ok -- tilesetW: "<<_tilesetWidth<<" tilesetH: "<<_tilesetHeight<<endl;

    cout<<"5) Obtenemos la imagen del tileset"<<endl;
    // obtenemos la imagen del tileset
    imagen = mapaXML->FirstChildElement("tileset")->FirstChildElement("image");
    ficheroimg   = (string)imageTileset->FirstChildElement("image")->Attribute("source");
    imagen->QueryIntAttribute("width",&_imageWidth);
    imagen->QueryIntAttribute("height",&_imageHeight);
    cout<<"-- ok "<<" imagen: "<<imagen<<" ficheroimg: "<<ficheroimg<<" width: "<<_imageWidth<<" height: "<<_imageHeight<<endl;

    cout<<"6) Cargamos la textura"<<endl;
    _tilesetTexture.loadFromFile(urlTiles);
    //cargamos la textura
    /*while(imageTileset){
        //
        if(!_tilesetTexture.loadFromFile(ficheroimg)){
        cout<<"No se ha podido cargar la textura"<<endl;
            exit(0);
        }
    }*/
    if(_tilesetTexture.loadFromFile(urlTiles));
        cout<<"-- ok"<<endl;

    // leemos y obtenemos el numero de capas
    cout<<"7) Leemos y obtenemos el numero de capas"<<endl;
    XMLElement *layer = mapaXML->FirstChildElement("layer");
    _numLayers = 0;
    while(layer){
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }
    cout << "-- ok Num de capas: " <<_numLayers<<endl;


    // creamos un array de tiles
    cout<<"8) Creamos un array de tiles"<<endl;
    filas       = _tilesetTexture.getSize().y/_tileHeight;
    columnas    = _tilesetTexture.getSize().x/_tileWidth;
    posicion    = 0;
    cout<<"filas :"<<filas<<" columnas: "<<columnas<<endl;
    sf::Sprite _tilesetSprite[filas*columnas+1];// +1?
    int t = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            posicion++;
            _tilesetSprite[posicion].setTexture(_tilesetTexture);
            _tilesetSprite[posicion].setTextureRect(sf::IntRect(j*_tileWidth,i*_tileHeight,_tileWidth,_tileHeight));//16*j,16*i,16,16
        }
    }
    cout << "-- ok"<<endl;
    /*
    colisionMap = new bool*[_height];
    for(int i = 0; i< _height; i++){
        colisionMap[i]=new bool[_width];
    }
    */
    int _tileMap[_numLayers][_height][_width];//asignamos capas, alto y ancho

    //cargamos los GIDs
    cout<<"9) Cargamos los GIDs"<<endl;
    XMLElement *data[_numLayers];
            //XMLElement *layer;
    data[0] = mapaXML->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    layer = mapaXML->FirstChildElement("layer");


    for(int l=0;l<_numLayers;l++){
        cout<<"layer actual "<<l<<" numlayers: "<<_numLayers<<endl;
        for(int y=0;y<_height;y++){
            for(int x=0;x<_width;x++){

                data[l]->QueryIntAttribute("gid",&_tileMap[l][y][x]);
                data[l]=data[l]->NextSiblingElement("tile");
            }
        }
        cout<<"capa "<<l<<" cargada"<<endl;
        if( _numLayers == 1){
            cout<<"solo 1 capa, salimos"<<endl;
            break;
        }
        if(data[l]==0){
            data[l+1]=layer->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
            cout<<"Pasamos al layer 2"<<endl;
        }
    }
     cout<<"-- ok"<<endl;

    //cargamos y resevamos memoria para la matriz 4d
    cout<<"10) Cargamos y reservamos memoria para la matriz 4d"<<endl;
    _tileMapSprite = new sf::Sprite***[_numLayers];
    for(int i=0;i<_numLayers;i++){
        _tileMapSprite[i]=new sf::Sprite**[_height];
    }

    for(int l=0;l<_numLayers;l++){
        for(int y=0;y<_height;y++){
            _tileMapSprite[l][y]=new sf::Sprite*[_width];
            for(int x=0;x<_width;x++){
                _tileMapSprite[l][y][x]=new sf::Sprite();
            }
        }
    }
    cout<<"-- ok"<<endl;
    //creamos array de sprites
    cout<<"11) Creamos un array de sprites"<<endl;
    for(int l=0;l<_numLayers;l++){
        for(int y=0;y<_height;y++){
            for(int x=0;x<_width;x++){
                gid = _tileMap[l][y][x];
                if(gid>=filas*columnas){// if(gid>=_tilesetWidth*_tilesetHeight)?
                    cout<<"Error"<<endl;
                }else if(gid>0){
                    _tileMapSprite[l][y][x]->setTextureRect(_tilesetSprite[gid].getTextureRect());//?
                    _tileMapSprite[l][y][x]=new sf::Sprite(_tilesetTexture,_tilesetSprite[gid].getTextureRect());
                    _tileMapSprite[l][y][x]->setPosition(x*_tileWidth,y*_tileHeight);
                }else{
                    _tileMapSprite[l][y][x]=NULL;
                }
            }
        }
    }
}
void Mapa::setActivateLayer(int layer){
    _activeLayer=layer;
}
void Mapa::drawMapa(sf::RenderWindow &window){
    for(int l=0;l<_numLayers;l++){
    //cout<<"D I B U J A M O S   M A P A"<<endl;
        for(int y=0;y<_height;y++){
            for(int x=0;x<_width;x++){
                 if(_tileMapSprite[l][x][y]!=NULL){
                    window.draw(*(_tileMapSprite[l][x][y]));
                 }
            }
        }
    }
}
