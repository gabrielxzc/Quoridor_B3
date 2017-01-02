#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include "defines.h"

using namespace std;

SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRenderer = nullptr;

bool isRunning = true; // Inchide tot programul

bool playerOneTurn = true;

short playerOneWalls = 10;
short playerTwoWalls = 10;

int p1X, p1Y, p2X, p2Y;

short Winner;

short gameMatrix[17][17];
short auxiliarMatrix[17][17];
void createAuxiliarMatrix(int i, int j,int position)
{

	int k, t;
	for (k = 0; k <= 16;k++)
	for (t = 0; t <= 16; t++)
		auxiliarMatrix[k][t] = gameMatrix[k][t];
	if (position == 1)
	{
		auxiliarMatrix[i][j * 2 + 1] = -1;
		auxiliarMatrix[i + 1][j * 2 + 1] = -1;
		auxiliarMatrix[i + 2][j * 2 + 1] = -1;
	}
	else
	{
		auxiliarMatrix[i][j * 2] = -1;
		auxiliarMatrix[i][j * 2 + 1] = -1;
		auxiliarMatrix[i][j * 2 + 2] = -1;

	}

}
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

bool checkLimits(int line,int column)
{

	if (line < 0) return false;
	if (line >16) return false;
	if (column < 0) return false;
	if (column>16) return false;
	return true;
}
	

bool thereIsaRoad(int player)
{
	int coada = 1; 
	bool directions = false;
	elements coadaElements[100];
	if (player == 1)
	{
		coadaElements[1].line = playerOne.line;
		coadaElements[1].column = playerOne.column;
	}
	if (player == 2)
	{
		{
			coadaElements[1].line = playerTwo.line;
			coadaElements[1].column = playerTwo.column;
		}
	}
	while (coada != 0)
	{
		int i;
		if (coadaElements[coada].line == 0 && player==1) return true;
		if (coadaElements[coada].line == 16 && player == 2) return true;
		auxiliarMatrix[coadaElements[coada].line][coadaElements[coada].column] = 3;
		directions = false;
		for (i = 0; i <= 3; i++)
		if (auxiliarMatrix[coadaElements[coada].line + directionsLine[i]][coadaElements[coada].column + directionsColumn[i]] != -1 && auxiliarMatrix[coadaElements[coada].line + moveForwardLine[i]][coadaElements[coada].column + moveForwardColumns[i]] != 3 && checkLimits(coadaElements[coada].line + moveForwardLine[i],coadaElements[coada].column+moveForwardColumns[i])==true)
			{
				coada++;
				coadaElements[coada].line = coadaElements[coada - 1].line + moveForwardLine[i];
				coadaElements[coada].column = coadaElements[coada - 1].column + moveForwardColumns[i];
				i = 4;
				directions = true;
			}
		if (directions == false) coada--;
	}
	return false;
}
bool thereIsaPathVertical(int i,int j)
{
	bool player1HasRoad, player2HasRoad;
	createAuxiliarMatrix(i, j, 1);

	player1HasRoad = thereIsaRoad(1);
	createAuxiliarMatrix(i, j, 1);
	player2HasRoad = thereIsaRoad(2);
	cout << player1HasRoad << endl;
	cout << player2HasRoad << endl;
	
	if (player1HasRoad == true && player2HasRoad == true) return true;
	return false;
}
bool thereIsaaPathOrizontal(int i, int j)
{
	bool player1HasRoad, player2HasRoad;
	createAuxiliarMatrix(i, j, 2);

	player1HasRoad = thereIsaRoad(1);
	createAuxiliarMatrix(i, j, 2);
	player2HasRoad = thereIsaRoad(2);


	if (player1HasRoad == true && player2HasRoad == true) return true;
	return false;


}


void initializeGameMatrix()
{
	short line, column;
	for (line = 0; line < 17; line++)
	{
		for (column = 0; column < 17; column++)
			gameMatrix[line][column] = 0;
	}

	playerOne.line = 16;
	playerOne.column = 8;
	playerTwo.line = 0;
	playerTwo.column = 8;

	gameMatrix[playerOne.line][playerOne.column] = 1;
	gameMatrix[playerTwo.line][playerTwo.column] = 2;
}

void initializeGameBoardSquaresCoordinates()
{
	int line, column;
	int currentX, currentY = 56;

	for (line = 0; line < 9; line++)
	{
		currentX = 147;

		for (column = 0; column < 9; column++)
		{
			gameBoardSquareMatrix[line][column].width = 35;
			gameBoardSquareMatrix[line][column].height = 35;

			gameBoardSquareMatrix[line][column].x = currentX;
			gameBoardSquareMatrix[line][column].y = currentY;

			currentX += 59;
		}

		currentY += 56;
	}
}

bool mouseHoverVerticalWall(SDL_Event event, int x, int y)
{
	if (event.motion.x >= x && event.motion.x <= x + 18 && event.motion.y >= y && event.motion.y <= y + 43)
		return true;
	return false;
}

