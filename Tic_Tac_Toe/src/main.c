#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

int main(int argc, char const *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window = SDL_CreateWindow("Tic Tac Toe", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    //initialize the game 
    game_t game = {
        .board = {
            EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY},
        .player = PLAYER_1,
        .state = RUNNING_STATE};

    SDL_Event event;
    //Game Loop
    while (game.state != QUIT_STATE)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game.state = QUIT_STATE;
                break;

            case SDL_MOUSEBUTTONDOWN:
                click_on_cell(&game,
                              event.button.y / CELL_HEIGHT,  //Converting the mouse position in cell cordinates
                              event.button.x / CELL_WIDTH);
                break;
                
            default:
            {
                //do nothing
            }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            render_game(renderer, &game);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
