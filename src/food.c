
#include "../include/food.h"

Food *CreateFood( void )
{
    Food *food = calloc( 1, sizeof( Food ) );
    
    if( food )
    {
        SetFoodPosition( food );
        return food;
    }
   
    return NULL;

}

void DestroyFood( Food *food )
{
    if( food )
    {
        free( food );
    }
}

void SetFoodPosition( Food *food )
{
    food->x = ( rand( ) % ROWS ) * ROWS;
    food->y = ( rand( ) % COLS ) * COLS;
}



void DrawFood( BITMAP *buffer, Food *food )
{
    
    rectfill( buffer, food->x, food->y, food->x + FOOD_SIZE, food->y + FOOD_SIZE, makecol( 0, 255, 0 ) );
    
}

bool AteFood( Food *food , Snake *snake )
{

    return snake->head->x == food->x && snake->head->y == food->y;
}