bool mouseHoverOrizontalWall(SDL_Event event, int x, int y)
{
	if (event.motion.x >= x && event.motion.x <= x + 40 && event.motion.y >= y && event.motion.y <= y + 15)
		return true;
	return false;
}

void initializeWallMatrix()
{
	int xImp, yImp, xPar, yPar, i, j;
	yPar = 53;
	yImp = 93;

	for (i = 0; i <= 15; i++)
	{
		xPar = 186;
		xImp = 146;

		for (j = 0; j <= 7; j++)
		{
			wallMatrix[i][j].placed = false;

			if (i % 2 == 0)
			{
				wallMatrix[i][j].x = xPar;
				wallMatrix[i][j].y = yPar;
				xPar = xPar + 59;
			}
			else
			{
				wallMatrix[i][j].x = xImp;
				wallMatrix[i][j].y = yImp;
				xImp = xImp + 58;
			}
		}

		if (i % 2 == 0)
		{
			yPar = yPar + 56;
		}

		else
		{
			yImp = yImp + 56;
		}

	}
}

void addImageToRenderer(const char *file,int x, int y, int w, int h)
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect imageSize = { x, y, w, h };

	surface = IMG_Load(file);
	texture = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_RenderCopy(mainRenderer, texture, nullptr, &imageSize);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

int checkPlayerProximity(int xFuture, int yFuture, int xOtherPlayer, int yOtherPlayer)
{
	if (xFuture == xOtherPlayer && yFuture == yOtherPlayer) return 0;
	return 1;
}

void createPlayTable()
{
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	SDL_RenderClear(mainRenderer);

	addImageToRenderer("images/gameBoard.JPG", 0, 0, 800, 600);
	addImageToRenderer("images/backButton.PNG", 700, 550, 70, 40);
	addImageToRenderer("images/playerOne.PNG", p1X, p1Y, 35, 35);
	addImageToRenderer("images/playerTwo.PNG", p2X, p2Y, 35, 35);

	short WallLevel1 = p1Y_StartWalls, walls;

	for (walls = 0; walls < playerOneWalls; walls++)
	{
		addImageToRenderer("images/pereteNotFilled.PNG", p1X_StartWalls, WallLevel1, WallWidth, WallLength);
		WallLevel1 = WallLevel1 - SideWallsDistance;
	}

	short WallLevel2 = p2Y_StartWalls;

	for (walls = 0; walls < playerTwoWalls; walls++)
	{
		addImageToRenderer("images/pereteNotFilled.PNG", p2X_StartWalls, WallLevel2, WallWidth, WallLength);
		WallLevel2 = WallLevel2 + SideWallsDistance;
	}

	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (i % 2 == 0)
			{
				if (wallMatrix[i][j].placed == true)
					addImageToRenderer("images/pereteVerticalFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 14, 98);
			}
			else
			{
				if (wallMatrix[i][j].placed == true)
					addImageToRenderer("images/pereteFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 98, 14);
			}
		}
	}

	SDL_RenderPresent(mainRenderer);
}

