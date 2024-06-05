#include <stdio.h>
#include "types.h"
#include "levels.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_turret.h"
#include "o_legend.h"

static level_t levels[] = {
    {
        .name = "novice",
        .nred = 2,
        .norange = 3,
        .nyellow = 5,
        .nprespawn = {
            .ba = 10,
            .bu = 100,
        }
    },
    {
        .name = "private",
        .nred = 4,
        .norange = 6,
        .nyellow = 10,
        .nprespawn = {
            .ba = 20,
            .bu = 70,
        }
    },
    {
        .name = "gunny",
        .nred = 8,
        .norange = 12,
        .nyellow = 20,
        .nprespawn = {
            .ba = 40,
            .bu = 40,
        }
    },
    {
        .name = "sharpshooter",
        .nred = 14,
        .norange = 21,
        .nyellow = 35,
        .nprespawn = {
            .ba = 70,
            .bu = 20,
        }
    },
    {
        .name = "assassin",
        .nred = 20,
        .norange = 30,
        .nyellow = 50,
        .nprespawn = {
            .ba = 100,
            .bu = 10,
        }
    },
    {
        .name = "berserker",
        .nred = 200,
        .norange = 300,
        .nyellow = 500,
        .nprespawn = {
            .ba = 1000,
            .bu = 10,
        }
    },
};

ctx_t * levels_deinit (ctx_t * ctx) {
    ctx->levels = NULL;
    return ctx;
}

ctx_t * levels_init (ctx_t * ctx) {
    ctx = levels_set(ctx, 0);
    return ctx;
}

ctx_t * levels_set (ctx_t * ctx, unsigned int ilevel) {
    ctx->ilevel = ilevel;
    ctx->level = &levels[ilevel];
    ctx->levels = &levels[0];
    ctx->nlevels = sizeof(levels) / sizeof(levels[0]);
    // --- concrete entities
    ctx = o_turret_init(ctx);
    ctx = o_barrel_init(ctx);
    ctx = o_balloons_init(ctx);
    ctx = o_bullets_init(ctx);
    ctx = o_collisions_init(ctx);
    ctx = o_flash_init(ctx);
    ctx = o_legend_init(ctx);
    return ctx;
}
