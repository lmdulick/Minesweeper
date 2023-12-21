// BOARD.CPP

#include "Board.h"
using namespace std;

//Builds the default Board
Board::Board() {
	tfRunMode = true;
	tfDebugMode = false;
	tfPaused = false;
	tfLB = false;
	mineNum = 0;
	row = 0;
	col = 0;
	
}

void Board::SetCols(int cols) {
	col = cols;
}

void Board::SetRows(int rows) {
	row = rows;
}

void Board::SetMineNum(int mines) {
	mineNum = mines;
}

void Board::Start() {
	this->tfRunMode = true;
}

void Board::End() {
	this->tfRunMode = false;
}

void Board::DrawBoard(sf::RenderWindow& windowName, Tile** (&tiles), Mine* (&mines), vector<Board_Nums>& bNumVect, vector<Flag>& flagVect, vector<Counter>& counterVect, vector<Button>& buttonVect, bool contGame, bool tfDebugMode) {
	int index = 0;
	if (contGame) {
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < col; c++) {
				index = CheckMinePosition(tiles[r][c], mines);
				if (index != -1 && tiles[r][c].TF_Open()) {
					windowName.draw(tiles[r][c].GetSprite());
					windowName.draw(mines[index].GetSprite());
				}
				else {
					windowName.draw(tiles[r][c].GetSprite());
					for (unsigned int n = 0; n < bNumVect.size(); n++) {
						if (tiles[r][c].TF_Open()) {
							if (bNumVect[n].tile.getPosition().x == tiles[r][c].tile.getPosition().x && bNumVect[n].tile.getPosition().y == tiles[r][c].tile.getPosition().y)
								windowName.draw(bNumVect[n].GetSprite());
						}
					}
				}
			}
		}
		if (TF_Win(tiles, mines, flagVect))
			windowName.draw(buttonVect[2].GetSprite());
		if (!TF_Win(tiles, mines, flagVect))
			windowName.draw(buttonVect[0].GetSprite());
	}
	if (!contGame || tfDebugMode) {
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < col; c++) {
				index = CheckMinePosition(tiles[r][c], mines);
				if (index != -1) {
					windowName.draw(tiles[r][c].GetSprite());
					windowName.draw(mines[index].GetSprite());
				}
				else {
					windowName.draw(tiles[r][c].GetSprite());
					for (unsigned int n = 0; n < bNumVect.size(); n++) {
						if (tiles[r][c].TF_Open()) {
							if (bNumVect[n].tile.getPosition().x == tiles[r][c].tile.getPosition().x && bNumVect[n].tile.getPosition().y == tiles[r][c].tile.getPosition().y)
								windowName.draw(bNumVect[n].GetSprite());
						}
					}
				}
			}
		}
		if (!contGame)
			windowName.draw(buttonVect[1].GetSprite());
		if (TF_Win(tiles, mines, flagVect))
			windowName.draw(buttonVect[2].GetSprite());
	}
	for (unsigned int i = 0; i < flagVect.size(); i++)
		windowName.draw(flagVect[i].GetSprite());
	// POSITIVE flags
	if (flagVect.size() <= (unsigned)mineNum) {
		index = mineNum - flagVect.size();
		// counterVect[0] == FIRST NUM
		counterVect[0].SetPosition(33, 32 * ((float)row + 0.5f) + 16);
		windowName.draw(counterVect[0].GetSprite());
		// counterVect[index / 10] == SECOND NUM
		counterVect[index / 10].SetPosition(54, 32 * ((float)row + 0.5f) + 16);
		windowName.draw(counterVect[index / 10].GetSprite());
		// counterVect[index % 10] == THIRD NUM
		counterVect[index % 10].SetPosition(75, 32 * ((float)row + 0.5f) + 16);
		windowName.draw(counterVect[index % 10].GetSprite());
	}
	// NEGATIVE flags
	else if (flagVect.size() > (unsigned)mineNum) {
		counterVect[10].SetPosition(12, 32 * ((float)row + 0.5f) + 16);
		windowName.draw(counterVect[10].GetSprite());
		index = flagVect.size() - mineNum;
		if (index >= mineNum * 2) {
			counterVect[index / 100].SetPosition(33, 32 * ((float)row + 0.5f) + 16);
			windowName.draw(counterVect[index / 100].GetSprite());
			counterVect[(index / 10) % 10].SetPosition(54, 32 * ((float)row + 0.5f) + 16);
			windowName.draw(counterVect[(index / 10) % 10].GetSprite());
			counterVect[index % 10].SetPosition(75, 32 * ((float)row + 0.5f) + 16);
			windowName.draw(counterVect[index % 10].GetSprite());
		}
		else {
			counterVect[0].SetPosition(33, 32 * ((float)row + 0.5f) + 16);
			windowName.draw(counterVect[0].GetSprite());
			counterVect[index / 10].SetPosition(54, 32 * ((float)row + 0.5f) + 16);
			windowName.draw(counterVect[index / 10].GetSprite());
			counterVect[index % 10].SetPosition(75, 32 * ((float)row + 0.5f) + 16);
			windowName.draw(counterVect[index % 10].GetSprite());
		}
	}
	windowName.draw(buttonVect[3].GetSprite());
	windowName.draw(buttonVect[4].GetSprite());
	windowName.draw(buttonVect[5].GetSprite());
}