void highlightPossibleMoves(int X, int Y, playerInMatrix player, int playerHighlighter)
{
	if (playerHighlighter == 1)
	{
		if (checkPlayerProximity(X - moveLeftRight, Y, p2X, p2Y) == 0 && X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight))
		{
			if (gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X - 2 * moveLeftRight, Y, 35, 35);
			else
			{
				if (gameMatrix[playerTwo.line - 1][playerTwo.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2 - 1][playerTwo.column / 2].x, gameBoardSquareMatrix[playerTwo.line / 2 - 1][playerTwo.column / 2].y, 35, 35);

				if (gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2 + 1][playerTwo.column / 2].x, gameBoardSquareMatrix[playerTwo.line / 2 + 1][playerTwo.column / 2].y, 35, 35);
			}
		}
		else 
			if (X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(X - moveLeftRight, Y, p2X, p2Y) == 1 && gameMatrix[player.line][player.column-1]!=-1) 
				addImageToRenderer("images/highlightedSquare.PNG", X - moveLeftRight, Y, 35, 35);
		

		if (checkPlayerProximity(X + moveLeftRight, Y, p2X, p2Y) == 0 && X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight))
		{
			if (gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X + 2 * moveLeftRight, Y, 35, 35);
			else
			{
				if (gameMatrix[playerTwo.line - 1][playerTwo.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2 - 1][playerTwo.column / 2].x, gameBoardSquareMatrix[playerTwo.line / 2 - 1][playerTwo.column / 2].y, 35, 35);

				if (gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2 + 1][playerTwo.column / 2].x, gameBoardSquareMatrix[playerTwo.line / 2 + 1][playerTwo.column / 2].y, 35, 35);
			}
		}
		else  
			if (X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(X + moveLeftRight, Y, p2X, p2Y)==1 && gameMatrix[player.line][player.column+1]!=-1) 
				addImageToRenderer("images/highlightedSquare.PNG", X + moveLeftRight, Y, 35, 35);
		

		if (checkPlayerProximity(X, Y + moveUpDown, p2X, p2Y) == 0 && Y + 2 * moveUpDown <= p1Y_Start)
		{
			if (gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X, Y + 2 * moveUpDown, 35, 35);
			else
			{
				if (gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 - 1].x, gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 - 1].y, 35, 35);
				if (gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 + 1].x, gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 + 1].y, 35, 35);
			}
		}
		else 
			if (Y + moveUpDown <= p1Y_Start &&checkPlayerProximity(X, Y + moveUpDown, p2X, p2Y)==1 && gameMatrix[player.line+1][player.column]!=-1) 
				addImageToRenderer("images/highlightedSquare.PNG", X, Y + moveUpDown, 35, 35);
		

		if (checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y) == 0 && Y - 2 * moveUpDown >= p2Y_Start)
		{
			if (gameMatrix[playerTwo.line - 1][playerTwo.column] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X, Y - 2 * moveUpDown, 35, 35);
			else
			{
				if (gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 - 1].x, gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 - 1].y, 35, 35);
				if (gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 + 1].x, gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 + 1].y, 35, 35);
			}
		}
		else 
			if (Y - moveUpDown >= p2Y_Start && checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y)==1 && gameMatrix[player.line-1][player.column]!=-1) 
				addImageToRenderer("images/highlightedSquare.PNG", X, Y - moveUpDown, 35, 35);
	}
	if (playerHighlighter == 2)
	{
		if (checkPlayerProximity(X - moveLeftRight, Y, p1X, p1Y) == 0 && X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight))
		{
			if (gameMatrix[playerOne.line][playerOne.column - 1] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X - 2 * moveLeftRight, Y, 35, 35);
			else
			{
				if (gameMatrix[playerOne.line - 1][playerOne.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2 - 1][playerOne.column / 2].x, gameBoardSquareMatrix[playerOne.line / 2 - 1][playerOne.column / 2].y, 35, 35);

				if (gameMatrix[playerOne.line + 1][playerOne.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2 + 1][playerOne.column / 2].x, gameBoardSquareMatrix[playerOne.line / 2 + 1][playerOne.column / 2].y, 35, 35);
			}
		}
		else
		if (X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(X - moveLeftRight, Y, p1X, p1Y) == 1 && gameMatrix[player.line][player.column - 1] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X - moveLeftRight, Y, 35, 35);


		if (checkPlayerProximity(X + moveLeftRight, Y, p1X, p1Y) == 0 && X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight))
		{
			if (gameMatrix[playerOne.line][playerOne.column + 1] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X + 2 * moveLeftRight, Y, 35, 35);
			else
			{
				if (gameMatrix[playerOne.line - 1][playerOne.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2 - 1][playerOne.column / 2].x, gameBoardSquareMatrix[playerOne.line / 2 - 1][playerOne.column / 2].y, 35, 35);

				if (gameMatrix[playerOne.line + 1][playerOne.column] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2 + 1][playerOne.column / 2].x, gameBoardSquareMatrix[playerOne.line / 2 + 1][playerOne.column / 2].y, 35, 35);
			}
		}
		else
		if (X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(X + moveLeftRight, Y, p1X, p1Y) == 1 && gameMatrix[player.line][player.column + 1] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X + moveLeftRight, Y, 35, 35);


		if (checkPlayerProximity(X, Y + moveUpDown, p1X, p1Y) == 0 && Y + 2 * moveUpDown <= p1Y_Start)
		{
			if (gameMatrix[playerOne.line + 1][playerOne.column] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X, Y + 2 * moveUpDown, 35, 35);
			else
			{
				if (gameMatrix[playerOne.line][playerOne.column - 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 - 1].x, gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 - 1].y, 35, 35);
				if (gameMatrix[playerOne.line][playerOne.column + 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 + 1].x, gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 + 1].y, 35, 35);
			}
		}
		else
		if (Y + moveUpDown <= p1Y_Start &&checkPlayerProximity(X, Y + moveUpDown, p1X, p1Y) == 1 && gameMatrix[player.line + 1][player.column] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X, Y + moveUpDown, 35, 35);


		if (checkPlayerProximity(X, Y - moveUpDown, p1X, p1Y) == 0 && Y - 2 * moveUpDown >= p2Y_Start)
		{
			if (gameMatrix[playerOne.line - 1][playerOne.column] != -1)
				addImageToRenderer("images/highlightedSquare.PNG", X, Y - 2 * moveUpDown, 35, 35);
			else
			{
				if (gameMatrix[playerOne.line][playerOne.column - 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 - 1].x, gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 - 1].y, 35, 35);
				if (gameMatrix[playerOne.line][playerOne.column + 1] != -1)
					addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 + 1].x, gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 + 1].y, 35, 35);
			}
		}
		else
		if (Y - moveUpDown >= p2Y_Start && checkPlayerProximity(X, Y - moveUpDown, p1X, p1Y) == 1 && gameMatrix[player.line - 1][player.column] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X, Y - moveUpDown, 35, 35);
	}
	SDL_RenderPresent(mainRenderer);
}

