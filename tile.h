//Arman Farhangi
//August 5, 2015
//Tiled Map Creator
//Tile head

#ifndef __game__tile__
#define __game__tile__

#include <SFML/Graphics.hpp>
//sprite.setTextureRect(sf::IntRect(widthProgress, heightProgress, tileWidth, tileHeight));
class Tile : public sf::Sprite
{
public:
    Tile();
    Tile(int ID);
    int getID();
    void setID(int ID);
    int x;
    int y;
    void changeObstacle();
private:
    int ID;
};

#endif
