#include "playerPlay.h"

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
						if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y + squareSideLength - moveUpDown && gameMatrix[playerTwo.line - 1][playerTwo.column] != -1){

							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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
						
						updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);
						
						p1X = p1X - 2 * moveLeftRight, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.column -= 4;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
				else
				if (p1X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(p1X - moveLeftRight, p1Y, p2X, p2Y) == 1 && gameMatrix[playerOne.line][playerOne.column - 1] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength)
				{
					updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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
							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + 2 * moveLeftRight && event.motion.x < p1X + 2 * moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength && gameMatrix[playerOne.line][playerOne.column + 3] != -1){
						
						updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);
						
						p1X = p1X + 2 * moveLeftRight, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.column += 4;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
				else
				if (p1X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(p1X + moveLeftRight, p1Y, p2X, p2Y) == 1 && gameMatrix[playerOne.line][playerOne.column + 1] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareSideLength && event.motion.y > p1Y && event.motion.y < p1Y + squareSideLength){
					
					updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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
							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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
							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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
						updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

						p1Y = p1Y + 2 * moveUpDown, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.line += 4;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
				else
				if (checkPlayerProximity(p1X, p1Y + moveUpDown, p2X, p2Y) == 1 && gameMatrix[playerOne.line + 1][playerOne.column] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + moveUpDown + squareSideLength)
				{
					updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

								updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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

								updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);

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
							
							updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);
							
							p1Y = p1Y - 2 * moveUpDown, turnOver = true;

							gameMatrix[playerOne.line][playerOne.column] = 0;
							playerOne.line -= 4;
							gameMatrix[playerOne.line][playerOne.column] = 1;
						}
					}
					else
					if (checkPlayerProximity(p1X, p1Y - moveUpDown, p2X, p2Y) == 1 && gameMatrix[playerOne.line - 1][playerOne.column] != -1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareSideLength && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y - moveUpDown + squareSideLength){
						
						updateMove(p1X, p1Y, playerOne.line, playerOne.column, 100, 0, false, true);
						
						p1Y = p1Y - moveUpDown, turnOver = true;

						gameMatrix[playerOne.line][playerOne.column] = 0;
						playerOne.line -= 2;
						gameMatrix[playerOne.line][playerOne.column] = 1;
					}
				}
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 10 && event.motion.x < 50 && event.motion.y > 20 && event.motion.y < 60 && moves !=0)
			{
				if (moves >= 2 && (stivaUndo[moves-1].j == 500 || stivaUndo[moves-1].x == 500))
				{
					undoMove();
					undoMove();
					return 1;
				}
				else
					if (stivaUndo[moves - 1].j != 500 && stivaUndo[moves - 1].x != 500)
					{
						undoMove();
						return 1;
					}
			}

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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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
						updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);
						
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

					updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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
							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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
							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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
						
						updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

						p2X = p2X + 2 * moveLeftRight, turnOver = true;

						gameMatrix[playerTwo.line][playerTwo.column] = 0;
						playerTwo.column += 4;
						gameMatrix[playerTwo.line][playerTwo.column] = 2;
					}
				}
				else
				if (p2X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(p2X - moveLeftRight, p2Y, p1X, p1Y) == 1 && gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareSideLength && event.motion.y > p2Y && event.motion.y < p2Y + squareSideLength){
					
					updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);
					
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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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

								updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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

								updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

							p2Y = p2Y + 2 * moveUpDown, turnOver = true;

							gameMatrix[playerTwo.line][playerTwo.column] = 0;
							playerTwo.line += 4;
							gameMatrix[playerTwo.line][playerTwo.column] = 2;
						}
					}
					else
					if (checkPlayerProximity(p2X, p2Y + moveUpDown, p1X, p1Y) == 1 && gameMatrix[playerTwo.line + 1][playerTwo.column] != -1)
					if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + moveUpDown + squareSideLength) {
						
						updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);
						
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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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

							updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);

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
						
						updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);
						
						p2Y = p2Y - 2 * moveUpDown, turnOver = true;

						gameMatrix[playerTwo.line][playerTwo.column] = 0;
						playerTwo.line -= 4;
						gameMatrix[playerTwo.line][playerTwo.column] = 2;
					}
				}
				else
				if (checkPlayerProximity(p2X, p2Y - moveUpDown, p1X, p1Y) == 1 && gameMatrix[playerTwo.line - 1][playerTwo.column] != -1)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareSideLength && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y - moveUpDown + squareSideLength){
					
					updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 0, false, false);
					
					p2Y = p2Y - moveUpDown, turnOver = true;

					gameMatrix[playerTwo.line][playerTwo.column] = 0;
					playerTwo.line -= 2;
					gameMatrix[playerTwo.line][playerTwo.column] = 2;
				}
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 10 && event.motion.x < 50 && event.motion.y > 20 && event.motion.y < 60 && moves != 0)
			{
				undoMove();
				return 1;
			}

			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
	}
	playerOneTurn = true;
}
