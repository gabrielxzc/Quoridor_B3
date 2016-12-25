#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

SDL_Window *mainWindow = nullptr;
SDL_Renderer *mainRenderer = nullptr;
bool isRunning = true; // Inchide tot programul

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

	SDL_RenderPresent(mainRenderer);

}

int playingAgainstComputer()
{
	SDL_Event event;

	createPlayTable();

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
		}
	}
	return 0;
}

int playingAgainstHuman()
{
	SDL_Event event;

	createPlayTable();

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
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
	SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 255);

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
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

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 95 && event.motion.x < 395 && event.motion.y > 125 && event.motion.y < 525) {
				playingAgainstComputer();
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 405 && event.motion.x < 705 && event.motion.y > 125 && event.motion.y < 525) {
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

			SDL_RenderPresent(mainRenderer);
		}
	}
	return 0;
}

int runInstructionsMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 255);

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_RenderClear(mainRenderer);

			addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 800, 600);
			addImageToRenderer("images/backButton.PNG", 365, 550, 70, 40);

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 365 && event.motion.x < 435 && event.motion.y > 550 && event.motion.y < 590))
				return 0;
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return 0;
			}
			SDL_RenderPresent(mainRenderer);
		}
	}

	return 0;
}

int runMainMenu()
{
	SDL_Event event;
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
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

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 175 && event.motion.y < 275))
				runStartGameMenu();
			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 300 && event.motion.y < 400))
				runInstructionsMenu();
			if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 225 && event.motion.x < 575 && event.motion.y > 425 && event.motion.y < 525))
				isRunning = false;

			SDL_RenderPresent(mainRenderer);
		}
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

	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}