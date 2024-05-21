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