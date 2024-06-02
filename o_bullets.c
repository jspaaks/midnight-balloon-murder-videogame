#include "o_bullets.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdlib.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include "constants.h"
#include "levels.h"
#include <math.h>
#include <SDL_scancode.h>

static ctx_t * o_bullets_update_add (ctx_t *);
static bullet_t * o_bullets_malloc (void);
static ctx_t * o_bullets_update_pos (ctx_t *);
static ctx_t * o_bullets_update_remove (ctx_t *);

static SDL_Rect src_bullet = { .x = 188, .y = 38, .w = 5, .h = 5 };
static Uint64 timeout = 150;

static ctx_t * o_bullets_update_add (ctx_t * ctx) {
    bool cond = ctx->nbullets > 0 &&
                SDL_GetTicks64() > ctx->tspawn_latestbullet + timeout &&
                ctx->keys[SDL_SCANCODE_SPACE];
    if (cond) {
        bullet_t * bu = malloc(1 * sizeof(bullet_t));
        if (bu == NULL) {
            fprintf(stderr, "Something went wrong allocating memory for new bullet.\n");
            exit(EXIT_FAILURE);
        }
        float a = M_PI * ctx->barrel.angle / 180;
        float x = ctx->barrel.pivot.x + cos(a) * (ctx->barrel.length + 20) - (src_bullet.w - 1) / 2;
        float y = ctx->barrel.pivot.y + sin(a) * (ctx->barrel.length + 20) - (src_bullet.h - 1) / 2;

        float speed = 90;
        *bu = (bullet_t) {
            .u = cos(a) * speed,
            .v = sin(a) * speed,
            .tspawned = SDL_GetTicks64(),
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
        ctx->nbullets--;
        ctx->tspawn_latestbullet = SDL_GetTicks64();
    }
    return ctx;
}

void o_bullets_draw (ctx_t * ctx) {
    bullet_t * bu = ctx->bullets;
    while (bu != NULL) {
        SDL_RenderCopy(ctx->renderer, ctx->spritesheet, bu->src, &bu->tgt);
        bu = bu->next;
    }
}

ctx_t * o_bullets_init (ctx_t * ctx) {
    ctx->bullets = o_bullets_malloc();
    ctx->nbullets = ctx->level->nbullets;
    return ctx;
}

static bullet_t * o_bullets_malloc (void) {
    bullet_t * bullets = NULL;
    return bullets;
}

ctx_t * o_bullets_update (ctx_t * ctx) {
    // update position
    ctx = o_bullets_update_pos(ctx);

    // if SPACE down, add a bullet to the list
    ctx = o_bullets_update_add(ctx);

    // if bullet is out of view, delete it from the list
    ctx = o_bullets_update_remove(ctx);
    return ctx;
}

static ctx_t * o_bullets_update_pos (ctx_t * ctx) {
    bullet_t * bu = ctx->bullets;
    while (bu != NULL) {
        bu->sim.x += bu->u * ctx->dt;
        bu->sim.y += bu->v * ctx->dt;
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
        doremove = this->tgt.y < 0 - this->tgt.h ||
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
                fprintf(stderr, "Something went wrong in removing a bullet from the list.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return ctx;
}
