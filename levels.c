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
        .nballoons = {
            .orange = 3,
            .prespawn = 10,
            .proceed = 8,
            .red = 2,
            .yellow = 5,
        },
        .nbullets = {
            .prespawn = 100,
        },
    },
    {
        .name = "private",
        .nballoons = {
            .orange = 6,
            .prespawn = 20,
            .proceed = 18,
            .red = 4,
            .yellow = 10,
        },
        .nbullets = {
            .prespawn = 70,
        },
    },
    {
        .name = "gunny",
        .nballoons = {
            .orange = 12,
            .prespawn = 40,
            .proceed = 38,
            .red = 8,
            .yellow = 20,
        },
        .nbullets = {
            .prespawn = 40,
        },
    },
    {
        .name = "sharpshooter",
        .nballoons = {
            .orange = 21,
            .prespawn = 70,
            .proceed = 67,
            .red = 14,
            .yellow = 35,
        },
        .nbullets = {
            .prespawn = 20,
        },
    },
    {
        .name = "assassin",
        .nballoons = {
            .orange = 30,
            .prespawn = 100,
            .proceed = 95,
            .red = 20,
            .yellow = 50,
        },
        .nbullets = {
            .prespawn = 10,
        },
    },
    {
        .name = "berserker",
        .nballoons = {
            .orange = 300,
            .prespawn = 1000,
            .proceed = 1001,
            .red = 200,
            .yellow = 500,
        },
        .nbullets = {
            .prespawn = 10,
        },
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
