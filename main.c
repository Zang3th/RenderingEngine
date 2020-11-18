#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("RenderingEngine", 0, 0, 1280, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 0);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(4000);

    SDL_DestroyWindow(window);

    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}