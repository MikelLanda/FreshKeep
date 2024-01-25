#ifndef TEXT_H
#define TEXT_H
#include <SDL.h>

void textuaGaitu(char *letra, int tamaina);
void textuaIdatzi(int x, int y, char *str, SDL_Color textColor);
void idatzi(SDL_Renderer *gRenderer, int x, int y, char *testua, SDL_Color kolorea, int tamaina, char *letra);
void tituluaIdatzi(char *str, SDL_Color textColor, SDL_Window *Ventana, char *fuente, int altuera);

#endif
