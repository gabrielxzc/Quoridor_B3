#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

struct wall {
	int x;
	int y;
	bool placed;
};

wall wallMatrix[17][8];

void initializeWallMatrix()
{
	int xImp, yImp, xPar, yPar, i, j;
	xPar = 184;
	yPar = 58;
	xImp = 150;
	yImp = 93;

	for (i = 0; i <= 16; i++)
	{
		xPar = 184;
		xImp = 146;

		for (j = 0; j <= 7; j++)
		{
			wallMatrix[i][j].placed = false;

			if (i % 2 == 0)
			{
				wallMatrix[i][j].x = xPar;
				wallMatrix[i][j].y = yPar;
				xPar = xPar + 60;
			}
			else
			{
				wallMatrix[i][j].x = xImp;
				wallMatrix[i][j].y = yImp;
				xImp = xImp + 59;
			}
		}

		if (i % 2 == 0)
		{
			yPar = yPar + 58;
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

	initializeWallMatrix();

	addImageToRenderer("images/gameBoard.JPG", 0, 0, 800, 600);
	addImageToRenderer("images/backButton.PNG", 700, 550, 70, 40);
	addImageToRenderer("images/playerOne.PNG", p1X, p1Y, 35, 35);
	addImageToRenderer("images/playerTwo.PNG", p2X, p2Y, 35, 35);

	for (int i = 1; i <= 16; i = i + 2)
	for (int j = 1; j <= 7; j=j+2)
		addImageToRenderer("images/pereteFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 98, 14);

	short WallLevel1 = p1Y_StartWalls, walls;

	for (walls = 0; walls <= 9; walls++)
	{
		addImageToRenderer("images/pereteNotFilled.PNG", p1X_StartWalls, WallLevel1, WallWidth, WallLength);
		WallLevel1 = WallLevel1 - SideWallsDistance;
	}

	short WallLevel2 = p2Y_StartWalls;

	for (walls = 0; walls <= 9; walls++)
	{
		addImageToRenderer("images/pereteNotFilled.PNG", p2X_StartWalls, WallLevel2, WallWidth, WallLength);
		WallLevel2 = WallLevel2 + SideWallsDistance;
	}

	SDL_RenderPresent(mainRenderer);
}

void highlightPossibleMoves(int X, int Y, int playerHighlighter)
{
	if (playerHighlighter == 1)
	{
		if (checkPlayerProximity(X-moveLeftRight,Y,p2X,p2Y)==0 && X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight)) addImageToRenderer("images/highlightedSquare.PNG", X - 2 * moveLeftRight, Y, 35, 35);
		else if (X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(X - moveLeftRight, Y, p2X, p2Y) == 1) addImageToRenderer("images/highlightedSquare.PNG", X - moveLeftRight, Y, 35, 35);
		
		if (checkPlayerProximity(X + moveLeftRight, Y, p2X, p2Y) == 0 && X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight)) addImageToRenderer("images/highlightedSquare.PNG", X + 2 * moveLeftRight, Y, 35, 35);
		else  if (X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(X + moveLeftRight, Y, p2X, p2Y)==1) addImageToRenderer("images/highlightedSquare.PNG", X + moveLeftRight, Y, 35, 35);
		
		if (checkPlayerProximity(X , Y+moveUpDown, p2X, p2Y) == 0 && Y + 2 * moveUpDown <= p1Y_Start) addImageToRenderer("images/highlightedSquare.PNG", X, Y + 2 * moveUpDown, 35, 35);
		else if (Y + moveUpDown <= p1Y_Start &&checkPlayerProximity(X, Y + moveUpDown, p2X, p2Y)==1) addImageToRenderer("images/highlightedSquare.PNG", X, Y + moveUpDown, 35, 35);
		
		if (checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y) == 0 && Y - 2 * moveUpDown >= p2Y_Start) addImageToRenderer("images/highlightedSquare.PNG", X, Y - 2 * moveUpDown, 35, 35);
		else	if (Y - moveUpDown >= p2Y_Start && checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y)==1) addImageToRenderer("images/highlightedSquare.PNG", X, Y - moveUpDown, 35, 35);
	}
	if (playerHighlighter == 2)
	{
		if (checkPlayerProximity(X - moveLeftRight, Y, p1X, p1Y) == 0 && X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight)) addImageToRenderer("images/highlightedSquare.PNG", X - 2 * moveLeftRight, Y, 35, 35);
		else if (X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(X - moveLeftRight, Y, p1X, p1Y)==1) addImageToRenderer("images/highlightedSquare.PNG", X - moveLeftRight, Y, 35, 35);
		
		if (checkPlayerProximity(X + moveLeftRight, Y, p1X, p1Y) == 0 && X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight)) addImageToRenderer("images/highlightedSquare.PNG", X + 2 * moveLeftRight, Y, 35, 35);
		else  if (X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(X + moveLeftRight, Y, p1X, p1Y)==1) addImageToRenderer("images/highlightedSquare.PNG", X + moveLeftRight, Y, 35, 35);
		
		if (checkPlayerProximity(X , Y+moveUpDown, p1X, p1Y) == 0 && Y + 2 * moveUpDown <= p1Y_Start) addImageToRenderer("images/highlightedSquare.PNG", X, Y + 2 * moveUpDown, 35, 35);
		else if (Y + moveUpDown <= p1Y_Start && checkPlayerProximity(X, Y + moveUpDown, p1X, p1Y) == 1) addImageToRenderer("images/highlightedSquare.PNG", X, Y + moveUpDown, 35, 35);
		
		if (checkPlayerProximity(X , Y-moveUpDown, p1X, p1Y) == 0 && Y - 2 * moveUpDown >= p2Y_Start) addImageToRenderer("images/highlightedSquare.PNG", X, Y - 2 * moveUpDown, 35, 35);
		else	if (Y - moveUpDown >= p2Y_Start&& checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y) == 1) addImageToRenderer("images/highlightedSquare.PNG", X, Y - moveUpDown, 35, 35);
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

