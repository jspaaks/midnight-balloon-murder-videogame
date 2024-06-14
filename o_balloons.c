#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SDL_timer.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_error.h"
#include "types.h"
#include "levels.h"
#include "o_balloons.h"
#include "o_scene.h"

static float o_balloons_unitrand(void);
static void o_balloons_update_pos (ctx_t *);
static void o_balloons_update_spawn (ctx_t *);
static void o_balloons_update_spawn_orange (ctx_t *);
static void o_balloons_update_spawn_red (ctx_t *);
static void o_balloons_update_spawn_yellow (ctx_t *);
static void o_balloons_update_test_exited (ctx_t *);

void o_balloons_deinit (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    while (b != NULL) {
        balloon_t * tmp = b;
        b = b->next;
        free(tmp);
    }
    ctx->balloons = NULL;
}

void o_balloons_draw (ctx_t * ctx, SDL_Renderer * renderer) {
    balloon_t * b = ctx->balloons;
    while (b != NULL) {
        SDL_Rect tgt = sim2tgt(ctx->scene, b->sim);
        SDL_RenderCopy(renderer, ctx->spritesheet, &b->src, &tgt);
        b = b->next;
    }
}

void o_balloons_init (ctx_t * ctx) {
    assert(ctx->level != NULL && "levels needs to be initialized before balloons");
    ctx->balloons = NULL;
    ctx->nballoons.airborne = 0;
    ctx->nballoons.hit = 0;
    ctx->nballoons.miss = 0;
    ctx->nballoons.orange = ctx->level->nballoons.orange;
    ctx->nballoons.prespawn = ctx->level->nballoons.prespawn;
    ctx->nballoons.red = ctx->level->nballoons.red;
    ctx->nballoons.yellow = ctx->level->nballoons.yellow;
}

static float o_balloons_unitrand(void) {
    return (float)(rand()) / (float)(RAND_MAX);
}

void o_balloons_update (ctx_t * ctx) {
    o_balloons_update_test_exited(ctx);
    o_balloons_update_remove(ctx);
    o_balloons_update_pos(ctx);
    o_balloons_update_spawn(ctx);
}

static void o_balloons_update_spawn (ctx_t * ctx) {
    static const float spawn_rate = 0.35; // balloons per second
    float spawn_chance = ctx->nballoons.airborne == 0 ? 1 : spawn_rate * ctx->dt.frame;
    if (ctx->nballoons.prespawn <= 0 || o_balloons_unitrand() > spawn_chance) {
        return;
    }
    unsigned int remaining = ctx->nballoons.yellow + ctx->nballoons.orange + ctx->nballoons.red;
    float y = (float)(ctx->nballoons.yellow) / remaining;
    float o = (float)(ctx->nballoons.orange) / remaining;
    float u = o_balloons_unitrand();
    if (u < y) {
        o_balloons_update_spawn_yellow(ctx);
        ctx->nballoons.yellow--;
    } else if (u < (y + o)) {
        o_balloons_update_spawn_orange(ctx);
        ctx->nballoons.orange--;
    } else {
        o_balloons_update_spawn_red(ctx);
        ctx->nballoons.red--;
    }
    ctx->nballoons.airborne++;
    ctx->nballoons.prespawn--;
}

static void o_balloons_update_spawn_orange (ctx_t * ctx) {
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new orange balloon.\n");
        exit(EXIT_FAILURE);
    }
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
    ctx->balloons = b;
}

static void o_balloons_update_spawn_red (ctx_t * ctx) {
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new red balloon.\n");
        exit(EXIT_FAILURE);
    }
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
    ctx->balloons = b;
}

static void o_balloons_update_spawn_yellow (ctx_t * ctx) {
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new yellow balloon.\n");
        exit(EXIT_FAILURE);
    }
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
    ctx->balloons = b;
}

static void o_balloons_update_pos (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    while (b != NULL) {
        b->sim.x += b->sim2.u * ctx->dt.frame;
        b->sim.y += b->sim2.v * ctx->dt.frame;
        b = b->next;
    }
}

void o_balloons_update_remove (ctx_t * ctx) {
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
}

static void o_balloons_update_test_exited (ctx_t * ctx) {
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
}
