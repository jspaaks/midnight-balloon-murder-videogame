#include "shared.h"
#include "playing.h"
#include "types.h"
#include "constants.h"
#include "fsm.h"
#include <SDL_render.h>
#include <SDL_rect.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_events.h>
#include <stdio.h>
#include <stdlib.h>

static void playing_draw_ground (ctx_t *);
static void playing_draw_moon (ctx_t *);
static void playing_draw_turret (ctx_t *);
static void playing_draw_barrel (ctx_t *);


static const int ground_height = 100;
static const int turret_height = 60;
static const int turret_width = 70;
static const int barrel_width = 45;
static const int barrel_height = 12;

void playing_draw (ctx_t * ctx) {
    shared_draw_background(ctx);
    playing_draw_ground(ctx);
    playing_draw_moon(ctx);
    playing_draw_turret(ctx);
    playing_draw_barrel(ctx);

    SDL_RenderPresent(ctx->renderer);
}

void playing_update (struct state ** game, SDL_Event * event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            fprintf(stdout, "Pausing.\n");
            *game = fsm_set_state(PAUSED);
        }
    }
}

static void playing_draw_ground (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 11, 1, 26, 0);
    static const SDL_Rect rect = {
        .x = 0,
        .y = SCREEN_HEIGHT - ground_height,
        .w = SCREEN_WIDTH,
        .h = ground_height,
    };
    SDL_RenderFillRect(ctx->renderer, &rect);
}

static void playing_draw_moon (ctx_t * ctx) {
    static const SDL_Rect src = {
        .x = 75,
        .y = 1,
        .w = 90,
        .h = 90,
    };
    static const SDL_Rect tgt = {
        .x = SCREEN_WIDTH - 90 - 40,
        .y = 40,
        .w = 90,
        .h = 90,
    };
    SDL_RenderCopy(ctx->renderer, ctx->sprites, &src, &tgt);
}

static void playing_draw_turret (ctx_t * ctx) {
    static const SDL_Rect src = {
        .x = 4,
        .y = 1,
        .w = turret_width,
        .h = turret_height,
    };
    static const SDL_Rect tgt = {
        .x = 180,
        .y = SCREEN_HEIGHT - ground_height - turret_height,
        .w = turret_width,
        .h = turret_height,
    };
    SDL_RenderCopy(ctx->renderer, ctx->sprites, &src, &tgt);
}

static void playing_draw_barrel (ctx_t * ctx) {
    static const SDL_Rect src = {
        .x = 4,
        .y = 68,
        .w = barrel_width,
        .h = barrel_height,
    };
    static const SDL_Rect tgt = {
        .x = 180 + turret_width - 20,
        .y = SCREEN_HEIGHT - ground_height - turret_height + turret_width / 2 - barrel_height / 2,
        .w = barrel_width,
        .h = barrel_height,
    };
    double angle = -65;
    static const SDL_Point center = {
        .x = turret_width / -2 + 20,
        .y = barrel_height / 2,
    };
    SDL_RenderCopyEx(ctx->renderer, ctx->sprites, &src, &tgt, angle, &center, SDL_FLIP_NONE);
}
