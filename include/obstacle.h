
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <allegro.h>
#include <stdbool.h>

#include "defines.h"

void CreateObstacle( int x , int y );
bool ObstacleCollision( Snake *snake );
void DrawObstacles(BITMAP *buffer );


#endif