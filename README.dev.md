Download, compile and install SDL2 from the repo:


```
git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure
make
sudo make install
```

After this, `sdl-config --version` returns `2.31.0`.



Converting SVG images to BMP with transparency using ImageMagick:

```
convert -background none -density 96 img/sprites.svg img/sprites.bmp
```

## TODO

1. bullets low warning
1. bullet objects
1. collision detection
1. hitpoints texts
1. hitpoints shrapnel
1. level indicator text / bullets remaining
1. legend texts
1. key help texts
