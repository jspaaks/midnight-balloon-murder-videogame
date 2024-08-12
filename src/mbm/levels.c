#include "mbm/levels.h"
#include "mbm/counters.h"
#include "mbm/drawable_balloons.h"
#include "mbm/drawable_barrel.h"
#include "mbm/drawable_bullets.h"
#include "mbm/drawable_collisions.h"
#include "mbm/drawable_flash.h"
#include "mbm/drawable_ground.h"
#include "mbm/drawable_legend.h"
#include "mbm/drawable_moon.h"
#include "mbm/drawable_turret.h"
#include "mbm/types.h"
#include <stdbool.h>
#include <stdio.h>

static level_t levels[] = {
    {
        .label = LEVEL_NOVICE,
        .label_next = LEVEL_PRIVATE,
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
        .next_unlocked = false,
    },
    {
        .label = LEVEL_PRIVATE,
        .label_next = LEVEL_GUNNY,
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
        .next_unlocked = false,
    },
    {
        .label = LEVEL_GUNNY,
        .label_next = LEVEL_SHARPSHOOTER,
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
        .next_unlocked = false,
    },
    {
        .label = LEVEL_SHARPSHOOTER,
        .label_next = LEVEL_ASSASSIN,
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
        .next_unlocked = false,
    },
    {
        .label = LEVEL_ASSASSIN,
        .label_next = LEVEL_BERSERKER,
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
        .next_unlocked = false,
    },
    {
        .label = LEVEL_BERSERKER,
        .label_next = LEVEL_BERSERKER,
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
        .next_unlocked = false,
    },
};

level_t levels_get_level (const level_enum_t label) {
    return levels[label];
}

void levels_reset_level (const level_t level, const drawing_t drawing, drawables_t * drawables,
                         counters_t * counters) {

    // --- deinit entities from previous levels
    drawable_balloons_deinit(&drawables->balloons);
    drawable_bullets_deinit(&drawables->bullets);
    drawable_collisions_deinit(&drawables->collisions);

    // --- concrete entities
    drawables->ground = drawable_ground_init(drawing.scene);
    drawables->moon = drawable_moon_init(drawing.scene);
    drawables->turret = drawable_turret_init(drawing.scene, drawables->ground);
    drawables->barrel = drawable_barrel_init(drawables->turret);
    drawables->flash = drawable_flash_init(drawables->barrel);
    drawables->legend = drawable_legend_init();
    drawables->balloons = drawable_balloons_init();
    drawables->bullets = drawable_bullets_init();
    drawables->collisions = drawable_collisions_init();
    *counters = counters_init(level);
}
