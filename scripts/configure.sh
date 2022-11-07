# Build SDL2-image lib
cd ./external/sdl2-image/
rm -rf ./out/
mkdir ./out/
mkdir ./out/build/
cmake -S . -B ./out/build/
cd ./out/build/
make
sudo make install
cd ../../../../

# Build SDL2 lib
cd ./external/sdl2/
rm -rf ./out/
mkdir ./out/
mkdir ./out/build/
cd ./out/build/
../../configure
make
sudo make install
cd ../../../../

# Configure local project
cmake -S . -B ./out/build/