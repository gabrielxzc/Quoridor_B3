#include "defines.h"

struct elements
{
	int line;
	int column;

};

struct wall {
	int x;
	int y;
	bool placed;
};

wall wallMatrix[16][8];

struct gameBoardSquare{
	int x;
	int y;
	int width;
	int height;
};

gameBoardSquare gameBoardSquareMatrix[9][9];

struct playerInMatrix{
	int line;
	int column;
};

playerInMatrix playerOne, playerTwo;
int directionsLine[] = { 1, -1, 0, 0 }, directionsColumn[] = { 0, 0, 1, -1 }, moveForwardLine[] = { 2, -2, 0, 0 }, moveForwardColumns[] = { 0, 0, 2, -2 };


SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRenderer = nullptr;

bool isRunning = true;

bool playerOneTurn = true;

short playerOneWalls = 10;
short playerTwoWalls = 10;

int p1X, p1Y, p2X, p2Y;

short Winner;

short gameMatrix[17][17];
short matriceDrumMinim[17][17];
short auxiliarMatrix[17][17];