void Board::DrawRevealed(sf::RenderWindow& windowName, Tile** (&revealedTs), bool contGame)
{
	if (contGame) {
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < col; c++) {
				if (revealedTs[r][c].TF_Reveal()) {
					windowName.draw(revealedTs[r][c].GetSprite());
				}
			}
		}
	}
}

void Board::Linked(Tile** (&tiles)) {
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			if (r == 0) {
				tiles[r][c].neighbors[0] = nullptr;
				tiles[r][c].neighbors[1] = nullptr;
				tiles[r][c].neighbors[7] = nullptr;
				if (c == 0) {
					tiles[r][c].neighbors[2] = &tiles[0][1];
					tiles[r][c].neighbors[3] = &tiles[1][1];
					tiles[r][c].neighbors[4] = &tiles[1][0];
					tiles[r][c].neighbors[5] = nullptr;
					tiles[r][c].neighbors[6] = nullptr;
				}
				if (c != 0 && c != col - 1) {
					tiles[r][c].neighbors[2] = &tiles[r][c + 1];
					tiles[r][c].neighbors[3] = &tiles[r + 1][c + 1];
					tiles[r][c].neighbors[4] = &tiles[r + 1][c];
					tiles[r][c].neighbors[5] = &tiles[r + 1][c - 1];
					tiles[r][c].neighbors[6] = &tiles[r][c - 1];
				}
				if (c == col - 1) {
					tiles[r][c].neighbors[6] = &tiles[r][c - 1];
					tiles[r][c].neighbors[5] = &tiles[r + 1][c - 1];
					tiles[r][c].neighbors[4] = &tiles[r + 1][c];
					tiles[r][c].neighbors[2] = nullptr;
					tiles[r][c].neighbors[3] = nullptr;
				}
			}
			else if (r != 0 && r != row - 1) {
				if (c == 0) {
					tiles[r][c].neighbors[0] = &tiles[r - 1][c];
					tiles[r][c].neighbors[1] = &tiles[r - 1][c + 1];
					tiles[r][c].neighbors[2] = &tiles[r][c + 1];
					tiles[r][c].neighbors[3] = &tiles[r + 1][c + 1];
					tiles[r][c].neighbors[4] = &tiles[r + 1][c];
					tiles[r][c].neighbors[5] = nullptr;
					tiles[r][c].neighbors[6] = nullptr;
					tiles[r][c].neighbors[7] = nullptr;
				}
				else if (c == col - 1) {
					tiles[r][c].neighbors[0] = &tiles[r - 1][c];
					tiles[r][c].neighbors[1] = nullptr;
					tiles[r][c].neighbors[2] = nullptr;
					tiles[r][c].neighbors[3] = nullptr;
					tiles[r][c].neighbors[4] = &tiles[r + 1][c];
					tiles[r][c].neighbors[5] = &tiles[r + 1][c - 1];
					tiles[r][c].neighbors[6] = &tiles[r][c - 1];
					tiles[r][c].neighbors[7] = &tiles[r - 1][c - 1];
				}
				else if (c != 0 && c != col - 1) {
					tiles[r][c].neighbors[0] = &tiles[r - 1][c];
					tiles[r][c].neighbors[1] = &tiles[r - 1][c + 1];
					tiles[r][c].neighbors[2] = &tiles[r][c + 1];
					tiles[r][c].neighbors[3] = &tiles[r + 1][c + 1];
					tiles[r][c].neighbors[4] = &tiles[r + 1][c];
					tiles[r][c].neighbors[5] = &tiles[r + 1][c - 1];
					tiles[r][c].neighbors[6] = &tiles[r][c - 1];
					tiles[r][c].neighbors[7] = &tiles[r - 1][c - 1];
				}
			}
			else if (r == row - 1) {
				tiles[r][c].neighbors[3] = nullptr;
				tiles[r][c].neighbors[4] = nullptr;
				tiles[r][c].neighbors[5] = nullptr;
				if (c == 0) {
					tiles[r][c].neighbors[2] = &tiles[r][c + 1];
					tiles[r][c].neighbors[1] = &tiles[r - 1][c + 1];
					tiles[r][c].neighbors[0] = &tiles[r - 1][c];
					tiles[r][c].neighbors[6] = nullptr;
					tiles[r][c].neighbors[7] = nullptr;
				}
				if (c != 0 && c != col - 1) {
					tiles[r][c].neighbors[0] = &tiles[r - 1][c];
					tiles[r][c].neighbors[1] = &tiles[r - 1][c + 1];
					tiles[r][c].neighbors[2] = &tiles[r][c + 1];
					tiles[r][c].neighbors[6] = &tiles[r][c - 1];
					tiles[r][c].neighbors[7] = &tiles[r - 1][c - 1];

				}
				if (c == col - 1) {
					tiles[r][c].neighbors[0] = &tiles[r - 1][c];
					tiles[r][c].neighbors[7] = &tiles[r - 1][c - 1];
					tiles[r][c].neighbors[6] = &tiles[r][c - 1];
					tiles[r][c].neighbors[2] = nullptr;
					tiles[r][c].neighbors[1] = nullptr;
				}
			}
		}
	}
}

