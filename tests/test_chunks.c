#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "deinit.h"
#include "chunks.h"
#include "types.h"

static bool test_chunks_init(void);
static bool test_chunks_deinit(void);

int main(void) {
    bool cond =
        test_chunks_init() &&
        test_chunks_deinit();
    return cond ? 0 : 1;
}

static bool test_chunks_deinit(void) {
    chunks_t chunks;
    deinit_prepare_chunks(&chunks);
    char * basepath = SDL_GetBasePath();
    chunks = chunks_init(basepath);
    assert(chunks.shoot != NULL && "expected chunks.shoot to be set at this stage.");
    assert(chunks.pop != NULL && "expected chunks.pop to be set at this stage.");
    assert(chunks.hit.orange != NULL && "expected chunks.hit.orange to be set at this stage.");
    assert(chunks.hit.red != NULL && "expected chunks.hit.red to be set at this stage.");
    assert(chunks.hit.yellow != NULL && "expected chunks.hit.yellow to be set at this stage.");
    chunks_deinit(&chunks);
    bool cond =
        chunks.shoot == NULL &&
        chunks.pop == NULL &&
        chunks.hit.orange == NULL &&
        chunks.hit.red == NULL &&
        chunks.hit.yellow == NULL;
    if (!cond) fprintf(stderr, "'test_chunks_deinit()' failed.\n");
    return cond;
}

static bool test_chunks_init(void) {
    chunks_t chunks;
    deinit_prepare_chunks(&chunks);
    char * basepath = SDL_GetBasePath();
    chunks = chunks_init(basepath);
    return chunks.shoot != NULL &&
        chunks.pop != NULL &&
        chunks.hit.orange != NULL &&
        chunks.hit.red != NULL &&
        chunks.hit.yellow != NULL;
}
