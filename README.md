# Sinky Engine

## How to clone repo

In order to clone repository with all of its dependencies following command should be used:

``` git clone --recursive git@github.com:Gilis95/stinky.git ```

## How to build project

Cmake should be used for generating platform dependent files. It's recommended to generate platform dependent files in separate directory. For example `build` directory can be created inside project root directory. 
To build project by mentioned above method, following secuence of commands should be used:

```
cd ${STINKY_PROJECT_ROOT_DIR}
mkdir build
cd build
cmake ../
```
In case this is done Windows OS, Visual Studio solution file will be generated. Now on you can open this sln file with `Visual Studio`.

In case this is done under Linux, Makefiles will be generated. Now on you can use ``` make ``` to generate `stinky-engine`(game engine) .so and `stinky-sandbox` executable.
