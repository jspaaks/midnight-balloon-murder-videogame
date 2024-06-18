#include "drawable_bullets.h"
#include "scene.h"
#include "SDL_error.h"
#include "SDL_keyboard.h"
#include "SDL_log.h"
#include "SDL_mixer.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "SDL_timer.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

static void drawable_bullets_update_pos (timing_t, bullet_t *);
static void drawable_bullets_update_remove (counters_t *, bullet_t **);
static void drawable_bullets_update_spawn (chunks_t, counters_t *, barrel_t *, flash_t *, bullet_t **);
static void drawable_bullets_update_test_exited (scene_t, groundrawable_t, bullet_t *);

void drawable_bullets_deinit (bullet_t ** bullets) {
    bullet_t * b = *bullets;
    while (b != NULL) {
        bullet_t * tmp = b;
        b = b->next;
        free(tmp);
    }
    *bullets = NULL;
}

void drawable_bullets_draw (SDL_Renderer * renderer, SDL_Texture * spritesheet, scene_t scene,
                     bullet_t * bullets) {
    bullet_t * bu = bullets;
    while (bu != NULL) {
        SDL_Rect tgt = sim2tgt(scene, bu->sim);
        SDL_RenderCopy(renderer, spritesheet, bu->src, &tgt);
        bu = bu->next;
    }
}

bullet_t * drawable_bullets_init (void) {
    return NULL;
}

void drawable_bullets_update (timing_t timing, scene_t scene, groundrawable_t ground, chunks_t chunks,
                       counters_t * counters, barrel_t * barrel, flash_t * flash,
                       bullet_t ** bullets) {
    // mark bullets that are out of frame
    drawable_bullets_update_test_exited(scene, ground, *bullets);

    // if bullet is marked for deletion, delete it from the list
    drawable_bullets_update_remove(counters, bullets);

    // update position
    drawable_bullets_update_pos(timing, *bullets);

    // if SPACE down, add a bullet to the list
    drawable_bullets_update_spawn(chunks, counters, barrel, flash, bullets);
}

static void drawable_bullets_update_spawn (chunks_t chunks, counters_t * counters, barrel_t * barrel,
                                    flash_t * flash, bullet_t ** bullets) {
    static const float PI = 3.14159265358979323846f;
    static SDL_Rect src_bullet = { .x = 188, .y = 38, .w = 5, .h = 5 };
    const Uint8 * keys = SDL_GetKeyboardState(NULL);
    bool has_bullets = counters->nbullets.prespawn > 0;
    bool key_pressed = keys[SDL_SCANCODE_SPACE];
    bool cooledrawable_down = barrel->countdown_remaining <= 0;

    if (key_pressed && cooledrawable_down) {
        if (has_bullets) {
            flash->hadrawable_bullets = true;
            bullet_t * b = malloc(1 * sizeof(bullet_t));
            if (b == NULL) {
                SDL_LogError(SDL_ENOMEM,
                             "Something went wrong allocating memory for new bullet.\n");
                exit(EXIT_FAILURE);
            }
            float a = PI * barrel->sim2.angle / 180;
            float x =
                barrel->sim2.pivot.x + cos(a) * (barrel->sim2.length + 20) - (src_bullet.w - 1) / 2;
            float y =
                barrel->sim2.pivot.y + sin(a) * (barrel->sim2.length + 20) - (src_bullet.h - 1) / 2;

            float speed = 380;
            *b = (bullet_t) {
                .next = *bullets,
                .sim = {
                    .x = x,
                    .y = y,
                    .w = 5,
                    .h = 5,
                },
                .sim2 = {
                    .u = cos(a) * speed,
                    .v = sin(a) * speed,
                },
                .src = &src_bullet,
                .state = ALIVE,
            };
            *bullets = b;
            counters->nbullets.prespawn--;
            counters->nbullets.airborne++;
            Mix_PlayChannel(-1, chunks.shoot, 0);
        } else {
            Mix_PlayChannel(-1, chunks.empty, 0);
            flash->hadrawable_bullets = false;
        }
        barrel->countdown_remaining = barrel->countdown_duration;
        flash->countdown_remaining = flash->countdown_duration;
    }
}

static void drawable_bullets_update_pos (timing_t timing, bullet_t * bullets) {
    const float gravity = 70; // pixels per second per second
    bullet_t * b = bullets;
    while (b != NULL) {
        b->sim2.v += gravity * timing.dt.frame;
        b->sim.x += b->sim2.u * timing.dt.frame;
        b->sim.y += b->sim2.v * timing.dt.frame;
        b = b->next;
    }
}

void drawable_bullets_update_remove (counters_t * counters, bullet_t ** bullets) {
    bullet_t * this = *bullets;
    bullet_t * prev = NULL;
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
                bullet_t * tmp = this;
                prev->next = this->next;
                if (this->state == HIT || this->state == EXITED) {
                    counters->nbullets.airborne--;
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
                bullet_t * tmp = this;
                if (this->state == HIT || this->state == EXITED) {
                    counters->nbullets.airborne--;
                }
                *bullets = this->next;
                this = this->next;
                free(tmp);
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED,
                             "Something went wrong in removing a bullet from the list.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

static void drawable_bullets_update_test_exited (scene_t scene, groundrawable_t ground, bullet_t * bullets) {
    bullet_t * this = bullets;
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
