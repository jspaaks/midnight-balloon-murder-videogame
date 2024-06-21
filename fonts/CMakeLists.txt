# copy font assets to build directory
set(
    MBM_FONTS
        Bayon-Regular.ttf
        OFL.txt
)
foreach(MBM_FONT IN LISTS MBM_FONTS)
    file(GENERATE OUTPUT ${MBM_FONT} INPUT ${MBM_FONT})
endforeach()
