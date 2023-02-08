#include "game.h"
#include "logic.h"

void switch_player(game_t *game)
{
    if (game->player == PLAYER_1)
    {
        game->player = PLAYER_2;
    }
    else if (game->player == PLAYER_2)
    {
        game->player = PLAYER_1;
    }
}

int check_player_won(game_t *game, int player)
{
    int row_count = 0;
    int column_count = 0;
    int diagon1_count = 0;
    int diagon2_count = 0;

    //iterate col, rows and diag for checking if the line have the same player
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (game->board[i * N + j] == player)
            {
                row_count++;
            }
            if (game->board[j * N + i] == player)
            {
                column_count++;
            }
        }
        if (row_count >= N || column_count >= N)
        {
            return 1;
        }
        row_count = 0;
        column_count = 0;

        if (game->board[i * N + i] == player)
        {
            diagon1_count++;
        }
        if (game->board[i * N + N - i - 1] == player)
        {
            diagon2_count++;
        }
    }

    return diagon1_count >= N || diagon2_count >= N;
}

int count_cells(const int *board, int cell)
{
    int count = 0;

    for (int i = 0; i < N * N; ++i)
    {
        if (board[i] == cell)
        {
            count++;
        }
    }

    return count;
}

void game_over_condition(game_t *game)
{
    if (check_player_won(game, PLAYER_1))
    {
        game->state = PLAYER_1_WON_STATE;
    }
    else if (check_player_won(game, PLAYER_2))
    {
        game->state = PLAYER_2_WON_STATE;
    }
    else if (count_cells(game->board, EMPTY) == 0)
    {
        game->state = TIE_STATE;
    }
}

void player_turn(game_t *game, int row, int column)
{
    if (game->board[row * N + column] == EMPTY)
    {
        game->board[row * N + column] = game->player;
        switch_player(game);
        game_over_condition(game);
    }
}

void reset_game(game_t *game)
{
    game->player = PLAYER_1;
    game->state = RUNNING_STATE;
    for (int i = 0; i < N * N; ++i)
    {
        game->board[i] = EMPTY;
    }
}

void click_on_cell(game_t *game, int row, int column)
{
    if (game->state == RUNNING_STATE)
    {
        player_turn(game, row, column);
    }
    else
    {
        reset_game(game);
    }
}