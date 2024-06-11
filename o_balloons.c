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
static ctx_t * o_balloons_update_add (ctx_t *);
static ctx_t * o_balloons_update_pos (ctx_t *);

ctx_t * o_balloons_deinit (ctx_t * ctx) {
    free(ctx->balloons);
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
    ctx->nprespawn.ba = ctx->level->nprespawn.ba;
    ctx->nairborne.ba = 0;
    ctx->nhit = 0;
    ctx->nmiss = 0;
    return ctx;
}

ctx_t * o_balloons_update (ctx_t * ctx) {
    ctx = o_balloons_update_pos(ctx);
    ctx = o_balloons_update_add(ctx);
    ctx = o_balloons_update_remove(ctx);
    return ctx;
}

static ctx_t * o_balloons_update_add (ctx_t * ctx) {
    static const float spawn_rate = 0.35; // balloons per second
    float spawn_chance = ctx->nairborne.ba == 0 ? 1 : spawn_rate * ctx->dt.frame;
    if (ctx->nprespawn.ba <= 0 || o_balloons_unitrand() > spawn_chance) {
        return ctx;
    }
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new balloon.\n");
        exit(EXIT_FAILURE);
    }
    *b = (balloon_t){
        .delete = false,
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
        .value = 3,
    };
    ctx->balloons = b;
    ctx->nairborne.ba++;
    ctx->nprespawn.ba--;
    return ctx;
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
        doremove = this->delete ||
                   this->sim.y < 0 - this->sim.h  ||
                   this->sim.x > ctx->scene.sim.w ||
                   this->sim.x < 0 - this->sim.w  ||
                   this->sim.y > ctx->scene.sim.h - ctx->ground.sim.h;
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
                ctx->nairborne.ba -= this->delete ? 0 : 1;
                ctx->nmiss += this->delete ? 0 : 1;
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
                ctx->nairborne.ba -= this->delete ? 0 : 1;
                ctx->nmiss += this->delete ? 0 : 1;
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

static float o_balloons_unitrand(void) {
    return (float)(rand()) / (float)(RAND_MAX);
}
