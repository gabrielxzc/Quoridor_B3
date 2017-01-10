#pragma once

#include "defines.h"
#include "variables.h"
#include "auxiliaries.h"

void checkPlaceWall(SDL_Event event, bool &turnOver, short playerTurn);
bool stillHasWalls(short playerTurn);
bool noVerticalWallsAround(int line, int column);
bool noHorizontalWallsAround(int line, int column);
int checkPlayerProximity(int xFuture, int yFuture, int xOtherPlayer, int yOtherPlayer);
short drumMinim(playerInMatrix player, short playerNumber);
bool mouseHoverVerticalWall(SDL_Event event, int x, int y);
bool mouseHoverOrizontalWall(SDL_Event event, int x, int y);
bool thereIsaaPathOrizontal(int i, int j);
bool thereIsaPathVertical(int i, int j);
bool thereIsaRoad(int player);
bool inMatrix(int line, int column);