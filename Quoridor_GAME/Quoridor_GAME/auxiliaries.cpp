#include "auxiliaries.h"

using namespace std;

void createAuxiliarForWalls()
{
	int k, t;
	for (k = 0; k <= 16; k++)
	for (t = 0; t <= 16; t++)
		auxiliarMatrix[k][t] = gameMatrix[k][t];


}

void createAuxiliarMatrix(int i, int j, int position)
{
	int k, t;
	for (k = 0; k <= 16; k++)
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

void initializeMatriceDrumMinim()
{
	short i, j;
	for (i = 0; i <= 16; i++)
	for (j = 0; j <= 16; j++)
	{
		if (gameMatrix[i][j] == 1)
			matriceDrumMinim[i][j] = -10;
		else if (gameMatrix[i][j] == 2)
			matriceDrumMinim[i][j] = -20;
		else
			matriceDrumMinim[i][j] = gameMatrix[i][j];
	}

}

void addNumberToStrig(short number, char string[])
{
	char swapValue;

	if (number == 0) 
	{
		string[0] = '0';
		string[1] = '\0';
	}
	else {
		short cifra;
		short i = 0;

		while (number != 0)
		{
			cifra = number % 10;
			string[i] = cifra + '0';
			i++;
			number = number / 10;
		}

		short st = 0, dr = i - 1;
		while (dr > st)
		{
			swapValue = string[st];
			string[st] = string[dr];
			string[dr] = swapValue;

			dr--;
			st++;
		}
		string[i] = '\0';
	}
}

int runTutorialMenu()
{
	SDL_Event event;

	ofstream settingsOut;

	short pos = strlen(settings) - 1;

	while (isRunning)
	{
		renderTutorialMenu();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x >= 450 && event.motion.x <= 472 && event.motion.y >= 566 && event.motion.y <= 588)
			{
				if (settings[pos] == '1')
				{
					settings[pos] = '0';
					settingsOut.open("settings.txt");
					settingsOut << settings;
					settingsOut.close();
				}
				else
				{
					settings[pos] = '1';
					settingsOut.open("settings.txt");
					settingsOut << settings;
					settingsOut.close();
				}
			}
			else 
			{
				if (event.type == SDL_MOUSEBUTTONDOWN)
					return 1;
			}
		}
	}
	return 1;
}