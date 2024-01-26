#ifndef GORDE_H
#define GORDE_H

void idatziFitxategian(char izena[], char testua[]);
int irakurri(char izena[], char produktuak[100][15], char datak[100][3][5]);
void datuakBihurtu(char str[], char izena[50], char data[3][5]);
int datakKonparatu(char data1[3][5], char data2[3][5]);
void datakOrdenatu(char datak[100][3][5], char produktuak[100][15], int zenbat);
void trukatuProduktuak(char produktu1[15], char data1[3][5], char produktu2[15], char data2[3][5]);
int konprobatuProduktuaFormatua(char produktua[20]);
int konprobatuDataFormatua(char data[20]);

#endif