void createPlayerWinTable(SDL_Event event, int Winner)
{
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	SDL_RenderClear(mainRenderer);
	if (Winner == 1) addImageToRenderer("images/PlayerOneWin.JPG", 0, 0, 800, 600);
	if (Winner == 2) addImageToRenderer("images/PlayerTwoWin.JPG", 0, 0, 800, 600);
	addImageToRenderer("images/backButton.PNG", 700, 550, 70, 40);

	SDL_RenderPresent(mainRenderer);
}

int runPlayerWinTable(int Winner)
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
	while (SDL_PollEvent(&event))
	{
		createPlayerWinTable(event,Winner);

		if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 365 && event.motion.x < 435 && event.motion.y > 550 && event.motion.y < 590))
			return 0;
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			return 0;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
			return 0;
	}
	return 0;
}

bool noVerticalWallsAround(int line, int column)
{
	if (wallMatrix[line][column].placed == true)
		return false;

	if (line >= 2 && wallMatrix[line - 2][column].placed == true)
		return false;

	if (line <= 12 && wallMatrix[line + 2][column].placed == true)
		return false;

	if (wallMatrix[line + 1][column].placed == true)
		return false;

	return true;
}

bool noHorizontalWallsAround(int line, int column)
{
	if (wallMatrix[line][column].placed == true)
		return false;

	if (column >= 1 && wallMatrix[line][column - 1].placed == true)
		return false;

	if (column <= 6 && wallMatrix[line][column + 1].placed == true)
		return false;

	if (wallMatrix[line - 1][column].placed == true)
		return false;

	return true;
}

bool stillHasWalls(short playerTurn)
{
	if (playerOneTurn == true && playerOneWalls == 0)
		return false;

	if (playerOneTurn == false && playerTwoWalls == 0)
		return false;

	return true;
}

int playingAgainstComputer()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			createPlayTable();

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;

			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}

	return 0;
}

void highlightWalls(SDL_Event event, int &highlightedWalls, short playerTurn)
{
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (i % 2 == 0)
			{
				if (mouseHoverVerticalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noVerticalWallsAround(i,j) && stillHasWalls(playerTurn)){
					createPlayTable();
				if (thereIsaPathVertical(i,j)==true)	addImageToRenderer("images/pereteVerticalNotFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 14, 98);
				else addImageToRenderer("images/pereteNotDrum.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 14, 98);
				SDL_RenderPresent(mainRenderer);
					highlightedWalls = 1;
				}
			}
			else
			{
				if (mouseHoverOrizontalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noHorizontalWallsAround(i, j) && stillHasWalls(playerTurn)){
					createPlayTable();
					if (thereIsaaPathOrizontal (i,j)== true)
					addImageToRenderer("images/pereteNotFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 98, 14);
				else addImageToRenderer("images/pereteNotDrum.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 98, 14);
				SDL_RenderPresent(mainRenderer);
					highlightedWalls = 1;
				}
			}
		}
	}
}

void checkPlaceWall(SDL_Event event, bool &turnOver, short playerTurn)
{
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (i % 2 == 0)
			{
				if (mouseHoverVerticalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noVerticalWallsAround(i, j) && stillHasWalls(playerTurn) && thereIsaPathVertical(i,j)==1){
					if (event.type == SDL_MOUSEBUTTONDOWN && wallMatrix[i][j].placed == 0)
					{
						if (playerOneTurn)
							playerOneWalls--;
						else
							playerTwoWalls--;

						gameMatrix[i][j * 2 + 1] = -1;
						gameMatrix[i + 1][j * 2 + 1] = -1;
						gameMatrix[i + 2][j * 2 + 1] = -1;

						wallMatrix[i][j].placed = 1;
						turnOver = true;
					}
				}
			}
			else
			{
				if (mouseHoverOrizontalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noHorizontalWallsAround(i, j) && stillHasWalls(playerTurn) && thereIsaaPathOrizontal(i, j) == 1){
					if (event.type == SDL_MOUSEBUTTONDOWN && wallMatrix[i][j].placed == 0)
					{
						if (playerOneTurn)
							playerOneWalls--;
						else
							playerTwoWalls--;

						gameMatrix[i][j * 2 ] = -1;
						gameMatrix[i][j * 2 + 1] = -1;
						gameMatrix[i][j * 2 + 2] = -1;

						wallMatrix[i][j].placed = 1;
						turnOver = true;
					}
				}
			}
		}
	}
}

