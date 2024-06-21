# copy image assets to build directory
set(
    MBM_IMAGES
        sprites.bmp
)
foreach(MBM_IMAGE IN LISTS MBM_IMAGES)
    file(GENERATE OUTPUT ${MBM_IMAGE} INPUT ${MBM_IMAGE})
endforeach()
