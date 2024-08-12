#include "mbm/drawing.h"
#include "mbm/colors.h"
#include "mbm/fonts.h"
#include "mbm/renderer.h"
#include "mbm/scene.h"
#include "SDL_video.h"
#include "mbm/spritesheet.h"
#include "mbm/types.h"
#include "mbm/window.h"

drawing_t drawing_init (char * basepath) {
    scene_t scene = scene_init();
    SDL_Window * window = window_init(scene);
    SDL_Renderer * renderer = renderer_init(window);
    return (drawing_t){
        .renderer = renderer,
        .scene = scene,
        .spritesheet = spritesheet_init(renderer, basepath),
        .colors = colors_init(),
        .fonts = fonts_init(basepath),
        .window = window,
    };
}
