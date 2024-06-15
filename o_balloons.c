#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SDL_timer.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_error.h"
#include "types.h"
#include "levels.h"
#include "o_balloons.h"
#include "o_scene.h"

static float o_balloons_unitrand(void);
static void o_balloons_update_pos (timing_t, balloon_t *);
static void o_balloons_update_remove (balloon_t **, nballoons_t *);
static void o_balloons_update_spawn (timing_t, scene_t, ground_t, balloon_t **, nballoons_t *);
static void o_balloons_update_spawn_orange (scene_t, ground_t, balloon_t **);
static void o_balloons_update_spawn_red (scene_t, ground_t, balloon_t **);
static void o_balloons_update_spawn_yellow (scene_t, ground_t, balloon_t **);
static void o_balloons_update_test_exited (scene_t, ground_t, balloon_t *);

void o_balloons_deinit (balloon_t ** balloons) {
    balloon_t * b = *balloons;
    while (b != NULL) {
        balloon_t * tmp = b;
        b = b->next;
        free(tmp);
    }
    *balloons = NULL;
}

void o_balloons_draw (SDL_Renderer * renderer, scene_t scene, SDL_Texture * spritesheet, balloon_t * balloons) {
    balloon_t * b = balloons;
    while (b != NULL) {
        SDL_Rect tgt = sim2tgt(scene, b->sim);
        SDL_RenderCopy(renderer, spritesheet, &b->src, &tgt);
        b = b->next;
    }
}

void o_balloons_init (level_t * level, balloon_t ** balloons, nballoons_t * nballoons) {
    assert(level != NULL && "levels needs to be initialized before balloons");
    *balloons = NULL;
    nballoons->airborne = 0;
    nballoons->hit = 0;
    nballoons->miss = 0;
    nballoons->orange = level->nballoons.orange;
    nballoons->prespawn = level->nballoons.prespawn;
    nballoons->red = level->nballoons.red;
    nballoons->yellow = level->nballoons.yellow;
}

static float o_balloons_unitrand(void) {
    return (float)(rand()) / (float)(RAND_MAX);
}

void o_balloons_update (timing_t timing, scene_t scene, ground_t ground, balloon_t ** balloons, nballoons_t * nballoons) {
    o_balloons_update_test_exited(scene, ground, *balloons);
    o_balloons_update_remove(balloons, nballoons);
    o_balloons_update_pos(timing, *balloons);
    o_balloons_update_spawn(timing, scene, ground, balloons, nballoons);
}

static void o_balloons_update_spawn (timing_t timing, scene_t scene, ground_t ground, balloon_t ** balloons, nballoons_t * nballoons) {
    static const float spawn_rate = 0.35; // balloons per second
    float spawn_chance = nballoons->airborne == 0 ? 1 : spawn_rate * timing.dt.frame;
    if (nballoons->prespawn <= 0 || o_balloons_unitrand() > spawn_chance) {
        return;
    }
    unsigned int remaining = nballoons->yellow + nballoons->orange + nballoons->red;
    float y = (float)(nballoons->yellow) / remaining;
    float o = (float)(nballoons->orange) / remaining;
    float u = o_balloons_unitrand();
    if (u < y) {
        o_balloons_update_spawn_yellow(scene, ground, balloons);
        nballoons->yellow--;
    } else if (u < (y + o)) {
        o_balloons_update_spawn_orange(scene, ground, balloons);
        nballoons->orange--;
    } else {
        o_balloons_update_spawn_red(scene, ground, balloons);
        nballoons->red--;
    }
    nballoons->airborne++;
    nballoons->prespawn--;
}

static void o_balloons_update_spawn_orange (scene_t scene, ground_t ground, balloon_t ** balloons) {
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new orange balloon.\n");
        exit(EXIT_FAILURE);
    }
    *b = (balloon_t){
        .next = *balloons,
        .sim = (SDL_FRect){
            .h = 12,
            .w = 9,
            .x = scene.sim.w / 2 + o_balloons_unitrand() * (0.4 * scene.sim.w),
            .y = scene.sim.h - ground.sim.h,
        },
        .sim2 = {
            .u = 0.0,
            .v = -30.0,
        },
        .src = (SDL_Rect){
            .h = 12,
            .w = 9,
            .x = 184,
            .y = 1,
        },
        .state = ALIVE,
        .value = 4,
    };
    *balloons = b;
}

