#include "drawable_collisions.h"
#include "deinit.h"
#include "drawable_balloons.h"
#include "drawable_bullets.h"
#include "scene.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool drawable_collisions_colliding(balloon_t, bullet_t);
static void drawable_collisions_update_age (timing_t, collision_t *);
static void drawable_collisions_update_play_sound(chunks_t, balloon_t);
static void drawable_collisions_update_pos (timing_t, collision_t *);
static void drawable_collisions_update_remove (collision_t **);
static void drawable_collisions_update_spawn_effect (balloon_t, collision_t **);
static void drawable_collisions_update_spawn_hitpoint (balloon_t, collision_t **);
static void drawable_collisions_update_test_exited (scene_t, ground_t, collision_t *);

static bool drawable_collisions_colliding (balloon_t balloon, bullet_t bullet) {
    float ba_l = balloon.sim.x;
    float ba_r = balloon.sim.x + balloon.sim.w;
    float ba_t = balloon.sim.y;
    float ba_b = balloon.sim.y + balloon.sim.h;

    float bu_l = bullet.sim.x;
    float bu_r = bullet.sim.x + bullet.sim.w;
    float bu_t = bullet.sim.y;
    float bu_b = bullet.sim.y + bullet.sim.h;

    bool separated = ba_t > bu_b || ba_r < bu_l || ba_b < bu_t || ba_l > bu_r;

    return !separated;
}

void drawable_collisions_deinit (collision_t ** collisions) {
    if (collisions == NULL) return;
    collision_t * c = *collisions;
    while (c != NULL) {
        collision_t * tmp = c;
        c = c->next;
        free(tmp);
    }
    *collisions = NULL;
}

void drawable_collisions_draw (SDL_Renderer * renderer, SDL_Texture * spritesheet, colors_t colors,
                               fonts_t fonts, scene_t scene, collision_t * collisions) {
    SDL_Surface * surf = NULL;
    SDL_Texture * txre = NULL;
    collision_t * this = collisions;
    while (this != NULL) {
        if (this->iseffect) {
            SDL_Rect tgt = sim2tgt(scene, this->sim);
            SDL_RenderCopy(renderer, spritesheet, &this->src, &tgt);
        } else {
            char caption[10];
            sprintf(caption, "+%d", this->value);

            SDL_Surface * surf =
                TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
            if (surf == NULL) goto cleanup;

            SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
            if (txre == NULL) goto cleanup;

            SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                              .x = this->sim.x - surf->w / 2,
                                              .y = this->sim.y - surf->h / 2,
                                              .w = surf->w,
                                              .h = surf->h,
                                          });
            SDL_RenderCopy(renderer, txre, NULL, &tgt);
            SDL_DestroyTexture(txre);
            SDL_FreeSurface(surf);
        }
        this = this->next;
    }
    return;
