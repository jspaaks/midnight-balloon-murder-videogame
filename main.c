#include "constants.h"
#include "types.h"
#include "fsm.h"
#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void deinit (ctx_t *);
bool init (ctx_t *);

void deinit (ctx_t * ctx) {
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
    ctx->window = NULL;
    ctx->renderer = NULL;
    ctx->sprites = NULL;
}

bool init (ctx_t * ctx) {
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    ctx->window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_RESIZABLE);
    if (ctx->window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return false;
    }

    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);

    SDL_Surface * image = SDL_LoadBMP("img/sprites.bmp");
    if (image == NULL) {
        fprintf(stdout, "Something went wrong loading spritesheet.\n");
    }
    ctx->sprites = SDL_CreateTextureFromSurface(ctx->renderer, image);
    return true;
}

int main (void) {
    ctx_t ctx = {
        .window = NULL,
        .renderer = NULL,
        .sprites = NULL,
    };
    struct state * game = fsm_set_state (PLAYING);
    SDL_Event event;

    bool success = init(&ctx);
    if (!success) {
        exit(EXIT_FAILURE);
    }

    Uint64 timeout = SDL_GetTicks64() + 10000;
    while (SDL_GetTicks64() < timeout) {
        while (SDL_WaitEvent(&event) != 0) {
            game->update(&game, &event);
            game->draw(&ctx);
        }
    }

    deinit(&ctx);
    return EXIT_SUCCESS;
}
