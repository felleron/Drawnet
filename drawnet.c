#include "drawnet.h"
#define WINDOW_X 100
#define WINDOW_Y 100
#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000

#define NETWORK_WIDTH (float)1400
#define NETWORK_HEIGHT (float)1000
#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))
int arch[] = {2,6,12,24,12,6,1,6,12,24,12,6,2};

void SDL_RenderFillCircle(SDL_Renderer *renderer ,int x, int y, int radius, SDL_Color c)
{
    SDL_SetRenderDrawColor(renderer,c.r, c.g, c.b, c.a);
    for(int w = 0; w < radius * 2; w++)   {
        for(int h = 0; h < radius * 2; h++)   {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius*radius))   {
                SDL_RenderDrawPoint(renderer,x+dx, y+dy);
            }
        }
    }
}

void render_network(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    SDL_Rect box;
    box.w = NETWORK_WIDTH;
    box.h = NETWORK_HEIGHT;
    box.x = x;
    box.y = y;

    SDL_RenderDrawRect(renderer, &box);
    SDL_Color c;
    c.r = 0x00;
    c.g = 0xFF;
    c.b = 0x00;
    c.a = 0x00;

    float layers = ARRAY_LEN(arch);
    float layer_width = NETWORK_WIDTH / layers;
    float x_offset = layer_width / 2;


    for(int i = 0; i < layers; i++) {
        float xPos = x + i * layer_width + x_offset;

        for(int j = 0; j < arch[i]; j++) {
            float neuron_height = NETWORK_HEIGHT / arch[i];
            float y_offset = neuron_height / 2;
            float yPos = y + j * neuron_height + y_offset;
                if(i < layers - 1)  {
                    for(int k = 0; k < arch[i+1]; k++) {
                        float xPos2 = x + (i+1) * layer_width + x_offset;
                        float neuron_height2 = NETWORK_HEIGHT / arch[i+1];
                        float y_offset2 = neuron_height2 / 2;
                        float yPos2 = y + k * neuron_height2 + y_offset2;
                        SDL_SetRenderDrawColor(renderer,0x55,0x55,0x55,255);
                        SDL_RenderDrawLine(renderer, xPos, yPos, xPos2, yPos2);

                        
                    }
                }
            int size = 100 / arch[i] + 2;
            SDL_RenderFillCircle(renderer, xPos, yPos, size, c);

        }


    }



    return;

}

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_INIT_VIDEO < 0) {
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO");
    }
    
    window = SDL_CreateWindow(
        "",
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        fprintf(stderr, "ERROR: !window");
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)  {
        fprintf(stderr, "ERROR: !renderer");
    } 

    int net_x = (WINDOW_WIDTH / 2) - (NETWORK_WIDTH / 2);
    int net_y = (WINDOW_HEIGHT / 2) - (NETWORK_HEIGHT / 2);

    SDL_Event event;
    bool quit = false;

    while(!quit)    {
        while(SDL_PollEvent(&event))    {
            switch(event.type)  {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)    {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            arch[0]++;
                            arch[1] = arch[1] + 2;
                            break;
                        case SDLK_DOWN:
                            arch[0]--;
                            arch[1] = arch[1] - 2;
                            break;
                        case SDLK_RIGHT:
                            arch[2]++;
                            break;
                        case SDLK_LEFT:
                            arch[2]--;
                            break;
                    }
                    break;
            } 

        }
        SDL_RenderClear(renderer);
        // start render loop

        render_network(renderer, net_x, net_y);

        // end redner loop
        SDL_SetRenderDrawColor(renderer, 0x11,0x11,0x11,255);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}