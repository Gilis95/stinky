# Sinky Engine

## Build Status

[![Build Status](https://travis-ci.com/Gilis95/stinky.svg?branch=master)](https://travis-ci.com/Gilis95/stinky)

## How to clone repo

Stinky is using modern CMake approach for handling 3rd party dependencies, so you're not obligated to clone recursively its submodules. However stinky is using [tracy](https://github.com/Gilis95/tracy) as a profile tool.
If you're going to profile the engine, you must clone repository recursively and compile tracy client.

To clone repository with all of its dependencies, following command should be used:

``` git clone --recursive git@github.com:Gilis95/stinky.git ```

To clone repository without its dependencies, following command must be executed:

``` git clone git@github.com:Gilis95/stinky.git ```

## How to build project

Project is using CMake as a build tool. It's recommended to generate platform dependent files and store them in new project root child directory, e.g. `build`. 
To build the project by mentioned above method, following secuence of commands should be used:

```
cd ${STINKY_PROJECT_ROOT_DIR}
mkdir build
cd build
cmake ../
```
