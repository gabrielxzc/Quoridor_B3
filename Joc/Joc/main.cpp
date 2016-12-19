#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
using namespace std;
int mouseX, mouseY;
SDL_Window* window = NULL;
SDL_Texture * Texture;
SDL_Renderer* renderer = NULL;
SDL_Surface * exitButton, *player, *computer, *startGame, *information;
SDL_Rect dstrect;
bool isRunning = true;
void createGameTable()
{
	SDL_RenderClear(renderer);
	SDL_GetMouseState(&mouseX, &mouseY);

	 exitButton = IMG_Load("backbutton.PNG");
	Texture = SDL_CreateTextureFromSurface(renderer, exitButton);
	dstrect = { 20, 20, 60, 60 };
	SDL_RenderCopy(renderer, Texture, NULL, &dstrect);

	SDL_RenderPresent(renderer);

}
int playingAgainstHuman()
{
	SDL_Event event;
	createGameTable();
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			if (event.type == SDL_MOUSEBUTTONDOWN && (mouseX > 20 && mouseX<80 && mouseY>20 && mouseY < 80))
				return 0;
			if (event.type == SDL_QUIT)
			{

				isRunning = false;
				return 0;
			}
		}
	}
}

int playingAgainstComputer()
{
	SDL_Event event;
	createGameTable();
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			if (event.type == SDL_MOUSEBUTTONDOWN && (mouseX > 20 && mouseX<80 && mouseY>20 && mouseY < 80))
				return 0;
			if (event.type == SDL_QUIT)
			{

				isRunning = false;
				return 0;
			}
		}
	}
}





int createDecisionWindow()
{
	
	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_RenderClear(renderer);
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX > 150 && mouseX<450 && mouseY>100 && mouseY < 700)
			{


				computer = IMG_Load("computercolor.PNG");
				Texture = SDL_CreateTextureFromSurface(renderer, computer);
				dstrect = { 150, 100, 300, 600 };
				SDL_RenderCopy(renderer, Texture, NULL, &dstrect);

			}
			else
			{
				computer = IMG_Load("computernoncolor.PNG");
				Texture = SDL_CreateTextureFromSurface(renderer, computer);
				dstrect = { 150, 100, 300, 600 };
				SDL_RenderCopy(renderer, Texture, NULL, &dstrect);
			}
			if (mouseX > 600 && mouseX<900 && mouseY>100 && mouseY < 700)
			{
				player = IMG_Load("versuscolor.PNG");
				Texture = SDL_CreateTextureFromSurface(renderer, player);
				dstrect = { 600, 100, 300, 600 };
				SDL_RenderCopy(renderer, Texture, NULL, &dstrect);
			}
			else
			{
				player = IMG_Load("versusnoncolor.PNG");
				Texture = SDL_CreateTextureFromSurface(renderer, player);
				dstrect = { 600, 100, 300, 600 };
				SDL_RenderCopy(renderer, Texture, NULL, &dstrect);
			}

			SDL_Surface * exitButton = IMG_Load("backbutton.PNG");
			Texture = SDL_CreateTextureFromSurface(renderer, exitButton);
			dstrect = { 20, 20, 60, 60 };
			SDL_RenderCopy(renderer, Texture, NULL, &dstrect);

			if (event.type == SDL_MOUSEBUTTONDOWN && mouseX > 150 && mouseX<450 && mouseY>100 && mouseY < 700) {
				playingAgainstComputer(); 
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&  mouseX > 600 && mouseX<900 && mouseY>100 && mouseY < 700) {
				playingAgainstHuman();
				return 0;
			}
			if ( event.type == SDL_MOUSEBUTTONDOWN && (mouseX > 20 && mouseX<80 && mouseY>20 && mouseY < 80))
				return 0;
			if (event.type == SDL_QUIT)
			{
				
				isRunning = false;
				return 0;
			}
			
			SDL_RenderPresent(renderer);


		}
	}




}
int createRulesWindow()
{
	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_RenderClear(renderer);
			SDL_GetMouseState(&mouseX, &mouseY);

			SDL_Surface * exitButton = IMG_Load("backbutton.PNG");
			Texture = SDL_CreateTextureFromSurface(renderer, exitButton);
			dstrect = { 20, 20, 60, 60 };
			SDL_RenderCopy(renderer, Texture, NULL, &dstrect);


			if (event.type == SDL_MOUSEBUTTONDOWN && (mouseX > 20 && mouseX<80 && mouseY>20 && mouseY < 80))
				return 0;
			if (event.type == SDL_QUIT)
			{

				isRunning = false;
				return 0;
			}

			SDL_RenderPresent(renderer);


		}

	}
}



void createMainMenu()
{

	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_RenderClear(renderer);
			SDL_GetMouseState(&mouseX, &mouseY);

			startGame = IMG_Load("startGame.PNG");
			Texture = SDL_CreateTextureFromSurface(renderer, startGame);
			dstrect = { 100, 300, 800, 100 };
			SDL_RenderCopy(renderer, Texture, NULL, &dstrect);


			information = IMG_Load("rules.PNG");
			Texture = SDL_CreateTextureFromSurface(renderer, information);
			dstrect = { 100, 450, 800, 100 };
			SDL_RenderCopy(renderer, Texture, NULL, &dstrect);


			SDL_Surface * exitButton = IMG_Load("exitButton.PNG");
			Texture = SDL_CreateTextureFromSurface(renderer, exitButton);
			dstrect = { 100, 600, 800, 100 };
			SDL_RenderCopy(renderer, Texture, NULL, &dstrect);

			if (event.type == SDL_MOUSEBUTTONDOWN && (mouseX > 100 && mouseX<900 && mouseY>300 && mouseY<400)) 	createDecisionWindow(); 
			if (event.type == SDL_MOUSEBUTTONDOWN && (mouseX > 100 && mouseX<900 && mouseY>450 && mouseY<550))  createRulesWindow();
			if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN && (mouseX>100 && mouseX<900 && mouseY>600 && mouseY<700))
				isRunning = false;
			SDL_RenderPresent(renderer);


		}
	}







}
int main(int argc, char** argv)
{
	
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow
		(
		"Quoridor", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		768,
		SDL_WINDOW_SHOWN
		);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
	createMainMenu();
	
	SDL_Event event;

	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	return 0;
}