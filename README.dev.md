# Dev notes

Download, compile and install SDL2 from the repo:

```
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

Converting SVG images to BMP with transparency using ImageMagick:

```
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
