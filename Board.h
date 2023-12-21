// BOARD.H

#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include "Tile.h"
#include "Mine.h"
#include "Button.h"
#include "Board_Nums.h"
#include "Counter.h"
#include "Flag.h"
#include "Random_Num_Gen.h"

class Board {
	bool tfRunMode;
	bool tfDebugMode;
	bool tfPaused;
	bool tfLB;
	int mineNum;
	int row;
	int col;
	

public:
	/*Board();
	void SetColumns(int);
	void SetRows(int);
	void SetNumMines(int);
	void StartGame();
	void EndGame();
	void DrawTiles(sf::RenderWindow& window, Tile** (&t), Mine* (&m), std::vector<Board_Nums>&, std::vector<Flag>&, std::vector<Counter>&, std::vector<Button>&, bool, bool);
	void LinkTiles(Tile** (&t));
	void SetTilePositions(Tile** (&t));
	void SetMinePositions(Tile** (&t), Mine* (&m));
	void SetNumbers(std::vector<Board_Nums>&, Tile** (&t));
	void AddFlag(std::vector<Flag>&, Tile(&t));
	void RemoveFlag(std::vector<Flag>&, Tile(&t));
	void CreateCounter(std::vector<Counter>&);
	void CreateButtons(std::vector<Button>&);
	void ChangeToPause(std::vector<Button>& buttons);
	void ChangeToPlay(std::vector<Button>& buttons);
	void ChangePauseBool();
	void SetBoard(std::vector<Board_Nums>&, std::vector<Flag>&, Tile** (&t), Mine* (&m));
	void SetDebugMode(bool);
	void DrawRevealedTiles(sf::RenderWindow& window, Tile** (&rt), bool);

	bool GetGameState();
	bool GetIsPaused();
	bool CheckMineDuplicates(std::vector<int>& randWidth, std::vector<int>& randHeight);
	bool GetDebugMode();
	bool CheckWin(Tile** (&t), Mine* (&m), std::vector<Flag>&);

	int CheckMinePosition(Tile(&t), Mine* (&m));*/

	Board();

	void SetCols(int cols);
	void SetRows(int rows);
	void SetMineNum(int mines);
	void Start();
	void End();
	void DrawBoard(sf::RenderWindow& windowName, Tile** (&tiles), Mine* (&mines), std::vector<Board_Nums>& bNumVect, std::vector<Flag>& flagVect, std::vector<Counter>& counterVect, std::vector<Button>& buttonVect, bool contGame, bool tfDebugMode);
	void Linked(Tile** (&tiles));
	void SetTPos(Tile** (&tiles));
	void SetMPos(Tile** (&tiles), Mine* (&mines));
	void SetNumb(std::vector<Board_Nums>&, Tile** (&tiles));
	void InsertFlag(std::vector<Flag>&, Tile(&tiles));
	void EraseFlag(std::vector<Flag>&, Tile(&tiles));
	void BuildCounter(std::vector<Counter>& counterVect);
	void BuildButtons(std::vector<Button>& buttonVect);
	void PlayToPause(std::vector<Button>& buttonVect);
	void PauseToPlay(std::vector<Button>& buttonVect);
	void SwitchPause();
	void NewBoard(std::vector<Board_Nums>&, std::vector<Flag>&, Tile** (&tiles), Mine* (&mines));
	void NewDebug(bool tfDebug2);
	void DrawRevealed(sf::RenderWindow& windowName, Tile** (&revealedTs), bool);
	void SwitchLB();

	bool TF_GameState();
	bool TF_Paused();
	bool TF_MineDups(std::vector<int>& newWidth, std::vector<int>& newHeight);
	bool TF_DebugMode();
	bool TF_Win(Tile** (&tiles), Mine* (&mines), std::vector<Flag>&);
	bool TF_LB();

	int CheckMinePosition(Tile(&tiles), Mine* (&mines));
};