int playerOnePlay()
{
	bool turnOver = false;

	SDL_Event event;

	int highlighted = 0;
	int highlightedWalls = 0;

	while (!turnOver)
	{
		while (SDL_PollEvent(&event))
		{
			highlightedWalls = 0;

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= p1X && event.motion.x <= p1X + 35 && event.motion.y >= p1Y && event.motion.y <= p1Y + 35)
			{
				if (highlighted == 0)
				{
					createPlayTable();
					highlightPossibleMoves(p1X, p1Y, playerOne, 1);
					highlighted = 1;
				}
				else
				{
					createPlayTable();
					highlighted = 0;
				}
			}

			if (highlighted == 0)
			{
				highlightWalls(event, highlightedWalls, 1);
				checkPlaceWall(event, turnOver, 1);
				if (turnOver){
					playerOneTurn = false;
					return 1;
				}
			}

			if (highlightedWalls == 0 && highlighted == 0)
				createPlayTable();

			if (highlighted == 1)
			{

				if (checkPlayerProximity(p1X - moveLeftRight, p1Y, p2X, p2Y) == 0 && p2X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight) && gameMatrix[playerOne.line][playerOne.column - 1] != -1)
				{
					if (gameMatrix[playerOne.line][playerOne.column - 3] == -1)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line - 1][playerTwo.column]!=-1){

							p1X = p1X - moveLeftRight;
							p1Y = p1Y - moveUpDown;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column -= 2;
							playerOne.line -= 2;
							gameMatrix[playerOne.line][playerOne.column] = 1;

							playerOneTurn = false;
							return 1;
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + squareSideLength + moveUpDown && gameMatrix[playerTwo.line + 1][playerTwo.column] != -1){

							p1X = p1X - moveLeftRight;
							p1Y = p1Y + moveUpDown;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column -= 2;
							playerOne.line += 2;
							gameMatrix[playerOne.line][playerOne.column] = 1;

							playerOneTurn = false;
							return 1; 
						}
					}

					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - 2 * moveLeftRight && event.motion.x < p1X - 2 * moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength && gameMatrix[playerOne.line][playerOne.column - 3] != -1){
						p1X = p1X - 2 * moveLeftRight, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.column -= 4;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
				else
				if (p1X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(p1X - moveLeftRight, p1Y, p2X, p2Y) == 1 && gameMatrix[playerOne.line][playerOne.column-1]!=-1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength)
				{
					p1X = p1X - moveLeftRight, turnOver = true;

					gameMatrix[playerOne.line][playerOne.column] = 0;
					playerOne.column -= 2;
					gameMatrix[playerOne.line][playerOne.column] = 1;
				}



				if (checkPlayerProximity(p1X + moveLeftRight, p1Y, p2X, p2Y) == 0 && p1X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight) && gameMatrix[playerOne.line][playerOne.column + 1] != -1)
				{
						if (gameMatrix[playerOne.line][playerOne.column + 3] == -1)
						{
							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + squareSideLength + moveUpDown && gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
							{

								p1X = p1X + moveLeftRight;
								p1Y = p1Y + moveUpDown;

								gameMatrix[playerOne.line][playerOne.column] = 0;
								playerOne.column += 2;
								playerOne.line += 2;
								gameMatrix[playerOne.line][playerOne.column] = 1;

								playerOneTurn = false;
								return 1;
							}

							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line - 1][playerTwo.column] != -1)
							{

								p1X = p1X + moveLeftRight;
								p1Y = p1Y - moveUpDown;

								gameMatrix[playerOne.line][playerOne.column] = 0;
								playerOne.column += 2;
								playerOne.line -= 2;
								gameMatrix[playerOne.line][playerOne.column] = 1;

								playerOneTurn = false;
								return 1;
							}
						}
					
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + 2 * moveLeftRight && event.motion.x < p1X + 2 * moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength && gameMatrix[playerOne.line][playerOne.column +3] != -1){
							p1X = p1X + 2 * moveLeftRight, turnOver = true;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column += 4;
							gameMatrix[playerOne.line][playerOne.column] = 1;
						}
				}
				else
				if (p1X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(p1X + moveLeftRight, p1Y, p2X, p2Y) == 1 && gameMatrix[playerOne.line][playerOne.column + 1] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength){
					p1X = p1X + moveLeftRight, turnOver = true;

					gameMatrix[playerOne.line][playerOne.column] = 0;
					playerOne.column += 2;
					gameMatrix[playerOne.line][playerOne.column] = 1;
				}


				if (p1Y + moveUpDown <= p1Y_Start)
				if (checkPlayerProximity(p1X, p1Y + moveUpDown, p2X, p2Y) == 0 && p1Y + 2 * moveUpDown <= p1Y_Start && gameMatrix[playerOne.line + 1][playerOne.column] != -1)
				{
					if (gameMatrix[playerOne.line + 3][playerOne.column] == -1)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + squareSideLength + moveUpDown && gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
						{
							p1X = p1X - moveLeftRight;
							p1Y = p1Y + moveUpDown;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column -= 2;
							playerOne.line += 2;
							gameMatrix[playerOne.line][playerOne.column] = 1;

							playerOneTurn = false;
							return 1;
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + squareSideLength + moveUpDown && gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
						{

							p1X = p1X + moveLeftRight;
							p1Y = p1Y + moveUpDown;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column += 2;
							playerOne.line += 2;
							gameMatrix[playerOne.line][playerOne.column] = 1;

							playerOneTurn = false;
							return 1;
						}
					}
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y + 2 * moveUpDown && event.motion.y < p1Y + 2 * moveUpDown + squareSideLength && gameMatrix[playerOne.line + 3][playerOne.column] != -1)
					{
						p1Y = p1Y + 2*moveUpDown, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.line += 4;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
				else
				if (checkPlayerProximity(p1X, p1Y + moveUpDown, p2X, p2Y) == 1 && gameMatrix[playerOne.line+1][playerOne.column] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + moveUpDown + squareSideLength)
				{
					p1Y = p1Y + moveUpDown, turnOver = true;

					gameMatrix[playerOne.line][playerOne.column] = 0;
					playerOne.line += 2;
					gameMatrix[playerOne.line][playerOne.column] = 1;
				}



				if (p1Y - moveUpDown >= p2Y_Start)
				if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y) == 0 && p1Y - 2 * moveUpDown >= p2Y_Start && gameMatrix[playerOne.line - 1][playerOne.column] != -1)
				{
					if (gameMatrix[playerOne.line - 3][playerOne.column] == -1)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line][playerTwo.column-1] != -1)
						{

							p1X = p1X - moveLeftRight;
							p1Y = p1Y - moveUpDown;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column -= 2;
							playerOne.line -= 2;
							gameMatrix[playerOne.line][playerOne.column] = 1;

							playerOneTurn = false;
							return 1;
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line][playerTwo.column+1] != -1)
						{

							p1X = p1X + moveLeftRight;
							p1Y = p1Y - moveUpDown;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.column += 2;
							playerOne.line -= 2;
							gameMatrix[playerOne.line][playerOne.column] = 1;

							playerOneTurn = false;
							return 1;
						}
					}
					
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y - 2 * moveUpDown && event.motion.y < p1Y - 2 * moveUpDown + squareSideLength && gameMatrix[playerOne.line-3][playerOne.column] != -1){
						p1Y = p1Y - 2 * moveUpDown, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.line -= 4;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
				else
				if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y) == 1 && gameMatrix[playerOne.line - 1][playerOne.column] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y - moveUpDown + squareSideLength){
					p1Y = p1Y - moveUpDown, turnOver = true;

					gameMatrix[playerOne.line][playerOne.column] = 0;
					playerOne.line -= 2;
					gameMatrix[playerOne.line][playerOne.column] = 1;
				}
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
	}
	playerOneTurn = false;
}

