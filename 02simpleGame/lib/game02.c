#include "game02.h"
#include "boton.h"
#include "ebentoak.h"
#include "gorde.h"
#include "graphics.h"
#include "ikono.h"
#include "imagen.h"
#include "input.h"
#include "soinua.h"
#include "text.h"
#include "zerrenda.h"
#include <input.h>
#include <stdio.h>

#define NOR_GARA_IMG "./img/nor_gara.bmp"
#define DONAZIOA_IMG "./img/donazioa.bmp"
#define GEHITU_IMG "./img/gehitu.bmp"
#define HASIERA_IMG "./img/hasiera.bmp"
#define HOSTOA_IMG "./img/hostoa.bmp"
#define LISTA_IMG "./img/lista.bmp"
#define OSASUNA_IMG "./img/osasuna.bmp"
#define FONDO_ABAJO_IMG "./img/fondo_abajo.bmp"
#define FONDO_ARRIBA_IMG "./img/fondo_arriba.bmp"
#define JOKOA_SOUND "./sound/Audio fondo.mp3"
#define LOGO_ESCRITORIO_IMG "./img/icono.png"
#define BERDEILUNA "./img/MugitzenDena.bmp"
#define SOINUAPIZTUTA "./img/soinuapiztu.bmp"
#define SOINUAITZALITA "./img/soinuaitzali.bmp"
#define PERFILMARKEL "./img/Perfil_Markel.bmp"
#define PERFILMIKEL "./img/Perfil_Mikel.bmp"
#define PERFILIZARO "./img/Perfil_Izaro.bmp"
#define PERFILNEREA "./img/Perfil_Nerea.bmp"
#define TESTUAHORIZONTAL "./img/TESTUA_NORGARA_HORIZONTALA.bmp"
#define TESTUABERTIKAL "./img/TESTUA_NORGARA_BERTIKALA.bmp"
#define JOKOA_SOUND "./sound/Audio fondo.mp3"
#define HOSTOA_SOUND "./sound/hostoa_sound.mp3"
#define GORDE_SOUND "./sound/gorde_sound.mp3"
// #define PASATU_ORRIA_SOUND "./sound/pasatuOrria_sound.mp3"
#define BOTOIAK_SOUND "./sound/botoiak_sound.mp3"
#define SOINUA_SOUND "./sound/soinua_sound.mp3"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int pantailaHasi();
int Irudiakjarri(int zeregin);
void refrescarpagina(int zeregin, int zerjarri);
void idatziFitxategian(char izena[], char testua[]);

char inputText[250] = "";
SDL_Window *Ventana = NULL;
SDL_Surface *Superficie = NULL;
SDL_Renderer *gRenderer;
SDL_Rect src, dst;
TTF_Font *font;
SDL_Color laukizuzenarenKolorea = {255, 255, 198, SDL_ALPHA_OPAQUE};
SDL_Color NorGaraKolorea = {255, 255, 255, SDL_ALPHA_OPAQUE};

Button Hostoa_Botoia = {{6, 1, 100, 70}, {255, 0, 0, 255}, 0};
Button Soinua_Botoia = {{1460, 3, 50, 50}, {255, 0, 0, 255}, 0};
Button Hasiera_Botoia = {{10, 100, 160, 50}, {255, 0, 0, 255}, 0};
Button ListaOsoa_Botoia = {{10, 180, 160, 50}, {255, 0, 0, 255}, 0};
Button Gehitu_Botoia = {{10, 260, 160, 50}, {255, 0, 0, 255}, 0};
Button NorGara_Botoia = {{10, 340, 160, 50}, {255, 0, 0, 255}, 0};
Button Idatzi_Botoia = {{600, 100, 180, 50}, {255, 0, 0, 255}, 0}; // 300

Input inputak[10] = {{{400, 250, 180, 50}, "", 0, "Produktua"}, {{400, 350, 180, 50}, "", 0, "Iraungitze data"}};
int zenbatInput = 2;
Input *inputAktiboa = &inputak[0];

