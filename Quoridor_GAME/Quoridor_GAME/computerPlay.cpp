#include "computerPlay.h"

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

	updateMove(p2X, p2Y, playerTwo.line, playerTwo.column, 100, 500, false, false);

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
		updateMove(0, 0, 0, 0, line, column/2, true, false);

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