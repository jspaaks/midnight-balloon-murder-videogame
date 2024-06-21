function(create_test_executable filename)
    message("Creating test executable from: ${filename}")
    get_filename_component(basename ${filename} NAME_WLE)
    add_executable(${basename})
    target_sources(
        ${basename}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/${basename}.c  # instead of src/main.c::main(), use tests/${basename}.c::main()
            ${CMAKE_CURRENT_LIST_DIR}/../src/chunks.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/colors.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/counters.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/deinit.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_background.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_balloons.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_barrel.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_bullets.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_collisions.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_flash.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_ground.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_keymap.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_legend.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_moon.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_titles.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawable_turret.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawables.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/drawing.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/fonts.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/fsm.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/fsm_level_finished.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/fsm_paused.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/fsm_playing.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/fsm_start.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/levels.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/renderer.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/scene.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/spritesheet.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/timing.c
            ${CMAKE_CURRENT_LIST_DIR}/../src/window.c
    )
    target_include_directories(
        ${basename}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/../src
    )
    target_link_libraries(
        ${basename}
        PRIVATE
            m
            SDL2
            SDL2_ttf
            SDL2_mixer
    )
    add_test(NAME ${basename} COMMAND $<TARGET_FILE:${basename}>)
endfunction()

set(
    TESTFILES
        test_counters_init.c
        test_fonts_init.c
        test_levels_get_level_novice.c
        test_levels_get_level_private.c
        test_levels_get_level_gunny.c
        test_levels_get_level_sharpshooter.c
        test_levels_get_level_assassin.c
        test_levels_get_level_berserker.c
)
foreach(TESTFILE IN LISTS TESTFILES)
    create_test_executable(${TESTFILE})
endforeach()
