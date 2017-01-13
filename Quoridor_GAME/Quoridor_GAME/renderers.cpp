#include "renderers.h"

void addTextToRenderer(char *font_path, int font_size, char *message_text, int x, int y, SDL_Color &color)
{
	TTF_Font *font = nullptr;
	SDL_Surface *textSurface = nullptr;
	SDL_Texture *textTexture = nullptr;
	SDL_Rect textRect;

	font = TTF_OpenFont(font_path, font_size);
	textSurface = TTF_RenderText_Solid(font, message_text, color);
	textTexture = SDL_CreateTextureFromSurface(mainRenderer, textSurface);

	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);

	SDL_RenderCopy(mainRenderer, textTexture, nullptr, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void addImageToRenderer(const char *file, int x, int y, int w, int h)
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

void renderInstructionsMenu(int page)
{
	SDL_RenderClear(mainRenderer);
	addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 800, 600);
	if (page == 1) addImageToRenderer("images/rulesPage1.PNG", 20, 130, 800, 408);
	if (page == 2) addImageToRenderer("images/rulesPage2.PNG", 20, 130, 800, 408);
	if (page == 3) addImageToRenderer("images/rulesPage3.PNG", 20, 130, 800, 408);
	if (page == 4) addImageToRenderer("images/rulesPage4.PNG", 20, 130, 800, 408);


	if (page != 1)addImageToRenderer("images/RulesLeft.PNG", 0, 250, 100, 100);
	if (page != 4)addImageToRenderer("images/RulesRight.PNG", 700, 250, 100, 100);
	addImageToRenderer("images/backButton.PNG", 365, 550, 70, 40);

	SDL_RenderPresent(mainRenderer);
}

void renderStartGameMenu(SDL_Event event)
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