static void o_balloons_update_spawn_red (scene_t scene, ground_t ground, balloon_t ** balloons) {
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new red balloon.\n");
        exit(EXIT_FAILURE);
    }
    *b = (balloon_t){
        .next = *balloons,
        .sim = (SDL_FRect){
            .h = 7,
            .w = 6,
            .x = scene.sim.w / 2 + o_balloons_unitrand() * (0.4 * scene.sim.w),
            .y = scene.sim.h - ground.sim.h,
        },
        .sim2 = {
            .u = 0.0,
            .v = -30.0,
        },
        .src = (SDL_Rect){
            .h = 7,
            .w = 6,
            .x = 184,
            .y = 20,
        },
        .state = ALIVE,
        .value = 3,
    };
    *balloons = b;
}

static void o_balloons_update_spawn_yellow (scene_t scene, ground_t ground, balloon_t ** balloons) {
    balloon_t * b = malloc(1 * sizeof(balloon_t));
    if (b == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for new yellow balloon.\n");
        exit(EXIT_FAILURE);
    }
    *b = (balloon_t){
        .next = *balloons,
        .sim = (SDL_FRect){
            .h = 16,
            .w = 12,
            .x = scene.sim.w / 2 + o_balloons_unitrand() * (0.4 * scene.sim.w),
            .y = scene.sim.h - ground.sim.h,
        },
        .sim2 = {
            .u = 0.0,
            .v = -30.0,
        },
        .src = (SDL_Rect){
            .h = 16,
            .w = 12,
            .x = 166,
            .y = 1,
        },
        .state = ALIVE,
        .value = 5,
    };
    *balloons = b;
}

static void o_balloons_update_pos (timing_t timing, balloon_t * balloons) {
    balloon_t * b = balloons;
    while (b != NULL) {
        b->sim.x += b->sim2.u * timing.dt.frame;
        b->sim.y += b->sim2.v * timing.dt.frame;
        b = b->next;
    }
}

static void o_balloons_update_remove (balloon_t ** balloons, nballoons_t * nballoons) {
    balloon_t * this = *balloons;
    balloon_t * prev = NULL;
    bool isfirst = false;
    bool doremove = false;
    while (this != NULL) {
        isfirst = prev == NULL;
        doremove = this->state != ALIVE;
        switch (isfirst << 1 | doremove ) {
            case 0: {
                // not first, not remove
                prev = this;
                this = this->next;
                break;
            }
            case 1: {
                // not first, remove
                balloon_t * tmp = this;
                prev->next = this->next;
                if (this->state == EXITED) {
                    nballoons->miss++;
                    nballoons->airborne--;
                }
                if (this->state == HIT) {
                    nballoons->hit++;
                    nballoons->airborne--;
                }
                this = this->next;
                free(tmp);
                break;
            }
            case 2: {
                // first, not remove
                prev = this;
                this = this->next;
                break;
            }
            case 3: {
                // first, remove
                balloon_t * tmp = this;
                *balloons = this->next;
                if (this->state == EXITED) {
                    nballoons->miss++;
                    nballoons->airborne--;
                }
                if (this->state == HIT) {
                    nballoons->hit++;
                    nballoons->airborne--;
                }
                this = this->next;
                free(tmp);
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED, "Something went wrong in removing a balloon from the list.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

static void o_balloons_update_test_exited (scene_t scene, ground_t ground, balloon_t * balloons) {
    balloon_t * this = balloons;
    bool exited;
    while (this != NULL) {
        exited = this->sim.y < 0 - this->sim.h  ||
                 this->sim.x > scene.sim.w ||
                 this->sim.x < 0 - this->sim.w  ||
                 this->sim.y > scene.sim.h - ground.sim.h;
        if (exited) {
            this->state = EXITED;
        }
        this = this->next;
    }
}
