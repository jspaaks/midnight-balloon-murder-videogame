# Dev notes

## Building, testing, and installing

Clone this repo recursively:

```console
$ cd <your project dir>
$ git clone https://github.com/jspaaks/midnight-balloon-murder-videogame.git --recursive .
```

Then use Cmake to configure, build and (optionally) install:

```console
# create an out-of-tree build directory, cd into it
$ mkdir build && cd build

# generate the build files
$ cmake -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=~/tmp/mbm ..

# compile using the generated build files
$ cmake --build .

# install in your CMAKE_INSTALL_PREFIX directory of choice
$ cmake --install .

# run the tests (requires configuring with -DBUILD_TESTING=ON and additionally assumes
# that the Criterion testing library has been installed)
$ ctest

# Run the binary from the prefix root
$ ~/tmp/mbm/bin/mbm
```

## Linting

```console
# see if main.c is compliant with rules in .clang-format
$ clang-format --dry-run --Werror ./src/main.c

# see what clang-format would like the file to look
$ clang-format --Werror ./src/main.c

# see if all files are compliant with rules in .clang-format
$ clang-format --dry-run --Werror `find ./src -maxdepth 1 -type f -name '*.[c|h]'`

# let clang-format change files in-place
$ clang-format -i `find ./src -maxdepth 1 -type f -name '*.[c|h]'`
```

## Generating a bitmap image from SVG

Install [ImageMagick](https://github.com/imagemagick/imagemagick) from repositories:

```console
$ sudo apt install imagemagick
```

Converting SVG images to BMP with transparency using ImageMagick's `convert` command:

```console
$ convert -background none -density 96 images/sprites.svg images/sprites.bmp
```

## Sound effects

Sounds effects are from https://sfxr.me/.

## See also

- https://www.youtube.com/watch?v=IZXNsim9TWI Bret Brown CppCon 2021
- https://www.youtube.com/watch?v=eC9-iRN2b04 Mathieu Ropert CppCon 2017

## Tools

- valgrind
- ldd
- nm
- ldconfig
- gdb

## TODO

1. packaging / distribution
1. github action build & test
1. testing setup could be more idiomatic, smarter.
1. review use of const
1. consider refactoring linked list instances into abstract data type module
