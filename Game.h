#pragma once

#include "LinkedList.h"
#include "Entity.h"

typedef struct {
	LinkedList brickTypes;
	LinkedList bricks;
	Entity* racket;
	LinkedList racketSingleton;
	Entity* ball;
	int ballsLeft;
	LinkedList borders;
	CvMat background;
}Game;

Game* Game_Create();
void Game_Free(Game* game);

void Game_Load(Game* game, const char* animationsRootFolder,
	size_t bricksWall_RowsCols[2],
	Point brickWall_TL);

void Game_MoveNext(Game* game);
void Game_DigestKeyPress(Game* game, int key);
CvMat Game_Draw(Game* game);

