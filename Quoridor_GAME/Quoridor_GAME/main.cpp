#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define p1XS 382
#define p1YS 504
#define p2XS 382
#define p2YS 56
#define moveUpDown 56
#define moveLeftRight 59
#define squareL 35

using namespace std;

SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRenderer = nullptr;
bool isRunning = true; // Inchide tot programul
bool playerOneTurn = true;
short playerOneWalls = 10;
short playerTwoWalls = 10;
int p1X, p1Y, p2X, p2Y;


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

void createPlayTable()
{
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	SDL_RenderClear(mainRenderer);

	addImageToRenderer("images/gameBoard.JPG", 0, 0, 800, 600);
	addImageToRenderer("images/backButton.PNG", 700, 550, 70, 40);
	addImageToRenderer("images/playerOne.PNG", p1X, p1Y, 35, 35);
	addImageToRenderer("images/playerTwo.PNG", p2X, p2Y, 35, 35);

	SDL_RenderPresent(mainRenderer);
}

void highlightPossibleMoves(int X, int Y)
{
	if (X - moveLeftRight >= p1XS - (4*moveLeftRight)) addImageToRenderer("images/highlightedSquare.PNG", X - moveLeftRight, Y, 35, 35);
	if (X + moveLeftRight <= p1XS + (4*moveLeftRight)) addImageToRenderer("images/highlightedSquare.PNG", X + moveLeftRight, Y, 35, 35);
	if (Y + moveUpDown <= p1YS ) addImageToRenderer("images/highlightedSquare.PNG", X, Y + moveUpDown, 35, 35);
	if (Y - moveUpDown >= p2YS ) addImageToRenderer("images/highlightedSquare.PNG", X, Y - moveUpDown, 35, 35);

	SDL_RenderPresent(mainRenderer);
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

void playerOnePlay()
{
	bool turnOver = false;
	SDL_Event event;

	highlightPossibleMoves(p1X, p1Y);

	while (!turnOver)
	{
		while (SDL_PollEvent(&event))
		{
			if (p1X - moveLeftRight >= p1XS - (4 * moveLeftRight))
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X - moveLeftRight && event.motion.x < p1X - moveLeftRight + squareL && event.motion.y > p1Y && event.motion.y < p1Y + squareL)
					p1X = p1X - moveLeftRight, turnOver = true;

			if (p1X + moveLeftRight <= p1XS + (4 * moveLeftRight))
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X + moveLeftRight && event.motion.x < p1X + moveLeftRight + squareL && event.motion.y > p1Y && event.motion.y < p1Y + squareL)
					p1X = p1X + moveLeftRight, turnOver = true;

			if (p1Y + moveUpDown <= p1YS)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareL && event.motion.y > p1Y + moveUpDown && event.motion.y < p1Y + moveUpDown + squareL)
					p1Y = p1Y + moveUpDown, turnOver = true;

			if (p1Y - moveUpDown >= p2YS)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p1X && event.motion.x < p1X + squareL && event.motion.y > p1Y - moveUpDown && event.motion.y < p1Y - moveUpDown + squareL)
					p1Y = p1Y - moveUpDown, turnOver = true;
		}
	}

	playerOneTurn = false;
}

void playerTwoPlay()
{
		bool turnOver = false;
		SDL_Event event;

		highlightPossibleMoves(p2X, p2Y);

		while (!turnOver)
		{
			while (SDL_PollEvent(&event))
			{
				if (p2X - moveLeftRight >= p1XS - (4 * moveLeftRight))
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X - moveLeftRight && event.motion.x < p2X - moveLeftRight + squareL && event.motion.y > p2Y && event.motion.y < p2Y + squareL)
					p2X = p2X - moveLeftRight, turnOver = true;

				if (p2X + moveLeftRight <= p1XS + (4 * moveLeftRight))
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X + moveLeftRight && event.motion.x < p2X + moveLeftRight + squareL && event.motion.y > p2Y && event.motion.y < p2Y + squareL)
					p2X = p2X + moveLeftRight, turnOver = true;

				if (p2Y + moveUpDown <= p1YS)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareL && event.motion.y > p2Y + moveUpDown && event.motion.y < p2Y + moveUpDown + squareL)
					p2Y = p2Y + moveUpDown, turnOver = true;

				if (p2Y - moveUpDown >= p2YS)
				if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > p2X && event.motion.x < p2X + squareL && event.motion.y > p2Y - moveUpDown && event.motion.y < p2Y - moveUpDown + squareL)
					p2Y = p2Y - moveUpDown, turnOver = true;
			}
		}
	playerOneTurn = true;
}

int playingAgainstHuman()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	
	p1X = p1XS, p1Y = p1YS, p2X = p2XS, p2Y = p2YS;

	while (isRunning)
		while (SDL_PollEvent(&event))
		{
			createPlayTable();

			if (playerOneTurn)
				playerOnePlay();
			else
				playerTwoPlay();

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 700 && event.motion.x < 770 && event.motion.y > 550 && event.motion.y < 590)
				return 0;

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