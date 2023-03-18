#ifndef PIPE_ENTRANCE_H
#define PIPE_ENTRANCE_H

#include "global.h"
#include "csimple.h"
#include "graphicsHandler.h"
#include "objectsHolder.h"

void initPipeEntrance(PipeEntrance* pipeEntrance, int xTile, int yTile, int direction, int destLevel, int destPipe, bool enterable) {
	pipeEntrance->xTile = xTile;
	pipeEntrance->yTile = yTile;
	pipeEntrance->exists = 1;
	pipeEntrance->direction = direction;
	pipeEntrance->destLevel = destLevel;
	pipeEntrance->destPipe = destPipe;
	pipeEntrance->enterable = enterable;
}

#endif