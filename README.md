Crinemaft
=========

Overview
--------
Crinemaft is a 3D voxel game inspired by Minecraft and written in C++ using
OpenGL / GLFW.

Build instructions for macOS
----------------------------
- Open a terminal and type this in: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
<br/>This installs [Homebrew](https://brew.sh).
- Navigate to the directory you want to have your game folder in and type these
commands:
    - `brew install git` (Install Git)
    - `brew install glfw` (Install GLFW)
    - `brew install cmake` (Install CMake)
    - `git clone https://github.com/adamhutchings/crinemaft` (Create a crinemaft folder with the game source)
    - `cd crinemaft` (Navigate to the folder)
    - `./scripts/build.sh` (Build the project)
    - `./scripts/run.sh` (Run the project)

When running the game a second time, you only need to run the last command to
play the game again (but make sure to navigate to the right directory first).

Build instructions for Linux
----------------------------
The Linux build is successful but I have been informed that the build process is
risky and unsuitable for normal use. If you want to try yourself, do:
`sudo apt-get build-dep glfw3` (an error message may pop up, the risky and
unsuitable part is our fix for above) and the follow the macOS instructions
from `git clone https://github.com/adamhutchings/crinemaft`.

Build instructions for Windows
------------------------------
Coming soon ...
