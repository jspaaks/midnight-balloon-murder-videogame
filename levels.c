#include "levels.h"
#include "context.h"
#include <stdio.h>

static level_t levels[] = {
    {
        .name = "novice",
        .nbullets = 100,
        .nred = 0,
        .norange = 0,
        .nyellow = 10,
        .nballoons = 10,
    },
    {
        .name = "private",
        .nbullets = 70,
        .nred = 0,
        .norange = 0,
        .nyellow = 20,
        .nballoons = 20,
    },
    {
        .name = "gunny",
        .nbullets = 40,
        .nred = 0,
        .norange = 0,
        .nyellow = 40,
        .nballoons = 40,
    },
    {
        .name = "sharpshooter",
        .nbullets = 20,
        .nred = 0,
        .norange = 0,
        .nyellow = 70,
        .nballoons = 70,
    },
    {
        .name = "assassin",
        .nbullets = 10,
        .nred = 0,
        .norange = 0,
        .nyellow = 100,
        .nballoons = 100,
    },
    {
        .name = "berserker",
        .nbullets = 10,
        .nred = 0,
        .norange = 0,
        .nyellow = 1000,
        .nballoons = 1000,
    },
};


int levels_get_nlevels(void) {
    return sizeof(levels) / sizeof(levels[0]);
}

level_t * levels_init (void) {
      return &levels[0];
}

