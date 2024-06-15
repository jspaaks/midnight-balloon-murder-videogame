#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "types.h"
#include "o_balloons.h"
#include "o_bullets.h"
#include "o_collisions.h"

static bool o_collisions_colliding(balloon_t *, bullet_t *);
static void o_collisions_update_pos (timing_t, collision_t **);
static void o_collisions_update_remove(collision_t **);
static void o_collisions_update_spawn (ctx_t *, counters_t *, balloon_t **, bullet_t **);
static void o_collisions_update_test_exited (scene_t, ground_t, collision_t **);

static bool o_collisions_colliding(balloon_t * ba, bullet_t * bu) {
    float ba_l = ba->sim.x;
    float ba_r = ba->sim.x + ba->sim.w;
    float ba_t = ba->sim.y;
    float ba_b = ba->sim.y + ba->sim.h;

    float bu_l = bu->sim.x;
    float bu_r = bu->sim.x + bu->sim.w;
    float bu_t = bu->sim.y;
    float bu_b = bu->sim.y + bu->sim.h;

    bool separated = ba_t > bu_b ||
                     ba_r < bu_l ||
                     ba_b < bu_t ||
                     ba_l > bu_r;

    return !separated;
}

void o_collisions_deinit (collision_t ** collisions) {
    collision_t * c = *collisions;
    while (c != NULL) {
        collision_t * tmp = c;
        c = c->next;
        free(tmp);
    }
    *collisions = NULL;
}

void o_collisions_draw (SDL_Renderer * renderer, scene_t, SDL_Texture *, collision_t * collisions) {
    collision_t * c = collisions;
    SDL_SetRenderDrawColor(renderer, 166, 166, 166, 0);
    while (c != NULL) {
        c = c->next;
    }
}

void o_collisions_init (collision_t ** collisions) {
    *collisions = NULL;
}

void o_collisions_update (timing_t timing, scene_t scene, ground_t ground, ctx_t * ctx, counters_t * counters, balloon_t ** balloons, bullet_t ** bullets, collision_t ** collisions) {
    o_collisions_update_test_exited(scene, ground, collisions);
    o_collisions_update_remove(collisions);
    o_collisions_update_pos(timing, collisions);
    o_collisions_update_spawn(ctx, counters, balloons, bullets);
}

static void o_collisions_update_pos (timing_t timing, collision_t ** collisions) {
    const float gravity = 70; // pixels per second per second
    collision_t * c = *collisions;
    while (c != NULL) {
        c->sim2.v += gravity * timing.dt.frame;
        c->sim.x += c->sim2.u * timing.dt.frame;
        c->sim.y += c->sim2.v * timing.dt.frame;
        c = c->next;
    }
}

static void o_collisions_update_remove (collision_t ** collisions) {
    collision_t * this = *collisions;
    collision_t * prev = NULL;
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
                SDL_LogError(SDL_UNSUPPORTED, "Something went wrong in removing a collision from the list.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

static void o_collisions_update_spawn (ctx_t * ctx, counters_t * counters, balloon_t ** balloons, bullet_t ** bullets) {
    balloon_t * ba = *balloons;
    while (ba != NULL) {
        bullet_t * bu = *bullets;
        while (bu != NULL) {
            if (o_collisions_colliding(ba, bu)) {

                // increase nbullets
                counters->nbullets.prespawn += ba->value;

                // mark bullet and balloon for deletion
                ba->state = HIT;
                bu->state = HIT;

                // spawn collision effect
                // TODO
                Mix_PlayChannel(-1, ctx->chunks.pop, 0);
                switch (ba->value) {
                    case 3: {
                        Mix_PlayChannel(-1, ctx->chunks.hit.yellow, 0);
                        break;
                    }
                    case 4: {
                        Mix_PlayChannel(-1, ctx->chunks.hit.orange, 0);
                        break;
                    }
                    case 5: {
                        Mix_PlayChannel(-1, ctx->chunks.hit.red, 0);
                        break;
                    }
                    default: {
                        SDL_LogError(SDL_UNSUPPORTED, "Something went wrong with assigning the sound to the collision.\n");
                    }
                }
            }
            bu = bu->next;
        }
        ba = ba->next;
    }
}

static void o_collisions_update_test_exited (scene_t scene, ground_t ground, collision_t ** collisions) {
    collision_t * this = *collisions;
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
