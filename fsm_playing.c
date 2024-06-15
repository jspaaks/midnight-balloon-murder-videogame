#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "fsm.h"
#include "fsm_playing.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_ground.h"
#include "o_keymap.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_scene.h"
#include "o_turret.h"

void fsm_playing_draw (ctx_t ctx, drawing_t drawing, drawables_t drawables) {

    o_background_draw(drawing.renderer);

    o_scene_draw(drawing.renderer,
                 drawing.scene,
                 drawing.colors);

    o_moon_draw(drawing.renderer,
                drawing.scene,
                drawing.spritesheet,
                drawables.moon);

    o_barrel_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.barrel);

    o_turret_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.turret);

    o_flash_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.barrel,
                  drawables.flash);

    o_legend_draw(ctx,
                  drawing.renderer,
                  drawing.scene,
                  drawing.fonts,
                  drawing.colors,
                  drawables.legend,
                  ctx.nballoons,
                  ctx.nbullets);

    o_balloons_draw(drawing.renderer,
                    drawing.scene,
                    drawing.spritesheet,
                    drawables.balloons);

    o_bullets_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.bullets);

    o_collisions_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.collisions);

    o_ground_draw(drawing.renderer,
                  drawing.scene,
                  drawing.colors,
                  drawables.ground);

    o_keymap_draw_pause(drawing.renderer,
                        drawing.scene,
                        drawing.fonts,
                        drawing.colors,
                        drawables.ground);

    o_keymap_draw_proceedhint(ctx,
                              drawing.renderer,
                              drawing.scene,
                              drawing.fonts,
                              drawing.colors,
                              drawables.ground);

    SDL_RenderPresent(drawing.renderer);
}

void fsm_playing_update (timing_t timing, ctx_t * ctx, SDL_Window * window, drawing_t * drawing, drawables_t * drawables, gamestate_t ** gamestate) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        SDL_Log("pausing\n");
                        *gamestate = fsm_gamestate_get(GAMESTATE_PAUSING);
                        break;
                    }
                    case SDLK_F11: {
                        SDL_SetWindowFullscreen(window, ctx->isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                        ctx->isfullscreen = !ctx->isfullscreen;
                        break;
                    }
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:  // fallthrough
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                         ctx->resized = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    o_scene_update(ctx,
                   drawing->renderer,
                   &drawing->scene);

    o_barrel_update(timing,
                    *ctx,
                    &drawables->barrel);

    o_flash_update(ctx, &drawables->flash);

    o_balloons_update(timing,
                      drawing->scene,
                      drawables->ground,
                      &drawables->balloons,
                      &ctx->nballoons);

    o_bullets_update(timing,
                     drawing->scene,
                     drawables->ground,
                     ctx,
                     drawables->barrel,
                     &drawables->bullets);

    o_collisions_update(timing,
                        drawing->scene,
                        drawables->ground,
                        ctx,
                        &drawables->balloons,
                        &drawables->bullets,
                        &drawables->collisions);

    bool no_more_balloons = ctx->nballoons.prespawn + ctx->nballoons.airborne == 0;
    bool no_more_bullets = ctx->nbullets.prespawn + ctx->nbullets.airborne == 0;
    if (no_more_balloons || no_more_bullets) {
        ctx->nballoons.miss += ctx->nballoons.prespawn + ctx->nballoons.airborne;
        ctx->nballoons.prespawn = 0;
        ctx->nballoons.airborne = 0;
        SDL_Log("finishing level\n");
        *gamestate = fsm_gamestate_get(GAMESTATE_FINISHING_LEVEL);
    }
}
