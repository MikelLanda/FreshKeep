// Esto con un incude de include
#include "input.h"
#include "zerrenda.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAPHICS

#include <SDL_ttf.h>

#include "graphics.h"
#include "imagen.h"

SDL_Window *window = NULL;
SDL_Renderer *gRenderer;
int colorR, colorG, colorB;

SDL_Renderer *getRenderer(void)
{
    return gRenderer;
}

int sgHasieratu()
{
    int ret = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "ezin SDL hasieratu: %s\n", SDL_GetError());
        return -1;
    }
    atexit(SDL_Quit);
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Ezin lehioa sortu: %s\n", SDL_GetError());
        return -1;
    }
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    atexit(TTF_Quit);
    return ret;
}

void sgItxi()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void arkatzKoloreaEzarri(int red, int green, int blue)
{
    colorR = red;
    colorG = green;
    colorB = blue;
}

void zuzenaMarraztu(int x1, int y1, int x2, int y2)
{
    SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

void puntuaMarraztu(int x, int y)
{
    SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(gRenderer, x, y);
}

void zirkuluaMarraztu(int x, int y, int r)
{

    int i, h;

    SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
    for (i = x - r; i <= x + r; i++)
    {
        h = (int)llround(sqrt((double)(r * r - (i - x) * (i - x))));
        SDL_RenderDrawLine(gRenderer, i, y + h, i, y - h);
    }
}

int irudiaMarraztu(SDL_Texture *texture, SDL_Rect *pDest)
{
    SDL_Rect src;

    src.x = 0;
    src.y = 0;
    src.w = pDest->w;
    src.h = pDest->h;
    SDL_RenderCopy(gRenderer, texture, &src, pDest);
    return 0;
}

void pantailaGarbitu()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
}

void pantailaBerriztu()
{
    SDL_RenderPresent(gRenderer);
}

void laukiaMarraztu(SDL_Renderer *gRenderer, int x, int y, int pw, int ph, SDL_Color color, TTF_Font *font,
                    const char *texto)
{
    SDL_Rect laukia = {x, y, pw, ph};
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(gRenderer, &laukia);
    SDL_Color tKolor = {0, 0, 0};
    font = TTF_OpenFontIndex("(Titulo)ChauPhilomeneOne-Regular.ttf", 40, 0);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, texto, tKolor);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    int textX = x + (pw - textWidth) / 2;
    int textY = y + (ph - textHeight) / 2;

    SDL_Rect textRect = {textX, textY, textWidth, textHeight};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &laukia);
}

void zerrendaLaukiaMarraztu(SDL_Renderer *gRenderer, int x, int y, int pw, int ph, SDL_Color color,
                            char produktuak[100][15], char datak[100][3][5])
{
    SDL_Rect laukia = {x, y, pw, ph};
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(gRenderer, &laukia);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &laukia);
    pantailaratuZerrenda(produktuak, datak, gRenderer, laukia);
}

void aldatuatala(SDL_Renderer *gRenderer, SDL_Color NorGaraKolorea, TTF_Font *font, int screenWidth, int zerjarri,
                 SDL_Window *Ventana, Input inputak[], int zenbatInput, char produktuak[100][15], char datak[100][3][5])
{
    if (zerjarri == 0)
    {
        irudiaMugitu(4, -2000, 200);
        irudiaMugitu(5, -2000, 200);
        irudiaMugitu(6, -2000, 200);
        irudiaMugitu(7, -2000, 200);
        irudiaMugitu(8, -2000, 200);
        irudiaMugitu(9, -2000, 200);

        inputak[0].inputBox.x = -2000;
        inputak[1].inputBox.x = -2000;
    }
    else if (zerjarri == 1)
    {
        irudiaMugitu(4, -2000, 200);
        irudiaMugitu(5, -2000, 200);
        irudiaMugitu(6, -2000, 200);
        irudiaMugitu(7, -2000, 200);
        irudiaMugitu(8, -2000, 200);
        irudiaMugitu(9, -2000, 200);

        laukiaMarraztu(gRenderer, 250, 200, (screenWidth - 500), 500, NorGaraKolorea, font, "");
        zerrendaLaukiaMarraztu(gRenderer, 250, 200, (screenWidth - 500), 500, NorGaraKolorea, produktuak, datak);

        inputak[0].inputBox.x = -2000;
        inputak[1].inputBox.x = -2000;
    }
    else if (zerjarri == 2)
    {
        irudiaMugitu(4, -2000, 200);
        irudiaMugitu(5, -2000, 200);
        irudiaMugitu(6, -2000, 200);
        irudiaMugitu(7, -2000, 200);
        irudiaMugitu(8, -2000, 200);
        irudiaMugitu(9, -2000, 200);

        laukiaMarraztu(gRenderer, 230, 200, (screenWidth - 460), 500, NorGaraKolorea, font, "");

        inputakZentratu(inputak, zenbatInput, gRenderer, Ventana);
        submiteguneratu(Ventana, 1, zerjarri, screenWidth);
        drawSubmitButton(gRenderer);
    }
    else if (zerjarri == 3)
    {
        inputak[0].inputBox.x = -2000;
        inputak[1].inputBox.x = -2000;

        irudiaMugitu(4, 200, 200);
        irudiaMugitu(5, 450, 200);
        irudiaMugitu(6, 700, 200);
        irudiaMugitu(7, 950, 200);
    }
}