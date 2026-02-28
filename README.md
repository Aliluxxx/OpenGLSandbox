# OpenGLSandbox
A sandbox to test OpenGL API in C++. This project is cross-platform, but was only tested on Windows, Linux and macOS.

## Download instructions
To clone the repository use the following git command:
`git clone https://github.com/Aliluxxx/OpenGLSandbox OpenGLSandbox`.

## Setup instructions
To generate build files, run the command `python Setup.py` inside the `scripts` folder (you must have [Python3](https://www.python.org/downloads/) installed on your machine).
The script will check if you have [CMake](https://cmake.org/download/) and some required python packages installed. If not, it will automatically install them (on operating systems other than Windows, the process may require manual installation). It will also check for missing git submodules and download them.
The build files will be located in the `build/{selected_build_system}` folder that will be created in the root directory of the project (where `{selected_build_system}` is the build system that was chosen during the setup phase and should be something like `vs2022`, `make`, `ninja` etc...).

## Compile instructions
To setup and compile the project, you can:
1. open any IDE that supports the previously selected build system and click on "compile" button
2. run the command `python SetupAndCompile.py` inside the `scripts` folder

## Run instructions
To setup, compile and run the project, you can:
1. open any IDE that supports the previously selected build system and click on "compile and run" button
2. run the command `python SetupAndCompile.py` inside the `scripts` folder and then execute manually the application by searching `build/{selected_build_system}/bin/{selected_configuration}` (where `{selected_configuration}` should be `Debug`, `Release` or `Dist`).
3. run the command `python Run.py` inside the `scripts` folder