int playerTwoPlay()
{
		bool turnOver = false;
		SDL_Event event;
		int highlighted = 0;
		int highlightedWalls = 0;

		while (!turnOver)
		{
			while (SDL_PollEvent(&event))
			{
				highlightedWalls = 0;

				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= p2X && event.motion.x <= p2X + 35 && event.motion.y >= p2Y && event.motion.y <= p2Y + 35)
				{
					if (highlighted == 0)
					{
						highlightPossibleMoves(p2X, p2Y, playerTwo, 2);
						highlighted = 1;
					}
					else
					{
						createPlayTable(); 
						highlighted = 0;
					}
				}

				if (highlighted == 0)
				{
					highlightWalls(event, highlightedWalls, 2);
					checkPlaceWall(event, turnOver, 2);

					if (turnOver){
						playerOneTurn = true;
						return 1;
					}
				}

				if (highlightedWalls == 0 && highlighted == 0)
					createPlayTable();

				if (highlighted == 1)
				{
					if (checkPlayerProximity(p2X - moveLeftRight, p2Y, p1X, p1Y) == 0 && p2X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight) && gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
					{
						if (gameMatrix[playerTwo.line][playerTwo.column - 3] == -1)
						{
							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y + squareSideLength - moveUpDown && gameMatrix[playerOne.line - 1][playerOne.column] != -1){

								p2X = p2X - moveLeftRight;
								p2Y = p2Y - moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column -= 2;
								playerTwo.line -= 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}

							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + squareSideLength + moveUpDown && gameMatrix[playerOne.line + 1][playerOne.column] != -1){

								p2X = p2X - moveLeftRight;
								p2Y = p2Y + moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column -= 2;
								playerTwo.line += 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - 2 * moveLeftRight && event.motion.x < p2X - 2 * moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength && gameMatrix[playerTwo.line][playerTwo.column - 3] != -1){
							p2X = p2X - 2 * moveLeftRight, turnOver = true;

							gameMatrix[playerTwo.line][playerTwo.column] = 0;
							playerTwo.column -= 4;
							gameMatrix[playerTwo.line][playerTwo.column] = 2;
						}
					}
					else
					if (p2X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(p2X - moveLeftRight, p2Y, p1X, p1Y) == 1 && gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength)
					{
						p2X = p2X - moveLeftRight, turnOver = true;

						gameMatrix[playerTwo.line][playerTwo.column] = 0;
						playerTwo.column -= 2;
						gameMatrix[playerTwo.line][playerTwo.column] = 2;
					}



					if (checkPlayerProximity(p2X + moveLeftRight, p2Y, p1X, p1Y) == 0 && p2X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight) && gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
					{
						if (gameMatrix[playerTwo.line][playerTwo.column + 3] == -1)
						{
							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + squareSideLength + moveUpDown && gameMatrix[playerOne.line + 1][playerOne.column] != -1)
							{

								p2X = p2X + moveLeftRight;
								p2Y = p2Y + moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column += 2;
								playerTwo.line += 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}

							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y + squareSideLength - moveUpDown && gameMatrix[playerOne.line - 1][playerOne.column] != -1)
							{

								p2X = p2X + moveLeftRight;
								p2Y = p2Y - moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column += 2;
								playerTwo.line -= 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + 2 * moveLeftRight && event.motion.x < p2X + 2 * moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength && gameMatrix[playerTwo.line][playerTwo.column + 3] != -1){
							p2X = p2X + 2 * moveLeftRight, turnOver = true;

							gameMatrix[playerTwo.line][playerTwo.column] = 0;
							playerTwo.column += 4;
							gameMatrix[playerTwo.line][playerTwo.column] = 2;
						}
					}
					else
					if (p2X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(p2X - moveLeftRight, p2Y, p1X, p1Y) == 1 && gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength){
						p2X = p2X + moveLeftRight, turnOver = true;

						gameMatrix[playerTwo.line][playerTwo.column] = 0;
						playerTwo.column += 2;
						gameMatrix[playerTwo.line][playerTwo.column] = 2;
					}



					if (p2Y + moveUpDown <= p1Y_Start)
					if (checkPlayerProximity(p2X, p2Y + moveUpDown, p1X, p1Y) == 0 && p2Y + 2 * moveUpDown <= p1Y_Start&& gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
					{
						if (gameMatrix[playerTwo.line + 3][playerTwo.column] == -1)
						{
							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + squareSideLength + moveUpDown && gameMatrix[playerOne.line][playerOne.column - 1] != -1)
							{
								p2X = p2X - moveLeftRight;
								p2Y = p2Y + moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column -= 2;
								playerTwo.line += 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}

							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + squareSideLength + moveUpDown && gameMatrix[playerOne.line][playerOne.column + 1] != -1)
							{

								p2X = p2X + moveLeftRight;
								p2Y = p2Y + moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column += 2;
								playerTwo.line += 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y + 2 * moveUpDown && event.motion.y < p2Y + 2 * moveUpDown + squareSideLength&& gameMatrix[playerTwo.line + 3][playerTwo.column] != -1)
						{
							p2Y = p2Y + 2*moveUpDown, turnOver = true;

							gameMatrix[playerTwo.line][playerTwo.column] = 0;
							playerTwo.line += 4;
							gameMatrix[playerTwo.line][playerTwo.column] = 2;
						}
					}
					else 
					if (checkPlayerProximity(p2X, p2Y + moveUpDown, p1X, p1Y) == 1 && gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + moveUpDown + squareSideLength) {
						p2Y = p2Y + moveUpDown, turnOver = true;

						gameMatrix[playerTwo.line][playerTwo.column] = 0;
						playerTwo.line += 2;
						gameMatrix[playerTwo.line][playerTwo.column] = 2;
					}

					
					
					if (p2Y - moveUpDown >= p2Y_Start)
					if (checkPlayerProximity(p2X, p2Y - moveUpDown, p1X, p1Y) == 0 && p2Y - 2 * moveUpDown >= p2Y_Start && gameMatrix[playerTwo.line - 1][playerTwo.column] != -1)
					{
						if (gameMatrix[playerTwo.line - 3][playerTwo.column] == -1)
						{
							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y + squareSideLength - moveUpDown && gameMatrix[playerOne.line][playerOne.column - 1] != -1)
							{
								p2X = p2X - moveLeftRight;
								p2Y = p2Y - moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column -= 2;
								playerTwo.line -= 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}

							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y + squareSideLength - moveUpDown && gameMatrix[playerOne.line][playerOne.column + 1] != -1)
							{
								p2X = p2X + moveLeftRight;
								p2Y = p2Y - moveUpDown;

								gameMatrix[playerTwo.line][playerTwo.column] = 0;
								playerTwo.column += 2;
								playerTwo.line -= 2;
								gameMatrix[playerTwo.line][playerTwo.column] = 2;

								playerOneTurn = true;
								return 1;
							}
						}

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y - 2 * moveUpDown && event.motion.y < p2Y - 2 * moveUpDown + squareSideLength && gameMatrix[playerTwo.line - 3][playerTwo.column] != -1){
							p2Y = p2Y - 2 * moveUpDown, turnOver = true;

							gameMatrix[playerTwo.line][playerTwo.column] = 0;
							playerTwo.line -= 4;
							gameMatrix[playerTwo.line][playerTwo.column] = 2;
						}
					}
					else
					if (checkPlayerProximity(p2X, p2Y - moveUpDown, p1X, p1Y) == 1 && gameMatrix[playerTwo.line-1][playerTwo.column] != -1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y - moveUpDown + squareSideLength){
						p2Y = p2Y - moveUpDown, turnOver = true;

						gameMatrix[playerTwo.line][playerTwo.column] = 0;
						playerTwo.line -= 2;
						gameMatrix[playerTwo.line][playerTwo.column] = 2;
					}
				}

				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
					return 0;
				if (event.type == SDL_QUIT)
				{
					isRunning = false;
					return 0;
				}
			}
		}
	playerOneTurn = true;
}