int fin = 0, id;
int screenWidth;
int screenHeight;
int kopuru, kop = 1, i;
int soinuapiztutadago = 1;
int lehenengoaldia = 1;
int menuairekita = 0;
int zeregin = 0;
int nuevoscreenWidth;
int nuevoscreenHeigth;
int zerjarri = 0;
int botoiabehinklikatu = 0;
int animazioaeginda = 0;
int HostoaSound = -2;
int BotoiakSound = -2;
int GordeSound = -2;
// int PasatuOrriaSound;
int SoinuaSound = -2;

char produktuak[100][15];
char datak[100][3][5];
int zenbatProduktu;

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
        Ventana = SDL_CreateWindow("FreshKeep", 20, 20, 1980, 920, SDL_WINDOW_RESIZABLE);
        SDL_SetWindowFullscreen(Ventana, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    gRenderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);
    aldatuatala(gRenderer, NorGaraKolorea, font, screenWidth, zerjarri, Ventana, inputak, zenbatInput, produktuak,
                datak, screenHeight, laukizuzenarenKolorea, menuairekita, soinuapiztutadago, animazioaeginda);
    animazioaeginda = 1;
    SDL_GetWindowSize(Ventana, &screenWidth, &screenHeight);
    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
    SDL_SetRenderDrawColor(gRenderer, 225, 255, 198, SDL_ALPHA_OPAQUE);
    SDL_Rect background = {0, 0, 1980, 920};
    SDL_RenderFillRect(gRenderer, &background);

    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_Color kolor = {0x00, 0x00, 0x00};

    kopuru = Irudiakjarri(0, screenWidth);

    // soinua
    audioInit();
    loadTheMusic(JOKOA_SOUND);
    playMusic();
    // idatziFitxategian("fitxategia.txt", "kaixo");

    // icono
    ikonoajarribehekobarran(Ventana, LOGO_ESCRITORIO_IMG);

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

                else if (ebentua.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (SDL_strlen(inputAktiboa->inputText) > 0 && inputAktiboa != NULL)
                    {
                        char text[250];
                        SDL_strlcpy(text, inputAktiboa->inputText, 50);
                        text[SDL_strlen(text) - 1] = '\0';
                        SDL_strlcpy(inputAktiboa->inputText, text, 50);
                        inputMarraztu(gRenderer, inputAktiboa);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick(&ebentua, &Hostoa_Botoia);
                handleMouseClick(&ebentua, &Soinua_Botoia);
                handleMouseClick(&ebentua, &Hasiera_Botoia);
                handleMouseClick(&ebentua, &ListaOsoa_Botoia);
                handleMouseClick(&ebentua, &Gehitu_Botoia);
                handleMouseClick(&ebentua, &NorGara_Botoia);
                if (inputAktiboa != NULL)
                {
                    int index;
                    // handleInputSelected(&ebentua, inputAktiboa, gRenderer);
                    index = searchSelectedInput(&ebentua, inputAktiboa, inputak, zenbatInput, gRenderer);
                    if (index >= 0)
                    {
                        inputAktiboa = &inputak[index];
                    }
                };
                int submit = handleSubmitButton(&ebentua);
                if (submit && inputAktiboa != NULL)
                {
                    if (GordeSound == -2)
                    {
                        GordeSound = loadSound(GORDE_SOUND);
                    }
                    playSound(GordeSound);
                    SDL_Log("Enter");
                    int strlen = 0;
                    char datua[50] = "";
                    SDL_strlcpy(datua, inputak[0].inputText, 50);
                    strlen = SDL_strlcat(datua, ", ", 50);
                    strlen = SDL_strlcat(datua, inputak[1].inputText, 50);
                    strlen = SDL_strlcat(datua, "\n", 50);
                    SDL_Log("%s", datua);
                    idatziFitxategian("fitxategia.txt", datua);
                    zenbatProduktu = irakurri("fitxategia.txt", produktuak, datak);
                    datakOrdenatu(datak, produktuak, zenbatProduktu);
                    inputakGarbitu(inputak, zenbatInput, gRenderer);
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
                    SDL_GetWindowSize(Ventana, &nuevoscreenWidth, &nuevoscreenHeigth);
                    if (nuevoscreenWidth > 950)
                    {
                        screenWidth = nuevoscreenWidth;
                    }
                    else
                    {
                        screenWidth = 950;
                    }
                    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
                    Soinua_Botoia.rect.x = screenWidth - 61;
                    if (!lehenengoaldia)
                    {
                        refrescarpagina(0, zerjarri);
                        inputakMarraztu(gRenderer, inputak, zenbatInput);
                    }
                }
                break;

            case SDL_TEXTINPUT:
                if (SDL_strlen(inputAktiboa->inputText) < 12 && inputAktiboa != NULL)
                {
                    SDL_strlcat(inputAktiboa->inputText, ebentua.text.text, 50);
                    inputMarraztu(gRenderer, inputAktiboa);
                }
            }
        }
        if (Hostoa_Botoia.isClicked)
        {
            if (HostoaSound == -2)
            {
                HostoaSound = loadSound(HOSTOA_SOUND);
            }
            playSound(HostoaSound);
            if (!menuairekita)
            {
                // Lógica cuando el botón es clicado por primera vez
                menuairekita = 1;
                /*tics = SDL_GetTicks();*/
                irudiaMugitubateskuinera(0);
                irudiaMugitubateskuinera(1);
                refrescarpagina(1, zerjarri);
            }
            else
            {
                // Lógica cuando el botón es clicado después de la primera vez
                menuairekita = 0;
                /*tics = SDL_GetTicks();*/
                irudiaMugitubatezkerrera(0);
                irudiaMugitubatezkerrera(1);
                refrescarpagina(1, zerjarri);
            }

            // Resetear la variable isClicked después de procesar el clic
            Hostoa_Botoia.isClicked = 0;
        }

        if (Soinua_Botoia.isClicked)
        {
            if (SoinuaSound == -2)
            {
                SoinuaSound = loadSound(SOINUA_SOUND);
            }
            playSound(SoinuaSound);
            if (soinuapiztutadago)
            {

                Mix_PauseMusic();
                irudiaMugitu(3, 1150, 1);
                irudiaMugitu(2, 3000, 0);
                soinuapiztutadago = 0;
                refrescarpagina(2, zerjarri);
            }
            else
            {
                Mix_ResumeMusic();
                irudiaMugitu(2, 1150, 1);
                irudiaMugitu(3, 3000, 0);
                soinuapiztutadago = 1;
                refrescarpagina(2, zerjarri);
            }
            Soinua_Botoia.isClicked = 0;
        }
        if (Hasiera_Botoia.isClicked)
        {
            if (BotoiakSound == -2)
            {
                BotoiakSound = loadSound(BOTOIAK_SOUND);
            }
            zerjarri = 0;
            refrescarpagina(0, zerjarri);
            SDL_RenderPresent(gRenderer);
            Hasiera_Botoia.isClicked = 0;
        }
        if (ListaOsoa_Botoia.isClicked)
        {
            if (BotoiakSound == -2)
            {
                BotoiakSound = loadSound(BOTOIAK_SOUND);
            }
            zerjarri = 1;
            refrescarpagina(0, zerjarri);
            SDL_RenderPresent(gRenderer);
            ListaOsoa_Botoia.isClicked = 0;
        }
        if (Gehitu_Botoia.isClicked)
        {
            zerjarri = 2;
            refrescarpagina(0, zerjarri);
            Gehitu_Botoia.isClicked = 0;
        }
        if (NorGara_Botoia.isClicked)
        {
            zerjarri = 3;
            refrescarpagina(0, zerjarri);
            NorGara_Botoia.isClicked = 0;
        }

        SDL_RenderPresent(gRenderer);
    }
    return 0;
}

