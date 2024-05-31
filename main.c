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
#include <SDL_timer.h>
#include "o_balloons.h"
#include "o_bullets.h"
#include "levels.h"
#include <time.h>

static void deinit (ctx_t *);
static bool init (ctx_t *);

static void deinit (ctx_t * ctx) {
    SDL_DestroyRenderer(ctx->renderer);
    ctx->renderer = NULL;

    SDL_DestroyWindow(ctx->window);
    ctx->window = NULL;

    SDL_DestroyTexture(ctx->spritesheet);
    ctx->spritesheet = NULL;

    o_balloons_free(ctx->balloons);
    ctx->balloons = NULL;

    ctx->levels = NULL;
    ctx->level = NULL;
    ctx->keys = NULL;

    SDL_Quit();
}

static bool init (ctx_t * ctx) {
    // initialize the random number generator
    srand(time(NULL));

    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    ctx->window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_BORDERLESS);
    if (ctx->window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return false;
    }
    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
    SDL_Surface * image = SDL_LoadBMP("img/sprites.bmp");
    if (image == NULL) {
        fprintf(stdout, "Something went wrong loading spritesheet.\n");
        return false;
    }
    ctx->spritesheet = SDL_CreateTextureFromSurface(ctx->renderer, image);
    ctx->keys = SDL_GetKeyboardState(NULL);
    ctx->dt = 0.0000000000001;
    ctx = levels_init(ctx);
    ctx = o_balloons_init(ctx);
    ctx = o_bullets_init(ctx);
    return true;
}

int main (void) {
    ctx_t ctx;
    if (!init(&ctx)) {
        exit(EXIT_FAILURE);
    }

    struct state * state = fsm_set_state (PLAYING);
    struct state * frame = state;
    Uint64 tstart;

    while (ctx.nprespawn + ctx.nairborne > 0) {
        tstart = SDL_GetTicks64();
        frame = state;  // so .update() and .draw() are of the same state
        frame->update(&ctx, &state);
        frame->draw(&ctx);
        ctx.dt = ((double) (SDL_GetTicks64() - tstart)) / 1000;
    }

    deinit(&ctx);
    return EXIT_SUCCESS;
}
