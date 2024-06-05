#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "types.h"
#include "o_collisions.h"

static bool o_collisions_colliding(balloon_t *, bullet_t *);
static ctx_t * o_collisions_add (ctx_t *, int, int);

static ctx_t * o_collisions_add (ctx_t * ctx, int x, int y) {
    //collision_t * c = malloc(1 * sizeof(collision_t));
    //if (c == NULL) {
    //    SDL_LogError(SDL_ENOMEM, "Error allocating memory for new collision: %s \n", SDL_GetError());
    //    exit(EXIT_FAILURE);
    //}
    //c = {
    //    .sim = {
    //        .x = x,
    //        .y = y,
    //        .w = 11,
    //        .w = 11,
    //    },
    //    .next = ctx->collisions;
    //};
    return ctx;
}

void o_collisions_draw (ctx_t * ctx) {
    collision_t * c = ctx->collisions;
    SDL_SetRenderDrawColor(ctx->renderer, 166, 166, 166, 0);
    while (c != NULL) {
        SDL_Log("collision\n");
        c = c->next;
    }
}

ctx_t * o_collisions_init (ctx_t * ctx) {
    ctx->collisions = NULL;
    return ctx;
}

ctx_t * o_collisions_update (ctx_t * ctx) {
    balloon_t * ba = ctx->balloons;
    for (unsigned int i = 0; i<ctx->level->nprespawn.ba; i++, ba++) {
        bullet_t * bu = ctx->bullets;
        while (bu != NULL) {
            if (o_collisions_colliding(ba, bu)) {
                // change state ba to BA_HIT
                ba->state = BA_HIT;

                // increase nbullets
                ctx->nprespawn.bu += ba->value;

                // mark bu for deletion
                bu->state = BU_HIT;

                // spawn collision effect
                o_collisions_add(ctx, ba->tgt.x, ba->tgt.y);
            }
            bu = bu->next;
        }
    }
    return ctx;
}

static bool o_collisions_colliding(balloon_t * ba, bullet_t * bu) {

    if (ba->state != BA_AIRBORNE) {
        return false;
    }

    int ba_l = ba->tgt.x;
    int ba_r = ba->tgt.x + ba->tgt.w;
    int ba_t = ba->tgt.y;
    int ba_b = ba->tgt.y + ba->tgt.h;

    int bu_l = bu->tgt.x;
    int bu_r = bu->tgt.x + bu->tgt.w;
    int bu_t = bu->tgt.y;
    int bu_b = bu->tgt.y + bu->tgt.h;

    bool separated = ba_t > bu_b ||
                     ba_r < bu_l ||
                     ba_b < bu_t ||
                     ba_l > bu_r  ;

    return !separated;
}
