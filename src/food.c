
#include "../include/food.h"

extern unsigned short int screen_matrix[ROWS][COLS];

void SetFoodPosition( Food *food )
{
    do
    {
        food->x = ( rand( ) % ROWS );
        food->y = ( rand( ) % COLS );
    
    }while(  screen_matrix[food->x][food->y] != 0 );
    
    screen_matrix[food->x][food->y] = 2;
}



void DrawFood( BITMAP *buffer, Food *food )
{
    
    rectfill( buffer, food->x * ROWS, food->y * COLS, food->x *ROWS  + FOOD_SIZE, food->y * COLS + FOOD_SIZE, makecol( 0, 255, 0 ) );
    
}

bool AteFood( Food *food , Snake *snake )
{

    if( snake->head->x == food->x * ROWS && snake->head->y == food->y * COLS )
    {
        screen_matrix[food->x][food->y] = 0;
        return true;
    }
    
    return false;
}