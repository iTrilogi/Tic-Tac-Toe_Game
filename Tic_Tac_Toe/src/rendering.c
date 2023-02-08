#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "game.h"
#include "rendering.h"

const SDL_Color GRID_COLOR = {.r = 255, .g = 255, .b = 255};
const SDL_Color PLAYER_1_COLOR = {.r = 255, .g = 50, .b = 50};
const SDL_Color PLAYER_2_COLOR = {.r = 50, .g = 100, .b = 255};
const SDL_Color TIE_COLOR = {.r = 100, .g = 100, .b = 100};

void render_grid(SDL_Renderer *renderer, const SDL_Color *color)
{

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (int i = 1; i < N; ++i)
    {
        SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}

void render_p1(SDL_Renderer *renderer, int row, int column, const SDL_Color *color)
{
    //Calculate a small square inside the orginal rectangle
    //Side is equal to half of min between h and w 
    //Then from center we are going to reach the corners

    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    thickLineRGBA(renderer,
                  center_x - half_box_side,
                  center_y - half_box_side,
                  center_x + half_box_side,
                  center_y + half_box_side,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  255);

    thickLineRGBA(renderer,
                  center_x + half_box_side,
                  center_y - half_box_side,
                  center_x - half_box_side,
                  center_y + half_box_side,
                  10,
                  color->r,
                  color->g,
                  color->b,
                  255);
}

void render_p2(SDL_Renderer *renderer, int row, int column, const SDL_Color *color)
{

    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.3;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    //Double filled circle 
    filledCircleRGBA(renderer,
                     center_x, center_y, half_box_side,
                     color->r, color->g, color->b, 255);
    filledCircleRGBA(renderer,
                     center_x, center_y, half_box_side - 8,
                     0, 0, 0, 255);
}

void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_1_color, const SDL_Color *player_2_color)
{
    //iterate all the cells and check
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            switch (board[i * N + j])
            {
            case PLAYER_1:
                render_p1(renderer, i, j, player_1_color);
                break;
            case PLAYER_2:
                render_p2(renderer, i, j, player_2_color);
                break;

            default:
            {
                // do nothing
            }
            }
        }
    }
}

void render_running_state(SDL_Renderer *renderer, const game_t *game)
{

    render_grid(renderer, &GRID_COLOR);
    render_board(renderer, game->board, &PLAYER_1_COLOR, &PLAYER_2_COLOR);
}

void render_game_over_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color)
{

    render_grid(renderer, color);
    render_board(renderer, game->board, color, color);
}

void render_game(SDL_Renderer *renderer, const game_t *game)
{

    switch (game->state)
    {
    case RUNNING_STATE:
        render_running_state(renderer, game);
        break;
    case PLAYER_1_WON_STATE:
        render_game_over_state(renderer, game, &PLAYER_1_COLOR);
        break;
    case PLAYER_2_WON_STATE:
        render_game_over_state(renderer, game, &PLAYER_2_COLOR);
        break;
    case TIE_STATE:
        render_game_over_state(renderer, game, &TIE_COLOR);
        break;
    default:
    {
        // do nothing
    }
    }
}