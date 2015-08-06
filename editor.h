//Arman Farhangi
//August 1, 2015
//Tiled Map Creator
//Editor head

#ifndef __game__editor__
#define __game__editor__

#include <SFML/Graphics.hpp>
#include <string>

class Editor
{
public:
    //constants and enums
    const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 700, RIGHT_SECTION_WIDTH = WINDOW_WIDTH/4;
    enum Level { INTRO, EDITOR, END };
    
    //functions
    Editor();
    ~Editor();
    void run();
    void intro();
    void editor();
    
private:
    sf::RenderWindow* window;
    Level level;
    sf::RectangleShape* rightSection;
    int tileWidth;
    int tileHeight;
    int tileRows;
    int tileColumns;
    std::string tileFileName;
    int tileMargins;
};

#endif
