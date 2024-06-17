# Dev notes

## Installing SDL2 from submodule

Clone this repo recursively:

```shell
cd <your project dir>
git clone https://github.com/jspaaks/libsdl2-game.git --recursive .
```

## Building with CMake

```shell
# generate the build files
mkdir build && cd build
cmake .. -DSDL2MIXER_OPUS=OFF \
         -DSDL2MIXER_MOD=OFF \
         -DSDL2MIXER_MIDI_FLUIDSYNTH=OFF \
         -DSDL2MIXER_WAVPACK=OFF

# compile using the generated build files
cmake --build .

# Run the binary from the project root
cd .. && ./build/src/mbm
```

### See also

- https://www.youtube.com/watch?v=IZXNsim9TWI Bret Brown CppCon 2021
- https://www.youtube.com/watch?v=eC9-iRN2b04 Mathieu Ropert CppCon 2017

## Generating a bitmap image from SVG

Install [ImageMagick](https://github.com/imagemagick/imagemagick) from repositories:

```shell
sudo apt install imagemagick
```

Converting SVG images to BMP with transparency using ImageMagick's `convert` command:

```shell
convert -background none -density 96 img/sprites.svg img/sprites.bmp
```

## Linting

Linting an individual file:

```
# see if main.c is compliant with rules in .clang-format
clang-format --dry-run --Werror ./main.c

# see what clang-format would like the file to look
clang-format --Werror ./main.c

# see if all files are compliant with rules in .clang-format
clang-format --dry-run --Werror `find . -maxdepth 1 -type f -name '*.[c|h]'`
```

# Sound effects

Sounds effects are from https://sfxr.me/.

## TODO

1. hitpoints texts
1. hitpoints shrapnel
1. review directory structure (src / bin / test etc)
1. packaging / distribution
1. consider adding tests, cmocka maybe
