#include "variables.h"

wall wallMatrix[16][8];

gameBoardSquare gameBoardSquareMatrix[9][9];

playerInMatrix playerOne, playerTwo;

int directionsLine[] = { 1, -1, 0, 0 }, directionsColumn[] = { 0, 0, 1, -1 }, moveForwardLine[] = { 2, -2, 0, 0 }, moveForwardColumns[] = { 0, 0, 2, -2 };

SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRenderer = nullptr;

undoInfo stivaUndo[501];

unsigned int moves = 0;

bool isRunning = true;

bool playerOneTurn = true;

short playerOneWalls = 10;
short playerTwoWalls = 10;

int p1X, p1Y, p2X, p2Y;

short Winner;

short gameMatrix[17][17];
short matriceDrumMinim[17][17];
short auxiliarMatrix[17][17];

bool chooseWhoStarts;

short playerOneScore, playerTwoScore;
char playerOneScoreC[4], playerTwoScoreC[4];