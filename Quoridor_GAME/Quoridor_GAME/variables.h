#pragma once

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

struct gameBoardSquare{
	int x;
	int y;
	int width;
	int height;
};

struct playerInMatrix{
	int line;
	int column;
};

extern gameBoardSquare gameBoardSquareMatrix[9][9];

extern wall wallMatrix[16][8];

extern playerInMatrix playerOne, playerTwo;

extern int directionsLine[4], directionsColumn[4], moveForwardLine[4], moveForwardColumns[4];

extern SDL_Window *mainWindow;
extern SDL_Renderer *mainRenderer;

extern bool isRunning;

extern bool playerOneTurn;

extern short playerOneWalls;
extern short playerTwoWalls;

extern int p1X, p1Y, p2X, p2Y;

extern short Winner;

extern short gameMatrix[17][17];
extern short matriceDrumMinim[17][17];
extern short auxiliarMatrix[17][17];

extern bool chooseWhoStarts;