//Arman Farhangi
//August 1, 2015
//Tiled Map Creator
//Editor source

#include "editor.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//constructor
Editor::Editor()
{
    //create main window
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tiled Map Creator");
    
    //set level to intro screen
    //level = INTRO;
    /*TEST*/
    level = EDITOR;
    /*TEST*/
    
    //create outline for right section
    rightSection = new sf::RectangleShape(sf::Vector2f(RIGHT_SECTION_WIDTH - 5, WINDOW_HEIGHT - 10));
    rightSection->setFillColor(sf::Color::Black);
    rightSection->setOutlineColor(sf::Color::White);
    rightSection->setOutlineThickness(5);
    rightSection->setPosition(WINDOW_WIDTH*3/4, 5);
    
    //set arbitrary tile defaults
    tileWidth = 30;
    tileHeight = 30;
}

//destructor
Editor::~Editor()
{
    delete window;
    delete rightSection;
}

//starts editor program
void Editor::run()
{
    while (level != END)
    {
        if (level == INTRO) intro();
        if (level == EDITOR) editor();
    }
    
    window->close();
}

//intro level
void Editor::intro()
{
    //create title text
    sf::Font font;
    font.loadFromFile("Resources/Fonts/retro.ttf");
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Welcome to ArmanSom's Tiled Map Creator!");
    titleText.setCharacterSize(35);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(WINDOW_WIDTH/20, WINDOW_HEIGHT/20);
    
    //create first instruction text
    sf::Text instruction1 = titleText;
    instruction1.setString("- First, enter tile dimensions\n    Width:\n    Height:");
    instruction1.setCharacterSize(33);
    instruction1.setPosition(WINDOW_WIDTH/20, WINDOW_HEIGHT*3/20);
    
    //create second instruction text
    sf::Text instruction2 = instruction1;
    instruction2.setString("- Now, enter initial number of rows and columns\n    Rows:\n    Columns:");
    instruction2.setPosition(WINDOW_WIDTH/20, WINDOW_HEIGHT*9/20);
    
    //create third instruction text
    sf::Text instruction3 = instruction1;
    instruction3.setString("- Last, enter file name and tile margins\n    Filename:\n    Margins:");
    instruction3.setPosition(WINDOW_WIDTH/20, WINDOW_HEIGHT*15/20);
    
    //create string for input
    std::string input = "";
    
    //create text to display user input
    sf::Text displayedInput;
    displayedInput.setFont(font);
    displayedInput.setString("");
    displayedInput.setCharacterSize(30);
    displayedInput.setColor(sf::Color::White);
    displayedInput.setPosition(WINDOW_WIDTH*1/6, WINDOW_HEIGHT*6/30 + 8);
    
    //create text to copy and display user inputted values
    sf::Text width, height, rows, columns, fileName;
    
    //create progress trackers
    bool widthEntered = false;
    bool heightEntered = false;
    bool rowsEntered = false;
    bool columnsEntered = false;
    bool fileNameEntered = false;
    bool marginsEntered = false;
    
    //MAIN LOOP
    while (level == INTRO)
    {
        //EVENT LOOP
        sf::Event event;
        while (window->pollEvent(event))
        {
            //window close condition
            if (event.type == sf::Event::Closed)
                level = END;
            
            //text entered condition
            if (event.type == sf::Event::TextEntered)
            {
                //allows for non-number codes to display in file name field
                if (columnsEntered == true && fileNameEntered == false)
                {
                    if (event.text.unicode >= 33 && event.text.unicode <= 126)
                        input += static_cast<char>(event.text.unicode);
                }
                //other fields only display number inputs
                else
                {
                    if (event.text.unicode >= 48 && event.text.unicode <= 57)
                    {
                        input += static_cast<char>(event.text.unicode);
                    }
                }
            }
            
            //key press conditions
            if (event.type == sf::Event::KeyPressed)
            {
                //backspace condition
                if (event.key.code == sf::Keyboard::BackSpace && input.length() > 0)
                    input.erase(input.length()-1, 1);
                
                //enter condition
                if (event.key.code == sf::Keyboard::Return)
                {
                    if (widthEntered == false && input != "")
                    {
                        std::stringstream ss(input);
                        ss >> tileWidth;
                        widthEntered = true;
                        width = displayedInput;
                        input = "";
                        displayedInput.setString("");
                        displayedInput.setPosition(WINDOW_WIDTH*1/6 + 16, WINDOW_HEIGHT*8/30 + 2);
                    }
                    
                    else if (heightEntered == false && input != "")
                    {
                        std::stringstream ss(input);
                        ss >> tileHeight;
                        heightEntered = true;
                        height = displayedInput;
                        input = "";
                        displayedInput.setString("");
                        displayedInput.setPosition(WINDOW_WIDTH*1/6 - 5, WINDOW_HEIGHT*15/30 + 9);
                    }
                    
                    else if (rowsEntered == false && input != "")
                    {
                        std::stringstream ss(input);
                        ss >> tileRows;
                        rowsEntered = true;
                        rows = displayedInput;
                        input = "";
                        displayedInput.setString("");
                        displayedInput.setPosition(WINDOW_WIDTH*1/6 + 52, WINDOW_HEIGHT*17/30 + 3);
                    }
                    
                    else if (columnsEntered == false && input != "")
                    {
                        std::stringstream ss(input);
                        ss >> tileColumns;
                        columnsEntered = true;
                        columns = displayedInput;
                        input = "";
                        displayedInput.setString("");
                        displayedInput.setPosition(WINDOW_WIDTH*1/6 + 60, WINDOW_HEIGHT*24/30 + 8);
                    }
                    
                    else if (fileNameEntered == false && input != "")
                    {
                        tileFileName = "Resources/Images/" + input;
                        fileNameEntered = true;
                        fileName = displayedInput;
                        input = "";
                        displayedInput.setString("");
                        displayedInput.setPosition(WINDOW_WIDTH*1/6 + 40, WINDOW_HEIGHT*26/30 + 3);
                    }
                    
                    else if (marginsEntered == false && input != "")
                    {
                        std::stringstream ss(input);
                        ss >> tileMargins;
                        marginsEntered = true;
                        level = EDITOR;
                    }
                }
            }
        }
        
        //CHANGES
        displayedInput.setString(input);
        
        //RENDER
        window->clear();
        window->draw(titleText);
        window->draw(*rightSection);
        window->draw(instruction1);
        window->draw(displayedInput);
        if (widthEntered == true) { window->draw(width); }
        if (heightEntered == true) { window->draw(height); }
        if (widthEntered == true && heightEntered == true) { window->draw(instruction2); }
        if (rowsEntered == true) { window->draw(rows); }
        if (columnsEntered == true) { window->draw(columns); }
        if (rowsEntered == true && columnsEntered == true) { window->draw(instruction3); }
        if (fileNameEntered == true) { window->draw(fileName); }
        
        //DRAW
        window->display();
    }
}

