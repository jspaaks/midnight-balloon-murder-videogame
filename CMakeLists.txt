# See also
# - https://www.youtube.com/watch?v=IZXNsim9TWI Bret Brown CppCon 2021
# - https://www.youtube.com/watch?v=eC9-iRN2b04 Mathieu Ropert CppCon 2017

cmake_minimum_required(VERSION 3.22...3.29)
project (mbm
    VERSION "0.1.0"
    DESCRIPTION "Midnight Balloon Murder"
    LANGUAGES "C"
)
# describe how to compile the SDL2, SDL2_ttf, and SDL2_mixer libraries
add_subdirectory(third_party/sdl EXCLUDE_FROM_ALL)
add_subdirectory(third_party/sdl_mixer EXCLUDE_FROM_ALL)
add_subdirectory(third_party/sdl_ttf EXCLUDE_FROM_ALL)
add_subdirectory(src)
