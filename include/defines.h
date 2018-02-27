
#ifndef DEFINES_H
#define DEFINES_H


#define SCREEN_WITDH 400
#define SCREEN_HEIGHT SCREEN_WITDH
#define ROWS 20
#define COLS ROWS

#define PIECE_SIZE 20
#define PIECE_BORDER 4
#define POSITION_INCREMENT 1

#define SWAP_INT( a , b , temp  ) temp = ( a ); ( a ) = ( b ) ; ( b ) = temp


#define FOOD_SIZE PIECE_SIZE
#define OBSTACLE_SIZE FOOD_SIZE


enum Direction{ HORIZONTAL , VERTICAL  };
enum Way{ POSITIVE  = 1, NEGATIVE = -1};
enum Object{NONE,FOOD, OBSTACLE };

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

typedef struct
{
    int x;
    int y;
    
} Food;


#endif