int playerOnePlay()
{
	bool turnOver = false;
	SDL_Event event;
	int highlighted = 0;
	

	while (!turnOver)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= p1X && event.motion.x <= p1X + 35 && event.motion.y >= p1Y && event.motion.y <= p1Y + 35)
			if (highlighted==0)	
			{
				highlightPossibleMoves(p1X, p1Y,1);
				highlighted = 1;
			}
			else
			{
				createPlayTable();
				highlighted = 0;
			}

			if (highlighted == 0)
			{

			}

			if (highlighted == 1)
			{

				if (checkPlayerProximity(p1X - moveLeftRight,p1Y, p2X, p2Y)==0 && p2X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight))
				{
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - 2 * moveLeftRight && event.motion.x < p1X - 2 * moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength)
						p1X = p1X - 2 * moveLeftRight, turnOver = true;
				}
				else
				if (p1X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(p1X - moveLeftRight, p1Y, p2X, p2Y) == 1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength)
				{
					p1X = p1X - moveLeftRight, turnOver = true;
				}



				if ( checkPlayerProximity (p1X + moveLeftRight,p1Y,p2X, p2Y)==0 && p1X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight))
				{
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + 2 * moveLeftRight && event.motion.x < p1X + 2 * moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength)
				
					p1X = p1X + 2 * moveLeftRight, turnOver = true;
				}
				else
				if (p1X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(p1X + moveLeftRight, p1Y, p2X, p2Y) ==1 )
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength)
					p1X = p1X + moveLeftRight, turnOver = true;



				if (p1Y + moveUpDown <= p1Y_Start)
				if (checkPlayerProximity(p1X, p1Y + moveUpDown, p2X, p2Y) == 0 && p1Y + 2*moveUpDown <= p1Y_Start)
				{
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y + 2 * moveUpDown && event.motion.y < p1Y + 2 * moveUpDown + squareSideLength)
					{
						p1Y = p1Y + 2*moveUpDown, turnOver = true;
					}
				}
				else
				if (checkPlayerProximity(p1X, p1Y + moveUpDown, p2X, p2Y)==1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + moveUpDown + squareSideLength)
				{
					p1Y = p1Y + moveUpDown, turnOver = true;
				}



				if (p1Y - moveUpDown >= p2Y_Start)
				if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y) == 0 && p1Y - 2*moveUpDown >= p2Y_Start)
				{
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y - 2 * moveUpDown && event.motion.y < p1Y - 2 * moveUpDown + squareSideLength)
						p1Y = p1Y - 2 * moveUpDown, turnOver = true;
				}
				else
				if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y)== 1 )
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y - moveUpDown + squareSideLength )
					p1Y = p1Y - moveUpDown, turnOver = true;
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

	playerOneTurn = false;
}

