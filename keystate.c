#include "SDL_keyboard.h"
#include "keystate.h"
#include "types.h"

ctx_t * keystate_deinit (ctx_t * ctx) {
    ctx->keys = NULL;
    return ctx;
}

ctx_t * keystate_init (ctx_t * ctx) {
    ctx->keys = SDL_GetKeyboardState(NULL);
    return ctx;
}
