#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include "Counter.h"
#include "FilePaths.h"
#include "Board.h"
#include "Random_Num_Gen.h"
#include "Mine.h"
#include "Flag.h"

using namespace std;
using sf::VideoMode;
using sf::Mouse;
using sf::Event;
using sf::Vector2f;

void setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

//void OpenLeaderBoard(int row, int col, Board& gameBoard, vector<Button>& buttons) {
//
//    ifstream readFile;
//    readFile.open("files/board_config.cfg");
//    string line;
//    getline(readFile, line, '\n');
//    int width = stoi(line);
//    getline(readFile, line, '\n');
//    int height = stoi(line);
//
//    int widthLB = width * 16;
//    int heightLB = (height * 16) + 50;
//
//    vector<string> names;
//    vector<string> timesLB;
//
//    sf::RenderWindow leaderWindow(sf::VideoMode(widthLB, heightLB), "Leaderboard", sf::Style::Close);
//
//    sf::Font Font;
//    sf::Text Text1;
//    Font.loadFromFile("files/font.ttf");
//    Text1.setFont(Font);
//    Text1.setCharacterSize(20);
//    Text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
//    Text1.setFillColor(sf::Color(255, 255, 255));
//    Text1.setString("LEADERBOARD");
//    setText(Text1, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 120);
//
//    fstream readFile("files/leaderboard.txt");
//    if (!readFile.is_open())
//    {
//        cout << "error: file isn't open" << endl;
//    }
//
//    for (int i = 0; i < 5; i++)
//    {
//        getline(readFile, line, ',');
//        timesLB.push_back(line);
//        getline(readFile, line, '\n');
//        names.push_back(line);
//    }
//
//    sf::Text t1;
//    sf::Text t2;
//    sf::Text t3;
//    sf::Text t4;
//    sf::Text t5;
//
//    // 1. 
//    t1.setFont(Font);
//    t1.setCharacterSize(18);
//    t1.setStyle(sf::Text::Bold);
//    t1.setFillColor(sf::Color::White);
//    t1.setString("1.\t" + timesLB[0] + "\t" + names[0]);
// 
//    setText(t1, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 60);
//    // 2. 
//    t2.setFont(Font);
//    t2.setCharacterSize(18);
//    t2.setStyle(sf::Text::Bold);
//    t2.setFillColor(sf::Color::White);
//    t2.setString("2.\t" + timesLB[1] + "\t" + names[1]);
//    setText(t2, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 30);
//    // 3. 
//    t3.setFont(Font);
//    t3.setCharacterSize(18);
//    t3.setStyle(sf::Text::Bold);
//    t3.setFillColor(sf::Color::White);
//    t3.setString("3.\t" + timesLB[2] + "\t" + names[2]);
//    setText(t3, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 0);
//    // 4. 
//    t4.setFont(Font);
//    t4.setCharacterSize(18);
//    t4.setStyle(sf::Text::Bold);
//    t4.setFillColor(sf::Color::White);
//    t4.setString("4.\t" + timesLB[3] + "\t" + names[3]);
//    setText(t4, (float)widthLB / 2.0f, (float)heightLB / 2.0f + 30);
//    // 5. 
//    t5.setFont(Font);
//    t5.setCharacterSize(18);
//    t5.setStyle(sf::Text::Bold);
//    t5.setFillColor(sf::Color::White);
//    t5.setString("5.\t" + timesLB[4] + "\t" + names[4]);
//    setText(t5, (float)widthLB / 2.0f, (float)heightLB / 2.0f + 60);
//
//    // leaderboard window while loop
//    while (leaderWindow.isOpen())
//    {
//
//
//        sf::Event event;
//        while (leaderWindow.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                leaderWindow.close();
//
//            }
//        }
//        leaderWindow.clear(sf::Color::Blue);
//        leaderWindow.draw(Text1);
//        leaderWindow.draw(t1);
//        leaderWindow.draw(t2);
//        leaderWindow.draw(t3);
//        leaderWindow.draw(t4);
//        leaderWindow.draw(t5);
//        leaderWindow.display();
//    }
//}

