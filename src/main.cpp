//**************************
//Tutoriel SDL 2.0
//
// AUTEUR : A.LEROUX
//          IUT GEII BRIVE
//**************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "IUTSDL.h"
#include "object.h"
#include "bomb.h"


// -----------------------------------------------------
// Constantes
// -----------------------------------------------------
// Nom du jeu
#define TITRE "Mario GEII"

// Dimensions de la grille
#define NBL 20          // Nombre de lignes
#define NBC 35          // Nombre de colonnes

// Dimensions des cases : correspond au images bitmap
#define CASE_W 34       // Largeur
#define CASE_H 34       // Hauteur

// Dimensions de l'écran
#define SCREEN_W NBC*CASE_W
#define SCREEN_H NBL*CASE_H

// Types de mouvements Mario. Indices des sprites correspondants dans le tableau des textures.
#define MOVE_LEFT    0
#define MOVE_RIGHT   1
#define MOVE_UP      2
#define MOVE_DOWN    3

// Position à atteindre pour fin du jeu : en haut à droite
#define XFIN    NBC-1
#define YFIN    0



// -----------------------------------------------------
// Globales
// -----------------------------------------------------
// Pour affichage (traitement timer)
char gTitle[100] = "";              // Titre a afficher sur la fenetre

/*char ecran[NBC][NBL];
{
    for int i =0
    {
        for int j =0
        {
            ecran[i][j]=' ';
            if ecran [i][j-1]!='M';
        }
    }



}*/


// Bitmaps pour l'affichage
SDL_Texture *pTextureFond ;
SDL_Texture *pTextureMur ;
SDL_Texture *pTextureCones ;
SDL_Texture *pTextureBomb ;
SDL_Texture *pTextureMario[4] ;     // Sprites Mario pour chaque direction de deplacement

// Coordonnées écran de chacune des cases pour l'affichage du fond et des sprites
SDL_Rect rectGrille[NBC][NBL] ;

// -----------------------------------------------------
// Callback timer pour affichage dans la barre de titre
// -----------------------------------------------------
// La fonction timer s'execute dans un thread different, donc ne peut pas mettre à jour le titre de la fenetre directement.
// On affiche donc l'heure dans une variable globale gTitle
// Le paramètre d'entrée interval est l'intervalle de temps du timer (en millisecondes).
// Il faut retourner la même valeur en sortie pour continuer.
// Le parametre param n'est pas utilisé ici. Il permet de passer une info à la callback (3eme parametre de SDL_AddTimer)
// A MODIFIER POUR AFFICHER L'HEURE SUR LA BARRE DE TITRE
Uint32 callback( Uint32 interval, void* param )
{
    static int compteur = 0 ;

    compteur+=interval;

    sprintf(gTitle,"Compteur : %d ...", compteur);

    return interval;
}

SDL_Texture *loadTexture(SDL_Renderer *sdlRenderer, char *filename) {
    char fullFilename[1024];
    sprintf(fullFilename, "images/%s", filename);
    return IUTSDL_LoadTexture(sdlRenderer, fullFilename ,0xFF,0xFF,0xFF);
}

// -----------------------------------------------------
// Initialisations jeu
// -----------------------------------------------------
// Chargement des bitmaps pour affichage
void initTextures(SDL_Renderer *sdlRenderer)
{
    pTextureFond=loadTexture(sdlRenderer, "fond.bmp");
    pTextureMur=loadTexture(sdlRenderer, "mur.bmp");
    pTextureMario[MOVE_LEFT]=loadTexture(sdlRenderer, "mario-gauche.bmp");
    pTextureMario[MOVE_RIGHT]=loadTexture(sdlRenderer, "mario-droite.bmp");
    pTextureMario[MOVE_UP]=loadTexture(sdlRenderer, "mario-haut.bmp");
    pTextureMario[MOVE_DOWN]=loadTexture(sdlRenderer, "mario-bas.bmp");

    pTextureCones=loadTexture(sdlRenderer, "dollar.bmp");
    pTextureBomb=loadTexture(sdlRenderer, "bombe.bmp");

}

