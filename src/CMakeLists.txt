# describe how to compile the executable
add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        chunks.c
        colors.c
        counters.c
        drawable_background.c
        drawable_balloons.c
        drawable_barrel.c
        drawable_bullets.c
        drawable_collisions.c
        drawable_flash.c
        drawable_ground.c
        drawable_keymap.c
        drawable_legend.c
        drawable_moon.c
        drawable_titles.c
        drawable_turret.c
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
