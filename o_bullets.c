#include "o_bullets.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdlib.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include "constants.h"
#include "levels.h"

static ctx_t * o_bullets_update_add (ctx_t *);
static bullet_t * o_bullets_malloc (void);
static ctx_t * o_bullets_update_pos (ctx_t *);
static ctx_t * o_bullets_update_remove (ctx_t *);

static SDL_Rect src_bullet = { .x = 100, .y =100, .w = 10, .h = 10 };

static ctx_t * o_bullets_update_add (ctx_t * ctx) {
    if (ctx->nbullets > 0) {
        bullet_t * bu = malloc(1 * sizeof(bullet_t));
        if (bu == NULL) {
            fprintf(stderr, "Something went wrong allocating memory for new bullet.\n");
            exit(EXIT_FAILURE);
        }
        *bu = (bullet_t) {
            .x = 100,
            .y = 400,
            .u = 30,
            .v = -10,
            .w = 10,
            .h = 10,
            .spawned = SDL_GetTicks64(),
            .src = &src_bullet,
            .tgt = {
                .x = 100,
                .y = 400,
                .w = 10,
                .h = 10,
            },
            .next = NULL,
        };
        bu->next = ctx->bullets;
        ctx->bullets = bu;
        ctx->nbullets--;
    }
    return ctx;
}

void o_bullets_draw (ctx_t * ctx) {
    bullet_t * bu = ctx->bullets;
    SDL_SetRenderDrawColor(ctx->renderer, 0, 255, 255, 0);
    while (bu != NULL) {
        SDL_RenderFillRect(ctx->renderer, &bu->tgt);
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
        bu->x += bu->u * ctx->dt;
        bu->y += bu->v * ctx->dt;
        bu->tgt.x = (int) bu->x;
        bu->tgt.y = (int) bu->y;
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
        doremove = false;
        if (this->y < 0 - this->tgt.h || this->x > SCREEN_WIDTH ||
            this->x < 0 - this->tgt.w || this->y > SCREEN_HEIGHT - GROUND_HEIGHT) {
            doremove = true;
        }
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
