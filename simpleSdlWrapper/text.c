
#include <SDL.h>
#include <SDL_ttf.h>

#include "graphics.h"
#include "imagen.h"
#include "text.h"
#include <stdio.h>

TTF_Font *font = 0;

void textuaGaitu(char *letra, int tamaina)
{
    TTF_Init();
    font = TTF_OpenFontIndex(letra, tamaina, 0);
    if (!font)
    {
        printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
        // handle error
    }
}

void textuaIdatzi(int x, int y, char *str, SDL_Color textColor)
{

    SDL_Surface *textSurface;
    SDL_Texture *mTexture;
    // SDL_Color textColor = {0X00, 0X00, 0X00};
    SDL_Rect src, dst;
    SDL_Renderer *gRenderer;

    if (font == 0)
    {
        return;
    }
    gRenderer = getRenderer();
    textSurface = TTF_RenderText_Solid(font, str, textColor);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    src.x = 0;
    dst.x = x;
    src.y = 0;
    dst.y = y;
    src.w = dst.w = textSurface->w;
    src.h = dst.h = textSurface->h;
    SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(mTexture);
}

void textuaDesgaitu(void)
{
    if (font != 0)
    {
        TTF_CloseFont(font);
    }
    font = 0;
}

void idatzi(SDL_Renderer *gRenderer, int x, int y, char *testua, SDL_Color kolorea, int tamaina, char *letra)
{
    textuaGaitu(letra, tamaina);
    textuaIdatzi(x, y, testua, kolorea);
    SDL_RenderPresent(gRenderer);
}

void tituluaIdatzi(char *str, SDL_Color textColor, SDL_Window *Ventana, char *fuente)
{
    textuaGaitu(fuente, 50);
    SDL_Surface *textSurface;
    SDL_Texture *mTexture;
    SDL_Rect src, dst;
    SDL_Renderer *gRenderer;
    int w = 0;
    int h = 0;
    int wWindow = 0;
    int hWindow = 0;

    if (font == 0)
    {
        return;
    }
    gRenderer = getRenderer();
    textSurface = TTF_RenderText_Solid(font, str, textColor);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_GetWindowSize(Ventana, &wWindow, &hWindow);
    SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
    src.x = 0;
    dst.x = (wWindow - w) / 2;
    src.y = 0;
    dst.y = 30;
    src.w = dst.w = textSurface->w;
    src.h = dst.h = textSurface->h;
    SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
    SDL_RenderPresent(gRenderer);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(mTexture);
}
