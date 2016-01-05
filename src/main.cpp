#include "game.h"
#include "IUTSDL.h"
#include "Windows.h"

#define TITRE "Shane's Mario Game GEII"

// Dimensions de la grille
#define NBL 20          // Nombre de lignes
#define NBC 35          // Nombre de colonnes

// Dimensions des cases : correspond au images bitmap
#define CASE_W 34       // Largeur
#define CASE_H 34       // Hauteur

// Dimensions de l'écran
#define SCREEN_W NBC*CASE_W
#define SCREEN_H NBL*CASE_H

#define MOVE_LEFT    0
#define MOVE_RIGHT   1
#define MOVE_UP      2
#define MOVE_DOWN    3


char gTitle[100] = "";


Uint32 callback( Uint32 interval, void* param )
{
    static int compteur = 0 ;

    compteur+=interval;
    int seconds;
    int total_time =60;
    int game_time;
    int rest_time =0;
    // Computer time
    SYSTEMTIME t;
    GetSystemTime(&t);

    seconds=compteur / 1000 ;
    game_time=seconds;
    game_time -=4;
    rest_time=total_time - game_time;

        if (total_time<seconds)
        {
            sprintf(gTitle,"NO Time left !!");
            SDL_Delay(1000);
            printf(gTitle,"The is going to close in %d second !",rest_time);
            SDL_Delay(1000);
            exit(0);
        }



    sprintf(gTitle,"%d: %d: %d | Game time: %d",t.wHour+1,t.wMinute,t.wSecond,seconds);

    return interval;
}

int main(int argc, char* argv[])
 {


    // Rappel : la console reste utilisable
    printf("\nVous pouvez faire des traces par printf sur la fenetre console pour debugger ... \n") ;
    printf("Le point de depart va s'afficher.\nUtiliser les fleches pour deplacer Mario\nFermer la fenetre pour terminer\n") ;
    SDL_Delay(2000) ;






    // Window
    SDL_Window   *pScreen=NULL;
     SDL_SetWindowTitle(pScreen, gTitle);
    // Création d'un timer pour affichage du titre. La fonction callback sera appellée périodiquement toutes les 100ms
    SDL_TimerID timerID = SDL_AddTimer(100, callback, NULL );
    //SDL_Window   *pScreen=NULL;

    // Video Buffer
    SDL_Renderer *sdlRenderer=NULL;


    // Init SDL with feature: video, timer
    if( IUTSDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) != NO_ERROR )
    {
        printf("Error: IUTSDL\n") ;
        exit(1) ;
    }

    // Create Window
    pScreen = IUTSDL_CreateWindow(TITRE, SCREEN_W, SCREEN_H);
    if (pScreen == NULL)
        {
            printf("Error: IUTSDL\n") ;
            exit(1) ;
        }

    // Setup renderer
    // Fallback to software only if hardware acceleration is not available
    sdlRenderer = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_SOFTWARE);

    // Nicely rescale the renderer
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_W, SCREEN_H);

    // Clear video buffer
    SDL_RenderClear(sdlRenderer);

    // Setup game
    Game *game = new Game(sdlRenderer);

    // Run game
    game->Run();
}
