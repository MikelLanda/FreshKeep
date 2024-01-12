#include "text.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int pantailaHasi();

SDL_Window *Ventana = NULL;
SDL_Surface *Superficie = NULL;
SDL_Renderer *gRenderer;
SDL_Rect src, dst;
int fin = 0;
int screenWidth;
int screenHeight;
int pantailaHasi()
{

    // Inicializa el subsistema de Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: No se pudo inicializar SDL, Error SDL: %s\n", SDL_GetError());
    }
    else
    {
        // Se crea la ventana principal
        Ventana = SDL_CreateWindow("FRESHKEEP", 20, 20, 1980, 920, SDL_WINDOW_RESIZABLE);
        SDL_SetWindowFullscreen(Ventana, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    gRenderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);
    SDL_GetWindowSize(Ventana, &screenWidth, &screenHeight);
    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
    SDL_SetRenderDrawColor(gRenderer, 225, 255, 198, SDL_ALPHA_OPAQUE);
    SDL_Rect background = {0, 0, 1980, 920};
    SDL_RenderFillRect(gRenderer, &background);

    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_Color kolor = {0x00, 0x00, 0x00};
    tituluaIdatzi("FRESHKEEP", kolor, Ventana, "(Titulo)ChauPhilomeneOne-Regular.ttf");

    // testua
    /*TTF_Init();
    SDL_Texture *texture;
    TTF_Font *letra = TTF_OpenFont("../Debug/(Titulo)ChauPhilomeneOne-Regular.ttf", 28);
    SDL_Color kolorea = {0, 0, 0};
    SDL_Surface *testuarenAzalera = TTF_RenderText_Solid(letra, "FRESHKEEP1", kolorea);
    texture = SDL_CreateTextureFromSurface(gRenderer, testuarenAzalera);
    src.x = 0;
    dst.x = 0;
    src.y = 0;
    dst.y = 0;
    src.w = dst.w = testuarenAzalera->w;
    src.h = dst.h = testuarenAzalera->h;
    SDL_RenderCopy(gRenderer, texture, &src, &dst);
    SDL_RenderPresent(gRenderer);*/

    while (!fin)
    {
        SDL_Event ebentua; // Aquí almacenaremos los eventos que vamos sacando de la cola
                           // Con esto controlamos cuando queremos acabar el programa
        while (SDL_PollEvent(&ebentua))
        { // Miramos y sacamos el siguiente evento en cola
            switch (ebentua.type)
            {                                              // Comprobamos el tipo de evento
            case SDL_KEYDOWN:                              // Si es una pulsación de tecla
                if (ebentua.key.keysym.sym == SDLK_ESCAPE) // Si es la tecla Escape
                {
                    SDL_SetWindowFullscreen(Ventana, 0); // Ponemos fin a true para salir del bucle
                }
                break;
            case SDL_QUIT: // Si hemos pulsado el cierre de la ventana
                fin = 1;
                SDL_DestroyWindow(Ventana);
                SDL_Quit(); // También acabamos
                break;

            case SDL_WINDOWEVENT:
                // SDL_DisplayMode mode;
                if (ebentua.window.event == SDL_WINDOWEVENT_EXPOSED)
                {
                    SDL_GetWindowSize(Ventana, &screenWidth, &screenHeight);
                    SDL_Log("h: %d, w: %d", screenHeight, screenWidth);
                    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
                    SDL_SetRenderDrawColor(gRenderer, 225, 255, 198, SDL_ALPHA_OPAQUE);
                    SDL_Rect background = {0, 0, screenWidth, screenHeight};
                    SDL_RenderFillRect(gRenderer, &background);

                    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
                    SDL_RenderPresent(gRenderer);
                    SDL_Color kolor = {0x00, 0x00, 0x00};
                    // idatzi(gRenderer, 40, 40, "FreshKeep",, kolor, 40, "OpenSans-Regular.ttf");
                    tituluaIdatzi("FRESHKEEP", kolor, Ventana, "(Titulo)ChauPhilomeneOne-Regular.ttf");
                }
                break;
            }
        }
    }

    return 0;
}

/* if (Ventana == NULL)
        {
            printf("ERROR: No se pudo crear la ventana, SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Se crea la superficie para la ventana principal
            Superficie = SDL_GetWindowSurface(Ventana);

            // Se actualiza la superficie
            SDL_UpdateWindowSurface(Ventanaa);*/
