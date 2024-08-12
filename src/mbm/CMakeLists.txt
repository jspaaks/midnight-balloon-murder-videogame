cmake_minimum_required(VERSION 3.23...3.28)

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/dist")
endif()

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
if (APPLE)
    list(APPEND CMAKE_INSTALL_RPATH @loader_path/../lib)
elseif(UNIX)
    list(APPEND CMAKE_INSTALL_RPATH $ORIGIN/../lib)
endif()

add_library(tgt_lib_mbm SHARED)

set_property(TARGET tgt_lib_mbm PROPERTY OUTPUT_NAME mbm)

target_compile_definitions(
    tgt_lib_mbm
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

target_compile_features(
    tgt_lib_mbm
    PRIVATE
        c_std_23
)

target_compile_options(
    tgt_lib_mbm
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Release>:-Werror>
)

target_include_directories(
    tgt_lib_mbm
    PRIVATE
        ${PROJECT_ROOT}/include
)

target_link_libraries(
    tgt_lib_mbm
    PRIVATE
        m
        SDL2
        SDL2_mixer
        SDL2_ttf
)

target_sources(
    tgt_lib_mbm
    PRIVATE
        ${PROJECT_ROOT}/src/mbm/chunks.c
        ${PROJECT_ROOT}/src/mbm/CMakeLists.txt
        ${PROJECT_ROOT}/src/mbm/colors.c
        ${PROJECT_ROOT}/src/mbm/counters.c
        ${PROJECT_ROOT}/src/mbm/deinit.c
        ${PROJECT_ROOT}/src/mbm/drawable_background.c
        ${PROJECT_ROOT}/src/mbm/drawable_balloons.c
        ${PROJECT_ROOT}/src/mbm/drawable_barrel.c
        ${PROJECT_ROOT}/src/mbm/drawable_bullets.c
        ${PROJECT_ROOT}/src/mbm/drawable_collisions.c
        ${PROJECT_ROOT}/src/mbm/drawable_flash.c
        ${PROJECT_ROOT}/src/mbm/drawable_ground.c
        ${PROJECT_ROOT}/src/mbm/drawable_keymap.c
        ${PROJECT_ROOT}/src/mbm/drawable_legend.c
        ${PROJECT_ROOT}/src/mbm/drawable_moon.c
        ${PROJECT_ROOT}/src/mbm/drawables.c
        ${PROJECT_ROOT}/src/mbm/drawable_titles.c
        ${PROJECT_ROOT}/src/mbm/drawable_turret.c
        ${PROJECT_ROOT}/src/mbm/drawing.c
        ${PROJECT_ROOT}/src/mbm/fonts.c
        ${PROJECT_ROOT}/src/mbm/fsm.c
        ${PROJECT_ROOT}/src/mbm/fsm_level_finished.c
        ${PROJECT_ROOT}/src/mbm/fsm_paused.c
        ${PROJECT_ROOT}/src/mbm/fsm_playing.c
        ${PROJECT_ROOT}/src/mbm/fsm_start.c
        ${PROJECT_ROOT}/src/mbm/levels.c
        ${PROJECT_ROOT}/src/mbm/renderer.c
        ${PROJECT_ROOT}/src/mbm/scene.c
        ${PROJECT_ROOT}/src/mbm/spritesheet.c
        ${PROJECT_ROOT}/src/mbm/timing.c
        ${PROJECT_ROOT}/src/mbm/window.c
    PUBLIC
        FILE_SET fset_lib_mbm_headers
        TYPE HEADERS
        BASE_DIRS
            ${PROJECT_ROOT}/include
        FILES
            ${PROJECT_ROOT}/include/mbm/chunks.h
            ${PROJECT_ROOT}/include/mbm/colors.h
            ${PROJECT_ROOT}/include/mbm/counters.h
            ${PROJECT_ROOT}/include/mbm/deinit.h
            ${PROJECT_ROOT}/include/mbm/drawable_background.h
            ${PROJECT_ROOT}/include/mbm/drawable_balloons.h
            ${PROJECT_ROOT}/include/mbm/drawable_barrel.h
            ${PROJECT_ROOT}/include/mbm/drawable_bullets.h
            ${PROJECT_ROOT}/include/mbm/drawable_collisions.h
            ${PROJECT_ROOT}/include/mbm/drawable_flash.h
            ${PROJECT_ROOT}/include/mbm/drawable_ground.h
            ${PROJECT_ROOT}/include/mbm/drawable_keymap.h
            ${PROJECT_ROOT}/include/mbm/drawable_legend.h
            ${PROJECT_ROOT}/include/mbm/drawable_moon.h
            ${PROJECT_ROOT}/include/mbm/drawables.h
            ${PROJECT_ROOT}/include/mbm/drawable_titles.h
            ${PROJECT_ROOT}/include/mbm/drawable_turret.h
            ${PROJECT_ROOT}/include/mbm/drawing.h
            ${PROJECT_ROOT}/include/mbm/fonts.h
            ${PROJECT_ROOT}/include/mbm/fsm.h
            ${PROJECT_ROOT}/include/mbm/fsm_level_finished.h
            ${PROJECT_ROOT}/include/mbm/fsm_paused.h
            ${PROJECT_ROOT}/include/mbm/fsm_playing.h
            ${PROJECT_ROOT}/include/mbm/fsm_start.h
            ${PROJECT_ROOT}/include/mbm/levels.h
            ${PROJECT_ROOT}/include/mbm/renderer.h
            ${PROJECT_ROOT}/include/mbm/scene.h
            ${PROJECT_ROOT}/include/mbm/spritesheet.h
            ${PROJECT_ROOT}/include/mbm/timing.h
            ${PROJECT_ROOT}/include/mbm/types.h
            ${PROJECT_ROOT}/include/mbm/window.h
)

install(TARGETS tgt_lib_mbm
    LIBRARY
    FILE_SET fset_lib_mbm_headers
)
