#include <iostream>
#include <stdlib.h>

#include "defines.h"
#include "variables.h"
#include "renderers.h"
#include "auxiliaries.h"
#include "logistics.h"
#include "computerPlay.h"
#include "playerPlay.h"

using namespace std;

int runPlayerWinTable(int Winner)
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	renderPlayerWinTable(Winner);

	SDL_RenderPresent(mainRenderer);

	while (isRunning)
	while (SDL_PollEvent(&event))
	{
		renderPlayerWinTable(Winner);
		if (event.motion.x >= 72 && event.motion.y >= 499 && event.motion.x <= 330 && event.motion.y <= 544)
		{
			if (Winner == 1) addImageToRenderer("images/PlayerOneWinMenuHighlighted.JPG", 0, 0, 800, 600);
			if (Winner == 2) addImageToRenderer("images/PlayerTwoWinMenuHighlighted.JPG", 0, 0, 800, 600);


		}
		if (event.motion.x >= 461 && event.motion.y >= 498 && event.motion.x <= 727 && event.motion.y <= 551)
		{
			if (Winner == 1) addImageToRenderer("images/PlayerOneWinAgainHighlighted.JPG", 0, 0, 800, 600);
			if (Winner == 2) addImageToRenderer("images/PlayerTwoWinAgainHighlighted.JPG", 0, 0, 800, 600);

		}

		SDL_RenderPresent(mainRenderer);
		if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= 72 && event.motion.y >= 499 && event.motion.x <= 330 && event.motion.y <= 544)
			return 0;
		if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= 461 && event.motion.y >= 498 && event.motion.x <= 727 && event.motion.y <= 551)
			return 1;
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			return 0;
		}

	}
	return 0;
}

int playingAgainstPlayer()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	int playAgain = 0;
	int menuCall=1;

	p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;

	playerOneWalls = 10;
	playerTwoWalls = 10;

	moves = 0;

	initializeWallMatrix();
	initializeGameMatrix();

	chooseWhoStarts = false;

	playerOneScore = 0;
	playerTwoScore = 0;

	addNumberToStrig(playerOneScore, playerOneScoreC);
	addNumberToStrig(playerTwoScore, playerTwoScoreC);

	while (isRunning)
	{
		renderPlayTable();

		while (SDL_PollEvent(&event))
		{
			if (chooseWhoStarts == false)
			{
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 297 && event.motion.x < 397 && event.motion.y > 288 && event.motion.y < 318)
				{
					playerOneTurn = true;
					chooseWhoStarts = true;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 405 && event.motion.x < 505 && event.motion.y > 288 && event.motion.y < 318)
				{
					playerOneTurn = false;
					chooseWhoStarts = true;
				}
			}
			else
			{
				if (playerOneTurn)
					menuCall = playerOnePlay();
				else
					menuCall = playerTwoPlay();

				if (menuCall == 0) return 0;

				if (p1Y == p2Y_Start)
				{
					Winner = 1;
					playerOneScore++;
					addNumberToStrig(playerOneScore, playerOneScoreC);
					playAgain = runPlayerWinTable(Winner);
					if (playAgain == 0) return 0;
					if (playAgain == 1)
					{
						moves = 0;
						initializeWallMatrix();
						initializeGameMatrix();
						p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
						playerOneWalls = 10;
						playerTwoWalls = 10;
						chooseWhoStarts = false;
					}
				}

				if (p2Y == p1Y_Start)
				{
					Winner = 2;
					playerTwoScore++;
					addNumberToStrig(playerTwoScore, playerTwoScoreC);
					playAgain = runPlayerWinTable(Winner);
					if (playAgain == 0) return 0;
					if (playAgain == 1)
					{
						moves = 0;
						initializeWallMatrix();
						initializeGameMatrix();
						p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
						playerOneWalls = 10;
						playerTwoWalls = 10;
						chooseWhoStarts = false;
					}
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
	return 0;
}

int playingAgainstComputer()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	int playAgain = 0;
	int menuCall = 1;

	p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;

	playerOneWalls = 10;
	playerTwoWalls = 10;

	initializeWallMatrix();
	initializeGameMatrix();

	moves = 0;

	chooseWhoStarts = false;

	playerOneScore = 0;
	playerTwoScore = 0;

	addNumberToStrig(playerOneScore, playerOneScoreC);
	addNumberToStrig(playerTwoScore, playerTwoScoreC);

	while (isRunning)
	{
		renderPlayTable();

		while (SDL_PollEvent(&event))
		{
			if (chooseWhoStarts == false)
			{
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 297 && event.motion.x < 397 && event.motion.y > 288 && event.motion.y < 318)
				{
					playerOneTurn = true;
					chooseWhoStarts = true;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 405 && event.motion.x < 505 && event.motion.y > 288 && event.motion.y < 318)
				{
					playerOneTurn = false;
					chooseWhoStarts = true;
				}
			}
			else
			{
				if (playerOneTurn)
					menuCall = playerOnePlay();
				else
					menuCall = computerPlay();

				if (menuCall == 0) return 0;

				if (p1Y == p2Y_Start)
				{
					Winner = 1;
					playerOneScore++;
					addNumberToStrig(playerOneScore, playerOneScoreC);
					playAgain = runPlayerWinTable(Winner);
					if (playAgain == 0) return 0;
					if (playAgain == 1)
					{
						moves = 0;
						initializeWallMatrix();
						initializeGameMatrix();
						p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
						playerOneWalls = 10;
						playerTwoWalls = 10;
						chooseWhoStarts = false;
					}
				}

				if (p2Y == p1Y_Start)
				{
					Winner = 2;
					playerTwoScore++;
					addNumberToStrig(playerTwoScore, playerTwoScoreC);
					playAgain = runPlayerWinTable(Winner);
					if (playAgain == 0) return 0;
					if (playAgain == 1)
					{
						moves = 0;
						initializeWallMatrix();
						initializeGameMatrix();
						p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
						playerOneWalls = 10;
						playerTwoWalls = 10;
						chooseWhoStarts = false;
					}
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
	return 0;
}

int runStartGameMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
		while (SDL_PollEvent(&event)) 
		{
			renderStartGameMenu(event);

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 95 && event.motion.x < 395 && event.motion.y > 125 && event.motion.y < 525) 
			{
				playingAgainstComputer();
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 405 && event.motion.x < 705 && event.motion.y > 125 && event.motion.y < 525) 
			{
				playingAgainstPlayer();
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

int runInstructionsMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	int page = 1;
	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			renderInstructionsMenu(page);

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 365 && event.motion.x < 435 && event.motion.y > 550 && event.motion.y < 590))
				return 0;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= 0 && event.motion.y >= 250 && event.motion.x <= 100 && event.motion.y <= 350 && page!=1) page--;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= 700 && event.motion.y >= 250 && event.motion.x <= 800 && event.motion.y <= 350 && page!=3) page++;
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
	return 0;
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