// Initialisation coordonnées des cases de la grille
void initRectGrille()
{
    for (int i=0 ; i<NBC ; i++ )
    {
        for (int j=0 ; j<NBL ; j++)
        {
            rectGrille[i][j].x = i * CASE_W ;
            rectGrille[i][j].y = j * CASE_H ;
            rectGrille[i][j].w = CASE_W ;
            rectGrille[i][j].h = CASE_H ;
        }
    }
}


// Affichage contenu fixe de la grille : fond et murs
void affichageFond(SDL_Renderer *sdlRenderer)
{
    // Affichage du fond sur toute la grille
    for (int i=0 ; i<NBC ; i++ )
    {
        for (int j=0 ; j<NBL ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond, NULL, &rect);
        }
    }
}

// Affichage Mario
void affichageMario(SDL_Renderer *sdlRenderer, int x, int y, int sens)
{
    SDL_Rect rectMario ;
    rectMario.x = x*CASE_W ;
    rectMario.y = y*CASE_H ;
    rectMario.w = CASE_W ;
    rectMario.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureMario[sens], NULL, &rectMario);
}
// Clear des traces de Mario
void cleartraceMario(SDL_Renderer *sdlRenderer, int x, int y)
{
   // Affichage du fond apres passage de Mario  la grille
            SDL_Rect rect = rectGrille[x][y] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond, NULL, &rect);
}



void wallCreater(SDL_Renderer *sdlRenderer)
{
    int i;

    for (i=0 ; i<10 ; i++)
    {
            SDL_Rect rectwallCreater ;
            rectwallCreater.x = i*CASE_W ;
            rectwallCreater.y = 10*CASE_H ;
            rectwallCreater.w = CASE_W ;
            rectwallCreater.h = CASE_H ;
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rectwallCreater);

    }

}
void RenderObject(SDL_Renderer *sdlRenderer, class Object *obj) {
    SDL_Texture *texture = loadTexture(sdlRenderer, obj->texture);
    SDL_Rect rect;
    rect.x = CASE_W * obj->x;
    rect.y = CASE_H * obj->y;
    rect.w = CASE_W;
    rect.h = CASE_H;
    SDL_RenderCopy(sdlRenderer, texture, NULL, &rect);
}


void Cones(SDL_Renderer *sdlRenderer)
{
    int i;

    for (i=5 ; i<20 ; i++)
    {
        RenderObject(sdlRenderer, new Object(4, 3+i, "dollar.bmp"));
    }

}


void Bomb(SDL_Renderer *sdlRenderer)
{   
    for(int i=0; i < 3; i++) {
        int dx = rand() % 10;
        Object *bomb = MakeBomb(5+dx, 10);
        RenderObject(sdlRenderer, bomb);
    }
}

// Fonction d'initialisation du jeu
void init(SDL_Renderer *sdlRenderer)
{
    // Init random
    srand(time(NULL));

    // Textures pour afficher éléments du jeu
    initTextures(sdlRenderer) ;

    // Grille pour affichage décors. Attention Table colonne/ligne pour respecter le sens x=colonne et y=ligne
    initRectGrille() ;

    // Affichage de la grille et des murs
    affichageFond(sdlRenderer) ;
    wallCreater(sdlRenderer) ;
    Cones(sdlRenderer);
    Bomb(sdlRenderer);
    // Mise à jour de l'affichage
    IUTSDL_RefreshScreen(sdlRenderer);
}

