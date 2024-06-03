# Dev notes

## Installing SDL2 from submodule

Download, compile and install SDL2 from the submodule bundled with the main:

```shell
cd <your project dir>
git clone https://github.com/jspaaks/libsdl2-game.git --recursive .
cd third_party/sdl
mkdir build
cd build
../configure --prefix <your project dir>/lib
make
make install
```

After this, `sdl-config --version` returns `2.31.0`.

## Uninstalling SDL2

```shell
cd <your project dir>
cd third_party/sdl/build
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
