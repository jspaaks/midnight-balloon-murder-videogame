# describe how to compile the executable
add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        chunks.c
        colors.c
        counters.c
        drawables.c
        drawing.c
        fonts.c
        fsm.c
        fsm_level_finished.c
        fsm_paused.c
        fsm_playing.c
        fsm_start.c
        levels.c
        main.c
        o_background.c
        o_balloons.c
        o_barrel.c
        o_bullets.c
        o_collisions.c
        o_flash.c
        o_ground.c
        o_keymap.c
        o_legend.c
        o_moon.c
        o_titles.c
        o_turret.c
        renderer.c
        scene.c
        spritesheet.c
        timing.c
        window.c
        wrapped.c
)

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
        c_std_23
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        -g
        -O0
        -Wall
        -Wextra
        -pedantic
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link the math, SDL2, SDL2_ttf, and SDL2_mixer libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        m
        SDL2
        SDL2_ttf
        SDL2_mixer
)
