# copy chunk assets to install directory
install(
    FILES
        empty.wav
        hit-orange.wav
        hit-red.wav
        hit-yellow.wav
        pop.wav
        shot.wav
    DESTINATION ${CMAKE_INSTALL_PREFIX}/chunks
)
