#include <iostream>
#include <stdlib.h>

#include "defines.h"
#include "variables.h"
#include "renderers.h"
#include "auxiliaries.h"
#include "logistics.h"

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
					renderPlayTable();
					highlightPossibleMoves(p1X, p1Y, playerOne, 1);
					highlighted = 1;
				}
				else
				{
					renderPlayTable();
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
				renderPlayTable();

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
				{
					if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y) == 0 && playerTwo.line == 0 && gameMatrix[playerOne.line - 1][playerOne.column] != -1)
					{
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
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

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
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

					if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y) == 0 && p1Y - 2 * moveUpDown >= p2Y_Start && gameMatrix[playerOne.line - 1][playerOne.column] != -1)
					{
						if (gameMatrix[playerOne.line - 3][playerOne.column] == -1)
						{
							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
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

							if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
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

						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y - 2 * moveUpDown && event.motion.y < p1Y - 2 * moveUpDown + squareSideLength && gameMatrix[playerOne.line - 3][playerOne.column] != -1){
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
						renderPlayTable(); 
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
					renderPlayTable();

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
					{
						if (checkPlayerProximity(p2X, p2Y + moveUpDown, p1X, p1Y) == 0 && playerOne.line == 16 && gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
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
								p2Y = p2Y + 2 * moveUpDown, turnOver = true;

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
	int playAgain = 0;
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
			renderPlayTable();

			if (playerOneTurn)
			menuCall=playerOnePlay();
			else
			menuCall=playerTwoPlay();

			if (menuCall == 0) return 0;

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;

			if (p1Y == p2Y_Start)
			{
				Winner = 1;
				playAgain = runPlayerWinTable(Winner);
				if (playAgain == 0) return 0;
				if (playAgain == 1)
				{
					initializeWallMatrix();
					initializeGameMatrix();
					p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
					playerOneWalls = 10;
					playerTwoWalls = 10;
					playerOneTurn = true;
				}
			}

			if (p2Y == p1Y_Start)
			{
				Winner = 2;
				playAgain = runPlayerWinTable(Winner);
				if (playAgain == 0) return 0;
				if (playAgain == 1)
				{
					initializeWallMatrix();
					initializeGameMatrix();
					p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
					playerOneWalls = 10;
					playerTwoWalls = 10;
					playerOneTurn = true;
				}
			}
			
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
	return 0;
}

void computerMove()
{
	short i;

	short line, column;
	short count = 999;

	short dirLine[] = { -1, 0, 1, 0 };
	short dirCol[] = { 0, 1, 0, -1 };
	int specialCondition = 0;
	playerInMatrix playerAuxiliar;

	short drumulScurt;

	initializeMatriceDrumMinim();
	if (drumMinim(playerTwo, 2) == 1)
	{
		p2Y = p1Y_Start;
		return;
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			initializeMatriceDrumMinim();

			if (playerTwo.line + 2 * dirLine[i] >= 0 && playerTwo.line + 2 * dirLine[i] <= 16 && playerTwo.column + 2 * dirCol[i] >= 0 && playerTwo.column + 2 * dirCol[i] <= 16 && matriceDrumMinim[playerTwo.line + dirLine[i]][playerTwo.column + dirCol[i]] == 0)
			{
				if (matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column + 2 * dirCol[i]] == 0)
				{
					matriceDrumMinim[playerTwo.line][playerTwo.column] = 0;
					matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column + 2 * dirCol[i]] = 2;

					playerAuxiliar.line = playerTwo.line + 2 * dirLine[i];
					playerAuxiliar.column = playerTwo.column + 2 * dirCol[i];

					drumulScurt = drumMinim(playerAuxiliar, 2);

					if (drumulScurt < count)
					{
						count = drumulScurt;
						line = playerAuxiliar.line;
						column = playerAuxiliar.column;
						specialCondition = 0;
					}
				}
				else if (matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column + 2 * dirCol[i]] == -10)
				{
					if (matriceDrumMinim[playerTwo.line + 3 * dirLine[i]][playerTwo.column + 3 * dirCol[i]] == 0)
					{

						if (playerTwo.line + 4 * dirLine[i] >= 0 && playerTwo.line + 4 * dirLine[i] <= 16 && playerTwo.column + 4 * dirCol[i] >= 0 && playerTwo.column + 4 * dirCol[i] <= 16)

						{
							matriceDrumMinim[playerTwo.line][playerTwo.column] = 0;
							matriceDrumMinim[playerTwo.line + 4 * dirLine[i]][playerTwo.column + 4 * dirCol[i]] = 2;

							playerAuxiliar.line = playerTwo.line + 4 * dirLine[i];
							playerAuxiliar.column = playerTwo.column + 4 * dirCol[i];

							drumulScurt = drumMinim(playerAuxiliar, 2);

							if (drumulScurt < count)
							{
								count = drumulScurt;
								line = playerAuxiliar.line;
								column = playerAuxiliar.column;
								specialCondition = 1;
							}
						}
					}
					else
					{
						if (matriceDrumMinim[playerTwo.line + 3 * dirLine[i]][playerTwo.column + 3 * dirCol[i]] == -1 || playerTwo.line + 3 * dirLine[i]>16)
						{
							if (dirCol[i] == 0)
							{
								if (matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column + 1] == 0 && playerTwo.line + 2 * dirLine[i] >= 0 && playerTwo.line + 2 * dirLine[i] <= 16 && playerTwo.column + 2 >= 0 && playerTwo.column + 2 <= 16)
								{
									matriceDrumMinim[playerTwo.line][playerTwo.column] = 0;
									matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column + 2] = 2;
									playerAuxiliar.line = playerTwo.line + 2 * dirLine[i];
									playerAuxiliar.column = playerTwo.column + 2;
									drumulScurt = drumMinim(playerAuxiliar, 2);
									if (drumulScurt < count)
									{
										count = drumulScurt;
										line = playerAuxiliar.line;
										column = playerAuxiliar.column;
										specialCondition = 0;
									}
								}
								if (matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column - 1] == 0 && playerTwo.line + 2 * dirLine[i] >= 0 && playerTwo.line + 2 * dirLine[i] <= 16 && playerTwo.column - 2 >= 0 && playerTwo.column - 2 <= 16)
								{
									matriceDrumMinim[playerTwo.line][playerTwo.column] = 0;
									matriceDrumMinim[playerTwo.line + 2 * dirLine[i]][playerTwo.column - 2] = 2;
									playerAuxiliar.line = playerTwo.line + 2 * dirLine[i];
									playerAuxiliar.column = playerTwo.column - 2;
									drumulScurt = drumMinim(playerAuxiliar, 2);
									if (drumulScurt < count)
									{
										count = drumulScurt;
										line = playerAuxiliar.line;
										column = playerAuxiliar.column;
										specialCondition = 0;
									}
								}
							}
							if (dirLine[i] == 0)
							{
								if (matriceDrumMinim[playerTwo.line + 1][playerTwo.line + 2 * dirCol[i]] == 0 && playerTwo.line + 2 >= 0 && playerTwo.line + 2 <= 16 && playerTwo.column + 2 * dirCol[i] >= 0 && playerTwo.column + 2 * dirCol[i] <= 16)
								{
									matriceDrumMinim[playerTwo.line][playerTwo.column] = 0;
									matriceDrumMinim[playerTwo.line + 2][playerTwo.column + 2 * dirCol[i]] = 2;
									playerAuxiliar.line = playerTwo.line + 2;
									playerAuxiliar.column = playerTwo.column + 2 * dirCol[i];
									drumulScurt = drumMinim(playerAuxiliar, 2);
									if (drumulScurt < count)
									{
										count = drumulScurt;
										line = playerAuxiliar.line;
										column = playerAuxiliar.column;
										specialCondition = 0;
									}
								}
								if (matriceDrumMinim[playerTwo.line - 1][playerTwo.line + 2 * dirCol[i]] == 0 && playerTwo.line - 2 >= 0 && playerTwo.line - 2 <= 16 && playerTwo.column + 2 * dirCol[i] >= 0 && playerTwo.column + 2 * dirCol[i] <= 16)
								{
									matriceDrumMinim[playerTwo.line][playerTwo.column] = 0;
									matriceDrumMinim[playerTwo.line - 2][playerTwo.column + 2 * dirCol[i]] = 2;
									playerAuxiliar.line = playerTwo.line - 2;
									playerAuxiliar.column = playerTwo.column + 2 * dirCol[i];
									drumulScurt = drumMinim(playerAuxiliar, 2);
									if (drumulScurt < count)
									{
										count = drumulScurt;
										line = playerAuxiliar.line;
										column = playerAuxiliar.column;
										specialCondition = 0;
									}
								}


							}

						}

					}
				}

			}
		}

		if (specialCondition == 0)
		{
			if (line - playerTwo.line > 0)
				p2Y = p2Y + moveUpDown;
			else
			{
				if (line - playerTwo.line < 0)
					p2Y = p2Y - moveUpDown;
			}

			if (column - playerTwo.column > 0)
				p2X = p2X + moveLeftRight;
			else
			{
				if (column - playerTwo.column < 0)
					p2X = p2X - moveLeftRight;
			}
		}
		if (specialCondition == 1)
		{
			if (line - playerTwo.line > 0)
				p2Y = p2Y + 2 * moveUpDown;
			else
			{
				if (line - playerTwo.line < 0)
					p2Y = p2Y - 2 * moveUpDown;
			}

			if (column - playerTwo.column > 0)
				p2X = p2X + 2 * moveLeftRight;
			else
			{
				if (column - playerTwo.column < 0)
					p2X = p2X - 2 * moveLeftRight;
			}
		}
		gameMatrix[playerTwo.line][playerTwo.column] = 0;
		gameMatrix[line][column] = 2;
		playerTwo.line = line;
		playerTwo.column = column;
	}
}

