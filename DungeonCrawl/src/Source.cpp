#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;

char grid[10][10]{};
char player{ 'P' };
char trap{ 'T' };
char treasure{ 'X' };
char enemy{ 'E' };
int moves{ 0 };
bool gameOver{false};
int playerLoc[2];
vector<vector<int>> enemyLoc;

void generateGrid() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			grid[i][j] = '.';
		}
	}
}

void placeTraps(int trapAmount, int seed) {
	int trapX, trapY;
	for (int i = 0; i < trapAmount; i++) {
		trapX = rand() % 10; trapY = rand() % 10;

		while (grid[trapY][trapX] != '.') {
			trapX = rand() % 10;
			trapY = rand() % 10;
		}

		grid[trapY][trapX] = trap;
	}
}

void placeTreasure(int seed) {
	int treasureX, treasureY;
	
	treasureX = rand() % 10; treasureY = rand() % 10;

	while (grid[treasureY][treasureX] != '.') {
		treasureX = rand() % 10;
		treasureY = rand() % 10;
	}

	grid[treasureY][treasureX] = treasure;
}

void placePlayer(int seed) {
	int playerX, playerY;

	playerX = rand() % 10; playerY = rand() % 10;

	while (grid[playerY][playerX] != '.') {
		playerX = rand() % 10;
		playerY = rand() % 10;
	}

	grid[playerY][playerX] = player;
	playerLoc[0] = playerX;
	playerLoc[1] = playerY;
}

void placeEnemy(int enemyAmount, int seed) {
	int enemyX, enemyY;
	vector<int> enemy1Loc;
	for (int i = 0; i < enemyAmount; i++) {
		enemyX = rand() % 10; enemyY = rand() % 10;

		while (grid[enemyY][enemyX] != '.') {
			enemyX = rand() % 10;
			enemyY = rand() % 10;
		}

		grid[enemyY][enemyX] = enemy;
		
		enemy1Loc.push_back(enemyX);
		enemy1Loc.push_back(enemyY);

		enemyLoc.push_back(enemy1Loc);

		enemy1Loc.clear();
	}
}

void printGrid() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
}

bool checkLoss(int playerX, int playerY) {
	if (grid[playerY][playerX] == 'T') {
		return true;
	} else if (grid[playerY][playerX] == 'E') {
		return true;
	}

	return false;
}

bool checkWin(int playerX, int playerY) {
	if (grid[playerY][playerX] == 'X') {
		return true;
	}

	return false;
}

int movePlayer(char direction) {
	int playerX = playerLoc[0], playerY = playerLoc[1];
	
	switch (direction) {
		case 'U':
			playerY -= 1;
			break;
		case 'D':
			playerY += 1;
			break;
		case 'L':
			playerX -= 1;
			break;
		case 'R':
			playerX += 1;
			break;
	}

	if (playerX < 0 || playerX > 9 || playerY < 0 || playerY > 9) {
		return 0;
	}

	grid[playerLoc[1]][playerLoc[0]] = '.';
	playerLoc[0] = playerX;
	playerLoc[1] = playerY;

	if (checkLoss(playerX, playerY)) {
		return -1;
	}
	if (checkWin(playerX, playerY)) {
		return 1;
	}

	grid[playerY][playerX] = 'P';

	return 0;
}

/*int moveEnemy(int enemyAmount) {
	int enemyX, enemyY;
	
	for (int i = 0; i < enemyAmount; i++) {
		enemyX = enemyLoc.at(i).at(0); enemyY = enemyLoc.at(i).at(1);

		int dir = rand() % 4;

		switch (dir) {
			case 0:
				enemyY -= 1;
				break;
			case 1:
				enemyY += 1;
				break;
			case 2:
				enemyX -= 1;
				break;
			case 3:
				enemyX += 1;
				break;
		}

		if (enemyX < 0 || enemyX > 9 || enemyY < 0 || enemyY > 9) {
			continue;
		}
		else if (grid[enemyY][enemyX] == 'X' || grid[enemyY][enemyX] == 'T'){
			continue;
		}

		grid[enemyLoc.at(i).at(1)][enemyLoc.at(i).at(0)] = '.';
		enemyLoc.at(i).at(0) = enemyX;
		enemyLoc.at(i).at(1) = enemyY;

		grid[enemyY][enemyX] = 'E';
	}

	return 0;
}*/

bool checkGameOver(char dir, bool gameOver) {
	switch (movePlayer(dir)) {
		case -1:
			system("CLS");
			printGrid();
			cout << "You stepped on a trap! You Lose!" << endl;
			gameOver = true;
			break;
		case 1:
			system("CLS");
			printGrid();
			cout << "You found the treasure! You Win!" << endl;
			gameOver = true;
			break;
	}

	return gameOver;
}

int main() {
	int trapAmount{ 0 }, enemyAmount{ 0 }, seed{}, enemySeed{};

	cout << "How many traps are there? (1 - 10)" << endl;
	cin >> trapAmount;
	//cout << "How many enemies are there? (1 - 10)" << endl;
	//cin >> enemyAmount;
	cout << "Enter a world seed: " << endl;
	cin >> seed;

	if (seed == NULL) srand(time(NULL));
	else srand(seed);

	generateGrid();
	placeTraps(trapAmount, seed);
	//placeEnemy(enemyAmount, seed);
	placeTreasure(seed);
	placePlayer(seed);

	#pragma warning(disable : 4996);
	while (!gameOver) {
		system("CLS");
		printGrid();
		//moveEnemy(enemyAmount);


		cout << "press any arrow key or Q to quit" << endl;
		getch();

		if (GetAsyncKeyState(VK_UP)) {
			gameOver = checkGameOver('U', gameOver);
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			gameOver = checkGameOver('D', gameOver);
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			gameOver = checkGameOver('L', gameOver);
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			gameOver = checkGameOver('R', gameOver);
		}
		else if (GetAsyncKeyState(0x51)) gameOver = true;

		Sleep(100);
	}

	system("pause");

	return 0;
}