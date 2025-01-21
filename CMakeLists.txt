cmake_minimum_required(VERSION 3.23...3.28)

project(project-mbm LANGUAGES C)
include(CTest)  # defines BUILD_TESTING

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




if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # I'm the top-most project
    option(MBM_BUILD_TESTING "Whether to build the mbm tests" ${BUILD_TESTING})
    if ((BUILD_TESTING AND NOT MBM_BUILD_TESTING) OR
        (NOT BUILD_TESTING AND MBM_BUILD_TESTING))
        message(WARNING, " will use more specific MBM_BUILD_TESTING=${MBM_BUILD_TESTING} over BUILD_TESTING=${BUILD_TESTING}")
    endif()
else()
    # I'm not the top-most project, use MBM_BUILD_TESTING as-is
    option(MBM_BUILD_TESTING "Whether to build the mbm tests" OFF)
endif()
if (MBM_BUILD_TESTING)
    add_subdirectory(${PROJECT_ROOT}/test/mbm)
endif()
