
#ifndef SNAKE_H
#define SNAKE_H

#include <allegro.h>
#include <stdbool.h>

#define SCREEN_WITDH 400
#define SCREEN_HEIGHT SCREEN_WITDH

#define ROWS 20
#define COLS ROWS


#define PIECE_SIZE 20
#define PIECE_BORDER 4

#define POSITION_INCREMENT PIECE_SIZE

#define SWAP_INT( a , b , temp  ) temp = ( a ); ( a ) = ( b ) ; ( b ) = temp

enum Direction{ HORIZONTAL , VERTICAL  };
enum Way{ POSITIVE  = 1, NEGATIVE = -1};


typedef struct SnakePiece
{
    int x;
    int y;
    int direction;
    int way;
    
    struct SnakePiece *next;
    
} SnakePiece;

typedef struct
{
    SnakePiece *head;
    SnakePiece *tail;
    
} Snake;


Snake *CreateSnake( void );
void DestroySnake( Snake *snake );
bool SnakeAppendPiece( Snake *snake );
void ChangeSnakeDirection( Snake *snake , int key );
void MoveSnake( Snake *snake);
void DrawSnake( BITMAP *buffer, Snake *snake );
bool WallCollision( Snake *snake );
bool SelfCollision( Snake *snake );



#endif