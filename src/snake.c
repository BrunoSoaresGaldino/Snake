
#include "../include/snake.h"

Snake *CreateSnake( void )
{
    Snake *snake = calloc( 1 , sizeof( Snake ) );
    
    if( snake )
    {
        snake->tail = snake->head = calloc( 1 , sizeof( SnakePiece ) );
        
        if( snake->head )// snake->next já é igual NULL, porque eu utilizei calloc. Calloc zera a memoria alocada
        {
            snake->head->y = snake->head->x = 0;
            snake->head->direction = HORIZONTAL;    
            snake->head->way = POSITIVE;
            
            return snake;
        }
        
        free( snake );// houve falha ao alocar memoria para a cabeca
        
    }
    
    return NULL;
}

void DestroySnake( Snake *snake )
{
    SnakePiece *piece;
    SnakePiece *aux;
    
    piece = snake->head;
    
    while( piece )
    {
        aux = piece;
        piece = piece->next;
        
        free( aux );
    }
 
    free( snake );
}

bool SnakeAppendPiece( Snake *snake )
{
    
    SnakePiece *piece = calloc( 1 , sizeof( SnakePiece ) );
 
    if( piece )
    {
        
        if( snake->tail->direction == HORIZONTAL )
        {
            piece->y = snake->tail->y;
            piece->direction = HORIZONTAL;
            piece->x = snake->tail->x +  - snake->tail->way * POSITION_INCREMENT;// se way é negativo, adicona 1 à posicao da calda e atribui ao elemento que sera inserido
            
        }
        else
        {
            piece->x = snake->tail->x;
            piece->direction = VERTICAL;
            piece->y = snake->tail->y - snake->tail->way * POSITION_INCREMENT;
            
        }
        
        piece->way = snake->tail->way;
        snake->tail = snake->tail->next = piece;
        
        return true;
        
    }        

   return false;
}
void ChangeSnakeDirection( Snake *snake , int key )
{
    
    if( key == KEY_LEFT && snake->head->direction != HORIZONTAL )
    {
        snake->head->direction = HORIZONTAL;
        snake->head->way = NEGATIVE;   
    }
    else if( key == KEY_RIGHT && snake->head->direction != HORIZONTAL )
    {
        snake->head->direction = HORIZONTAL;
        snake->head->way = POSITIVE;
    }
    else if( key == KEY_UP && snake->head->direction != VERTICAL )
    {
        snake->head->direction = VERTICAL;
        snake->head->way = NEGATIVE;   
    }
    else if( key == KEY_DOWN && snake->head->direction != VERTICAL )
    {
        snake->head->direction = VERTICAL;
        snake->head->way = POSITIVE;
    }   
    

}

void MoveSnake( Snake *snake)
{
    
    SnakePiece *piece;
    
    int x = snake->head->x;
    int y = snake->head->y;
    int direction = snake->head->direction;
    int way = snake->head->way;
    int temp;
    
    if( direction == HORIZONTAL )
    {
        snake->head->x += way * POSITION_INCREMENT;
    }
    else
    {
        snake->head->y += way * POSITION_INCREMENT;
    }
    
    
    piece  = snake->head->next;
    
    while( piece )//os atributos espacias de N serão iguais o de N-1
    {
        SWAP_INT( piece->x, x , temp );// troca o valor de x da iteração anterior, com o do passo atual
        SWAP_INT( piece->y, y , temp );
        SWAP_INT( piece->direction, direction, temp );
        SWAP_INT( piece->way, way, temp );
        
        piece = piece->next;
    }
    
    
    
}

void DrawSnake( BITMAP *buffer, Snake *snake )
{
    
    SnakePiece *piece = snake->head;
    
    while( piece )
    {
        rectfill( buffer, piece->x * ROWS, piece->y * COLS  , piece->x * ROWS + PIECE_SIZE, piece->y * COLS + PIECE_SIZE , makecol( 2555 , 0 , 0 ) );
        rect( buffer, piece->x * ROWS , piece->y * COLS , piece->x * ROWS + PIECE_SIZE, piece->y * COLS + PIECE_SIZE , makecol( 255 , 255 , 255 ) );
        
        piece = piece->next;
    }
    
}

bool WallCollision( Snake *snake )
{
    
    return snake->head->x < 0 || snake->head->x >= ROWS || snake->head->y < 0 || snake->head->y >= COLS;
    
}

bool SelfCollision( Snake *snake )
{
    
    SnakePiece *piece = snake->head->next;
    
    while( piece )
    {
        if( snake->head->x == piece->x && snake->head->y == piece->y )
        {
            return true;
        }
        
        piece = piece->next;
    }
    
    return false;
}