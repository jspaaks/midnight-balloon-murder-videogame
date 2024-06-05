#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_scancode.h"
#include "SDL_log.h"
#include "SDL_error.h"
#include "constants.h"
#include "o_bullets.h"

static ctx_t * o_bullets_update_add (ctx_t *);
static ctx_t * o_bullets_update_pos (ctx_t *);
static ctx_t * o_bullets_update_remove (ctx_t *);

static ctx_t * o_bullets_update_add (ctx_t * ctx) {

    static const float PI = 3.14159265358979323846f;
    static Uint64 timeout = 150;
    static SDL_Rect src_bullet = { .x = 188, .y = 38, .w = 5, .h = 5 };

    bool cond = ctx->nprespawn.bu > 0 &&
                SDL_GetTicks64() > ctx->tspawn_latestbullet + timeout &&
                ctx->keys[SDL_SCANCODE_SPACE];

    if (cond) {
        bullet_t * bu = malloc(1 * sizeof(bullet_t));
        if (bu == NULL) {
            SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new bullet.\n");
            exit(EXIT_FAILURE);
        }
        float a = PI * ctx->barrel.angle / 180;
        float x = ctx->barrel.pivot.x + cos(a) * (ctx->barrel.length + 20) - (src_bullet.w - 1) / 2;
        float y = ctx->barrel.pivot.y + sin(a) * (ctx->barrel.length + 20) - (src_bullet.h - 1) / 2;

        float speed = 380;
        *bu = (bullet_t) {
            .u = cos(a) * speed,
            .v = sin(a) * speed,
            .state = BU_AIRBORNE,
            .sim = {
                .x = x,
                .y = y,
                .w = src_bullet.w,
                .h = src_bullet.h,
            },
            .src = &src_bullet,
            .tgt = {
                .x = (int) x,
                .y = (int) y,
                .w = src_bullet.w,
                .h = src_bullet.h,
            },
            .next = NULL,
        };
        bu->next = ctx->bullets;
        ctx->bullets = bu;
        ctx->nprespawn.bu--;
        ctx->nairborne.bu++;
        ctx->tspawn_latestbullet = SDL_GetTicks64();
    }
    return ctx;
}

void o_bullets_draw (ctx_t * ctx) {
    bullet_t * bu = ctx->bullets;
    while (bu != NULL) {
        if (bu->state == BU_AIRBORNE) {
            SDL_RenderCopy(ctx->renderer, ctx->spritesheet, bu->src, &bu->tgt);
        }
        bu = bu->next;
    }
}

ctx_t * o_bullets_init (ctx_t * ctx) {
    assert(ctx->level != NULL && "levels needs to be initialized before bullets");
    ctx->bullets = NULL;
    ctx->nprespawn.bu = ctx->level->nprespawn.bu;
    return ctx;
}

ctx_t * o_bullets_update (ctx_t * ctx) {
    // update position
    ctx = o_bullets_update_pos(ctx);

    // if SPACE down, add a bullet to the list
    ctx = o_bullets_update_add(ctx);

    // if bullet is out of view or marked for deletion, delete it from the list
    ctx = o_bullets_update_remove(ctx);
    return ctx;
}

static ctx_t * o_bullets_update_pos (ctx_t * ctx) {
    const float gravity = 70; // pixels per second per second
    bullet_t * bu = ctx->bullets;
    while (bu != NULL) {
        bu->v += gravity * ctx->dt.frame;
        bu->sim.x += bu->u * ctx->dt.frame;
        bu->sim.y += bu->v * ctx->dt.frame;
        bu->tgt.x = (int) bu->sim.x;
        bu->tgt.y = (int) bu->sim.y;
        bu = bu->next;
    }
    return ctx;
}

static ctx_t * o_bullets_update_remove (ctx_t * ctx) {
    bullet_t * this = ctx->bullets;
    bullet_t * prev = NULL;
    bool isfirst = false;
    bool doremove = false;
    while (this != NULL) {
        isfirst = prev == NULL;
        doremove = this->state == BU_HIT         ||
                   this->tgt.y < 0 - this->tgt.h ||
                   this->tgt.x > SCREEN_WIDTH    ||
                   this->tgt.x < 0 - this->tgt.w ||
                   this->tgt.y > SCREEN_HEIGHT - GROUND_HEIGHT;
        switch (isfirst << 1 | doremove ) {
            case 0: {
                // not first, not remove
                prev = this;
                this = this->next;
                break;
            }
            case 1: {
                // not first, remove
                bullet_t * tmp = this;
                prev->next = this->next;
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
                bullet_t * tmp = this;
                this = this->next;
                ctx->bullets = this;
                free(tmp);
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED, "Something went wrong in removing a bullet from the list.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return ctx;
}
