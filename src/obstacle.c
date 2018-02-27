#include "../include/obstacle.h"


extern unsigned short int screen_matrix[ROWS][COLS];

void CreateObstacle( int x , int y )
{
    x /= ROWS;
    y /= COLS;
    
    screen_matrix[x][y] = 1;
    
}

bool ObstacleCollision( Snake *snake )
{
    int i;
    int j;
    
    for( i = 0; i < ROWS ; i++ )
    {
        for( j = 0 ; j < COLS ; j++ )
        {
            if( screen_matrix[i][j] == 1 )
            {
                if( i == snake->head->x/ ROWS && j == snake->head->y/COLS )
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}

void DrawObstacles(BITMAP *buffer )
{
    int i;
    int j;
    
    for( i = 0; i < ROWS ; i++ )
    {
        for( j = 0 ; j < COLS ; j++ )
        {
            if( screen_matrix[i][j] == 1 )
            {
                rectfill( buffer, i * ROWS , j * COLS, i * ROWS + OBSTACLE_SIZE, j * COLS + OBSTACLE_SIZE, makecol( 0, 0, 0 ) );
            }
        }
    }
    
}