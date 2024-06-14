#include "SDL_keyboard.h"
#include "keystate.h"
#include "types.h"

void keystate_deinit (ctx_t * ctx) {
    ctx->keys = NULL;
}

void keystate_init (ctx_t * ctx) {
    ctx->keys = SDL_GetKeyboardState(NULL);
}
