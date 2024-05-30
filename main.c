#include "constants.h"
#include "context.h"
#include "fsm.h"
#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <SDL_render.h>
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
    ctx->spritesheet = NULL;
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
    ctx->spritesheet = SDL_CreateTextureFromSurface(ctx->renderer, image);
    return true;
}

int main (void) {
    ctx_t ctx = {
        .window = NULL,
        .renderer = NULL,
        .spritesheet = NULL,
        .keys = SDL_GetKeyboardState(NULL)
    };
    struct state * state = fsm_set_state (PLAYING);
    struct state * frame = state;

    bool success = init(&ctx);
    if (!success) {
        exit(EXIT_FAILURE);
    }

    while (true) {
        frame = state;  // so .update() and .draw() are of the same state
        frame->update(&ctx, &state);
        frame->draw(&ctx);
    }

    deinit(&ctx);
    return EXIT_SUCCESS;
}