int playerTwoPlay()
{
		bool turnOver = false;
		SDL_Event event;
		int highlighted = 0;
		

		while (!turnOver)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= p2X && event.motion.x <= p2X + 35 && event.motion.y >= p2Y && event.motion.y <= p2Y + 35)
				if (highlighted == 0)
				{
					highlightPossibleMoves(p2X, p2Y,2);
					highlighted = 1;
				}
				else{
					createPlayTable(); highlighted = 0;
				}
				if (highlighted == 1)
				{
					if (checkPlayerProximity(p2X - moveLeftRight,p2Y,p1X,p1Y)==0 && p2X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight))
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - 2 * moveLeftRight && event.motion.x < p2X - 2 * moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength)
							p2X = p2X - 2 * moveLeftRight, turnOver = true;
					}
					else
					if (p2X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(p2X - moveLeftRight, p2Y, p1X, p1Y)==1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength)
					{
						p2X = p2X - moveLeftRight, turnOver = true;
					}



					if (checkPlayerProximity(p2X + moveLeftRight, p2Y, p1X, p1Y)==0 && p2X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight))
					{if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + 2 * moveLeftRight && event.motion.x < p2X + 2 * moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength)
					
						p2X = p2X + 2 * moveLeftRight, turnOver = true;
					}
					else
					if (p2X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(p2X - moveLeftRight, p2Y, p1X, p1Y)==1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength)
						p2X = p2X + moveLeftRight, turnOver = true;



					if (p2Y + moveUpDown <= p1Y_Start)
					if (checkPlayerProximity(p2X, p2Y + moveUpDown, p1X, p1Y) == 0 && p2Y + 2*moveUpDown <= p1Y_Start)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y + 2*moveUpDown && event.motion.y < p2Y + 2*moveUpDown + squareSideLength)
						{
							p2Y = p2Y + 2*moveUpDown, turnOver = true;
						}
					}
					else 
					if (checkPlayerProximity(p2X, p2Y + moveUpDown, p1X, p1Y)==1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + moveUpDown + squareSideLength)
					{p2Y = p2Y + moveUpDown, turnOver = true;}

					
					
					if (p2Y - moveUpDown >= p2Y_Start)
					if (checkPlayerProximity(p2X, p2Y - moveUpDown, p1X, p1Y) == 0 && p2Y -2* moveUpDown >= p2Y_Start)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y -2* moveUpDown && event.motion.y < p2Y - 2*moveUpDown + squareSideLength)
							p2Y = p2Y - 2*moveUpDown, turnOver = true;
					}
					else
					if (checkPlayerProximity(p2X, p2Y - moveUpDown, p1X, p1Y) == 1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y - moveUpDown + squareSideLength)
						p2Y = p2Y - moveUpDown, turnOver = true;
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
	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			createPlayTable();

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

void createInstructionsMenu(SDL_Event event)
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
			createInstructionsMenu(event);

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

void createMainMenu(SDL_Event event)
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
			createMainMenu(event);

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

	runMainMenu();

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}