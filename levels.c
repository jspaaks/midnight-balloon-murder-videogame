#include <stdbool.h>
#include <stdio.h>
#include "types.h"
#include "levels.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"

static level_t levels[] = {
    {
        .name = "novice",
        .norange = 3,
        .nprespawn = {
            .ba = 10,
            .bu = 100,
        },
        .nproceed = 8,
        .nred = 2,
        .nyellow = 5,
    },
    {
        .name = "private",
        .norange = 6,
        .nprespawn = {
            .ba = 20,
            .bu = 70,
        },
        .nproceed = 18,
        .nred = 4,
        .nyellow = 10,
    },
    {
        .name = "gunny",
        .norange = 12,
        .nprespawn = {
            .ba = 40,
            .bu = 40,
        },
        .nproceed = 38,
        .nred = 8,
        .nyellow = 20,
    },
    {
        .name = "sharpshooter",
        .norange = 21,
        .nprespawn = {
            .ba = 70,
            .bu = 20,
        },
        .nproceed = 67,
        .nred = 14,
        .nyellow = 35,
    },
    {
        .name = "assassin",
        .norange = 30,
        .nprespawn = {
            .ba = 100,
            .bu = 10,
        },
        .nproceed = 95,
        .nred = 20,
        .nyellow = 50,
    },
    {
        .name = "berserker",
        .norange = 300,
        .nprespawn = {
            .ba = 1000,
            .bu = 10,
        },
        .nproceed = 1001,
        .nred = 200,
        .nyellow = 500,
    },
};

ctx_t * levels_deinit (ctx_t * ctx) {
    ctx->levels = NULL;
    return ctx;
}

ctx_t * levels_init (ctx_t * ctx) {
    unsigned int unl = 0;
    ctx->ilevel_unlocked = unl;
    ctx = levels_set(ctx, unl);
    return ctx;
}

ctx_t * levels_set (ctx_t * ctx, unsigned int ilevel) {
    // --- deinit entities from previous levels
    ctx = o_balloons_deinit(ctx);
    ctx = o_bullets_deinit(ctx);
    ctx = o_collisions_deinit(ctx);
    // --- new level
    ctx->ilevel = ilevel;
    ctx->level = &levels[ilevel];
    ctx->levels = &levels[0];
    ctx->nlevels = sizeof(levels) / sizeof(levels[0]);
    // --- concrete entities
    ctx = o_ground_init(ctx);
    ctx = o_moon_init(ctx);
    ctx = o_turret_init(ctx);
    ctx = o_barrel_init(ctx);
    ctx = o_balloons_init(ctx);
    ctx = o_bullets_init(ctx);
    ctx = o_collisions_init(ctx);
    ctx = o_flash_init(ctx);
    ctx = o_legend_init(ctx);
    return ctx;
}
