# describe how to compile the executable
add_executable(${PROJECT_NAME} main.c)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/chunks.c
        ${CMAKE_CURRENT_SOURCE_DIR}/colors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/counters.c
        ${CMAKE_CURRENT_SOURCE_DIR}/drawables.c
        ${CMAKE_CURRENT_SOURCE_DIR}/drawing.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fonts.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fsm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fsm_level_finished.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fsm_paused.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fsm_playing.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fsm_start.c
        ${CMAKE_CURRENT_SOURCE_DIR}/levels.c
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_background.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_balloons.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_barrel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_bullets.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_collisions.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_flash.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_ground.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_keymap.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_legend.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_moon.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_titles.c
        ${CMAKE_CURRENT_SOURCE_DIR}/o_turret.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/scene.c
        ${CMAKE_CURRENT_SOURCE_DIR}/spritesheet.c
        ${CMAKE_CURRENT_SOURCE_DIR}/timing.c
        ${CMAKE_CURRENT_SOURCE_DIR}/window.c
        ${CMAKE_CURRENT_SOURCE_DIR}/wrapped.c
)

target_compile_options(${PROJECT_NAME}
    PUBLIC
        -std=c2x
        -g
        -O0
        -Wall
        -Wextra
        -pedantic
        -MMD
        -MP
)

# Link the math, SDL2, SDL2_ttf, and SDL2_mixer libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        m
        SDL2
        SDL2_ttf
        SDL2_mixer
)