//editor level
void Editor::editor()
{
    //load tilesheet
    sf::Texture tileSheet;
    /* TEST */
    tileWidth = 70;
    tileHeight = 70;
    tileRows = 5;
    tileColumns = 5;
    tileFileName = "Resources/Images/tilesheet.png";
    tileMargins = 2;
    /* TEST */
    tileSheet.loadFromFile(tileFileName);
    
    //create vector to hold row outlines
    std::vector<sf::RectangleShape> rows(tileRows);
    int count = 0;
    while (count < tileRows)
    {
        sf::RectangleShape rect(sf::Vector2f(tileWidth*tileColumns, tileHeight));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setPosition(0, count*tileHeight);
        rows.push_back(rect);
        ++count;
    }
    //create vector to hold column outlines
    std::vector<sf::RectangleShape> columns(tileColumns);
    count = 0;
    while (count < tileColumns)
    {
        sf::RectangleShape rect(sf::Vector2f(tileWidth, tileHeight*tileRows));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setPosition(count*tileWidth, 0);
        columns.push_back(rect);
        ++count;
    }
    
    //create vector to hold all tile sprites
    std::vector<sf::Sprite> tileSprites;
    int sheetWidth = tileSheet.getSize().x;
    int sheetHeight = tileSheet.getSize().y;
    int widthProgress = 0;
    int heightProgress = 0;
    while (widthProgress < sheetWidth && heightProgress < sheetHeight)
    {
        sf::Sprite sprite;
        sprite.setTexture(tileSheet);
        sprite.setTextureRect(sf::IntRect(widthProgress, heightProgress, tileWidth, tileHeight));
        tileSprites.push_back(sprite);
        widthProgress += tileWidth + tileMargins;
        if (widthProgress > sheetWidth)
            { widthProgress = 0; heightProgress += tileHeight + tileMargins; }
    }
    
    //MAIN LOOP
    while (level == EDITOR)
    {
        //EVENT LOOP
        sf::Event event;
        while (window->pollEvent(event))
        {
            //window close condition
            if (event.type == sf::Event::Closed)
                level = END;
        }
        
        //CHANGES
        
        //RENDER
        window->clear();
        window->draw(*rightSection);
        for (int i = 0; i < rows.size(); ++i) { window->draw(rows[i]); }
        for (int i = 0; i < columns.size(); ++i) { window->draw(columns[i]); }
        
        //DRAW
        window->display();
    }
}