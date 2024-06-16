#include "SDL_video.h"
#include "colors.h"
#include "drawing.h"
#include "fonts.h"
#include "renderer.h"
#include "spritesheet.h"
#include "types.h"

drawing_t drawing_init (SDL_Window * window) {
    SDL_Renderer * renderer = renderer_init(window);
    return (drawing_t) {
        .renderer = renderer,
        .spritesheet = spritesheet_init(renderer),
        .colors = colors_init(),
        .fonts = fonts_init(),
    };
}
