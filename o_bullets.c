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
#include "o_bullets.h"
#include "o_scene.h"

static ctx_t * o_bullets_update_pos (ctx_t *);
static ctx_t * o_bullets_update_remove (ctx_t *);
static ctx_t * o_bullets_update_spawn (ctx_t *);
static ctx_t * o_bullets_update_test_exited (ctx_t *);

ctx_t * o_bullets_deinit (ctx_t * ctx) {
    bullet_t * b = ctx->bullets;
    while (b != NULL) {
        bullet_t * tmp = b;
        b = b->next;
        free(tmp);
    }
    ctx->bullets = NULL;
    return ctx;
}

void o_bullets_draw (ctx_t * ctx) {
    bullet_t * bu = ctx->bullets;
    while (bu != NULL) {
        SDL_Rect tgt = sim2tgt(ctx->scene, bu->sim);
        SDL_RenderCopy(ctx->renderer, ctx->spritesheet, bu->src, &tgt);
        bu = bu->next;
    }
}

ctx_t * o_bullets_init (ctx_t * ctx) {
    assert(ctx->level != NULL && "levels needs to be initialized before bullets");
    assert(ctx->ground.sim.w != 0 && "ground needs to be initialized before bullets");
    ctx->bullets = NULL;
    ctx->nbullets.prespawn = ctx->level->nbullets.prespawn;
    ctx->nbullets.airborne = 0;
    return ctx;
}

ctx_t * o_bullets_update (ctx_t * ctx) {
    // mark bullets that are out of frame
    ctx = o_bullets_update_test_exited(ctx);

    // if bullet is marked for deletion, delete it from the list
    ctx = o_bullets_update_remove(ctx);

    // update position
    ctx = o_bullets_update_pos(ctx);

    // if SPACE down, add a bullet to the list
    ctx = o_bullets_update_spawn(ctx);
    return ctx;
}

static ctx_t * o_bullets_update_spawn (ctx_t * ctx) {
    static const float PI = 3.14159265358979323846f;
    static Uint64 timeout = 150;
    static SDL_Rect src_bullet = { .x = 188, .y = 38, .w = 5, .h = 5 };

    bool cond = ctx->nbullets.prespawn > 0 &&
                SDL_GetTicks64() > ctx->tspawn_latestbullet + timeout &&
                ctx->keys[SDL_SCANCODE_SPACE];

    if (cond) {
        bullet_t * b = malloc(1 * sizeof(bullet_t));
        if (b == NULL) {
            SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new bullet.\n");
            exit(EXIT_FAILURE);
        }
        float a = PI * ctx->barrel.sim2.angle / 180;
        float x = ctx->barrel.sim2.pivot.x + cos(a) * (ctx->barrel.sim2.length + 20) - (src_bullet.w - 1) / 2;
        float y = ctx->barrel.sim2.pivot.y + sin(a) * (ctx->barrel.sim2.length + 20) - (src_bullet.h - 1) / 2;

        float speed = 380;
        *b = (bullet_t) {
            .next = ctx->bullets,
            .sim = {
                .x = x,
                .y = y,
                .w = 5,
                .h = 5,
            },
            .sim2 = {
                .u = cos(a) * speed,
                .v = sin(a) * speed,
            },
            .src = &src_bullet,
            .state = ALIVE,
        };
        ctx->bullets = b;
        ctx->nbullets.prespawn--;
        ctx->nbullets.airborne++;
        ctx->tspawn_latestbullet = SDL_GetTicks64();
    }
    return ctx;
}

static ctx_t * o_bullets_update_pos (ctx_t * ctx) {
    const float gravity = 70; // pixels per second per second
    bullet_t * b = ctx->bullets;
    while (b != NULL) {
        b->sim2.v += gravity * ctx->dt.frame;
        b->sim.x += b->sim2.u * ctx->dt.frame;
        b->sim.y += b->sim2.v * ctx->dt.frame;
        b = b->next;
    }
    return ctx;
}

ctx_t * o_bullets_update_remove (ctx_t * ctx) {
    bullet_t * this = ctx->bullets;
    bullet_t * prev = NULL;
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
                bullet_t * tmp = this;
                prev->next = this->next;
                if (this->state == HIT || this->state == EXITED) {
                    ctx->nbullets.airborne--;
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
                bullet_t * tmp = this;
                if (this->state == HIT || this->state == EXITED) {
                    ctx->nbullets.airborne--;
                }
                ctx->bullets = this->next;
                this = this->next;
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

static ctx_t * o_bullets_update_test_exited (ctx_t * ctx) {
    bullet_t * this = ctx->bullets;
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