int Irudiakjarri(int zeregin, int pantailarentamaina)
{
    int id = -1;

    if (lehenengoaldia)
    {
        id = irudiaKargatu(BERDEILUNA);       // 0
        id = irudiaKargatu(HOSTOA_IMG);       // 1
        id = irudiaKargatu(SOINUAPIZTUTA);    // 2
        id = irudiaKargatu(SOINUAITZALITA);   // 3
        id = irudiaKargatu(PERFILMARKEL);     // 4
        id = irudiaKargatu(PERFILMIKEL);      // 5
        id = irudiaKargatu(PERFILIZARO);      // 6
        id = irudiaKargatu(PERFILNEREA);      // 7
        id = irudiaKargatu(TESTUAHORIZONTAL); // 8
        id = irudiaKargatu(TESTUABERTIKAL);   // 9
        irudiaMugitu(0, -327, 0);
        irudiaMugitu(1, 6, 1);
        irudiaMugitu(2, pantailarentamaina - 75, 3);
        irudiaMugitu(3, -1150, 5);
        irudiaMugitu(4, -2000, 200);
        irudiaMugitu(5, -2000, 200);
        irudiaMugitu(6, -2000, 200);
        irudiaMugitu(7, -2000, 200);
        irudiaMugitu(8, -2000, 200);
        irudiaMugitu(9, -2000, 200);

        lehenengoaldia = 0;
    }
    if ((zeregin == 0) || (zeregin == 1))
    {
        if (!menuairekita)
        {
            irudiaMugitu(0, -327, 0);
            irudiaMugitu(1, 6, 1);
            Hostoa_Botoia.rect.x = 6;
            Hostoa_Botoia.rect.y = 1;
        }
        else if (menuairekita)
        {
            irudiaMugitu(0, -152, 0);
            irudiaMugitu(1, 181, 1);
            Hostoa_Botoia.rect.x = 181;
            Hostoa_Botoia.rect.y = 1;
        }
    }
    else if ((zeregin == 0) || (zeregin == 2))
    {
        if (!soinuapiztutadago)
        {
            irudiaMugituPantailarekinEzkerrerantz(3, Ventana);
        }
        else if (soinuapiztutadago)
        {
            irudiaMugituPantailarekinEzkerrerantz(2, Ventana);
        }
    }
    if ((zerjarri == 3) && (pantailarentamaina > 1200))
    {
        irudiaMugitu(4, 200, 200);
        irudiaMugitu(5, 450, 200);
        irudiaMugitu(6, 700, 200);
        irudiaMugitu(7, 950, 200);
        irudiaMugitu(8, (pantailarentamaina / 2) - 325, 475);
        irudiaMugitu(9, -2000, 175);
    }
    else if ((zerjarri == 3) && (pantailarentamaina > 600))
    {
        irudiaMugitu(4, 200, 200);
        irudiaMugitu(5, 200, 450);
        irudiaMugitu(6, 450, 200);
        irudiaMugitu(7, 450, 450);
        irudiaMugitu(8, -2000, 550);
        irudiaMugitu(9, pantailarentamaina - 305, 220);
    }
    if (soinuapiztutadago)
    {
        irudiaMugituPantailarekinEzkerrerantz(2, Ventana);
    }
    else if (!soinuapiztutadago)
    {

        irudiaMugituPantailarekinEzkerrerantz(3, Ventana);
    }
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
}

