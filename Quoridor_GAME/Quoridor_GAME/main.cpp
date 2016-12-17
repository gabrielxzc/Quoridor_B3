#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

SDL_Window *mainMenu()
{
	SDL_Window *window = nullptr;
	window = SDL_CreateWindow("Quoridor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	// Setup renderer
	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Set render color to red ( background will be rendered in this color )
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	// Clear winow
	SDL_RenderClear(renderer);

	// Create 3 rects for the menu buttons
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_Rect start = { 325, 150, 150, 50 }, info = { 325, 250, 150, 50 }, exit = { 325, 350, 150, 50 };
	SDL_RenderFillRect(renderer, &start);
	SDL_RenderFillRect(renderer, &info);
	SDL_RenderFillRect(renderer, &exit);

	// Render the rect to the screen
	SDL_RenderPresent(renderer);

	return window;
}

SDL_Window *gameMenu()
{
	// Aici Cristinel
}

SDL_Window *instructionsMenu()
{
	// Aici Ionica
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window = nullptr;
	bool isRunning = true;
	SDL_Event event;

	window = mainMenu();

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
			if () // Buton start - Cristi
			{
				window = gameMenu();
				window = mainMenu();
			}
			if () // Buton instructiuni - Ioana
			{
				window = instructionsMenu();
				window = mainMenu();
			}
			if () // Buton exit - Codrin
			{
				isRunning = false;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}