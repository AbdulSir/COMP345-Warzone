# COMP 345 WARZONE

## Project Description
<p>The specific project consists in building a simple “Risk” computer game using C++. The developed program
will have to be compatible with the rules and map files and the command-line play of the “Warzone” version of
Risk, which can be found at: https://www.warzone.com/. A Warzone game setup consists of a connected graph
map representing a world map, where each node is a country and each edge represents adjacency between
countries. Two or more players can play by placing armies on countries they own, from which they can attack
adjacent countries to conquer them. The objective of the game is to conquer all countries on the map. For futher details, read 'Project Description.pdf'</p>

## Members List:

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
