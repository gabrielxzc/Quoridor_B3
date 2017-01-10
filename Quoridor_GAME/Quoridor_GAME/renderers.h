#pragma once
#include "defines.h"
#include "variables.h"
#include "logistics.h"

void addTextToRenderer(char *font_path, int font_size, char *message_text, int x, int y, SDL_Color &color);
void addImageToRenderer(const char *file, int x, int y, int w, int h);
void renderMainMenu(SDL_Event event);
void renderInstructionsMenu(int page);
void renderStartGameMenu(SDL_Event event);
void highlightWalls(SDL_Event event, int &highlightedWalls, short playerTurn);
void highlightPossibleMoves(int X, int Y, playerInMatrix player, int playerHighlighter);
void renderPlayTable();
void renderPlayerWinTable(int Winner);