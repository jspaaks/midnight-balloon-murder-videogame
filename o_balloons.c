#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SDL_timer.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_error.h"
#include "types.h"
#include "constants.h"
#include "levels.h"
#include "o_balloons.h"
#include "o_scene.h"

static float o_balloons_unitrand(void);
static ctx_t * o_balloons_update_pos (ctx_t *);
static ctx_t * o_balloons_update_spawn (ctx_t *);
static void o_balloons_update_spawn_orange (ctx_t * ctx, balloon_t *);
static void o_balloons_update_spawn_red (ctx_t * ctx, balloon_t *);
static void o_balloons_update_spawn_yellow (ctx_t * ctx, balloon_t *);
static ctx_t * o_balloons_update_test_exited (ctx_t *);

ctx_t * o_balloons_deinit (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    while (b != NULL) {
        balloon_t * tmp = b;
        b = b->next;
        free(tmp);
    }
    ctx->balloons = NULL;
    return ctx;
}

void o_balloons_draw (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    while (b != NULL) {
        SDL_Rect tgt = sim2tgt(ctx->scene, b->sim);
        SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &b->src, &tgt);
        b = b->next;
    }
}

ctx_t * o_balloons_init (ctx_t * ctx) {
    assert(ctx->level != NULL && "levels needs to be initialized before balloons");
    // TODO free balloons from previous levels
    ctx->balloons = NULL;
    ctx->nballoons.prespawn = ctx->level->nballoons.prespawn;
    ctx->nballoons.airborne = 0;
    ctx->nballoons.hit = 0;
    ctx->nballoons.miss = 0;
    return ctx;
}

static float o_balloons_unitrand(void) {
    return (float)(rand()) / (float)(RAND_MAX);
}

ctx_t * o_balloons_update (ctx_t * ctx) {
    ctx = o_balloons_update_test_exited(ctx);
    ctx = o_balloons_update_remove(ctx);
    ctx = o_balloons_update_pos(ctx);
    ctx = o_balloons_update_spawn(ctx);
    return ctx;
}

static ctx_t * o_balloons_update_spawn (ctx_t * ctx) {
    static const float spawn_rate = 0.35; // balloons per second
    float spawn_chance = ctx->nballoons.airborne == 0 ? 1 : spawn_rate * ctx->dt.frame;
    if (ctx->nballoons.prespawn <= 0 || o_balloons_unitrand() > spawn_chance) {
        return ctx;
    }
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new balloon.\n");
        exit(EXIT_FAILURE);
    }
    switch (rand() % 3) {
        case 0: {
            o_balloons_update_spawn_yellow(ctx, b);
            break;
        }
        case 1: {
            o_balloons_update_spawn_orange(ctx, b);
            break;
        }
        case 2: {
            o_balloons_update_spawn_red(ctx, b);
            break;
        }
        default: {
            SDL_Log("uh oh");
            break;
        }
    }
    ctx->balloons = b;
    ctx->nballoons.airborne++;
    ctx->nballoons.prespawn--;
    return ctx;
}

static void o_balloons_update_spawn_orange (ctx_t * ctx, balloon_t * b) {
    *b = (balloon_t){
        .next = ctx->balloons,
        .sim = (SDL_FRect){
            .h = 12,
            .w = 9,
            .x = ctx->scene.sim.w / 2 + o_balloons_unitrand() * (0.4 * ctx->scene.sim.w),
            .y = ctx->scene.sim.h - ctx->ground.sim.h,
        },
        .sim2 = {
            .u = 0.0,
            .v = -30.0,
        },
        .src = (SDL_Rect){
            .h = 12,
            .w = 9,
            .x = 184,
            .y = 1,
        },
        .state = ALIVE,
        .value = 4,
    };
}

static void o_balloons_update_spawn_red (ctx_t * ctx, balloon_t * b) {
    *b = (balloon_t){
        .next = ctx->balloons,
        .sim = (SDL_FRect){
            .h = 7,
            .w = 6,
            .x = ctx->scene.sim.w / 2 + o_balloons_unitrand() * (0.4 * ctx->scene.sim.w),
            .y = ctx->scene.sim.h - ctx->ground.sim.h,
        },
        .sim2 = {
            .u = 0.0,
            .v = -30.0,
        },
        .src = (SDL_Rect){
            .h = 7,
            .w = 6,
            .x = 184,
            .y = 20,
        },
        .state = ALIVE,
        .value = 3,
    };
}

static void o_balloons_update_spawn_yellow (ctx_t * ctx, balloon_t * b) {
    *b = (balloon_t){
        .next = ctx->balloons,
        .sim = (SDL_FRect){
            .h = 16,
            .w = 12,
            .x = ctx->scene.sim.w / 2 + o_balloons_unitrand() * (0.4 * ctx->scene.sim.w),
            .y = ctx->scene.sim.h - ctx->ground.sim.h,
        },
        .sim2 = {
            .u = 0.0,
            .v = -30.0,
        },
        .src = (SDL_Rect){
            .h = 16,
            .w = 12,
            .x = 166,
            .y = 1,
        },
        .state = ALIVE,
        .value = 5,
    };
}

static ctx_t * o_balloons_update_pos (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    while (b != NULL) {
        b->sim.x += b->sim2.u * ctx->dt.frame;
        b->sim.y += b->sim2.v * ctx->dt.frame;
        b = b->next;
    }
    return ctx;
}

ctx_t * o_balloons_update_remove (ctx_t * ctx) {
    balloon_t * this = ctx->balloons;
    balloon_t * prev = NULL;
    bool isfirst = false;
    bool doremove = false;
    while (this != NULL) {
        isfirst = prev == NULL;
        doremove = this->state != ALIVE;
        switch (isfirst << 1 | doremove ) {
            case 0: {
                // not first, not remove
                prev = this;
                this = this->next;
                break;
            }
            case 1: {
                // not first, remove
                balloon_t * tmp = this;
                prev->next = this->next;
                if (this->state == EXITED) {
                    ctx->nballoons.miss++;
                    ctx->nballoons.airborne--;
                }
                if (this->state == HIT) {
                    ctx->nballoons.hit++;
                    ctx->nballoons.airborne--;
                }
                this = this->next;
                free(tmp);
                break;
            }
            case 2: {
                // first, not remove
                prev = this;
                this = this->next;
                break;
            }
            case 3: {
                // first, remove
                balloon_t * tmp = this;
                ctx->balloons = this->next;
                if (this->state == EXITED) {
                    ctx->nballoons.miss++;
                    ctx->nballoons.airborne--;
                }
                if (this->state == HIT) {
                    ctx->nballoons.hit++;
                    ctx->nballoons.airborne--;
                }
                this = this->next;
                free(tmp);
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED, "Something went wrong in removing a balloon from the list.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return ctx;
}

static ctx_t * o_balloons_update_test_exited (ctx_t * ctx) {
    balloon_t * this = ctx->balloons;
    bool exited;
    while (this != NULL) {
        exited = this->sim.y < 0 - this->sim.h  ||
                 this->sim.x > ctx->scene.sim.w ||
                 this->sim.x < 0 - this->sim.w  ||
                 this->sim.y > ctx->scene.sim.h - ctx->ground.sim.h;
        if (exited) {
            this->state = EXITED;
        }
        this = this->next;
    }
    return ctx;
}
