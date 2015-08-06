//Arman Farhangi
//August 1, 2015
//Tiled Map Creator
//Tile source

#include "tile.h"

Tile::Tile()
{
    Tile::ID = 0;
}

Tile::Tile(int ID)
{
    Tile::ID = ID;
    x = 0;
    y = 0;
}

int Tile::getID()
{
    return ID;
}