int playingAgainstHuman()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	int menuCall=1;

	p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;

	playerOneWalls = 10;
	playerTwoWalls = 10;

	playerOneTurn = true;

	initializeWallMatrix();
	initializeGameMatrix();

	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			createPlayTable();

			system("cls");

			for (int i = 0; i < 17; i++)
			{
				for (int j = 0; j < 17; j++)
					cout << gameMatrix[i][j] << ' ';
				cout << '\n';
			}

			cout << playerOne.line << "  " << playerOne.column << '\n';
			cout << playerTwo.line << "  " << playerTwo.column << '\n';

			if (playerOneTurn)
			menuCall=playerOnePlay();
			else
				menuCall=playerTwoPlay();

			if (menuCall == 0) return 0;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;
			if (p1Y == p2Y_Start) { Winner = 1; runPlayerWinTable(Winner); return 0; }
			if (p2Y == p1Y_Start) { Winner = 2; runPlayerWinTable(Winner); return 0; }
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}

			SDL_RenderPresent(mainRenderer);
		}
	return 0;
}

void createStartGameMenu(SDL_Event event)
{
	SDL_RenderClear(mainRenderer);

	addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 800, 600);
	addImageToRenderer("images/backButton.PNG", 365, 550, 70, 40);

	if (event.motion.x > 95 && event.motion.x < 395 && event.motion.y > 125 && event.motion.y < 525)
		addImageToRenderer("images/computerColor.png", 95, 125, 300, 400);
	else
		addImageToRenderer("images/computerNonColor.PNG", 95, 125, 300, 400);

	if (event.motion.x > 405 && event.motion.x < 705 && event.motion.y > 125 && event.motion.y < 525)
		addImageToRenderer("images/vsPlayerColor.PNG", 405, 125, 300, 400);
	else
		addImageToRenderer("images/vsPlayerNonColor.PNG", 405, 125, 300, 400);

	SDL_RenderPresent(mainRenderer);
}

int runStartGameMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
		while (SDL_PollEvent(&event)) 
		{
			createStartGameMenu(event);

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 95 && event.motion.x < 395 && event.motion.y > 125 && event.motion.y < 525) 
			{
				playingAgainstComputer();
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 405 && event.motion.x < 705 && event.motion.y > 125 && event.motion.y < 525) 
			{
				playingAgainstHuman();
				return 0;
			}
			if ((event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 365 && event.motion.x < 435 && event.motion.y > 550 && event.motion.y < 590)) || event.key.keysym.sym == SDLK_ESCAPE)
				return 0;

			if (event.type == SDL_QUIT) 
			{
				isRunning = false;
				return 0;
			}
		}
	return 0;
}

void renderInstructionsMenu(SDL_Event event)
{
	SDL_RenderClear(mainRenderer);

	addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 800, 600);
	addImageToRenderer("images/backButton.PNG", 365, 550, 70, 40);

	SDL_RenderPresent(mainRenderer);
}

int runInstructionsMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			renderInstructionsMenu(event);

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 365 && event.motion.x < 435 && event.motion.y > 550 && event.motion.y < 590))
				return 0;
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
	return 0;
}

void renderMainMenu(SDL_Event event)
{
	SDL_RenderClear(mainRenderer);

	addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 800, 600);

	if (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 175 && event.motion.y < 275)
		addImageToRenderer("images/startGameHIGHLIGHT.PNG", 225, 175, 350, 100);
	else
		addImageToRenderer("images/startGame.PNG", 225, 175, 350, 100);

	if (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 300 && event.motion.y < 400)
		addImageToRenderer("images/rulesHIGHLIGHT.PNG", 225, 300, 350, 100);
	else
		addImageToRenderer("images/rules.PNG", 225, 300, 350, 100);

	if (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 425 && event.motion.y < 525)
		addImageToRenderer("images/exitButtonHIGHLIGHT.PNG", 225, 425, 350, 100);
	else
		addImageToRenderer("images/exitButton.PNG", 225, 425, 350, 100);

	SDL_RenderPresent(mainRenderer);
}

int runMainMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			renderMainMenu(event);

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 175 && event.motion.y < 275))
				runStartGameMenu();
			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 300 && event.motion.y < 400))
				runInstructionsMenu();
			if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 425 && event.motion.y < 525))
				isRunning = false;
		}
	return 0;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

	mainWindow = SDL_CreateWindow("Quoridor",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		0);

	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	initializeGameBoardSquaresCoordinates();
	runMainMenu();

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}