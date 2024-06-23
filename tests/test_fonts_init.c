#include <stdbool.h>
#include "deinit.h"
#include "fonts.h"
#include "types.h"

int main(void) {
    fonts_t fonts;
    deinit_prepare_fonts(&fonts);

    char * basepath = SDL_GetBasePath();
    fonts = fonts_init(basepath);
    bool cond = fonts.regular != NULL;
    return cond ? 0 : 1;
}
