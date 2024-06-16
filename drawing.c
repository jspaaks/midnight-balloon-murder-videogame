#include "SDL_video.h"
#include "colors.h"
#include "drawing.h"
#include "fonts.h"
#include "renderer.h"
#include "scene.h"
#include "spritesheet.h"
#include "types.h"
#include "window.h"

drawing_t drawing_init (void) {
    scene_t scene = scene_init();
    SDL_Window * window = window_init(scene);
    SDL_Renderer * renderer = renderer_init(window);
    return (drawing_t) {
        .renderer = renderer,
        .scene = scene,
        .spritesheet = spritesheet_init(renderer),
        .colors = colors_init(),
        .fonts = fonts_init(),
        .window = window,
    };
}
