# copy chunk assets to build directory
set(
    MBM_CHUNKS
        empty.wav
        hit-orange.wav
        hit-red.wav
        hit-yellow.wav
        pop.wav
        shot.wav
)
foreach(MBM_CHUNK IN LISTS MBM_CHUNKS)
    file(GENERATE OUTPUT ${MBM_CHUNK} INPUT ${MBM_CHUNK})
endforeach()