void computerPlaceWall()
{
	short i, j;
	short count = 999;
	bool playerOneRoad, playerTwoRoad;
	short minPlayerOne, minPlayerTwo;
	short line = 0, column = 0;

	initializeMatriceDrumMinim();
	minPlayerTwo = drumMinim(playerTwo, 2);

	initializeMatriceDrumMinim();
	minPlayerOne = drumMinim(playerOne, 1);

	short drumInitial = minPlayerTwo - minPlayerOne;

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			initializeMatriceDrumMinim();
			if (i % 2 == 0)
			{

				j++;

				if (matriceDrumMinim[i][j] != -1 && matriceDrumMinim[i + 1][j] != -1 && matriceDrumMinim[i + 2][j] != -1)
				{

					gameMatrix[i][j] = -1;
					gameMatrix[i + 1][j] = -1;
					gameMatrix[i + 2][j] = -1;
					createAuxiliarForWalls();
					playerOneRoad = thereIsaRoad(1);
					createAuxiliarForWalls();
					playerTwoRoad = thereIsaRoad(2);

					if (playerOneRoad == true && playerTwoRoad == true)
					{
						initializeMatriceDrumMinim();
						minPlayerTwo = drumMinim(playerTwo, 2);

						initializeMatriceDrumMinim();
						minPlayerOne = drumMinim(playerOne, 1);



						if (minPlayerTwo - minPlayerOne <= count)
						{
							count = minPlayerTwo - minPlayerOne;
							line = i;
							column = j;

						}
					}
					gameMatrix[i][j] = 0;
					gameMatrix[i + 1][j] = 0;
					gameMatrix[i + 2][j] = 0;
				}

			}
			else
			{

				if (matriceDrumMinim[i][j] != -1 && matriceDrumMinim[i][j + 1] != -1 && matriceDrumMinim[i][j + 2] != -1)
				{

					gameMatrix[i][j] = -1;
					gameMatrix[i][j + 1] = -1;
					gameMatrix[i][j + 2] = -1;
					createAuxiliarForWalls();
					playerOneRoad = thereIsaRoad(1);
					createAuxiliarForWalls();
					playerTwoRoad = thereIsaRoad(2);
					if (playerOneRoad == true && playerTwoRoad == true)
					{
						initializeMatriceDrumMinim();
						minPlayerTwo = drumMinim(playerTwo, 2);

						initializeMatriceDrumMinim();
						minPlayerOne = drumMinim(playerOne, 1);



						if (minPlayerTwo - minPlayerOne <= count)
						{
							count = minPlayerTwo - minPlayerOne;
							line = i;
							column = j;
						}

					}
					gameMatrix[i][j] = 0;
					gameMatrix[i][j + 1] = 0;
					gameMatrix[i][j + 2] = 0;
				}

				j++;
			}
		}
	}



	if (count >= drumInitial)
	{
		computerMove();
	}
	else
	{
		wallMatrix[line][column / 2].placed = 1;

		if (line % 2 == 0)
		{
			gameMatrix[line][column] = -1;
			gameMatrix[line + 1][column] = -1;
			gameMatrix[line + 2][column] = -1;
		}
		else
		{
			gameMatrix[line][column] = -1;
			gameMatrix[line][column + 1] = -1;
			gameMatrix[line][column + 2] = -1;
		}

		playerTwoWalls--;
	}
}

