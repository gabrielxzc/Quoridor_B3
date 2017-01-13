#pragma once

#include "defines.h"
#include "variables.h"
#include "renderers.h"

void createAuxiliarForWalls();
void createAuxiliarMatrix(int i, int j, int position);
void initializeGameMatrix();
void initializeGameBoardSquaresCoordinates();
void initializeWallMatrix();
void initializeMatriceDrumMinim();
void addNumberToStrig(short number, char string[]);
int runTutorialMenu();