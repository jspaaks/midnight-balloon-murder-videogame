#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "types.h"
#include "o_balloons.h"
#include "o_bullets.h"
#include "o_collisions.h"

static bool o_collisions_colliding(balloon_t *, bullet_t *);

static bool o_collisions_colliding(balloon_t * ba, bullet_t * bu) {
    float ba_l = ba->sim.x;
    float ba_r = ba->sim.x + ba->sim.w;
    float ba_t = ba->sim.y;
    float ba_b = ba->sim.y + ba->sim.h;

    float bu_l = bu->sim.x;
    float bu_r = bu->sim.x + bu->sim.w;
    float bu_t = bu->sim.y;
    float bu_b = bu->sim.y + bu->sim.h;

    bool separated = ba_t > bu_b ||
                     ba_r < bu_l ||
                     ba_b < bu_t ||
                     ba_l > bu_r;

    return !separated;
}

void o_collisions_draw (ctx_t * ctx) {
    collision_t * c = ctx->collisions;
    SDL_SetRenderDrawColor(ctx->renderer, 166, 166, 166, 0);
    while (c != NULL) {
        c = c->next;
    }
}

ctx_t * o_collisions_init (ctx_t * ctx) {
    // TODO free collisions from previous levels
    ctx->collisions = NULL;
    return ctx;
}

ctx_t * o_collisions_update (ctx_t * ctx) {
    balloon_t * ba = ctx->balloons;
    while (ba != NULL) {
        bullet_t * bu = ctx->bullets;
        while (bu != NULL) {
            if (o_collisions_colliding(ba, bu)) {

                // increase nbullets
                ctx->nprespawn.bu += ba->value;
                ctx->nhit++;
                ctx->nairborne.ba--;
                ctx->nairborne.bu--;

                // mark bullet and balloon for deletion
                ba->delete = true;
                bu->delete = true;

                // spawn collision effect
                // TODO
            }
            bu = bu->next;
        }
        ba = ba->next;
    }
    return ctx;
}
