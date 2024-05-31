#include "levels.h"
#include "context.h"
#include <stdio.h>

static level_t levels[] = {
    {
        .name = "novice",
        .nbullets = 100,
        .nred = 2,
        .norange = 3,
        .nyellow = 5,
        .nballoons = 10,
    },
    {
        .name = "private",
        .nbullets = 70,
        .nred = 4,
        .norange = 6,
        .nyellow = 10,
        .nballoons = 20,
    },
    {
        .name = "gunny",
        .nbullets = 40,
        .nred = 8,
        .norange = 12,
        .nyellow = 20,
        .nballoons = 40,
    },
    {
        .name = "sharpshooter",
        .nbullets = 20,
        .nred = 14,
        .norange = 21,
        .nyellow = 35,
        .nballoons = 70,
    },
    {
        .name = "assassin",
        .nbullets = 10,
        .nred = 20,
        .norange = 30,
        .nyellow = 50,
        .nballoons = 100,
    },
    {
        .name = "berserker",
        .nbullets = 10,
        .nred = 200,
        .norange = 300,
        .nyellow = 500,
        .nballoons = 1000,
    },
};


ctx_t * levels_init (ctx_t * ctx) {
    ctx->levels = &levels[0];
    ctx->level = ctx->levels + 1;
    ctx->nlevels = sizeof(levels) / sizeof(levels[0]);
    return ctx;
}
