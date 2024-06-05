#include <stdio.h>
#include "types.h"
#include "levels.h"

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
    ctx->level = NULL;
    ctx->nlevels = -1;
    return ctx;
}

ctx_t * levels_init (ctx_t * ctx) {
    ctx->levels = &levels[0];
    ctx->level = ctx->levels + 1;
    ctx->nlevels = sizeof(levels) / sizeof(levels[0]);
    return ctx;
}