int computerPlay()
{
	initializeMatriceDrumMinim();
	short minPlayerOne = drumMinim(playerOne, 1);

	initializeMatriceDrumMinim();
	short minPlayerTwo = drumMinim(playerTwo, 2);
	cout << minPlayerOne << ' ' << minPlayerTwo << endl;
	if (minPlayerOne >= minPlayerTwo)
	{
		computerMove();
	}
	else
	{
		if (playerTwoWalls > 0)
			computerPlaceWall();
		else
			computerMove();
	}

	playerOneTurn = true;
	return 1;
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

	playerOneTurn = true;

	initializeWallMatrix();
	initializeGameMatrix();

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (playerOneTurn)
				menuCall = playerOnePlay();
			else
				menuCall = computerPlay();

			if (menuCall == 0) return 0;

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;

			if (p1Y == p2Y_Start)
			{
				Winner = 1;
				playAgain = runPlayerWinTable(Winner);
				if (playAgain == 0) return 0;
				if (playAgain == 1)
				{
					initializeWallMatrix();
					initializeGameMatrix();
					p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
					playerOneWalls = 10;
					playerTwoWalls = 10;
					playerOneTurn = true;
				}
			}

			if (p2Y == p1Y_Start)
			{
				Winner = 2;
				playAgain = runPlayerWinTable(Winner);
				if (playAgain == 0) return 0;
				if (playAgain == 1)
				{
					initializeWallMatrix();
					initializeGameMatrix();
					p1X = p1X_Start, p1Y = p1Y_Start, p2X = p2X_Start, p2Y = p2Y_Start;
					playerOneWalls = 10;
					playerTwoWalls = 10;
					playerOneTurn = true;
				}
			}

			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
		renderPlayTable();
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

