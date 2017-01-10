#include "logistics.h"

void checkPlaceWall(SDL_Event event, bool &turnOver, short playerTurn)
{
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (i % 2 == 0)
			{
				if (mouseHoverVerticalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noVerticalWallsAround(i, j) && stillHasWalls(playerTurn) && thereIsaPathVertical(i, j) == 1){
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

						gameMatrix[i][j * 2] = -1;
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
bool stillHasWalls(short playerTurn)
{
	if (playerOneTurn == true && playerOneWalls == 0)
		return false;

	if (playerOneTurn == false && playerTwoWalls == 0)
		return false;

	return true;
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
int checkPlayerProximity(int xFuture, int yFuture, int xOtherPlayer, int yOtherPlayer)
{
	if (xFuture == xOtherPlayer && yFuture == yOtherPlayer) return 0;
	return 1;
}
short drumMinim(playerInMatrix player, short playerNumber)
{
	short i, j;
	struct pozitii {
		short x, y;
	};

	pozitii coada[2000];
	bool checkedOtherplayer = false;
	short dirLine[] = { -1, 0, 1, 0 };
	short dirCol[] = { 0, 1, 0, -1 };



	short elementeCoada = 0, contorCoada = 0;

	for (i = 0; i < 4; i++)
	{
		if (player.line + 2 * dirLine[i] >= 0 && player.line + 2 * dirLine[i] <= 16 && player.column + 2 * dirCol[i] >= 0 && player.column + 2 * dirCol[i] <= 16)
		{
			if (matriceDrumMinim[player.line + dirLine[i]][player.column + dirCol[i]] == 0 && matriceDrumMinim[player.line + 2 * dirLine[i]][player.column + 2 * dirCol[i]] == 0)
			{
				matriceDrumMinim[player.line + 2 * dirLine[i]][player.column + 2 * dirCol[i]] = 1;
				coada[elementeCoada].x = player.line + 2 * dirLine[i];
				coada[elementeCoada].y = player.column + 2 * dirCol[i];
				elementeCoada++;
			}
			if (matriceDrumMinim[player.line + dirLine[i]][player.column + dirCol[i]] == 0 && (matriceDrumMinim[player.line + 2 * dirLine[i]][player.column + 2 * dirCol[i]] == -10 || -matriceDrumMinim[player.line + 2 * dirLine[i]][player.column + 2 * dirCol[i]] == -20))
			{


				if (matriceDrumMinim[player.line + 3 * dirLine[i]][player.column + 3 * dirCol[i]] == -1)
				{
					if (dirLine[i])
					{
						if (matriceDrumMinim[player.line + 1][player.column + 2 * dirCol[i]] == 0 && player.line + 2 <= 16 && player.line + 2 >= 0 && player.column + 2 * dirCol[i] <= 16 && player.column + 2 * dirCol[i] >= 0)
						{
							matriceDrumMinim[player.line + 2][player.column + 2 * dirCol[i]] = 1;
							coada[elementeCoada].x = player.line + 2;
							coada[elementeCoada].y = player.column + 2 * dirCol[i];
							elementeCoada++;
						}
						if (matriceDrumMinim[player.line - 1][player.column + 2 * dirCol[i]] == 0 && player.line - 2 <= 16 && player.line - 2 >= 0 && player.column + 2 * dirCol[i] <= 16 && player.column + 2 * dirCol[i] >= 0)
						{
							matriceDrumMinim[player.line - 2][player.column + 2 * dirCol[i]] = 1;
							coada[elementeCoada].x = player.line - 2;
							coada[elementeCoada].y = player.column + 2 * dirCol[i];
							elementeCoada++;
						}
					}
					else
					{
						if (matriceDrumMinim[player.line + 2 * dirLine[i]][player.column + 1] == 0 && player.line + 2 * dirLine[i] <= 16 && player.line + 2 * dirLine[i] >= 0 && player.column + 2 <= 16 && player.column + 2 >= 0)
						{
							matriceDrumMinim[player.line + dirLine[i]][player.column + 2] = 1;
							coada[elementeCoada].x = player.line + dirLine[i];
							coada[elementeCoada].y = player.column + 2;
							elementeCoada++;
						}
						if (matriceDrumMinim[player.line + 2 * dirLine[i]][player.column - 1] == 0 && player.line + 2 * dirLine[i] <= 16 && player.line + 2 * dirLine[i] >= 0 && player.column - 2 <= 16 && player.column - 2 >= 0)
						{
							matriceDrumMinim[player.line + dirLine[i]][player.column - 2] = 1;
							coada[elementeCoada].x = player.line + dirLine[i];
							coada[elementeCoada].y = player.column - 2;
							elementeCoada++;
						}


					}



					if (((coada[contorCoada].x + 3 * dirLine[i] > 16 && playerNumber == 2) || (coada[contorCoada].x + 3 * dirLine[i] < 0 && playerNumber == 1)) && checkedOtherplayer == false)
					{
						checkedOtherplayer = true;
						if (matriceDrumMinim[player.line + 2 * dirLine[i]][player.column + 1] == 0 && player.line + 2 * dirLine[i] <= 16 && player.line + 2 * dirLine[i] >= 0 && player.column + 2 <= 16 && player.column + 2 >= 0)
						{
							matriceDrumMinim[player.line + dirLine[i]][player.column + 2] = 1;
							coada[elementeCoada].x = player.line + dirLine[i];
							coada[elementeCoada].y = player.column + 2;
							elementeCoada++;
						}
						if (matriceDrumMinim[player.line + 2 * dirLine[i]][player.column - 1] == 0 && player.line + 2 * dirLine[i] <= 16 && player.line + 2 * dirLine[i] >= 0 && player.column - 2 <= 16 && player.column - 2 >= 0)
						{
							matriceDrumMinim[player.line + dirLine[i]][player.column - 2] = 1;
							coada[elementeCoada].x = player.line + dirLine[i];
							coada[elementeCoada].y = player.column - 2;
							elementeCoada++;
						}
					}
				}


				else
				{

					matriceDrumMinim[player.line + 4 * dirLine[i]][player.column + 4 * dirCol[i]] = 1;
					coada[elementeCoada].x = player.line + 4 * dirLine[i];
					coada[elementeCoada].y = player.column + 4 * dirCol[i];
					elementeCoada++;
				}
			}
		}
	}

	while (contorCoada < elementeCoada)
	{
		for (i = 0; i < 4; i++)
		{
			if (coada[contorCoada].x + 2 * dirLine[i] >= 0 && coada[contorCoada].x + 2 * dirLine[i] <= 16 && coada[contorCoada].y + 2 * dirCol[i] >= 0 && coada[contorCoada].y + 2 * dirCol[i] <= 16)
			{
				if (matriceDrumMinim[coada[contorCoada].x + dirLine[i]][coada[contorCoada].y + dirCol[i]] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2 * dirCol[i]] == 0 || matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2 * dirCol[i]] > matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1))
				{
					matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2 * dirCol[i]] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
					coada[elementeCoada].x = coada[contorCoada].x + 2 * dirLine[i];
					coada[elementeCoada].y = coada[contorCoada].y + 2 * dirCol[i];
					elementeCoada++;
				}

				if (matriceDrumMinim[coada[contorCoada].x + dirLine[i]][coada[contorCoada].y + dirCol[i]] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2 * dirCol[i]] == -10 || matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2 * dirCol[i]] == -20))
				{
					if (((coada[contorCoada].x + 3 * dirLine[i] > 16 && playerNumber == 2) || (coada[contorCoada].x + 3 * dirLine[i] < 0 && playerNumber == 1)) && checkedOtherplayer == false)
					{
						checkedOtherplayer = true;
						if (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 1] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 1]==0 || matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2]>matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1) && coada[contorCoada].x + 2 * dirLine[i] >= 0 && coada[contorCoada].x + 2 * dirLine[i] <= 16 && coada[contorCoada].y + 2 >= 0 && coada[contorCoada].y + 2 <= 16)
						{
							matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
							coada[elementeCoada].x = coada[contorCoada].x + 2 * dirLine[i];
							coada[elementeCoada].y = coada[contorCoada].y + 2;
							elementeCoada++;
						}
						if (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 1] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 2] == 0 || matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 2]> matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1) && coada[contorCoada].x + 2 * dirLine[i] >= 0 && coada[contorCoada].x + 2 * dirLine[i] <= 16 && coada[contorCoada].y - 2 >= 0 && coada[contorCoada].y - 2 <= 16)
						{
							matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 2] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
							coada[elementeCoada].x = coada[contorCoada].x + 2 * dirLine[i];
							coada[elementeCoada].y = coada[contorCoada].y - 2;
							elementeCoada++;
						}


					}

					if (matriceDrumMinim[coada[contorCoada].x + 3 * dirLine[i]][coada[contorCoada].y + 3 * dirCol[i]] == -1)
					{

						if (dirCol[i] == 0)
						{
							if (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 1] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2] == 0 || matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2]>matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1) && coada[contorCoada].x + 2 * dirLine[i] >= 0 && coada[contorCoada].x + 2 * dirLine[i] <= 16 && coada[contorCoada].y + 2 >= 0 && coada[contorCoada].y + 2 <= 16)
							{
								matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y + 2] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
								coada[elementeCoada].x = coada[contorCoada].x + 2 * dirLine[i];
								coada[elementeCoada].y = coada[contorCoada].y + 2;
								elementeCoada++;
							}
							if (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 1] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 2] == 0 || matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 2]> matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1) && coada[contorCoada].x + 2 * dirLine[i] >= 0 && coada[contorCoada].x + 2 * dirLine[i] <= 16 && coada[contorCoada].y - 2 >= 0 && coada[contorCoada].y - 2 <= 16)
							{
								matriceDrumMinim[coada[contorCoada].x + 2 * dirLine[i]][coada[contorCoada].y - 2] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
								coada[elementeCoada].x = coada[contorCoada].x + 2 * dirLine[i];
								coada[elementeCoada].y = coada[contorCoada].y - 2;
								elementeCoada++;
							}
						}
						if (dirLine[i] == 0)
						{
							if (matriceDrumMinim[coada[contorCoada].x + 1][coada[contorCoada].y + 2 * dirCol[i]] == 0 && (matriceDrumMinim[coada[contorCoada].x + 2][coada[contorCoada].y + 2 * dirCol[i]] == 0 || matriceDrumMinim[coada[contorCoada].x + 2][coada[contorCoada].y + 2 * dirCol[i]]>matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1) && coada[contorCoada].x + 2 >= 0 && coada[contorCoada].x + 2 <= 16 && coada[contorCoada].y + 2 * dirCol[i] >= 0 && coada[contorCoada].y + 2 * dirCol[i] <= 16)
							{
								matriceDrumMinim[coada[contorCoada].x + 2][coada[contorCoada].y + 2 * dirCol[i]] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
								coada[elementeCoada].x = coada[contorCoada].x + 2;
								coada[elementeCoada].y = coada[contorCoada].y + 2 * dirCol[i];
								elementeCoada++;
							}
							if (matriceDrumMinim[coada[contorCoada].x - 1][coada[contorCoada].y + 2 * dirCol[i]] == 0 && (matriceDrumMinim[coada[contorCoada].x - 2][coada[contorCoada].y + 2 * dirCol[i]] == 0 || matriceDrumMinim[coada[contorCoada].x - 2][coada[contorCoada].y + 2 * dirCol[i]]>matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1) && coada[contorCoada].x - 2 >= 0 && coada[contorCoada].x - 2 <= 16 && coada[contorCoada].y + 2 * dirCol[i] >= 0 && coada[contorCoada].y + 2 * dirCol[i] <= 16)
							{
								matriceDrumMinim[coada[contorCoada].x - 2][coada[contorCoada].y + 2 * dirCol[i]] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
								coada[elementeCoada].x = coada[contorCoada].x - 2;
								coada[elementeCoada].y = coada[contorCoada].y + 2 * dirLine[i];
								elementeCoada++;
							}


						}


					}
					else
					{
						if (coada[contorCoada].x + 4 * dirLine[i] >= 0 && coada[contorCoada].x + 4 * dirLine[i] <= 16 && coada[contorCoada].y + 4 * dirCol[i] >= 0 && coada[contorCoada].y + 4 * dirCol[i] <= 16 && (matriceDrumMinim[coada[contorCoada].x + 4 * dirLine[i]][coada[contorCoada].y + 4 * dirCol[i]] == 0 || matriceDrumMinim[coada[contorCoada].x + 4 * dirLine[i]][coada[contorCoada].y + 4 * dirCol[i]] > matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1))
						{
							matriceDrumMinim[coada[contorCoada].x + 4 * dirLine[i]][coada[contorCoada].y + 4 * dirCol[i]] = matriceDrumMinim[coada[contorCoada].x][coada[contorCoada].y] + 1;
							coada[elementeCoada].x = coada[contorCoada].x + 4 * dirLine[i];
							coada[elementeCoada].y = coada[contorCoada].y + 4 * dirCol[i];
							elementeCoada++;
						}

					}
				}
			}
		}

		contorCoada++;
	}

	short count = 100;
	if (playerNumber == 1)
	{
		for (i = 0; i <= 16; i = i + 2)

		if (matriceDrumMinim[0][i] < count && matriceDrumMinim[0][i]>0)
			count = matriceDrumMinim[0][i];
	}
	else
	{
		for (i = 0; i <= 16; i = i + 2)
		if (matriceDrumMinim[16][i] < count && matriceDrumMinim[16][i]>0)
			count = matriceDrumMinim[16][i];
	}

	return count;
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
bool inMatrix(int line, int column)
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
		if (coadaElements[coada].line == 0 && player == 1) return true;
		if (coadaElements[coada].line == 16 && player == 2) return true;
		auxiliarMatrix[coadaElements[coada].line][coadaElements[coada].column] = 3;
		directions = false;
		for (i = 0; i <= 3; i++)
		if (auxiliarMatrix[coadaElements[coada].line + directionsLine[i]][coadaElements[coada].column + directionsColumn[i]] != -1 && auxiliarMatrix[coadaElements[coada].line + moveForwardLine[i]][coadaElements[coada].column + moveForwardColumns[i]] != 3 && inMatrix(coadaElements[coada].line + moveForwardLine[i], coadaElements[coada].column + moveForwardColumns[i]) == true)
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
bool thereIsaPathVertical(int i, int j)
{
	bool player1HasRoad, player2HasRoad;
	createAuxiliarMatrix(i, j, 1);

	player1HasRoad = thereIsaRoad(1);
	createAuxiliarMatrix(i, j, 1);
	player2HasRoad = thereIsaRoad(2);

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