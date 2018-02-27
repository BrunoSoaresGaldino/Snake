
#ifndef FOOD_H
#define FOOD_H

#include <allegro.h>
#include <stdbool.h>

#include "defines.h"

void SetFoodPosition( Food *food );
void DrawFood( BITMAP *buffer, Food *food );
bool AteFood( Food *food , Snake *snake );



#endif