#include <stdlib.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include "o_scene.h"
#include "fsm.h"
#include "fsm_start.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_ground.h"
#include "o_moon.h"
#include "o_keymap.h"
#include "o_titles.h"

void fsm_start_draw (ctx_t, drawing_t drawing, drawables_t drawables, counters_t) {
    o_background_draw(drawing.renderer);

    o_scene_draw(drawing.renderer,
                 drawing.scene,
                 drawing.colors);

    o_moon_draw(drawing.renderer,
                drawing.scene,
                drawing.spritesheet,
                drawables.moon);

    o_ground_draw(drawing.renderer,
                  drawing.scene,
                  drawing.colors,
                  drawables.ground);

    o_keymap_draw_start(drawing.renderer,
                        drawing.scene,
                        drawing.fonts,
                        drawing.colors,
                        drawables.ground);

    o_titles_draw_opening_title(drawing.renderer,
                                drawing.scene,
                                drawing.fonts,
                                drawing.colors);

    SDL_RenderPresent(drawing.renderer);
}

void fsm_start_update (timing_t, counters_t *, ctx_t * ctx, SDL_Window * window, drawing_t * drawing, drawables_t *, gamestate_t ** gamestate) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    SDL_Log("playing\n");
                    *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(window, ctx->isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    ctx->isfullscreen = !ctx->isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    ctx->resized = true;
                }
                break;
            }
        }
    }
    o_scene_update(ctx,
                   drawing->renderer,
                   &drawing->scene);
}
