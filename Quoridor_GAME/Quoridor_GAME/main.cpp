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

int playingAgainstComputer()
{
	return 0;
}

int playingAgainstHuman()
{
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

			addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 1024, 768);
			addImageToRenderer("images/backButton.PNG", 20, 20, 60, 60);

			if (event.motion.x > 150 && event.motion.x<450 && event.motion.y>100 && event.motion.y < 700)
				addImageToRenderer("images/computercolor.png", 150, 100, 300, 600);
			else
				addImageToRenderer("images/computernoncolor.PNG", 150, 100, 300, 600);
			if (event.motion.x > 600 && event.motion.x<900 && event.motion.y>100 && event.motion.y < 700)
				addImageToRenderer("images/versuscolor.PNG", 600, 100, 300, 600);
			else
				addImageToRenderer("images/versusnoncolor.PNG", 600, 100, 300, 600);

			if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x > 150 && event.motion.x<450 && event.motion.y>100 && event.motion.y < 700) {
				playingAgainstComputer();
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&  event.motion.x > 600 && event.motion.x<900 && event.motion.y>100 && event.motion.y < 700) {
				playingAgainstHuman();
				return 0;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 20 && event.motion.x<80 && event.motion.y>20 && event.motion.y < 80))
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

			addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 1024, 768);
			addImageToRenderer("images/backButton.PNG", 20, 20, 60, 60);

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 20 && event.motion.x<80 && event.motion.y>20 && event.motion.y < 80))
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

			addImageToRenderer("images/mainMenuBackground.JPG", 0, 0, 1024, 768);
			addImageToRenderer("images/startGame.PNG", 100, 300, 800, 100);
			addImageToRenderer("images/rules.PNG", 100, 450, 800, 100);
			addImageToRenderer("images/exitButton.PNG", 100, 600, 800, 100);

			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 100 && event.motion.x < 900 && event.motion.y > 300 && event.motion.y < 400))
				runStartGameMenu();
			if (event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x > 100 && event.motion.x<900 && event.motion.y>450 && event.motion.y<550))
				runInstructionsMenu();
			if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x>100 && event.motion.x<900 && event.motion.y>600 && event.motion.y < 700))
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
		1024,
		768,
		0);

	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	runMainMenu();

	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}