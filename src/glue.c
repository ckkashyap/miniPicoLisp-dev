#include <stdio.h>
#include <SDL.h>

typedef void (*ACTION)(void);
SDL_Renderer* renderer = NULL;

__declspec(dllexport) int Clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    return 0;
}

__declspec(dllexport) int Swap()
{
    SDL_RenderPresent(renderer);
    return 0;
}

__declspec(dllexport) int DrawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    return 0;
}

__declspec(dllexport) int glue(int width, int height, ACTION a)
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;

        if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                // SDL_RenderClear(renderer);
                // SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                // SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
                // SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                // SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
                // SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                // SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
                // SDL_RenderPresent(renderer);
                a();

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = NULL;
        }
    }
    SDL_Quit();
    return 0;
}

