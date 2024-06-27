# See also
# - https://www.youtube.com/watch?v=IZXNsim9TWI Bret Brown CppCon 2021
# - https://www.youtube.com/watch?v=eC9-iRN2b04 Mathieu Ropert CppCon 2017

cmake_minimum_required(VERSION 3.22...3.29)
project (mbm
    VERSION "0.1.0"
    DESCRIPTION "Midnight Balloon Murder"
    LANGUAGES "C"
)

list(APPEND CMAKE_INSTALL_RPATH $ORIGIN $ORIGIN/../lib)

# describe how to compile the SDL2 library
set(SDL_Haptic OFF)
set(SDL_Joystick OFF)
set(SDL_Threads OFF)
add_subdirectory(third_party/sdl)

# describe how to compile the SDL2_ttf library
set(SDL2TTF_HARFBUZZ ON)
set(SDL2TTF_SAMPLES OFF)
set(SDL2TTF_VENDORED ON)
add_subdirectory(third_party/sdl_ttf)

# describe how to compile the SDL2_mixer library
set(SDL2MIXER_FLAC OFF)
set(SDL2MIXER_GME OFF)
set(SDL2MIXER_GME_SHARED OFF)
set(SDL2MIXER_MIDI OFF)
set(SDL2MIXER_MOD OFF)
set(SDL2MIXER_MP3 OFF)
set(SDL2MIXER_OPUS OFF)
set(SDL2MIXER_SAMPLES OFF)
set(SDL2MIXER_VENDORED ON)
set(SDL2MIXER_VORBIS "")
set(SDL2MIXER_WAVE ON)
set(SDL2MIXER_WAVPACK OFF)
add_subdirectory(third_party/sdl_mixer)

# add assets to the build
add_subdirectory(chunks)
add_subdirectory(fonts)
add_subdirectory(images)

# defer to the CMakeLists.txt in src/
add_subdirectory(src)

# enable testing for this project, then defer to the CMakeLists.txt in tests/
enable_testing()
add_subdirectory(tests)

# copy libs to bin directory
install(
    FILES
        build/third_party/sdl/libSDL2-2.0.so
        build/third_party/sdl/libSDL2-2.0.so.0
        build/third_party/sdl/libSDL2-2.0.so.0.3100.0
        build/third_party/sdl_mixer/libSDL2_mixer-2.0.so.0.800.0
        build/third_party/sdl_mixer/libSDL2_mixer-2.0.so.0
        build/third_party/sdl_mixer/libSDL2_mixer-2.0.so
        build/third_party/sdl_mixer/libSDL2_mixer.so
        build/third_party/sdl_ttf/libSDL2_ttf-2.0.so.0.2300.0
        build/third_party/sdl_ttf/libSDL2_ttf-2.0.so.0
        build/third_party/sdl_ttf/libSDL2_ttf-2.0.so
        build/third_party/sdl_ttf/libSDL2_ttf.so
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
