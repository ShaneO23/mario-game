#include "game.h"
#include "IUTSDL.h"

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

int main(int argc, char* argv[])
 {

    // Window
    SDL_Window   *pScreen=NULL;
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
