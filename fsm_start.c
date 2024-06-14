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

void fsm_start_draw (ctx_t * ctx, SDL_Renderer * renderer) {
    o_background_draw(renderer);
    o_scene_draw(ctx, renderer);
    o_moon_draw(ctx, renderer);
    o_ground_draw(ctx, renderer);
    o_keymap_draw_start(ctx, renderer);
    o_titles_draw_opening_title(ctx, renderer);
    SDL_RenderPresent(renderer);
}

void fsm_start_update (ctx_t * ctx, SDL_Window * window, SDL_Renderer * renderer, gamestate_t ** gamestate) {
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
                    ctx->scene.resized = true;
                }
                break;
            }
        }
    }
    o_scene_update(ctx, renderer);
}
