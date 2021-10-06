# COMP 345 WARZONE

COMP 345 Warzone project
Member List:

- Jason
- Bea
- Vanessa
- Wilson Wei Chen Huang (40077333)
- Abdul

## Build

Our project uses CMake for version control purposes. To install CMake and dependencies please run the build follow the instruction below:

### MacOS

- Install `cmake` and `make` using `brew install cmake make`
- Run `mkdir build` to make a folder called `build`
- Install dependency `Boost` using `brew install Boost`
- Build the project using `cmake -S . -B ./build`

### Linux/WSL

- Install `cmake` and `make` using `sudo apt install cmake make`
- Run `mkdir build` to make a folder called `build`
- Install dependency `Boost` using `sudo apt-get install libboost-dev`
- Build the project using `cmake -S . -B ./build`

After installing and generate build configuration based on `CMakeLists.txt`, to compile the program, do the following commands starting from the project root directory:

```
cd build
make
```

To run the compiled program: `./${ProgramName}`
Change the `ProgramName` above based on the file you wish to run
