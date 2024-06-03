#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "SDL.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_log.h"

#include "SDL_ttf.h"

#include "constants.h"
#include "types.h"
#include "fsm.h"
#include "levels.h"
#include "colors.h"

#include "o_balloons.h"
#include "o_bullets.h"
#include "o_turret.h"
#include "o_barrel.h"
#include "o_flash.h"
#include "o_collisions.h"

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

    TTF_Quit();
    SDL_Quit();
}

static bool init (ctx_t * ctx) {
    // initialize the random number generator
    srand(time(NULL));

    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() != 0) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        return false;
    }

    ctx->window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_BORDERLESS);
    if (ctx->window == NULL) {
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        return false;
    }
    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
    SDL_Surface * image = SDL_LoadBMP("img/sprites.bmp");
    if (image == NULL) {
        SDL_Log("Something went wrong loading spritesheet.\n");
        return false;
    }
    ctx->spritesheet = SDL_CreateTextureFromSurface(ctx->renderer, image);
    ctx->keys = SDL_GetKeyboardState(NULL);
    ctx->dt = 0.0000000000001;
    ctx = colors_init(ctx);
    ctx = levels_init(ctx);
    ctx = o_turret_init(ctx);
    ctx = o_barrel_init(ctx);
    ctx = o_flash_init(ctx);
    ctx = o_balloons_init(ctx);
    ctx = o_bullets_init(ctx);
    ctx = o_collisions_init(ctx);

    int ptsize = 20;
    char fontfile[] = "fonts/Bayon-Regular.ttf";
    TTF_Font * font = TTF_OpenFont(fontfile, ptsize);
    if (font == NULL) {
        SDL_Log("Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, SDL_GetError());
        return false;
    }
    SDL_Surface * text = TTF_RenderText_Shaded(font, "midnight balloon murder", ctx->colors.white, ctx->colors.bg);
    SDL_Texture * message = SDL_CreateTextureFromSurface(ctx->renderer, text);
    SDL_RenderCopy(ctx->renderer, message, NULL, NULL);
    SDL_RenderPresent(ctx->renderer);
    SDL_Delay(3000);

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

    bool have_balloons = true;
    bool have_bullets = true;

    while (have_balloons && have_bullets) {
        tstart = SDL_GetTicks64();
        frame = state;  // so .update() and .draw() are of the same state
        frame->update(&ctx, &state);
        frame->draw(&ctx);
        ctx.dt = ((float) (SDL_GetTicks64() - tstart)) / 1000;
        have_balloons = ctx.nprespawn + ctx.nairborne > 0;
        have_bullets = ctx.nbullets > 0; // TODO take airborne bullets into account
    }
    if (!have_balloons) {
        SDL_Log("No more balloons.\n");
    }
    if (!have_bullets) {
        SDL_Log("No more bullets.\n");
    }

    deinit(&ctx);
    return EXIT_SUCCESS;
}
