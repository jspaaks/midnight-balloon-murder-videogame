#include "drawable_barrel.h"
#include "scene.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "types.h"
#include <assert.h>

static float drawable_barrel_max (float, float);
static float drawable_barrel_min (float, float);
static float drawable_barrel_clip (float);

static float drawable_barrel_clip (float v) {
    const float barrel_angle_min = -71;
    const float barrel_angle_max = -18;
    v = drawable_barrel_max(v, barrel_angle_min);
    v = drawable_barrel_min(v, barrel_angle_max);
    return v;
}

void drawable_barrel_draw (SDL_Renderer * renderer, SDL_Texture * spritesheet, scene_t scene,
                    barrel_t barrel) {
    SDL_Rect tgt = sim2tgt(scene, barrel.sim);
    SDL_Point pivot_offset = (SDL_Point){
        .x = (int) (barrel.sim2.pivot_offset.x * scene.scale),
        .y = (int) (barrel.sim2.pivot_offset.y * scene.scale),
    };
    SDL_RenderCopyEx(renderer, spritesheet, &barrel.src, &tgt, barrel.sim2.angle, &pivot_offset,
                     SDL_FLIP_NONE);
}

barrel_t drawable_barrel_init (turret_t turret) {
    assert(turret.sim.x != 0 && "turret needs to be initialized before barrel");
    SDL_Rect src = {
        .h = 11,
        .w = 55,
        .x = 4,
        .y = 68,
    };
    SDL_FRect sim = {
        .h = src.h,
        .w = src.w,
        .x = turret.sim.x + (turret.sim.w - 1) / 2,
        .y = turret.sim.y + (turret.sim.w - 1) / 2 - (src.h - 1) / 2,
    };
    return (barrel_t) {
        .countdown_duration = 75,
        .countdown_remaining = 0,
        .sim = {
            .h = sim.h,
            .w = sim.w,
            .x = sim.x,
            .y = sim.y,
        },
        .sim2 = {
            .angle = -25.0,
            .length = sim.w,
            .pivot = (SDL_FPoint) {
                .x = turret.sim.x + turret.sim.w / 2,
                .y = turret.sim.y + turret.sim.w / 2,
            },
            .pivot_offset = (SDL_FPoint) {
                .x = 0,
                .y = (int) sim.h / 2,
            },
            .speed = 17,
        },
        .src = src,
    };
}

static float drawable_barrel_max (float a, float b) {
    return a > b ? a : b;
}

static float drawable_barrel_min (float a, float b) {
    return a < b ? a : b;
}

void drawable_barrel_update (timing_t timing, barrel_t * barrel) {
    const Uint8 * keys = SDL_GetKeyboardState(NULL);
    int flags = keys[SDL_SCANCODE_W] | keys[SDL_SCANCODE_S] << 1;
    switch (flags) {
        case 1: {
            barrel->sim2.angle =
                drawable_barrel_clip(barrel->sim2.angle + -1 * barrel->sim2.speed * timing.dt.frame);
            break;
        }
        case 2: {
            barrel->sim2.angle =
                drawable_barrel_clip(barrel->sim2.angle + 1 * barrel->sim2.speed * timing.dt.frame);
            break;
        }
    }
    if (barrel->countdown_remaining > 0) {
        barrel->countdown_remaining -= timing.dt.frame;
    }
}
