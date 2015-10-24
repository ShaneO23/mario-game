#include <SDL2/SDL.h>
#include <stdio.h>

#include "IUTSDL.h"

#define MAX_LEN 100

SDL_Surface  *icon;


//***********************************************************
// Notification d'erreur
//***********************************************************

void IUTSDL_Print_Error (const char message[])

{  char buffer [MAX_LEN];

   sprintf(buffer, "%s\n\n=> %s", message, SDL_GetError());
   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Notification d Erreur...",  buffer, NULL);

}  // Fin de la fonction IUTSDL_Print_Error()



//***********************************************************
// Initialisation de la bibliotheque SDL
//***********************************************************

Uint32 IUTSDL_Init(Uint32 param)
{
   Uint32 error;

   error=SDL_Init(param);

   //***********************************************************
   // Initialisation de la bibliotheque SDL
   //***********************************************************
   // Fonction :               retour=SDL_Init(param)
   //-----------------------------------------------------------
   // Parametres Principaux :  Type : ENTIER
   //                          SDL_INIT_TIMER
   //                          SDL_INIT_AUDIO
   //                          SDL_INIT_VIDEO
   //                          SDL_INIT_CDROM
   //                          SDL_INIT_JOYSTICK
   //
   //                          SDL_INIT_EVERYTHING
   //
   // Autres Parametres :      SDL_INIT_NOPARACHUTE
   //                          SDL_INIT_EVENTTHREAD
   //-----------------------------------------------------------
   // Retour de la fonction :  Type : ENTIER
   //                           0 => OK
   //                          -1 => Probleme
   //-----------------------------------------------------------
   // Exemple 1 :  SDL_Init( SDL_INIT_VIDEO );
   // Exemple 2 :  SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   //-----------------------------------------------------------
   // Fonction Associée : SDL_GetError()
   //                     Après l'appel de SDL_Init() cette
   //                     Fonction retourne le code du probleme
   //                     Type du Retour : ENTIER
   //***********************************************************

   if (error != NO_ERROR)
     { IUTSDL_Print_Error("Fonction IUTSDL_Init()");
     }  // Fin du if

   return error;

}  // Fin de la fonction IUTSDL_Init()




//***********************************************************
// Ouverture d'une Fenetre / Plein Ecran
//***********************************************************

SDL_Window* IUTSDL_CreateWindow (const char titre[], Uint32 largeur, Uint32 hauteur)
{

   SDL_Window* pScreen;

   //***********************************************************
   // Ouverture d'une Fenetre / Plein Ecran
   //***********************************************************
   // Fonction :               retour=SDL_CreateWindow(param1,param2,param3,param4,param5,param6)
   //-----------------------------------------------------------
   // Parametre 1 :            Type : Chaine de caractere
   //                          Description : Nom de la fenetre qui sera affiché en mode fenetré  dans la barre de titre
   //-----------------------------------------------------------
   // Parametre 2 & 3 :        Type : ENTIER
   //                          Position X,Y (en pixel) de la fenetre à afficher par rapport à l'écran actuel
   //                          Avec : 0 < param2 < Taille MAX de l'écran en largeur
   //                                 0 < param3 < Taille MAX de l'écran en hauteur
   //                          Autre Valeur : param2 = SDL_WINDOWPOS_UNDEFINED    => Au pif
   //                                                = SDL_WINDOWPOS_CENTERED     => Fenetre centrée sur l'axe X
   //                                         param3 = Idem pour Y
   //-----------------------------------------------------------
   // Parametre 4 & 5 :        Type : ENTIER
   //                          Taille X,Y de la fenetre (en pixel) à afficher
   //                          param4 = Taille X
   //                          param5 = Taille Y
   //-----------------------------------------------------------
   // Parametre 6 : (Options)  Type : ENTIER
   //                          SDL_WINDOW_FULLSCREEN          => Crée une fenêtre plein écran aus dimensions X,Y (Attention aux modes Video)
   //                          SDL_WINDOW_FULLSCREEN_DESKTOP  => Crée une fenêtre plein écran à la résolution actuelle du bureau
   //                          SDL_WINDOW_OPENGL              => Crée une fenêtre pouvant être utilisée pour OpenGL
   //                          SDL_WINDOW_BORDERLESS          => Crée une fenêtre sans bordure ni titre
   //                          SDL_WINDOW_RESIZABLE           => Crée une fenêtre redimensionnable
   //                          SDL_WINDOW_MINIMIZED           => Crée une fenêtre minimisée
   //                          SDL_WINDOW_MAXIMIZED           => Crée une fenêtre maximisée
   //                          SDL_WINDOW_INPUT_GRABBED       => Crée une fenêtre et les positions de la souris ne dépaceront pas la taille de la fenetre
   //
   // Autres Options :         SDL_WINDOW_SHOWN               => Crée une fenêtre et l'afficher (Vrai par defaut)
   //                          SDL_WINDOW_HIDDEN              => Crée une fenêtre cachée
   //                          SDL_WINDOW_INPUT_FOCUS         => Crée une fenêtre et donne le focus d'entrée
   //                          SDL_WINDOW_MOUSE_FOCUS         => Crée une fenêtre et donne le focus de la souris
   //                          SDL_WINDOW_FOREIGN             => La fenêtre n'est pas créée par la SDL
   //
   //-----------------------------------------------------------
   // Retour de la fonction :   NULL   => Probleme
   //                           Pointeur Type : SDL_Window*
   //-----------------------------------------------------------
   // Exemple 1 :               SDL_Window *screen = SDL_CreateWindow("R-TYPE Version A.LEROUX...",
   //                                                                  SDL_WINDOWPOS_CENTERED,
   //                                                                  SDL_WINDOWPOS_CENTERED,
   //                                                                  1280, 800,
   //                                                                  SDL_WINDOW_RESIZABLE);
   //-----------------------------------------------------------
   // Fonction Associée : SDL_GetError()
   //                     Après l'appel de SDL_CreateWindow() cette
   //                     Fonction retourne le code du probleme
   //***********************************************************

   pScreen = SDL_CreateWindow(titre,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              largeur,
                              hauteur,
                              SDL_WINDOW_RESIZABLE);

   if (pScreen == NULL)
     { IUTSDL_Print_Error("Fonction IUTSDL_CreateWindow()");
     }  // Fin du if

   return pScreen;

}  //  Fin de la Fonction IUTSDL_CreateWindow()







