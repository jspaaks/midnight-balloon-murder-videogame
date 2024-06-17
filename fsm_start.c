#include "fsm_start.h"
#include "fsm.h"
#include "o_background.h"
#include "o_ground.h"
#include "o_keymap.h"
#include "o_moon.h"
#include "o_titles.h"
#include "scene.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include "types.h"
#include "wrapped.h"
#include <stdlib.h>

void fsm_start_draw (level_t, drawing_t drawing, drawables_t drawables, counters_t) {
    o_background_draw(drawing.renderer, drawing.colors, drawing.scene);
    o_moon_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.moon);
    o_ground_draw(drawing.renderer, drawing.colors, drawing.scene, drawables.ground);
    o_keymap_draw_start(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                        drawables.ground);
    o_titles_draw_opening_title(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene);
    SDL_RenderPresent(drawing.renderer);
}

void fsm_start_update (timing_t, chunks_t, counters_t *, drawing_t * drawing, drawables_t *,
                       gamestate_t ** gamestate, level_t *) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    SDL_Log("playing\n");
                    *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(drawing->window, drawing->scene.isfullscreen
                                                                 ? 0
                                                                 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    drawing->scene.isfullscreen = !drawing->scene.isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    drawing->scene.resized = true;
                }
                break;
            }
        }
    }
    scene_update(drawing->renderer, &drawing->scene);
}