void highlightWalls(SDL_Event event, int &highlightedWalls, short playerTurn)
{
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (i % 2 == 0)
			{
				if (mouseHoverVerticalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noVerticalWallsAround(i, j) && stillHasWalls(playerTurn)){
					renderPlayTable();
					if (thereIsaPathVertical(i, j) == true)	addImageToRenderer("images/pereteVerticalNotFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 14, 98);
					else addImageToRenderer("images/pereteNotDrum.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 14, 98);
					SDL_RenderPresent(mainRenderer);
					highlightedWalls = 1;
				}
			}
			else
			{
				if (mouseHoverOrizontalWall(event, wallMatrix[i][j].x, wallMatrix[i][j].y) && noHorizontalWallsAround(i, j) && stillHasWalls(playerTurn)){
					renderPlayTable();
					if (thereIsaaPathOrizontal(i, j) == true)
						addImageToRenderer("images/pereteNotFilled.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 98, 14);
					else addImageToRenderer("images/pereteNotDrum.png", wallMatrix[i][j].x, wallMatrix[i][j].y, 98, 14);
					SDL_RenderPresent(mainRenderer);
					highlightedWalls = 1;
				}
			}
		}
	}
}

void highlightPossibleMoves(int X, int Y, playerInMatrix player, int playerHighlighter)
{
	if (playerHighlighter == 1)
	{
		if (checkPlayerProximity(X - moveLeftRight, Y, p2X, p2Y) == 0 && X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight) && gameMatrix[player.line][player.column - 1] != -1)
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
		if (X - moveLeftRight >= p1X_Start - (4 * moveLeftRight) && checkPlayerProximity(X - moveLeftRight, Y, p2X, p2Y) == 1 && gameMatrix[player.line][player.column - 1] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X - moveLeftRight, Y, 35, 35);


		if (checkPlayerProximity(X + moveLeftRight, Y, p2X, p2Y) == 0 && X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight) && gameMatrix[player.line][player.column + 1] != -1)
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
		if (X + moveLeftRight <= p1X_Start + (4 * moveLeftRight) && checkPlayerProximity(X + moveLeftRight, Y, p2X, p2Y) == 1 && gameMatrix[player.line][player.column + 1] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X + moveLeftRight, Y, 35, 35);


		if (checkPlayerProximity(X, Y + moveUpDown, p2X, p2Y) == 0 && Y + 2 * moveUpDown <= p1Y_Start && gameMatrix[player.line + 1][player.column] != -1)
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
		if (Y + moveUpDown <= p1Y_Start &&checkPlayerProximity(X, Y + moveUpDown, p2X, p2Y) == 1 && gameMatrix[player.line + 1][player.column] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X, Y + moveUpDown, 35, 35);

		if (checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y) == 0 && playerTwo.line == 0 && gameMatrix[player.line - 1][player.column] != -1)
		{
			if (gameMatrix[playerTwo.line][playerTwo.column - 1] != -1)
				addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 - 1].x, gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 - 1].y, 35, 35);
			if (gameMatrix[playerTwo.line][playerTwo.column + 1] != -1)
				addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 + 1].x, gameBoardSquareMatrix[playerTwo.line / 2][playerTwo.column / 2 + 1].y, 35, 35);
		}

		if (checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y) == 0 && Y - 2 * moveUpDown >= p2Y_Start && gameMatrix[player.line - 1][player.column] != -1)
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
		if (Y - moveUpDown >= p2Y_Start && checkPlayerProximity(X, Y - moveUpDown, p2X, p2Y) == 1 && gameMatrix[player.line - 1][player.column] != -1)
			addImageToRenderer("images/highlightedSquare.PNG", X, Y - moveUpDown, 35, 35);
	}

	if (playerHighlighter == 2)
	{
		if (checkPlayerProximity(X - moveLeftRight, Y, p1X, p1Y) == 0 && X - 2 * moveLeftRight >= p1X_Start - (4 * moveLeftRight) && gameMatrix[player.line][player.column - 1] != -1)
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


		if (checkPlayerProximity(X + moveLeftRight, Y, p1X, p1Y) == 0 && X + 2 * moveLeftRight <= p1X_Start + (4 * moveLeftRight) && gameMatrix[player.line][player.column + 1] != -1)
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

		if (checkPlayerProximity(X, Y + moveUpDown, p1X, p1Y) == 0 && playerOne.line == 16 && gameMatrix[player.line + 1][player.column] != -1)
		{
			if (gameMatrix[playerOne.line][playerOne.column - 1] != -1)
				addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 - 1].x, gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 - 1].y, 35, 35);
			if (gameMatrix[playerOne.line][playerOne.column + 1] != -1)
				addImageToRenderer("images/highlightedSquare.png", gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 + 1].x, gameBoardSquareMatrix[playerOne.line / 2][playerOne.column / 2 + 1].y, 35, 35);
		}

		if (checkPlayerProximity(X, Y + moveUpDown, p1X, p1Y) == 0 && Y + 2 * moveUpDown <= p1Y_Start && gameMatrix[player.line + 1][player.column] != -1)
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


		if (checkPlayerProximity(X, Y - moveUpDown, p1X, p1Y) == 0 && Y - 2 * moveUpDown >= p2Y_Start && gameMatrix[player.line - 1][player.column] != -1)
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

void renderPlayTable()
{
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	SDL_RenderClear(mainRenderer);

	if (playerOneTurn == true) addImageToRenderer("images/gameBoardPlayer1.PNG", 0, 0, 800, 600);
	else addImageToRenderer("images/gameBoardPlayer2.PNG", 0, 0, 800, 600);

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

	if (chooseWhoStarts == false)
	{
		addImageToRenderer("images/chooseWhoStartsButton.png", 250, 220, 300, 120);
		addImageToRenderer("images/chooseRed.png", 297, 288, 100, 30);
		addImageToRenderer("images/chooseGreen.png", 405, 288, 100, 30);
	}

	SDL_Color grey = {40, 40, 40, 255};

	addTextToRenderer("fonts/yorkbailehill.ttf", 27, playerOneScoreC, 117, 552, grey);
	addTextToRenderer("fonts/yorkbailehill.ttf", 27, playerTwoScoreC, 667, -10, grey);

	addImageToRenderer("images/undo.png", 10, 20, 40, 40);

	SDL_RenderPresent(mainRenderer);
}

void renderPlayerWinTable(int Winner)
{
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mainRenderer);
	if (Winner == 1) addImageToRenderer("images/PlayerOneWin.JPG", 0, 0, 800, 600);
	if (Winner == 2) addImageToRenderer("images/PlayerTwoWin.JPG", 0, 0, 800, 600);

}