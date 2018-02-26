
#ifndef FOOD_H
#define FOOD_H

#include <allegro.h>
#include <stdbool.h>

#include "snake.h"

#define FOOD_SIZE 20

typedef struct
{
    int x;
    int y;
    
} Food;

Food *CreateFood( void );
void DestroyFood( Food *food );
void SetFoodPosition( Food *food );
void DrawFood( BITMAP *buffer, Food *food );
bool AteFood( Food *food , Snake *snake );



#endif