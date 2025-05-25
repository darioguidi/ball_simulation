#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore nella inizializzazone di SDL\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "BALL BALL ball bal...",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (window == NULL){
        printf("Errore nella inizializzazone di SDL\n");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL){
        printf("Errore nella inizializzazone di SDL\n");
        return 1;
    }

    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}