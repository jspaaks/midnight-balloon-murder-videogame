# describe how to compile the executable
add_executable(mbm)

target_sources(
    mbm
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/chunks.c
        ${CMAKE_CURRENT_LIST_DIR}/colors.c
        ${CMAKE_CURRENT_LIST_DIR}/counters.c
        ${CMAKE_CURRENT_LIST_DIR}/deinit.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_background.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_balloons.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_barrel.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_bullets.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_collisions.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_flash.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_ground.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_keymap.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_legend.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_moon.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_titles.c
        ${CMAKE_CURRENT_LIST_DIR}/drawable_turret.c
        ${CMAKE_CURRENT_LIST_DIR}/drawables.c
        ${CMAKE_CURRENT_LIST_DIR}/drawing.c
        ${CMAKE_CURRENT_LIST_DIR}/fonts.c
        ${CMAKE_CURRENT_LIST_DIR}/fsm.c
        ${CMAKE_CURRENT_LIST_DIR}/fsm_level_finished.c
        ${CMAKE_CURRENT_LIST_DIR}/fsm_paused.c
        ${CMAKE_CURRENT_LIST_DIR}/fsm_playing.c
        ${CMAKE_CURRENT_LIST_DIR}/fsm_start.c
        ${CMAKE_CURRENT_LIST_DIR}/levels.c
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/renderer.c
        ${CMAKE_CURRENT_LIST_DIR}/scene.c
        ${CMAKE_CURRENT_LIST_DIR}/spritesheet.c
        ${CMAKE_CURRENT_LIST_DIR}/timing.c
        ${CMAKE_CURRENT_LIST_DIR}/window.c
)

target_compile_features(
    mbm
    PRIVATE
        c_std_23
)

target_compile_options(
    mbm
    PRIVATE
        -g
        -O0
        -Wall
        -Wextra
        -pedantic
)

target_include_directories(
    mbm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link the math, SDL2, SDL2_ttf, and SDL2_mixer libraries
target_link_libraries(
    mbm
    PRIVATE
        m
        SDL2
        SDL2_ttf
        SDL2_mixer
)

# Include the executable in install directory
install(
    TARGETS
        mbm
    RUNTIME
)
