#include "drawable_balloons.h"
#include "drawable_bullets.h"
#include "chunks.h"
#include "drawable_collisions.h"
#include "deinit.h"
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
collision_t ** collisions_ref = NULL;
SDL_Renderer ** renderer_ref = NULL;
SDL_Window ** window_ref = NULL;
SDL_Texture ** spritesheet_ref = NULL;
fonts_t * fonts_ref = NULL;
chunks_t * chunks_ref = NULL;

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

void deinit_prepare(balloon_t ** balloons, bullet_t ** bullets, collision_t ** collisions, SDL_Renderer ** renderer, SDL_Window ** window, SDL_Texture ** spritesheet, fonts_t * fonts, chunks_t * chunks) {
    balloons_ref = balloons;
    bullets_ref = bullets;
    collisions_ref = collisions;
    renderer_ref = renderer;
    window_ref = window;
    spritesheet_ref = spritesheet;
    fonts_ref = fonts;
    chunks_ref = chunks;
}