void Board::SetTPos(Tile** (&tiles)) {
	float x = 0.0f;
	float y = 0.0f;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			tiles[r][c].SetPosition(x, y);
			x += 32.0f;
		}
		x = 0;
		y += 32.0f;
	}
}

void Board::SetMPos(Tile** (&tiles), Mine* (&mines)) {
	vector<int> randWidth;
	vector<int> randHeight;
	for (int i = 0; i < mineNum; i++) {
		int height = Random_Num_Gen::IntegerNum(0, row - 1);
		randHeight.push_back(height);
		int width = Random_Num_Gen::IntegerNum(0, col - 1);
		randWidth.push_back(width);
	}
	if (TF_MineDups(randWidth, randHeight)) {
		randWidth.clear();
		randHeight.clear();
		SetMPos(tiles, mines);
	}
	else {
		for (int i = 0; i < mineNum; i++) {
			mines[i].SetPosition(tiles[randHeight[i]][randWidth[i]].tile.getPosition().x, tiles[randHeight[i]][randWidth[i]].tile.getPosition().y);
			tiles[randHeight[i]][randWidth[i]].SetMine();
		}
	}
}

int Board::CheckMinePosition(Tile(&tiles), Mine* (&mines)) {
	for (int i = 0; i < mineNum; i++) {
		if (tiles.tile.getPosition().x == mines[i].tile.getPosition().x && tiles.tile.getPosition().y == mines[i].tile.getPosition().y) {
			return i;
		}
	}
	return -1;
}

bool Board::TF_MineDups(vector<int>& newWidth, vector<int>& newHeight) {
	for (unsigned int i = 0; i < newHeight.size(); i++) {
		for (unsigned int j = i + 1; j < newHeight.size(); j++) {
			if (newHeight[i] == newHeight[j] && i != j) {
				if (newWidth[i] == newWidth[j]) {
					return true;
				}
			}
		}
	}
	return false;
}

void Board::SetNumb(vector<Board_Nums>& nums, Tile** (&tiles)) {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			count = tiles[i][j].CheckNeighborMines();
			if (count != 0) {
				if (!tiles[i][j].TF_Mine()) {
					Board_Nums n(count);
					n.SetPosition(tiles[i][j].tile.getPosition().x, tiles[i][j].tile.getPosition().y);
					nums.push_back(n);
				}
			}
		}
	}
}

