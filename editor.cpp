//Arman Farhangi
//August 1, 2015
//Tiled Map Creator
//Editor source

#include "editor.h"
#include "tile.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

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
    rightSection = new sf::RectangleShape(sf::Vector2f(RIGHT_SECTION_WIDTH, WINDOW_HEIGHT));
    rightSection->setFillColor(sf::Color::Transparent);
    rightSection->setOutlineColor(sf::Color::White);
    rightSection->setOutlineThickness(5);
    rightSection->setPosition(WINDOW_WIDTH*3/4, 0);
    
    //set arbitrary tile defaults
    tileWidth = 30;
    tileHeight = 30;
    
    //set map count to allow for creation of multiple txt map files
    mapCount = 0;
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
        if (level == RESTART) level = EDITOR;
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
                
                //return condition
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
    tileRows = 10;
    tileColumns = 12;
    tileFileName = "Resources/Images/tilesheet.png";
    tileMargins = 2;
    /* TEST */
    tileSheet.loadFromFile(tileFileName);
    
    //create vector to hold row outlines
    int gridRows = WINDOW_HEIGHT/tileHeight;
    int gridColumns = (WINDOW_WIDTH - RIGHT_SECTION_WIDTH)/tileWidth;
    std::vector<sf::RectangleShape> rows(gridRows);
    int count = 0;
    while (count < gridRows)
    {
        sf::RectangleShape rect(sf::Vector2f(tileWidth*gridColumns, tileHeight));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setPosition(0, count*tileHeight);
        rows.push_back(rect);
        ++count;
    }
    //create vector to hold column outlines
    std::vector<sf::RectangleShape> columns(gridColumns);
    count = 0;
    while (count < gridColumns)
    {
        sf::RectangleShape rect(sf::Vector2f(tileWidth, tileHeight*gridRows));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setPosition(count*tileWidth, 0);
        columns.push_back(rect);
        ++count;
    }
    
    //create vector to hold all tile sprites
    std::vector<Tile> tileSprites;
    int sheetWidth = tileSheet.getSize().x;
    int sheetHeight = tileSheet.getSize().y;
    int widthProgress = 0;
    int heightProgress = 0;
    count = 0;
    while (widthProgress <= sheetWidth && heightProgress <= sheetHeight)
    {
        Tile tile(count + 1);
        tile.setTexture(tileSheet);
        tile.setTextureRect(sf::IntRect(widthProgress, heightProgress, tileWidth, tileHeight));
        tileSprites.push_back(tile);
        heightProgress += tileHeight + tileMargins;
        if (heightProgress >= sheetHeight)
            { heightProgress = 0; widthProgress += tileWidth + tileMargins; }
        ++count;
    }
    
    //create vectors to hold subsets of tile sprites in right section
    int RSrows = WINDOW_HEIGHT/(tileHeight + tileMargins);
    int RScolumns = RIGHT_SECTION_WIDTH/(tileWidth + tileMargins);
    size_t vectorAmount;
    if (tileSprites.size()%RSrows*RScolumns == 0)
        vectorAmount = tileSprites.size()/(RSrows*RScolumns);
    else
        vectorAmount = tileSprites.size()/(RSrows*RScolumns) + 1;
    std::vector<std::vector<Tile>> tileSelectionSprites(vectorAmount);
    count = 0;
    for (int i = 0; i < vectorAmount; ++i)
    {
        int columnsProgress = 0;
        int rowsProgress = 0;
        while (columnsProgress < RScolumns && rowsProgress < RSrows && count < tileSprites.size())
        {
            tileSprites[count].x = columnsProgress*(tileWidth + tileMargins) + WINDOW_WIDTH - RIGHT_SECTION_WIDTH;
            tileSprites[count].y = rowsProgress*(tileHeight + tileMargins);
            tileSprites[count].setPosition(tileSprites[count].x, tileSprites[count].y);
            tileSelectionSprites[i].push_back(tileSprites[count]);
            ++count;
            ++columnsProgress;
            if (columnsProgress >= RScolumns)
                { columnsProgress = 0; ++rowsProgress; }
        }
    }
    
    //create rectangle to hover over selected tile in right section
    sf::RectangleShape tileOutline(sf::Vector2f(tileWidth - 10, tileHeight - 10));
    tileOutline.setFillColor(sf::Color::Transparent);
    tileOutline.setOutlineColor(sf::Color::White);
    tileOutline.setOutlineThickness(5);
    tileOutline.setPosition(tileSelectionSprites[0][0].x + 5, tileSelectionSprites[0][0].y + 5);
    
    //create buffer to help load tile from selection to grid
    Tile tileBuffer = tileSprites[0];
    
    //create vectors to hold tiles to be used in the grid
    std::vector<std::vector<Tile>> grid(tileRows);
    for (int i = 0; i < tileRows; ++i)
        for (int j = 0; j < tileColumns; ++j)
        {
            grid[i].push_back(Tile());
            grid[i][j].setPosition(tileWidth*j, tileHeight*i);
        }
    
    //create trackers
    int tileGroupSelected = 0;
    bool focusRight = true;
    int mouseXPos = 0;
    int mouseYPos = 0;
    int tileSelected = 0;
    int selectedGridRow = 0;
    int selectedGridColumn = 0;
    
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
            
            //key press conditions
            if (event.type == sf::Event::KeyPressed)
            {
                //if mouse last clicked right section
                if (focusRight == true)
                {
                    //down condition
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        if (tileGroupSelected < vectorAmount - 1)
                        {
                            ++tileGroupSelected;
                            tileOutline.setPosition(tileSelectionSprites[tileGroupSelected][0].x + 5, tileSelectionSprites[tileGroupSelected][0].y + 5);
                            tileBuffer = tileSelectionSprites[tileGroupSelected][0];
                        }
                    }
                    //up condition
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        if (tileGroupSelected > 0)
                        {
                            --tileGroupSelected;
                            tileOutline.setPosition(tileSelectionSprites[tileGroupSelected][0].x + 5, tileSelectionSprites[tileGroupSelected][0].y + 5);
                            tileBuffer = tileSelectionSprites[tileGroupSelected][0];
                        }
                    }
                }
                
                //if mouse last clicked left
                else if (focusRight == false)
                {
                    //backspace condition
                    if (event.key.code == sf::Keyboard::BackSpace)
                    {
                        grid[selectedGridRow][selectedGridColumn].setID(0);
                    }
                    
                    //o condition
                    if (event.key.code == sf::Keyboard::O)
                    {
                        if (grid[selectedGridRow][selectedGridColumn].getID() > 0)
                            grid[selectedGridRow][selectedGridColumn].makeObstacle();
                    }
                    
                    //n condition
                    if (event.key.code == sf::Keyboard::N)
                    {
                        if (grid[selectedGridRow][selectedGridColumn].getID() < 0)
                            grid[selectedGridRow][selectedGridColumn].makeObstacle();
                    }
                    
                    //return condition
                    if (event.key.code == sf::Keyboard::Return)
                    {
                        std::stringstream ss;
                        ss << "Resources/Texts/map" << mapCount << ".txt";
                        std::fstream streamOut;
                        streamOut.open(ss.str(), std::ios::out);
                        
                        for (int i = 0; i < grid.size(); ++i)
                        {
                            for (int j = 0; j < grid[i].size(); ++j)
                            {
                                streamOut << grid[i][j].getID() << " ";
                                if (j == grid[i].size() - 1)
                                    streamOut << "\n";
                            }
                        }
                        
                        streamOut.close();
                    }
                    
                    //escape condition
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        level = RESTART;
                        ++mapCount;
                    }
                    
                    //r condition
                    if (event.key.code == sf::Keyboard::R)
                    {
                        ++tileRows;
                        grid.push_back(std::vector<Tile>(tileColumns));
                    }
                    
                    //c condition
                    if (event.key.code == sf::Keyboard::C)
                    {
                        ++tileColumns;
                        for (int i = 0; i < tileRows; ++i)
                            grid[i].push_back(Tile());
                    }
                }
            }
            
            //left click conditions
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mouseXPos = sf::Mouse::getPosition(*window).x;
                mouseYPos = sf::Mouse::getPosition(*window).y;
                
                //if clicked in right section
                if (mouseXPos >= WINDOW_WIDTH - RIGHT_SECTION_WIDTH)
                {
                    focusRight = true;
                    mouseXPos -= WINDOW_WIDTH - RIGHT_SECTION_WIDTH;
                    int selectedColumn, selectedRow;
                    if (mouseXPos%tileWidth == 0) selectedColumn = mouseXPos/tileWidth;
                    else selectedColumn = mouseXPos/tileWidth + 1;
                    if (mouseYPos%tileHeight == 0) selectedRow = mouseYPos/tileHeight;
                    else selectedRow = mouseYPos/tileHeight + 1;
                    tileSelected = ((selectedRow - 1)*RScolumns + selectedColumn) - 1;
                    if (tileSelected < tileSelectionSprites[tileGroupSelected].size())
                    {
                        tileOutline.setPosition(tileSelectionSprites[tileGroupSelected][tileSelected].x + 5, tileSelectionSprites[tileGroupSelected][tileSelected].y + 5);
                        tileBuffer = tileSelectionSprites[tileGroupSelected][tileSelected];
                    }
                }
                
                //if clicked in left section (that is within grid)
                else if (mouseXPos < gridColumns*tileWidth)
                {
                    focusRight = false;
                    if (mouseXPos%tileWidth == 0) selectedGridColumn = mouseXPos/tileWidth;
                    else selectedGridColumn = mouseXPos/tileWidth;
                    if (mouseYPos%tileHeight == 0) selectedGridRow = mouseYPos/tileHeight;
                    else selectedGridRow = mouseYPos/tileHeight;
                    if (selectedGridRow < grid.size() && selectedGridColumn < grid[selectedGridRow].size())
                    {
                        grid[selectedGridRow][selectedGridColumn] = tileBuffer;
                        grid[selectedGridRow][selectedGridColumn].setPosition(selectedGridColumn*tileWidth, selectedGridRow*tileHeight);
                    }
                }
            }
        }
        
        //CHANGES
        
        //RENDER
        window->clear();
        
        for (int i = 0; i < tileSelectionSprites[tileGroupSelected].size(); ++i)
            window->draw(tileSelectionSprites[tileGroupSelected][i]);
        
        window->draw(*rightSection);
        
        window->draw(tileOutline);
        
        for (int i = 0; i < grid.size(); ++i)
            for (int j = 0; j < grid[i].size(); ++j)
                if (grid[i][j].getID() != 0)
                    window->draw(grid[i][j]);
        
        for (int i = 0; i < rows.size(); ++i) { window->draw(rows[i]); }
        
        for (int i = 0; i < columns.size(); ++i) { window->draw(columns[i]); }
        
        //DRAW
        window->display();
    }
}