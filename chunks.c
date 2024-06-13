#include <stdlib.h>
#include "SDL_mixer.h"
#include "chunks.h"

ctx_t * chunks_deinit(ctx_t * ctx) {

    // clean up chunks
    Mix_FreeChunk(ctx->chunks.shoot);
    ctx->chunks.shoot = NULL;

    Mix_FreeChunk(ctx->chunks.pop);
    ctx->chunks.pop = NULL;

    Mix_FreeChunk(ctx->chunks.hit.red);
    ctx->chunks.hit.red = NULL;

    Mix_FreeChunk(ctx->chunks.hit.orange);
    ctx->chunks.hit.orange = NULL;

    Mix_FreeChunk(ctx->chunks.hit.yellow);
    ctx->chunks.hit.yellow = NULL;

    // clean up audio device resource
    Mix_CloseAudio();

    // clean up mixer
    Mix_Quit();

    return ctx;
}

ctx_t * chunks_init(ctx_t * ctx) {

    // --- initialize the audio module

    MIX_InitFlags flags = 0x00000000 | MIX_INIT_MP3;
    if ((Mix_Init(flags) & 0x11111111) == flags) {
        SDL_LogError(SDL_UNSUPPORTED, "Something went wrong initializing the audio. %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    // --- open an audio device

    int frequency = 48000;  // Hz
    Uint16 format = AUDIO_F32SYS;
    int nchannels = 2;
    int chunksize = 4096;
    const char * device = NULL;
    int allowed_changes = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE;

    if (Mix_OpenAudioDevice(frequency,
                            format,
                            nchannels,
                            chunksize,
                            device,
                            allowed_changes) < 0) {
        SDL_LogError(SDL_UNSUPPORTED, "Something went wrong opening the audio device. %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    // --- load music data

    char * filename = NULL;

    filename = "chunks/empty.wav";
    ctx->chunks.empty = Mix_LoadWAV(filename);
    if (ctx->chunks.empty == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        exit(EXIT_FAILURE);
    }

    filename = "chunks/hit-red.wav";
    ctx->chunks.hit.red = Mix_LoadWAV(filename);
    if (ctx->chunks.hit.red == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        exit(EXIT_FAILURE);
    }

    filename = "chunks/hit-orange.wav";
    ctx->chunks.hit.orange = Mix_LoadWAV(filename);
    if (ctx->chunks.hit.orange == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        exit(EXIT_FAILURE);
    }

    filename = "chunks/hit-yellow.wav";
    ctx->chunks.hit.yellow = Mix_LoadWAV(filename);
    if (ctx->chunks.hit.yellow == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        exit(EXIT_FAILURE);
    }

    filename = "chunks/pop.wav";
    ctx->chunks.pop = Mix_LoadWAV(filename);
    if (ctx->chunks.pop == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        exit(EXIT_FAILURE);
    }

    filename = "chunks/shot.wav";
    ctx->chunks.shoot = Mix_LoadWAV(filename);
    if (ctx->chunks.shoot == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        exit(EXIT_FAILURE);
    }

    return ctx;
}
