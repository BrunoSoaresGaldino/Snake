
#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/defines.h"
#include "../include/snake.h"
#include "../include/food.h"
#include "../include/obstacle.h"

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
    SAMPLE *snake_attack;
    SAMPLE *game_over;
    Snake *snake;
    Food food;
    int score = 0;
    int last_score = 0;
    
    
    allegro_init( );
    install_mouse( );
    install_timer( );
    install_keyboard( );
    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
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
    
    if( !( snake_attack = load_sample("../sound/snake_attack.wav") ) )
    {
        ShowMessage("Erro ao carregar efeito de ataque da cobra");
        ExitProgram( );
    }

    if( !( game_over = load_sample("../sound/game_over.wav") ) )
    {
        ShowMessage("Erro ao carregar efeito de gameover");
        ExitProgram( );
    }
    
    if( !( snake = CreateSnake( ) ) )
    {
        ShowMessage("Erro ao criar cobra");
        ExitProgram( );
    }        

    LOCK_VARIABLE( exit_program );
    LOCK_FUNCTION( ExitProgram );
    set_close_button_callback( ExitProgram );
    
    LOCK_VARIABLE( tic )
    LOCK_FUNCTION( SetTic );
    install_int_ex( SetTic, BPS_TO_TIMER( FRAMES_PER_SEC ) );
    
    SetFoodPosition( &food );
    
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
        if( (score+1) % 15 == 0 && score < 300 && score != last_score  )
        {
            last_score = score;
            CreateObstacle( snake->tail->x, snake->tail->y );
        }
        
        if( AteFood( &food , snake ) )
        {   
            play_sample( snake_attack , 255, 128 , 1000, false );
            SnakeAppendPiece( snake );          
            SetFoodPosition( &food );
            score++;
        }
        
        if( WallCollision( snake ) || SelfCollision( snake ) || ObstacleCollision( snake ) )
        {
            play_sample( game_over , 255, 128 ,1000,false);
            rest(1800);
            ExitProgram( );
        }
        
        if( tic )
        {
            MoveSnake( snake );
            tic = false;
            
            // desenho
            clear_to_color( buffer , makecol( 255 ,255 ,255 ) );
        
            DrawFood( buffer, &food);
            DrawSnake( buffer, snake );
            DrawObstacles( buffer );
       
            textprintf_ex( buffer ,font, 2 , 2, makecol( 0, 0, 0 ), -1,"Score: %d",score);
            
            draw_sprite( screen , buffer , 0 , 0);
        }
        
        rest( 1 );
        
    }
    
    DestroySnake( snake );
    destroy_bitmap( buffer );
    destroy_sample( game_over );
    destroy_sample( snake_attack);
    
    return 0;
    
}
END_OF_MAIN( )