#include "chunks.h"
#include "deinit.h"
#include "SDL_mixer.h"
#include <stdlib.h>

void chunks_deinit (chunks_t * chunks) {

    // clean up chunks
    Mix_FreeChunk(chunks->shoot);
    chunks->shoot = NULL;

    Mix_FreeChunk(chunks->pop);
    chunks->pop = NULL;

    Mix_FreeChunk(chunks->hit.red);
    chunks->hit.red = NULL;

    Mix_FreeChunk(chunks->hit.orange);
    chunks->hit.orange = NULL;

    Mix_FreeChunk(chunks->hit.yellow);
    chunks->hit.yellow = NULL;

    // clean up audio device resource
    Mix_CloseAudio();

    // clean up mixer
    Mix_Quit();
}

chunks_t chunks_init (void) {

    // --- initialize the audio module

    MIX_InitFlags flags = 0x00000000 | MIX_INIT_MP3;
    if ((Mix_Init(flags) & 0x11111111) == flags) {
        SDL_LogError(SDL_UNSUPPORTED, "Something went wrong initializing the audio. %s\n",
                     Mix_GetError());
        deinit();
    }

    // --- open an audio device

    int frequency = 48000; // Hz
    Uint16 format = AUDIO_F32SYS;
    int nchannels = 2;
    int chunksize = 4096;
    const char * device = NULL;
    int allowed_changes = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE;

    if (Mix_OpenAudioDevice(frequency, format, nchannels, chunksize, device, allowed_changes) < 0) {
        SDL_LogError(SDL_UNSUPPORTED, "Something went wrong opening the audio device. %s\n",
                     Mix_GetError());
        deinit();
    }

    // --- load music data

    chunks_t chunks;
    char * filename = NULL;

    filename = "chunks/empty.wav";
    chunks.empty = Mix_LoadWAV(filename);
    if (chunks.empty == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        deinit();
        ;
    }

    filename = "chunks/hit-red.wav";
    chunks.hit.red = Mix_LoadWAV(filename);
    if (chunks.hit.red == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        deinit();
        ;
    }

    filename = "chunks/hit-orange.wav";
    chunks.hit.orange = Mix_LoadWAV(filename);
    if (chunks.hit.orange == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        deinit();
    }

    filename = "chunks/hit-yellow.wav";
    chunks.hit.yellow = Mix_LoadWAV(filename);
    if (chunks.hit.yellow == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        deinit();
    }

    filename = "chunks/pop.wav";
    chunks.pop = Mix_LoadWAV(filename);
    if (chunks.pop == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        deinit();
    }

    filename = "chunks/shot.wav";
    chunks.shoot = Mix_LoadWAV(filename);
    if (chunks.shoot == NULL) {
        SDL_LogError(SDL_UNSUPPORTED, "Error loading '%s'. %s\n", filename, Mix_GetError());
        deinit();
    }

    return chunks;
}
