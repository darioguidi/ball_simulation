#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCREEN_OFFSET_X SCREEN_WIDTH/2
#define SCREEN_OFFSET_Y SCREEN_HEIGHT/2
#define PI 3.141592653589793
#define SIZE_POINT 5

float phi = 5;
float theta = 5; 


// Struct - Point
struct Point {
    int x;
    int y;
    int z;
};

// Disegna un singolo punto
void draw_point(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect rect = (SDL_Rect) {x,y,SIZE_POINT,SIZE_POINT};
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer,&rect);
}

// Disegnare il punto applicata la trasformazione
void draw_point_3d(SDL_Renderer *renderer, struct Point point)
{
    int x = point.x;
    int y = point.y;
    int z = point.z; 

    draw_point(renderer, x,y);
}

void draw_point_3d_array(SDL_Renderer *renderer, struct Point *ball)
{
    for(int i=0;i<10;i++){
        draw_point_3d(renderer, *(ball+i));
    }
}

struct Point* generate_ball(int raggio)
{
    int total_number_point = 4*PI*(raggio)*(raggio);
    struct Point *ball = malloc(total_number_point*sizeof(struct Point));

    for(int i=0;i<total_number_point;i++){
        int x_2d  = SCREEN_OFFSET_X+raggio*sin(phi)*cos(theta);
        int y_2d  = SCREEN_OFFSET_Y+raggio*sin(phi)*sin(theta);
        int z_2d = SCREEN_OFFSET_X+raggio*cos(phi);

        *(ball+i) = (struct Point) {x_2d,y_2d,z_2d};
    }

    return ball;
}

// Main
int main(int argc, char* argv[])
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

    struct Point *ball = generate_ball(100);

    int running = 1;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Chiusura programma\n");
                running=0;
            }

            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            
            draw_point_3d_array(renderer, ball);
            SDL_RenderPresent(renderer);

            SDL_RenderClear(renderer);
            SDL_Delay(16);
            
            phi+=0.05;
            theta+=0.05;
        }
    }

    free(ball);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}