
#ifndef SNAKE_H
#define SNAKE_H

#include <allegro.h>
#include <stdbool.h>

#include "defines.h"

Snake *CreateSnake( void );
void DestroySnake( Snake *snake );
bool SnakeAppendPiece( Snake *snake );
void ChangeSnakeDirection( Snake *snake , int key );
void MoveSnake( Snake *snake );
void DrawSnake( BITMAP *buffer, Snake *snake );
bool WallCollision( Snake *snake );
bool SelfCollision( Snake *snake );



#endif