//***********************************************************
// Affichage Icone dans la barre de titre
//***********************************************************

void IUTSDL_SetWindowIcon (SDL_Window *pScreen, const char fichier[])
{
  icon= SDL_LoadBMP(fichier);
  SDL_SetWindowIcon(pScreen, icon);

}  // Fin de la Fonction IUTSDL_SetWindowIcon()




//***********************************************************
// Libere la Memoire de l'Ecran
// + Fin d'utilisation de la SDL
//***********************************************************

void IUTSDL_Quit(SDL_Window *pScreen)
{
    //***********************************************************
    // Fin d'utilisation de la Fenetre
    //***********************************************************
    // Fonction :   SDL_DestroyWindow()
    // Parametres : Pointeur Type : SDL_Window*
    //-----------------------------------------------------------
    // Retour de la fonction : AUCUN
    //-----------------------------------------------------------
    // Exemple :  SDL_DestroyWindow(pScreen);
    //***********************************************************

    SDL_FreeSurface(icon);
    SDL_DestroyWindow(pScreen);

    SDL_Quit();

}  // Fin de la fonction IUTSDL_Quit())

//**********************************************************
// Fonctions supplémentaires
//**********************************************************

void IUTSDL_ClearScreen(SDL_Renderer *sdlRenderer)

{
   SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 0);                                  // Affectation de la couleur de Nettoyage du Buffer Video
   SDL_RenderClear(sdlRenderer);                                                       // Nettoyage du Buffer Video
   SDL_RenderPresent(sdlRenderer);                                                     // Mise à Jour de la Fenetre => Copie du Buffer Video dans la Fenetre

}  // Fin de la fonction IUTSDL_ClearScreen




SDL_Texture* IUTSDL_LoadTexture(SDL_Renderer *sdlRenderer, const char fichier[], Uint8 colorkey_red, Uint8 colorkey_green, Uint8 colorkey_blue)
{

   SDL_Surface *pSurface  = SDL_LoadBMP(fichier);                                       // Chargement d'une Surface
   SDL_SetColorKey( pSurface,   1, SDL_MapRGB( pSurface->format, colorkey_red, colorkey_green, colorkey_blue ));          // Affectation de la Couleur de Transparence (Ici NOIR)
   SDL_Texture *pTexture = SDL_CreateTextureFromSurface(sdlRenderer, pSurface);    // Transformation de la Surface en Texture
   SDL_FreeSurface(pSurface);                                                         // Liberation de la mémoire de a Surface

   return pTexture;


}  // Fin de la fonction IUTSDL_LoadTexture




SDL_Texture* IUTSDL_LoadBackGround(SDL_Renderer *sdlRenderer, const char fichier[])
{

   SDL_Surface *pBackground  = SDL_LoadBMP(fichier);                                            // Chargement d'une Surface
   SDL_Texture *pTextureBackground = SDL_CreateTextureFromSurface(sdlRenderer, pBackground);    // Transformation de la Surface en Texture
   SDL_FreeSurface(pBackground);                                                                // Liberation de la mémoire de a Surface

   return pTextureBackground;


}  // Fin de la fonction IUTSDL_LoadBackGround



void IUTSDL_RefreshScreen (SDL_Renderer *sdlRenderer)
{
  SDL_RenderPresent(sdlRenderer);

}  // Fin de la Fonction IUTSDL_RefreshScreen()



