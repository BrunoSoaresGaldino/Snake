
#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/food.h"
#include "../include/snake.h"

#define FRAMES_PER_SEC 3

void ShowMessage( const char *message )
{
    if( message )
    {
        puts( message );
    }

}

void Pause( void )
{
    while( !key[KEY_ESC] && !key[KEY_SPACE] )
    {
        rest(0);
    }
    
    key[ KEY_ESC ] = key[ KEY_SPACE] = 0;
}

bool exit_program = false;
void ExitProgram( void )
{
    exit_program = true;
}
END_OF_FUNCTION( ExitProgram )


bool tic = true;
void SetTic( void )
{
    tic = true;
}
END_OF_FUNCTION( SetTic );


int main( void )
{
    srand( time(NULL) );
    
    BITMAP *buffer;
    Snake *snake;
    Food *food = NULL;
    
    
    allegro_init( );
    install_mouse( );
    install_timer( );
    install_keyboard( );
    set_color_depth( 24 );
    set_window_title("Snake");
    if(  set_gfx_mode( GFX_AUTODETECT_WINDOWED , SCREEN_WITDH , SCREEN_HEIGHT , 0 ,0 )  )
    {
        ShowMessage("Erro ao iniciar modo grafico");
        ExitProgram( );
    }
    
    if( !(  buffer = create_bitmap( SCREEN_WITDH , SCREEN_HEIGHT ) ) )
    {
        ShowMessage("Erro ao criar buffer");
        ExitProgram( );
    }
    
    
    if( !( snake = CreateSnake( ) ) )
    {
        ShowMessage("Erro ao criar cobra");
        ExitProgram( );
    }        

    if( !( food = CreateFood( ) ) )
    {
        ShowMessage("Erro ao criar comida");
        ExitProgram( );
    }    
    

    LOCK_VARIABLE( exit_program );
    LOCK_FUNCTION( ExitProgram );
    set_close_button_callback( ExitProgram );
    
    LOCK_VARIABLE( tic )
    LOCK_FUNCTION( SetTic );
    install_int_ex( SetTic, BPS_TO_TIMER( FRAMES_PER_SEC ) );
    
    
    while( !exit_program )
    {
        // input
        if( key[KEY_LEFT] )
        {
            ChangeSnakeDirection( snake , KEY_LEFT );
        }
        
        if( key[KEY_RIGHT] )
        {
            ChangeSnakeDirection( snake , KEY_RIGHT );
        }
        
        if( key[KEY_UP] )
        {
            ChangeSnakeDirection( snake , KEY_UP );
        }
        
        if( key[KEY_DOWN] )
        {
            ChangeSnakeDirection( snake , KEY_DOWN );
        }

        if( key[ KEY_SPACE ] )
        {
            key[ KEY_SPACE ] = 0;
            Pause( );
        }
        
        //mudanças
        if( AteFood( food , snake ) )
        {
            SnakeAppendPiece( snake );          
            SetFoodPosition( food );
        }
        
        if( WallCollision( snake ) || SelfCollision( snake ) )
        {
            ShowMessage("Colidiu");
            ExitProgram( );
        }
        
        if( tic )
        {
            MoveSnake( snake );
            tic = false;
            
            // desenho
            clear_to_color( buffer , makecol( 255 ,255 ,255 ) );
        
            DrawFood( buffer, food);
            DrawSnake( buffer, snake );
       
            draw_sprite( screen , buffer , 0 , 0);
        }
        
        rest( 1 );
        
    }
    
    DestroyFood( food );
    DestroySnake( snake );
    destroy_bitmap( buffer );
    
    return 0;
    
}
END_OF_MAIN( )