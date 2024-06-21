#include <stdbool.h>
#include "deinit.h"
#include "fonts.h"
#include "types.h"

int main(void) {
    fonts_t fonts;
    deinit_prepare_fonts(&fonts);

    fonts = fonts_init();
    bool cond = fonts.regular != NULL;
    return cond ? 0 : 1;
}
