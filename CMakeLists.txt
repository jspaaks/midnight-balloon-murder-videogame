cmake_minimum_required(VERSION 3.23...3.28)

project(project LANGUAGES C)

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/dist")
endif()




add_subdirectory(${PROJECT_ROOT}/assets)




# describe how to compile the SDL2 library
set(SDL_Haptic OFF)
set(SDL_Joystick OFF)
set(SDL_Threads OFF)
set(SDL_TESTS OFF)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_ROOT}/third_party/sdl)
install(TARGETS SDL2)




# describe how to compile the SDL2_ttf library
set(SDL2TTF_HARFBUZZ ON)
set(SDL2TTF_SAMPLES OFF)
set(SDL2TTF_VENDORED ON)
add_subdirectory(${PROJECT_ROOT}/third_party/sdl_ttf)
install(TARGETS SDL2_ttf)



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
add_subdirectory(${PROJECT_ROOT}/third_party/sdl_mixer)
install(TARGETS SDL2_mixer)




add_subdirectory(${PROJECT_ROOT}/src/exe)




add_subdirectory(${PROJECT_ROOT}/src/mbm)




#add_subdirectory(${PROJECT_ROOT}/test/mbm)

