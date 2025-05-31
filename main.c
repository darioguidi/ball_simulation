#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define SCREEN_OFFSET_X SCREEN_WIDTH/2
#define SCREEN_OFFSET_Y SCREEN_HEIGHT/2
#define PI 3.141592653589793
#define CONSTANT_GTAVITATIONAL = 9,80
#define SIZE_POINT_SPHERE 2
#define SIZE_POINT_SPACE 1

float phi = 5;
float theta = 5; 


// Struct - Point
typedef struct Point {
    int x;
    int y;
    int z;
} Point;

// Sfera------------------------------------------------------------------------
// Disegna un singolo punto
void draw_point(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect rect = (SDL_Rect) {x,y,SIZE_POINT_SPHERE,SIZE_POINT_SPHERE};
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer,&rect);
}

// Disegnare il punto applicata la trasformazione
void draw_point_3d(SDL_Renderer *renderer, Point point, float massa)
{
    float x = point.x;
    float y = point.y;
    float z = point.z;

    // Rotazione attorno a Y
    float x_rot = x * cos(theta) - z * sin(theta);
    float z_rot = x * sin(theta) + z * cos(theta);

    // Rotazione attorno a X
    float y_rot = y * cos(phi) - z_rot * sin(phi);

    int screen_x = (int)(SCREEN_OFFSET_X + x_rot / 10);  // scala per stare dentro la finestra
    int screen_y = (int)(SCREEN_OFFSET_Y + y_rot / 10);

    draw_point(renderer, screen_x, screen_y);
}

void draw_point_3d_array(SDL_Renderer *renderer, Point *ball, int total_point, float massa)
{
    for(int i=0;i<total_point;i++){
        draw_point_3d(renderer, *(ball+i), massa);
    }
}

Point* generate_ball(int raggio, int total_number_point)
{
    Point *ball = malloc(total_number_point*sizeof(struct Point));
    for(int i=0;i<total_number_point;i++){

        float u = (float)rand() / RAND_MAX;
        float v = (float)rand() / RAND_MAX;
        float theta_point = 2 * PI * u;
        float phi_point = acos(2 * v - 1);

        int x_2d = raggio * sin(phi_point) * cos(theta_point);
        int y_2d = raggio * sin(phi_point) * sin(theta_point);
        int z_2d = raggio * cos(phi_point);

        *(ball+i) = (struct Point) {x_2d,y_2d,z_2d};
    }

    return ball;
}

// Spazio------------------------------------------------------------------------

// Genera il piano
Point* generate_space(int size){
    Point *space = malloc(size*sizeof(Point));
    for (int i=0; i<size; i++){
        *(space+i) = (Point) {0,1,1};
    }
    return space;
}


// Main
int main(int argc, char* argv[])
{
    int r;
    float massa_sfera;

    printf("Inserire raggio della sfera\n");
    scanf("%d",&r);

    printf("Inserire la massa della sfera: ");
    scanf("%f", &massa_sfera);


    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore nella inizializzazone di SDL\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "sphere",
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

    // int total_number_point = 4*PI*(r)*(r);
    int total_number_point = 1500;
    Point *ball = generate_ball(r, total_number_point);
    Point *space = generate_space(900);

    int running = 1;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Chiusura programma\n");
                running=0;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
            
        draw_point_3d_array(renderer, ball, total_number_point, massa_sfera);
        SDL_RenderPresent(renderer);

        SDL_RenderClear(renderer);
        SDL_Delay(16);
            
        phi+=0.002;
        theta+=0.002;

        printf("%f and %f \n", theta, phi);
    }

    free(ball);
    free(space);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}