void refrescarpagina(int zeregin, int zerjarri)
{
    SDL_GetWindowSize(Ventana, &screenWidth, &screenHeight);
    SDL_Log("h: %d, w: %d", screenHeight, screenWidth);
    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
    SDL_SetRenderDrawColor(gRenderer, 225, 255, 198, SDL_ALPHA_OPAQUE);
    SDL_Rect background = {0, 0, screenWidth, screenHeight};
    SDL_RenderFillRect(gRenderer, &background);
    aldatuatala(gRenderer, NorGaraKolorea, font, screenWidth, zerjarri, Ventana, inputak, zenbatInput, produktuak,
                datak, screenHeight, laukizuzenarenKolorea, menuairekita, soinuapiztutadago, animazioaeginda);
    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_RenderPresent(gRenderer);

    SDL_Color kolor = {0x00, 0x00, 0x00};
    tituluaIdatzi("FRESHKEEP", kolor, Ventana, "(Titulo)ChauPhilomeneOne-Regular.ttf", 30);
    Irudiakjarri(zeregin, screenWidth);
    if (menuairekita)
    {
        laukiaMarraztu(gRenderer, 10, 100, 160, 50, laukizuzenarenKolorea, font, "Hasiera");
        laukiaMarraztu(gRenderer, 10, 180, 160, 50, laukizuzenarenKolorea, font, "Lista osoa");
        laukiaMarraztu(gRenderer, 10, 260, 160, 50, laukizuzenarenKolorea, font, "Gehitu");
        laukiaMarraztu(gRenderer, 10, 340, 160, 50, laukizuzenarenKolorea, font, "Nor gara");
        SDL_RenderPresent(gRenderer);
    }
    submiteguneratu(Ventana, menuairekita, zerjarri, screenWidth);
}