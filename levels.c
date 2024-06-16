#include <stdbool.h>
#include <stdio.h>
#include "counters.h"
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
        .label = LEVEL_NOVICE,
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
        .label = LEVEL_PRIVATE,
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
        .label = LEVEL_GUNNY,
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
        .label = LEVEL_SHARPSHOOTER,
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
        .label = LEVEL_ASSASSIN,
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
        .label = LEVEL_BERSERKER,
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

void levels_deinit (ctx_t * ctx) {
    ctx->levels = NULL;
}

void levels_init (ctx_t * ctx) {
    ctx->ilevel = 0;
    ctx->ilevel_unlocked = 0;
    ctx->level = &levels[0];
    ctx->levels = &levels[0];
    ctx->nlevels = sizeof(levels) / sizeof(levels[0]);
}

void levels_set (scene_t scene, ctx_t * ctx, counters_t * counters, unsigned int ilevel, drawables_t * drawables) {
    // --- deinit entities from previous levels
    o_balloons_deinit(&drawables->balloons);
    o_bullets_deinit(&drawables->bullets);
    o_collisions_deinit(&drawables->collisions);
    // --- new level
    ctx->ilevel = ilevel;
    ctx->level = &levels[ilevel];
    ctx->levels = &levels[0];
    ctx->nlevels = sizeof(levels) / sizeof(levels[0]);
    // --- concrete entities
    drawables->ground = o_ground_init(scene);
    drawables->moon = o_moon_init(scene);
    drawables->turret = o_turret_init(scene, drawables->ground);
    drawables->barrel = o_barrel_init(drawables->turret);
    drawables->flash = o_flash_init(drawables->barrel);
    drawables->legend = o_legend_init();
    drawables->balloons = o_balloons_init();
    drawables->bullets = o_bullets_init();
    drawables->collisions = o_collisions_init();
    *counters = counters_init(*ctx->level);
}
