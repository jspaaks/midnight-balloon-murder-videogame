#include "deinit.h"
#include "chunks.h"
#include "drawable_balloons.h"
#include "drawable_bullets.h"
#include "drawable_collisions.h"
#include "fonts.h"
#include "renderer.h"
#include "SDL.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "spritesheet.h"
#include "types.h"
#include "window.h"

balloon_t ** balloons_ref = NULL;
bullet_t ** bullets_ref = NULL;
chunks_t * chunks_ref = NULL;
collision_t ** collisions_ref = NULL;
fonts_t * fonts_ref = NULL;
SDL_Renderer ** renderer_ref = NULL;
SDL_Texture ** spritesheet_ref = NULL;
SDL_Window ** window_ref = NULL;

void deinit (void) {

    // -- drawables
    drawable_balloons_deinit(balloons_ref);
    drawable_bullets_deinit(bullets_ref);
    drawable_collisions_deinit(collisions_ref);

    // -- drawing
    renderer_deinit(renderer_ref);
    window_deinit(window_ref);
    spritesheet_deinit(spritesheet_ref);
    fonts_deinit(fonts_ref);

    // -- chunks
    chunks_deinit(chunks_ref);

    // -- sdl library resources
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void deinit_prepare_all (balloon_t ** balloons, bullet_t ** bullets, collision_t ** collisions,
                         SDL_Renderer ** renderer, SDL_Window ** window, SDL_Texture ** spritesheet,
                         fonts_t * fonts, chunks_t * chunks) {
    balloons_ref = balloons;
    bullets_ref = bullets;
    chunks_ref = chunks;
    collisions_ref = collisions;
    fonts_ref = fonts;
    renderer_ref = renderer;
    spritesheet_ref = spritesheet;
    window_ref = window;
}

void deinit_prepare_balloons (balloon_t ** balloons) {
    balloons_ref = balloons;
}

void deinit_prepare_bullets (bullet_t ** bullets) {
    bullets_ref = bullets;
}

void deinit_prepare_chunks (chunks_t * chunks) {
    chunks_ref = chunks;
}

void deinit_prepare_collisions (collision_t ** collisions) {
    collisions_ref = collisions;
}

void deinit_prepare_fonts (fonts_t * fonts) {
    fonts_ref = fonts;
}

void deinit_prepare_renderer (SDL_Renderer ** renderer) {
    renderer_ref = renderer;
}

void deinit_prepare_spritesheet (SDL_Texture ** spritesheet) {
    spritesheet_ref = spritesheet;
}

void deinit_prepare_window (SDL_Window ** window) {
    window_ref = window;
}