void Board::InsertFlag(std::vector<Flag>& flags, Tile& tiles) {
	Flag flagObj;
	flagObj.SetPosition(tiles.tile.getPosition().x, tiles.tile.getPosition().y);
	flags.push_back(flagObj);
	tiles.SetFlag();
}

void Board::EraseFlag(std::vector<Flag>& flags, Tile& tiles) {
	for (unsigned int i = 0; i < flags.size(); i++) {
		if (flags[i].tile.getPosition().x == tiles.tile.getPosition().x && flags[i].tile.getPosition().y == tiles.tile.getPosition().y)
			flags.erase(flags.begin() + i);
	}
	tiles.EraseFlag();
}

void Board::BuildCounter(std::vector<Counter>& counterVect) {
	for (int i = 0; i <= 10; i++) {
		Counter c(i);
		counterVect.push_back(c);
	}
}

void Board::BuildButtons(std::vector<Button>& buttonVect) {
	Button b0("face_happy");
	b0.SetPosition((((float)col / 2.0)*32)-32, 32*((float)row + 0.5f));
	Button b1("face_lose");
	b1.SetPosition((((float)col / 2.0) * 32) - 32, 32 * ((float)row + 0.5f));
	Button b2("face_win");
	b2.SetPosition((((float)col / 2.0) * 32) - 32, 32 * ((float)row + 0.5f));
	Button b3("debug");
	b3.SetPosition(((float)col * 32) - 304, 32 * ((float)row + 0.5f));
	Button b4("play");
	b4.SetPosition(((float)col * 32) - 240, 32 * ((float)row + 0.5f));
	Button b5("leaderboard");
	b5.SetPosition(((float)col * 32) - 176, 32 * ((float)row + 0.5f));

	buttonVect.push_back(b0);
	buttonVect.push_back(b1);
	buttonVect.push_back(b2);
	buttonVect.push_back(b3);
	buttonVect.push_back(b4);
	buttonVect.push_back(b5);
}

void Board::PlayToPause(std::vector<Button>& buttonVect)
{
	Button b4("pause");
	b4.SetPosition(((float)col * 32) - 240, 32 * ((float)row + 0.5f));
	buttonVect[4] = b4;
}

void Board::PauseToPlay(std::vector<Button>& buttonVect)
{
	Button b4("play");
	b4.SetPosition(((float)col * 32) - 240, 32 * ((float)row + 0.5f));
	buttonVect[4] = b4;
}

bool Board::TF_GameState() {
	return this->tfRunMode;
}

bool Board::TF_Paused() {
	return this->tfPaused;
}

void Board::SwitchPause()
{
	tfPaused = !tfPaused;
}

//Resets the Board, then sets the Board with new vectors of Mines and Numbers and sets tfRunMode to true
void Board::NewBoard(std::vector<Board_Nums>& numbers, std::vector<Flag>& flags, Tile** (&tiles), Mine* (&mines)) {
	numbers.clear();
	flags.clear();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			tiles[i][j].ResetTile();
	}
	SetMPos(tiles, mines);
	SetNumb(numbers, tiles);
	Start();
}

void Board::NewDebug(bool tfDebug2) {
	this->tfDebugMode = tfDebug2;
}

void Board::SwitchLB()
{
	this->tfLB = !tfLB;
}

bool Board::TF_DebugMode() {
	return this->tfDebugMode;
}

bool Board::TF_Win(Tile** (&tiles), Mine* (&mines), vector<Flag>& flagVect) {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (tiles[i][j].TF_Open() && CheckMinePosition(tiles[i][j], mines) == -1)
				count++;
		}
	}
	if (count == (row * col) - mineNum) {
		flagVect.clear();
		for (int i = 0; i < mineNum; i++) {
			Flag flagObj;
			flagObj.SetPosition(mines[i].GetSprite().getPosition().x, mines[i].GetSprite().getPosition().y);
			flagVect.push_back(flagObj);
		}
		return true;
	}
	else {
		return false;
	}
}

bool Board::TF_LB()
{
	return tfLB;
}
