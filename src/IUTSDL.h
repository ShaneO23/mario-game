#define NO_ERROR 0
#define OK 1



//***********************************************************
// Notification d'erreur
//***********************************************************
// Fonction :               IUTSDL_Print_Error()
//-----------------------------------------------------------
// Parametre :              Type : Chaine de caractere
//-----------------------------------------------------------
// Retour de la fonction :  AUCUN
//***********************************************************

void IUTSDL_Print_Error (const char message[]);



//***********************************************************
// Initialisation de la bibliotheque SDL
//***********************************************************
// Fonction :               retour=IUTSDL_Init(param)
//-----------------------------------------------------------
// Parametres Principaux :  Type : ENTIER
//                          SDL_INIT_TIMER
//                          SDL_INIT_AUDIO
//                          SDL_INIT_VIDEO
//                          SDL_INIT_CDROM
//                          SDL_INIT_JOYSTICK
//
//                          SDL_INIT_EVERYTHING
//-----------------------------------------------------------
// Retour de la fonction :  Type : ENTIER
//                           0 => OK
//                          -1 => Probleme
//-----------------------------------------------------------
// Exemple 1 :  SDL_Init( SDL_INIT_VIDEO );
// Exemple 2 :  SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//***********************************************************

Uint32 IUTSDL_Init(Uint32 param);



//***********************************************************
// Ouverture d'une Fenetre / Plein Ecran
//***********************************************************
// Fonction :               retour=IUTSDL_CreateWindow(param1,param2,param3)
//-----------------------------------------------------------
// Parametre 1 :            Type : Chaine de caractere
//                          Description : Nom de la fenetre qui sera affiché en mode fenetré dans la barre de titre
//-----------------------------------------------------------
// Parametre 2 & 3 :        Type : ENTIER
//                          Taille X,Y de la fenetre (en pixel) à afficher
//                          param4 = Taille X
//                          param5 = Taille Y
//-----------------------------------------------------------
// Retour de la fonction :  NULL   => Probleme
//                          Pointeur Type : SDL_Window*
//-----------------------------------------------------------
// Exemple 1 :              SDL_Window *pScreen = IUTSDL_CreateWindow("R-TYPE Version A.LEROUX...",
//                                                                    1280, 800,
//                                                                    SDL_WINDOW_RESIZABLE);
//-----------------------------------------------------------
// Fonction Associée :      SDL_GetError()
//                          Après l'appel de IUTSDL_CreateWindow() cette
//                          Fonction retourne le code du probleme
//***********************************************************

SDL_Window* IUTSDL_CreateWindow (const char titre[], Uint32 largeur, Uint32 hauteur);




//***********************************************************
// Affichage Icone dans la barre de titre
//***********************************************************
// Fonction :    IUTSDL_SetWindowIcon(param1, param2)
//-----------------------------------------------------------
// Parametre 1 : Pointeur Type : SDL_WindowSDL_Window*
//-----------------------------------------------------------
// Parametre 2 : chaine de caractère => chemin vers fichier
//-----------------------------------------------------------
// Retour de la fonction : AUCUN
//-----------------------------------------------------------
// Exemple :  IUTSDL_SetWindowIcon(pScreen,".\\icone.bmp");
//***********************************************************

void IUTSDL_SetWindowIcon (SDL_Window *pScreen, const char fichier[]);




//***********************************************************
// Libere la Memoire de l'Ecran
// + Fin d'utilisation de la SDL
//***********************************************************
// Fonction :   IUTSDL_Quit(param1)
//-----------------------------------------------------------
// Parametres : Pointeur Type : SDL_Window*
//-----------------------------------------------------------
// Retour de la fonction : AUCUN
//-----------------------------------------------------------
// Exemple :  IUTSDL_Quit(pScreen);
//***********************************************************

void IUTSDL_Quit(SDL_Window *pScreen);


//**********************************************************
// Fonctions supplémentaires
//**********************************************************

void IUTSDL_ClearScreen(SDL_Renderer *sdlRenderer) ;

SDL_Texture* IUTSDL_LoadTexture(SDL_Renderer *sdlRenderer, const char fichier[], Uint8 colorkey_red, Uint8 colorkey_green, Uint8 colorkey_blue) ;

SDL_Texture* IUTSDL_LoadBackGround(SDL_Renderer *sdlRenderer, const char fichier[]) ;

void IUTSDL_RefreshScreen (SDL_Renderer *sdlRenderer) ;
