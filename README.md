# COMP 345 WARZONE

Project description placeholder

## Build

Our project uses CMake for version control purposes. To install CMake and run the build follow the instruction below:

### MacOS

- Install `cmake` and `make` using `brew install cmake make`
- Run `mkdir build` to make a folder called build
- Change the directory to build and run `cmake -S . -B ./build`

### Linux/WSL

- Install `cmake` and `make` using `sudo apt install cmake make`
- Run `mkdir build` to make a folder called build
- Change the directory to build and run `cmake -S . -B ./build`

After installing and generate build configuration based on `CMakeLists.txt`, to compile the program, do the following commands starting at the root directory:

```
cd build
make
```

To run the compiled program: `./WARZONE`
