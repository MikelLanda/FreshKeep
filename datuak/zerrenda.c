#include "gorde.h"
#include "text.h"
#include <SDL.h>
#include <stdio.h>
#include <time.h>

void eguneratuData(char data[3][5]);
void pantailaratuZerrenda(char produktuak[100][15], char datak[100][3][5], SDL_Renderer *gRenderer, SDL_Rect laukia)
{
    int x = 400, y = laukia.y + 40, i = 0, zenbat = 0, diferentzia = 0, pantailaratuak = 0;
    SDL_Color kolorea = {0x00, 0x00, 0x00};
    zenbat = irakurri("fitxategia.txt", produktuak, datak);
    int gaurkoData[3] = {0, 0, 0};
    eguneratuData(gaurkoData);
    while (i < zenbat && pantailaratuak < 9)
    {
        char data[20];

        diferentzia = denboraKalkulatu(datak[i], gaurkoData, data);
        if (diferentzia >= 0)
        {
            idatzi(gRenderer, laukia.x + 40, y, produktuak[i], kolorea, 30, "OpenSans-Regular.ttf");
            idatzi(gRenderer, laukia.x + laukia.w - 180, y, data, kolorea, 30, "OpenSans-Regular.ttf");
            y += 50;
            pantailaratuak++;
        }
        i++;
    }

    SDL_RenderPresent(gRenderer);
}

void eguneratuData(int data[3])
{
    time_t t;
    struct tm *tm;
    t = time(NULL);
    tm = localtime(&t);

    data[0] = 1900 + tm->tm_year;
    data[1] = tm->tm_mon + 1;
    data[2] = tm->tm_mday;
}

int denboraKalkulatu(char data[3][5], int gaurkoData[3], char dst[20])
{
    int urtea = atoi(data[0]);
    int urteAktuala = gaurkoData[0];
    int hilabetea = atoi(data[1]);
    int hilabeteAktuala = gaurkoData[1];
    int eguna = atoi(data[2]);
    int egunAktuala = gaurkoData[2];

    int diferentzia = 0;
    char unitatea[10];

    if (urtea != urteAktuala)
    {
        diferentzia = urtea - urteAktuala;
        SDL_strlcpy(unitatea, " urte", 20);
    }
    else if (hilabetea != hilabeteAktuala)
    {
        diferentzia = hilabetea - hilabeteAktuala;
        SDL_strlcpy(unitatea, " hilabete", 20);
    }
    else
    {
        diferentzia = eguna - egunAktuala;
        SDL_strlcpy(unitatea, " egun", 20);
    }

    if (diferentzia >= 0)
    {
        sprintf(dst, "%d", diferentzia);
        SDL_strlcat(dst, unitatea, 20);
    }

    return diferentzia;
}