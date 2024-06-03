# Dev notes

## Installing SDL2 from submodule

Clone this repo recursively:

```shell
cd <your project dir>
git clone https://github.com/jspaaks/libsdl2-game.git --recursive .
```

Compile and install SDL2 from the bundled submodule (`third_party/sdl`):

```shell
cd <project dir>
mkdir -p build/sdl
cd build/sdl
../../third_party/sdl/configure --prefix <project dir>/lib
make
make install
```
After this, `sdl-config --version` returns `2.31.0`.

Compile and install SDL_ttf from the bundled submodule (`third_party/sdl_ttf`):

```shell
cd <project dir>
mkdir -p build/sdl_ttf
cd build/sdl_ttf
../../third_party/sdl_ttf/configure --prefix <project dir>/lib
make
make install
```

## Uninstalling SDL2

```shell
cd <your project dir>/build/sdl
make uninstall
```

## Uninstalling SDL_ttf

```shell
cd <your project dir>/build/sdl_ttf
make uninstall
```

## Generating a bitmap image from SVG

Install [ImageMagick](https://github.com/imagemagick/imagemagick) from repositories:

```shell
sudo apt install imagemagick
```

Converting SVG images to BMP with transparency using ImageMagick's `convert` command:

```shell
convert -background none -density 96 img/sprites.svg img/sprites.bmp
```

## TODO

1. hitpoints texts
1. hitpoints shrapnel
1. level indicator text / bullets remaining
1. legend texts
1. key help texts

## Q

1. what happens when `dt` is 0?