// -----------------------------------------------------
// Fonction main
// -----------------------------------------------------
int main( int argc, char* args[] )
{
    SDL_Window   *pScreen=NULL;         // Fenetre
    SDL_Renderer *sdlRenderer=NULL;     // Declaration du Buffer Video

    // Nouvelles positions pour calcul
    int x, y ;
    int sens ;

    // Position Mario
    int xMario, yMario ;        // Position de Mario
    // Direction Mario
    int dirMario ;

    // Rappel : la console reste utilisable
    printf("\nVous pouvez faire des traces par printf sur la fenetre console pour debugger ... \n") ;
    printf("Le point de depart va s'afficher.\nUtiliser les fleches pour deplacer Mario\nFermer la fenetre pour terminer\n") ;
    //
    // Initialisations graphique SDL
    // LAISSER TEL QUEL
    //
    // Initialisation utilisation de la SDL
    if( IUTSDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) != NO_ERROR )
    {
        printf("Erreur IUTSDL\n") ;
        exit(1) ;
    }

    // Création de la fenêtre
    pScreen = IUTSDL_CreateWindow(TITRE, SCREEN_W, SCREEN_H);
    if (pScreen == NULL)
    {
        printf("Erreur IUTSDL\n") ;
        exit(1) ;
    }

    // Icône
    IUTSDL_SetWindowIcon (pScreen, ".\\mario-icone-64.bmp");

    // Début affichege
    //sdlRenderer = SDL_CreateRenderer(pScreen, -1, 0 /*SDL_RENDERER_ACCELERATED*/);      // Association du Buffer Video à la Fenetre
    sdlRenderer = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_SOFTWARE);      // Association du Buffer Video à la Fenetre

    IUTSDL_ClearScreen(sdlRenderer);

    // Fin d'initialisation graphique SDL
    //

    //
    // Timer
    //
    // Création d'un timer pour affichage du titre. La fonction callback sera appellée périodiquement toutes les 100ms
    SDL_TimerID timerID = SDL_AddTimer(100, callback, NULL );




    //
    // Jeu
    //
    // Initialisations
    init(sdlRenderer) ;

    // Positionner Mario pour les test : au milieu
    xMario = NBC/2 ;
    yMario = NBL/2 ;
    dirMario = MOVE_DOWN ;

    // Jeu
    int sortie = 0 ;
    while(!sortie)
    {
        // Affichage titre de fenetre
        SDL_SetWindowTitle(pScreen, gTitle);

        // Attendre un poil
        SDL_Delay(50) ;

        // Recup des evenements externe (clavier, souris)
        SDL_Event( event );
        while( SDL_PollEvent( &event ) != 0 )
        {
            sens = -1 ;
            switch ( event.type)
            {
                case SDL_QUIT :
                    // Sortie
                    SDL_SetWindowTitle(pScreen, "       Sortie !!!        ") ;
                    sortie = 1 ;
                    break;

                case SDL_KEYDOWN :
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_LEFT:
                            sens = MOVE_LEFT ;
                            break;
                        case SDLK_RIGHT:
                            sens = MOVE_RIGHT ;
                            break;
                        case SDLK_UP:
                            sens = MOVE_UP ;
                            break;
                        case SDLK_DOWN:
                            sens = MOVE_DOWN ;
                            break;
                    }
            }

            // Traitement des evenements du type fleche
             cleartraceMario(sdlRenderer, xMario, yMario);

            if (sens == MOVE_UP)
            {
                dirMario=sens ;
                x=xMario ;


                if(y==0)
                {
                    y=(yMario);
                }
                else
                {
                    y=(yMario-1);
                }
            }
            else if (sens == MOVE_DOWN)
            {
                dirMario=sens ;
                x=xMario ;


                if (y==NBL-1)
                {
                    y=(yMario);
                }
                else
                {
                    y=(yMario+1);
                }
            }
            else if (sens == MOVE_LEFT)
            {
                dirMario=sens ;
                y=yMario ;

                if (x==0)
                {
                    x=(xMario);
                }
                else
                {
                    x=(xMario-1);
                }
            }
            else if (sens == MOVE_RIGHT)
            {
                dirMario=sens ;
                y=yMario ;

                if (x==NBC-1)
                {
                    x=(xMario);
                }
                else
                {
                    x=(xMario+1);
                }
            }
            else
            {
                x=xMario ;
                y=yMario ;
            }

            // Déplacement
            xMario=x ;
            yMario=y ;
            affichageMario(sdlRenderer, xMario, yMario, dirMario) ;

        }

        // Mise à jour de l'affichage
        IUTSDL_RefreshScreen(sdlRenderer);
    }


    // Ménage
    SDL_RemoveTimer( timerID );

    // Affichage score final
    printf("\nBye Bye !!\n") ;

    return 0 ;
}
