#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

void idatziFitxategian(char izena[], char testua[]);
int irakurri(char izena[], char produktuak[100][15], char datak[100][3][5]);
void datuakBihurtu(char str[], char izena[50], char data[3][5]);
int datakKonparatu(char data1[3][5], char data2[3][5]);
void datakOrdenatu(char datak[100][3][5], char produktuak[100][15], int zenbat);
void trukatuProduktuak(char produktu1[15], char data1[3][5], char produktu2[15], char data2[3][5]);

void idatziFitxategian(char izena[], char testua[])
{

    char database[300] = "";
    FILE *fitxategia;
    fitxategia = fopen(izena, "a");
    if (fitxategia)
    {
        fprintf(fitxategia, "%s", testua);
    }

    fclose(fitxategia);
}

int irakurri(char izena[], char produktuak[100][15], char datak[100][3][5])
{
    FILE *fitxategia;
    char linea[30];
    int i = 0;
    int amaituta = 0;
    fitxategia = fopen(izena, "r");
    if (fitxategia)
    {
        while (!amaituta)
        {
            if (fgets(linea, 125, fitxategia) != NULL) // Konprobatu lerroa hutsik badago
            {
                datuakBihurtu(linea, produktuak[i], datak[i]);
                i++;
            }
            else
            {
                amaituta = 1;
            }
        }
    }
    fclose(fitxategia);
    datakOrdenatu(datak, produktuak, i);
    return i;
}

void datuakBihurtu(char str[], char izena[50], char data[3][5])
{
    int i = 0, j = 0;
    char produktua[30];
    char urtea[5];
    char hilabetea[3];
    char eguna[3];

    while (i < SDL_strlen(str) && str[i] != ',')
    {
        produktua[i] = str[i];
        i++;
    }
    i += 2;
    while (i < SDL_strlen(str) && str[i] != '/')
    {

        urtea[j] = str[i];
        j++;
        i++;
    }
    i++;
    j = 0;
    while (i < SDL_strlen(str) && str[i] != '/')
    {

        hilabetea[j] = str[i];
        j++;
        i++;
    }
    i++;
    j = 0;
    while (i < SDL_strlen(str) && str[i] != '\0')
    {

        eguna[j] = str[i];
        j++;
        i++;
    }
    produktua[i] = '\0';
    urtea[4] = '\0';
    hilabetea[2] = '\0';
    eguna[2] = '\0';
    SDL_Log("Produktua: %s", produktua);
    SDL_Log("Urtea: %s", urtea);
    SDL_strlcpy(izena, produktua, 10);
    SDL_strlcpy(data[0], urtea, 10);
    SDL_strlcpy(data[1], hilabetea, 10);
    SDL_strlcpy(data[2], eguna, 10);
    //{produktua, {urtea, hila, egun}}
}

int datakKonparatu(char data1[3][5], char data2[3][5])
{
    int urte1 = atoi(data1[0]);
    int urte2 = atoi(data2[0]);
    int hilabete1 = atoi(data1[1]);
    int hilabete2 = atoi(data2[1]);
    int egun1 = atoi(data1[2]);
    int egun2 = atoi(data2[2]);

    int diferentzia = 0;

    if (urte1 != urte2)
    {
        diferentzia = urte2 - urte1;
    }
    else if (hilabete1 != hilabete2)
    {
        diferentzia = hilabete2 - hilabete1;
    }
    else
    {
        diferentzia = egun2 - egun1;
    }
    return diferentzia;
}

void datakOrdenatu(char datak[100][3][5], char produktuak[100][15], int zenbat)
{
    for (int i = 0; i < zenbat - 1; i++)
    {
        for (int j = 0; j < zenbat - i - 1; j++)
        {
            if (datakKonparatu(datak[j], datak[j + 1]) < 0)
            {
                trukatuProduktuak(produktuak[j], datak[j], produktuak[j + 1], datak[j + 1]);
            }
        }
    }
}

void trukatuProduktuak(char produktu1[15], char data1[3][5], char produktu2[15], char data2[3][5])
{
    char tmpProduktua[15];
    char tmpData[3][5];

    SDL_strlcpy(tmpProduktua, produktu1, 15);
    SDL_strlcpy(tmpData[0], data1[0], 5);
    SDL_strlcpy(tmpData[1], data1[1], 5);
    SDL_strlcpy(tmpData[2], data1[2], 5);
    SDL_strlcpy(produktu1, produktu2, 15);
    SDL_strlcpy(data1[0], data2[0], 5);
    SDL_strlcpy(data1[1], data2[1], 5);
    SDL_strlcpy(data1[2], data2[2], 5);
    SDL_strlcpy(produktu2, tmpProduktua, 15);
    SDL_strlcpy(data2[0], tmpData[0], 5);
    SDL_strlcpy(data2[1], tmpData[1], 5);
    SDL_strlcpy(data2[2], tmpData[2], 5);
}