int main()
{
  
    ifstream readFile;
    readFile.open("files/board_config.cfg");
    string line;
    getline(readFile, line, '\n');
    int col = stoi(line);
    getline(readFile, line, '\n');
    int row = stoi(line);
    getline(readFile, line, '\n');
    int numMines = stoi(line);


    Board gameBoard;
    gameBoard.SetCols(col);
    gameBoard.SetRows(row);
    gameBoard.SetMineNum(numMines);

    // WELCOME WINDOW dimensions
    int welcomeWidth = 800;
    int welcomeHeight = 600;
 
    // clockog = clock running the whole game
    auto clockog = chrono::high_resolution_clock::now();

    // clockNew = clock running only when game is paused
    auto clockNew = chrono::high_resolution_clock::now();
    auto clock2Dur = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - clockNew).count();

    // map for digits -> CREDIT TA MADDIE FOR DEMO (THIS clockNums map IS HEAVILY INFLUENCED BY HER DEMO)
    map<int, sf::Sprite> clockNums;

    sf::Texture digitsText;
    digitsText.loadFromFile("files/images/digits.png");
    sf::Sprite digits;
    digits.setTexture(digitsText);

    sf::IntRect zeroRect(0, 0, 21, 32);
    digits.setTextureRect(zeroRect);
    sf::Sprite zero = digits;
    clockNums.emplace(0, zero);

    sf::IntRect oneRect(21, 0, 21, 32);
    digits.setTextureRect(oneRect);
    sf::Sprite one = digits;
    clockNums.emplace(1, one);

    sf::IntRect twoRect(42, 0, 21, 32);
    digits.setTextureRect(twoRect);
    sf::Sprite two = digits;
    clockNums.emplace(2, two);

    sf::IntRect threeRect(63, 0, 21, 32);
    digits.setTextureRect(threeRect);
    sf::Sprite three = digits;
    clockNums.emplace(3, three);

    sf::IntRect fourRect(84, 0, 21, 32);
    digits.setTextureRect(fourRect);
    sf::Sprite four = digits;
    clockNums.emplace(4, four);

    sf::IntRect fiveRect(105, 0, 21, 32);
    digits.setTextureRect(fiveRect);
    sf::Sprite five = digits;
    clockNums.emplace(5, five);

    sf::IntRect sixRect(126, 0, 21, 32);
    digits.setTextureRect(sixRect);
    sf::Sprite six = digits;
    clockNums.emplace(6, six);

    sf::IntRect sevenRect(147, 0, 21, 32);
    digits.setTextureRect(sevenRect);
    sf::Sprite seven = digits;
    clockNums.emplace(7, seven);

    sf::IntRect eightRect(168, 0, 21, 32);
    digits.setTextureRect(eightRect);
    sf::Sprite eight = digits;
    clockNums.emplace(8, eight);

    sf::IntRect nineRect(189, 0, 21, 32);
    digits.setTextureRect(nineRect);
    sf::Sprite nine = digits;
    clockNums.emplace(9, nine);

    bool tfClock = false;

    while (true)
    {

        sf::RenderWindow welcomeWindow(sf::VideoMode(welcomeWidth, welcomeHeight), "Welcome Window", sf::Style::Close);

        cout << "welcome window open!" << endl;

        // "WELCOME TO MINESWEEPER!"
        sf::Font Font;
        sf::Text Text1;
        Font.loadFromFile("files/font.ttf");
        Text1.setFont(Font);
        Text1.setCharacterSize(24);
        Text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
        Text1.setFillColor(sf::Color(255, 255, 255));
        Text1.setString("WELCOME TO MINESWEEPER!");
        setText(Text1, welcomeWidth / 2.0f, welcomeHeight / 2.0f - 150);

        // "Enter your name:"
        sf::Text Text2;
        Text2.setFont(Font);
        Text2.setCharacterSize(20);
        Text2.setStyle(sf::Text::Bold);
        Text2.setFillColor(sf::Color(255, 255, 255));
        Text2.setString("Enter your name:");
        setText(Text2, welcomeWidth / 2.0f, welcomeHeight / 2.0f - 75);

        // "|" to track user-inputted name
        sf::Text Text3;
        Text3.setFont(Font);
        Text3.setCharacterSize(18);
        Text3.setStyle(sf::Text::Bold);
        Text3.setFillColor(sf::Color::Yellow);
        Text3.setString("|");
        setText(Text3, welcomeWidth / 2.0f, welcomeHeight / 2.0f - 45);

        string userName;

        // while WELCOME WINDOW is open

        while (welcomeWindow.isOpen())
        {
            sf::Event event;
            while (welcomeWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    welcomeWindow.close();
                    return 0;
                }

                if (event.type == sf::Event::TextEntered)
                {
                    if (isalpha(event.text.unicode))
                    {
                        if (userName.length() < 11)
                        {
                            if (userName.length() == 0)
                            {
                                userName += toupper(event.text.unicode);
                                Text3.setString(userName + "|");
                                setText(Text3, welcomeWidth / 2.0f, welcomeHeight / 2.0f - 45);
                                cout << "| moved over successfully" << endl;
                            }
                            else if (userName.length() <= 9)
                            {
                                userName += tolower(event.text.unicode);
                                Text3.setString(userName + "|");
                                setText(Text3, welcomeWidth / 2.0f, welcomeHeight / 2.0f - 45);
                                cout << "| moved over successfully" << endl;
                            }
                            cout << "user name: " << userName << endl;
                        }
                        else
                        {
                            userName.erase(userName.length() - 1, 1);
                            cout << "name was more than 10 chars" << endl;
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Backspace)
                    {
                        cout << "key was hit" << endl;
                        userName.erase(userName.length() - 1, 1);
                        Text3.setString(userName + "|");
                        setText(Text3, welcomeWidth / 2.0f, welcomeHeight / 2.0f - 45);
                    }

                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        cout << "Enter was hit" << endl;
                        if (userName.length() != 0)
                        {
                            welcomeWindow.close();
                            break;
                        }
                        else
                        {
                            cout << "no name was entered" << endl;
                        }
                    }
                }
            }
            welcomeWindow.clear(sf::Color(0, 0, 255, 255));
            welcomeWindow.draw(Text1);
            welcomeWindow.draw(Text2);
            welcomeWindow.draw(Text3);
            welcomeWindow.display();
        }

        sf::RenderWindow window(VideoMode(col * 32, (row * 32) + 100), "Minesweeper", sf::Style::Close);

        Tile** tiles = new Tile * [row];
        for (int r = 0; r < row; r++)
            tiles[r] = new Tile[col];


        Tile** revealedTiles = new Tile * [row];
        for (int r = 0; r < row; r++)
        {
            revealedTiles[r] = new Tile[col];
            for (int c = 0; c < col; c++)
            {
                revealedTiles[r][c].SetSprite("tile_revealed");
            }
        }

        Mine* mines = new Mine[numMines];

        char** store = new char* [row];
        for (int r = 0; r < row; r++)
            store[r] = new char[col];

        Event event;
       
        vector<Board_Nums> bNumVect;
        vector<Flag> flagVect;
        vector<Counter> counterVect;
        vector<Button> buttonVect;
                
        gameBoard.BuildButtons(buttonVect);
        gameBoard.BuildCounter(counterVect);
        gameBoard.SetTPos(tiles);
        gameBoard.Linked(tiles);
        gameBoard.SetMPos(tiles, mines);
        gameBoard.SetNumb(bNumVect, tiles);

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }                
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (!gameBoard.TF_Paused())
                    {
                        if (Mouse::isButtonPressed(Mouse::Left)) {

                            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                            for (int r = 0; r < row; r++) {
                                for (int c = 0; c < col; c++) {
                                    if (tiles[r][c].tile.getGlobalBounds().contains(mousePos) && !tiles[r][c].TF_Flag() && gameBoard.TF_GameState()) {
                                        tiles[r][c].RevealTile();
                                        if (tiles[r][c].TF_Mine())
                                            gameBoard.End();
                                        else
                                            tiles[r][c].RevealNeighbors();
                                    }
                                }
                            }

                            //Happy face
                            if (buttonVect[1].GetSprite().getGlobalBounds().contains(mousePos)) {
                                gameBoard.NewBoard(bNumVect, flagVect, tiles, mines);
                            }
                            //debugMode
                            else if (buttonVect[3].GetSprite().getGlobalBounds().contains(mousePos) && !gameBoard.TF_DebugMode())
                            {
                                gameBoard.NewDebug(true);
                            }
                            else if (buttonVect[3].GetSprite().getGlobalBounds().contains(mousePos) && gameBoard.TF_DebugMode())
                            {
                                gameBoard.NewDebug(false);
                            }

                            // pause button
                            else if (buttonVect[4].GetSprite().getGlobalBounds().contains(mousePos) && !gameBoard.TF_Paused() && gameBoard.TF_GameState())
                            {
                                // START CLOCK
                                tfClock = !tfClock;

                                // when game is paused
                                if (tfClock)
                                {
                                    clockNew = chrono::high_resolution_clock::now();
                                }
                                // when game isn't paused ("play")
                                else
                                {
                                    auto clockPause = chrono::steady_clock::now();
                                    clock2Dur += chrono::duration_cast<chrono::seconds>(clockPause - clockNew).count();
                                }

                               cout << "paused1" << endl;

                                gameBoard.SwitchPause();

                                cout << "Here1: " << gameBoard.TF_Paused() << endl;

                                gameBoard.PlayToPause(buttonVect);

                                if (gameBoard.TF_Paused())
                                {
                                    for (int r = 0; r < row; r++) {
                                        for (int c = 0; c < col; c++) {
                                            revealedTiles[r][c].SetPosition(c * 32, r * 32);
                                            revealedTiles[r][c].SwitchReveal();
                                        }
                                    }
                                }
                            }
                            // play button
                            else if (buttonVect[4].GetSprite().getGlobalBounds().contains(mousePos) && gameBoard.TF_Paused() && gameBoard.TF_GameState())
                            {
                                cout << "play1" << endl;

                                gameBoard.SwitchPause();

                                cout << "Here2: " << gameBoard.TF_Paused() << endl;
                                
                                gameBoard.PauseToPlay(buttonVect);

                            }
                            else if (buttonVect[5].GetSprite().getGlobalBounds().contains(mousePos))
                            {
                                cout << "entering code 1??" << endl;

                                gameBoard.SwitchPause();
                                gameBoard.PlayToPause(buttonVect);
                                
                                // START CLOCK
                                tfClock = !tfClock;

                                // when game is paused
                                if (tfClock)
                                {
                                    clockNew = chrono::high_resolution_clock::now();
                                }
                                // when game isn't paused ("play")
                                else
                                {
                                    auto clockPaused = chrono::steady_clock::now();
                                    clock2Dur += chrono::duration_cast<chrono::seconds>(clockPaused - clockNew).count();
                                }
                                
                                ifstream readFile;
                                readFile.open("files/board_config.cfg");
                                string line;
                                getline(readFile, line, '\n');
                                int width = stoi(line);
                                getline(readFile, line, '\n');
                                int height = stoi(line);

                                int widthLB = width * 16;
                                int heightLB = (height * 16) + 50;

                                vector<string> names;
                                vector<string> timesLB;

                                sf::RenderWindow leaderWindow(sf::VideoMode(widthLB, heightLB), "Leaderboard", sf::Style::Close);

                                // "LEADERBOARD"
                                //cout << "leaderboard button pressed" << endl;
                                // all tiles display "tile_revealed.png"
                                // "LEADERBOARD"

                                sf::Font Font;
                                sf::Text Text1;
                                Font.loadFromFile("files/font.ttf");
                                Text1.setFont(Font);
                                Text1.setCharacterSize(20);
                                Text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
                                Text1.setFillColor(sf::Color(255, 255, 255));
                                Text1.setString("LEADERBOARD");
                                setText(Text1, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 120);

                                /*fstream readFile("files/leaderboard.txt");
                                if (!readFile.is_open())
                                {
                                    cout << "error: file isn't open" << endl;
                                }*/

                                for (int i = 0; i < 5; i++)
                                {
                                    getline(readFile, line, ',');
                                    timesLB.push_back(line);
                                    getline(readFile, line, '\n');
                                    names.push_back(line);
                                }

                                sf::Text first;
                                sf::Text second;
                                sf::Text third;
                                sf::Text fourth;
                                sf::Text fifth;

                                // 1. 
                                first.setFont(Font);
                                first.setCharacterSize(18);
                                first.setStyle(sf::Text::Bold);
                                first.setFillColor(sf::Color::White);
                                first.setString("1.\t" + timesLB[0] + "\t" + names[0]);
                                //first.setPosition((float)widthLB / 2.0f - 110, (float)heightLB / 2.0f - 60);
                                setText(first, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 60);
                                // 2. 
                                second.setFont(Font);
                                second.setCharacterSize(18);
                                second.setStyle(sf::Text::Bold);
                                second.setFillColor(sf::Color::White);
                                second.setString("2.\t" + timesLB[1] + "\t" + names[1]);
                                setText(second, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 30);
                                // 3. 
                                third.setFont(Font);
                                third.setCharacterSize(18);
                                third.setStyle(sf::Text::Bold);
                                third.setFillColor(sf::Color::White);
                                third.setString("3.\t" + timesLB[2] + "\t" + names[2]);
                                setText(third, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 0);
                                // 4. 
                                fourth.setFont(Font);
                                fourth.setCharacterSize(18);
                                fourth.setStyle(sf::Text::Bold);
                                fourth.setFillColor(sf::Color::White);
                                fourth.setString("4.\t" + timesLB[3] + "\t" + names[3]);
                                setText(fourth, (float)widthLB / 2.0f, (float)heightLB / 2.0f + 30);
                                // 5. 
                                fifth.setFont(Font);
                                fifth.setCharacterSize(18);
                                fifth.setStyle(sf::Text::Bold);
                                fifth.setFillColor(sf::Color::White);
                                fifth.setString("5.\t" + timesLB[4] + "\t" + names[4]);
                                setText(fifth, (float)widthLB / 2.0f, (float)heightLB / 2.0f + 60);

                                // leaderboard window while loop
                                while (leaderWindow.isOpen())
                                {

                                    sf::Event event;
                                    while (leaderWindow.pollEvent(event))
                                    {
                                        if (event.type == sf::Event::Closed)
                                        {
                                            leaderWindow.close();
                                            gameBoard.SwitchPause();
                                            gameBoard.PauseToPlay(buttonVect);
 
                                        }
                                    }
                                    leaderWindow.clear(sf::Color::Blue);
                                    leaderWindow.draw(Text1);
                                    leaderWindow.draw(first);
                                    leaderWindow.draw(second);
                                    leaderWindow.draw(third);
                                    leaderWindow.draw(fourth);
                                    leaderWindow.draw(fifth);
                                    leaderWindow.display();
                                }
                                gameBoard.SwitchPause();
                                gameBoard.PauseToPlay(buttonVect);
                            }
                        }

                        //Flag a Tile
                        if (Mouse::isButtonPressed(Mouse::Right)) {
                            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                            for (int r = 0; r < row; r++) {
                                for (int c = 0; c < col; c++) {
                                    if (tiles[r][c].tile.getGlobalBounds().contains(mousePos) && !tiles[r][c].TF_Flag() && !tiles[r][c].TF_Open() && gameBoard.TF_GameState())
                                        gameBoard.InsertFlag(flagVect, tiles[r][c]);
                                    else if (tiles[r][c].tile.getGlobalBounds().contains(mousePos) && !tiles[r][c].TF_Open() && tiles[r][c].TF_Flag() && gameBoard.TF_GameState())
                                        gameBoard.EraseFlag(flagVect, tiles[r][c]);
                                }
                            }
                        }
                        break;
                    }

                    //{
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        //Happy face is clicked
                        if (buttonVect[1].GetSprite().getGlobalBounds().contains(mousePos)) {
                            gameBoard.NewBoard(bNumVect, flagVect, tiles, mines);
                        }
                        // pause button
                        else if (buttonVect[4].GetSprite().getGlobalBounds().contains(mousePos) && !gameBoard.TF_Paused())
                        {
                            cout << "paused2" << endl;

                            gameBoard.SwitchPause();
                            

                            cout << "Here3: " << gameBoard.TF_Paused() << endl;

                            gameBoard.PlayToPause(buttonVect);
                        }
                        // play button
                        else if (buttonVect[4].GetSprite().getGlobalBounds().contains(mousePos) && gameBoard.TF_Paused())
                        {
                            // START CLOCK
                            tfClock = !tfClock;

                            // when game is paused
                            if (tfClock)
                            {
                                clockNew = chrono::high_resolution_clock::now();
                            }
                            // when game isn't paused ("play")
                            else
                            {
                                auto clockPaused = chrono::steady_clock::now();
                                clock2Dur += chrono::duration_cast<chrono::seconds>(clockPaused - clockNew).count();
                            }

                            gameBoard.SwitchPause();

                            gameBoard.PauseToPlay(buttonVect);

                            cout << "play2" << endl;

                            cout << "Here4: " << gameBoard.TF_Paused() << endl;

                            for (int r = 0; r < row; r++) {
                                for (int c = 0; c < col; c++) {
                                    revealedTiles[r][c].TF_Reveal();
                                }
                            }

                            // display overlayed "fake" tiles
                            if (gameBoard.TF_Paused())
                            {
                                for (int r = 0; r < row; r++) {
                                    for (int c = 0; c < col; c++) {
                                        revealedTiles[r][c].SetPosition(c * 32, r * 32);
                                        revealedTiles[r][c].TF_Reveal();
                                    }
                                }
                            }
                        }
                        //// Leaderboard button is clicked
                        //else if (buttons[5].GetSprite().getGlobalBounds().contains(mousePos))
                        //{
                        //    cout << "entering code 2??" << endl;
                        //    //// START CLOCK
                        //    //tfClock = !tfClock;
                        //
                        //    //// when game is paused
                        //    //if (tfClock)
                        //    //{
                        //    //    clock2 = chrono::high_resolution_clock::now();
                        //    //}
                        //    //// when game isn't paused ("play")
                        //    //else
                        //    //{
                        //    //    auto clock3 = chrono::steady_clock::now();
                        //    //    clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                        //    //}
                        //    
                        //    //OpenLeaderBoard(row, col, gameBoard, buttons);
                        //    //Read Config.cfg file
                        //    ifstream cfg;
                        //    cfg.open("files/board_config.cfg");
                        //    string line;
                        //    getline(cfg, line, '\n');
                        //    int width = stoi(line);
                        //    getline(cfg, line, '\n');
                        //    int height = stoi(line);
                        //
                        //    int widthLB = width * 16;
                        //    int heightLB = (height * 16) + 50;
                        //
                        //    vector<string> names;
                        //    vector<string> timesLB;
                        //
                        //    sf::RenderWindow leaderWindow(sf::VideoMode(widthLB, heightLB), "Leaderboard", sf::Style::Close);
                        //
                        //    // "LEADERBOARD"
                        //    //cout << "leaderboard button pressed" << endl;
                        //    // all tiles display "tile_revealed.png"
                        //    // "LEADERBOARD"
                        //
                        //    sf::Font Font;
                        //    sf::Text Text1;
                        //    Font.loadFromFile("files/font.ttf");
                        //    Text1.setFont(Font);
                        //    Text1.setCharacterSize(20);
                        //    Text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
                        //    Text1.setFillColor(sf::Color(255, 255, 255));
                        //    Text1.setString("LEADERBOARD");
                        //    setText(Text1, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 120);
                        //
                        //    fstream readFile("files/leaderboard.txt");
                        //    if (!readFile.is_open())
                        //    {
                        //        cout << "error: file isn't open" << endl;
                        //    }
                        //
                        //    for (int i = 0; i < 5; i++)
                        //    {
                        //        getline(readFile, line, ',');
                        //        timesLB.push_back(line);
                        //        getline(readFile, line, '\n');
                        //        names.push_back(line);
                        //    }
                        //
                        //    sf::Text first;
                        //    sf::Text second;
                        //    sf::Text third;
                        //    sf::Text fourth;
                        //    sf::Text fifth;
                        //
                        //    // 1. 
                        //    first.setFont(Font);
                        //    first.setCharacterSize(18);
                        //    first.setStyle(sf::Text::Bold);
                        //    first.setFillColor(sf::Color::White);
                        //    first.setString("1.\t" + timesLB[0] + "\t" + names[0]);
                        //    //first.setPosition((float)widthLB / 2.0f - 110, (float)heightLB / 2.0f - 60);
                        //    setText(first, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 60);
                        //    // 2. 
                        //    second.setFont(Font);
                        //    second.setCharacterSize(18);
                        //    second.setStyle(sf::Text::Bold);
                        //    second.setFillColor(sf::Color::White);
                        //    second.setString("2.\t" + timesLB[1] + "\t" + names[1]);
                        //    setText(second, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 30);
                        //    // 3. 
                        //    third.setFont(Font);
                        //    third.setCharacterSize(18);
                        //    third.setStyle(sf::Text::Bold);
                        //    third.setFillColor(sf::Color::White);
                        //    third.setString("3.\t" + timesLB[2] + "\t" + names[2]);
                        //    setText(third, (float)widthLB / 2.0f, (float)heightLB / 2.0f - 0);
                        //    // 4. 
                        //    fourth.setFont(Font);
                        //    fourth.setCharacterSize(18);
                        //    fourth.setStyle(sf::Text::Bold);
                        //    fourth.setFillColor(sf::Color::White);
                        //    fourth.setString("4.\t" + timesLB[3] + "\t" + names[3]);
                        //    setText(fourth, (float)widthLB / 2.0f, (float)heightLB / 2.0f + 30);
                        //    // 5. 
                        //    fifth.setFont(Font);
                        //    fifth.setCharacterSize(18);
                        //    fifth.setStyle(sf::Text::Bold);
                        //    fifth.setFillColor(sf::Color::White);
                        //    fifth.setString("5.\t" + timesLB[4] + "\t" + names[4]);
                        //    setText(fifth, (float)widthLB / 2.0f, (float)heightLB / 2.0f + 60);
                        //
                        //    // leaderboard window while loop
                        //    while (leaderWindow.isOpen())
                        //    {
                        //        //gameBoard.ChangePauseBool();
                        //        //gameBoard.ChangeToPause(buttons);
                        //
                        //        sf::Event event;
                        //        while (leaderWindow.pollEvent(event))
                        //        {
                        //            if (event.type == sf::Event::Closed)
                        //            {
                        //                leaderWindow.close();
                        //                //gameBoard.ChangePauseBool();
                        //                //gameBoard.ChangeToPlay(buttons);
                        //            }
                        //        }
                        //        leaderWindow.clear(sf::Color::Blue);
                        //        leaderWindow.draw(Text1);
                        //        leaderWindow.draw(first);
                        //        leaderWindow.draw(second);
                        //        leaderWindow.draw(third);
                        //        leaderWindow.draw(fourth);
                        //        leaderWindow.draw(fifth);
                        //        leaderWindow.display();
                        //    }
                        //    gameBoard.ChangeToPause(buttons);
                        //    gameBoard.ChangePauseBool();
                        //
                        //}
                    }                   
                }
            } // while gameWindow / window is_open()

            //Draw the Tiles according to what is clicked up above
            window.clear(sf::Color::White);
            gameBoard.DrawBoard(window, tiles, mines, bNumVect, flagVect, counterVect, buttonVect, gameBoard.TF_GameState(), gameBoard.TF_DebugMode());
            gameBoard.DrawRevealed(window, revealedTiles, gameBoard.TF_GameState());
           
            auto clock1Dur = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - clockog);
            int realTime = clock1Dur.count();

            int mins = 0;
            int secs = 0;

            if (!tfClock)
            {
                realTime = realTime - clock2Dur;
                mins = realTime / 60;
                secs = realTime % 60;
            }

            int digit0 = mins / 10 % 10;
            int digit1 = mins % 10;
            int digit2 = secs / 10 % 10;
            int digit3 = secs % 10;

            clockNums[digit0].setPosition((col * 32) - 97, 32 * (row + 0.5f) + 16);
            window.draw(clockNums[digit0]);

            clockNums[digit1].setPosition((col * 32) - 76, 32 * (row + 0.5f) + 16);
            window.draw(clockNums[digit1]);

            clockNums[digit2].setPosition((col * 32) - 54, 32 * (row + 0.5f) + 16);
            window.draw(clockNums[digit2]);

            clockNums[digit3].setPosition((col * 32) - 33, 32 * (row + 0.5f) + 16);
            window.draw(clockNums[digit3]);
            
            window.display();
        }
    } // while(true)
    FilePaths::Clear();
    return 0;
}