cleanup:
    SDL_Log("Error creating the hitpoint text.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

collision_t * drawable_collisions_init (void) {
    return NULL;
}

void drawable_collisions_update (timing_t timing, scene_t scene, ground_t ground, chunks_t chunks,
                                 balloon_t * balloons, bullet_t * bullets, counters_t * counters,
                                 collision_t ** collisions) {
    drawable_collisions_update_test_exited(scene, ground, *collisions);
    drawable_collisions_update_remove(collisions);
    drawable_collisions_update_pos(timing, *collisions);
    drawable_collisions_update_age(timing, *collisions);
    balloon_t * balloon = balloons;
    while (balloon != NULL) {
        bullet_t * bullet = bullets;
        while (bullet != NULL) {
            if (drawable_collisions_colliding(*balloon, *bullet)) {
                // increase nbullets
                counters->nbullets.prespawn += balloon->value;

                // mark balloon and bullet for deletion
                balloon->state = HIT;
                bullet->state = HIT;

                // play sound effect
                drawable_collisions_update_play_sound(chunks, *balloon);

                // spawn collision effects
                drawable_collisions_update_spawn_effect(*balloon, collisions);

                // spawn collision hitpoint text
                drawable_collisions_update_spawn_hitpoint(*balloon, collisions);
            }
            bullet = bullet->next;
        }
        balloon = balloon->next;
    }
}

static void drawable_collisions_update_age (timing_t timing, collision_t * collisions) {
    collision_t * this = collisions;
    while (this != NULL) {
        this->age += timing.dt.frame;
        if (this->age > this->age_max) {
            this->state = TIMEOUT_ENDED;
        }
        this = this->next;
    }
}

static void drawable_collisions_update_play_sound (chunks_t chunks, balloon_t balloon) {
    Mix_PlayChannel(-1, chunks.pop, 0);
    switch (balloon.value) {
        case 3: {
            Mix_PlayChannel(-1, chunks.hit.yellow, 0);
            break;
        }
        case 4: {
            Mix_PlayChannel(-1, chunks.hit.orange, 0);
            break;
        }
        case 5: {
            Mix_PlayChannel(-1, chunks.hit.red, 0);
            break;
        }
        default: {
            SDL_LogError(SDL_UNSUPPORTED,
                         "Something went wrong with assigning the sound to the collision.\n");
        }
    }
}

static void drawable_collisions_update_pos (timing_t timing, collision_t * collisions) {
    const float gravity = 70; // pixels per second per second
    collision_t * c = collisions;
    while (c != NULL) {
        c->sim2.v += c->iseffect ? gravity * timing.dt.frame : 0;
        c->sim.x += c->sim2.u * timing.dt.frame;
        c->sim.y += c->sim2.v * timing.dt.frame;
        c = c->next;
    }
}

static void drawable_collisions_update_remove (collision_t ** collisions) {
    collision_t * this = *collisions;
    collision_t * prev = NULL;
    bool isfirst = false;
    bool doremove = false;
    while (this != NULL) {
        isfirst = prev == NULL;
        doremove = this->state != ALIVE;
        switch (isfirst << 1 | doremove) {
            case 0: {
                // not first, not remove
                prev = this;
                this = this->next;
                break;
            }
            case 1: {
                // not first, remove
                collision_t * tmp = this;
                prev->next = this->next;
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
                collision_t * tmp = this;
                *collisions = this->next;
                this = this->next;
                free(tmp);
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED,
                             "Something went wrong in removing a collision from the list.\n");
                deinit();
            }
        }
    }
}

static void drawable_collisions_update_spawn_effect (balloon_t balloon, collision_t ** collisions) {
    int n = 4 + rand() % 10;
    for (int i = 0; i < n; i++) {
        collision_t * c = malloc(1 * sizeof(collision_t));
        if (c == NULL) {
            SDL_Log("Something went wrong allocating memory for new collision.\n");
            deinit();
        }
        *c = (collision_t) {
            .age = 0.000,
            .age_max = (float)(600 + rand() % 600) / 1000,
            .iseffect = true,
            .next = *collisions,
            .sim = {
                .x = balloon.sim.x - balloon.sim.w / 2,
                .y = balloon.sim.y - balloon.sim.h / 2,
                .w = 3,
                .h = 3,
            },
            .sim2 = {
                .u = -50 + rand() % 100,
                .v = -50 + rand() % 100,
            },
            .src = {
                 .x = 172,
                 .y = 38,
                 .w = 3,
                 .h = 3,
            },
            .state = ALIVE,
        };
        *collisions = c;
    }
}

static void drawable_collisions_update_spawn_hitpoint (balloon_t balloon,
                                                       collision_t ** collisions) {
    collision_t * c = malloc(1 * sizeof(collision_t));
    if (c == NULL) {
        SDL_Log("Something went wrong allocating memory for new collision.\n");
        deinit();
    }
    *c = (collision_t) {
        .age = 0.000,
        .age_max = 1.6,
        .iseffect = false,
        .next = *collisions,
        .sim = {
            .x = balloon.sim.x - balloon.sim.w / 2,
            .y = balloon.sim.y - balloon.sim.h / 2,
            .w = 5,
            .h = 5,
        },
        .sim2 = {
            .u = -70 + (rand() % 140),
            .v = -70,
        },
        .src = {
             .x = 188,
             .y = 38,
             .w = 5,
             .h = 5,
        },
        .state = ALIVE,
        .value = balloon.value,
    };
    *collisions = c;
}

static void drawable_collisions_update_test_exited (scene_t scene, ground_t ground,
                                                    collision_t * collisions) {
    collision_t * this = collisions;
    bool exited;
    while (this != NULL) {
        exited = this->sim.y < 0 - this->sim.h || this->sim.x > scene.sim.w ||
                 this->sim.x < 0 - this->sim.w || this->sim.y > scene.sim.h - ground.sim.h;
        if (exited) {
            this->state = EXITED;
        }
        this = this->next;
    }
}
