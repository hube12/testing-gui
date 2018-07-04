# imgui-glfw

[https://github.com/urddru/imgui-glfw](https://github.com/urddru/imgui-glfw)

This is a simple template project that can build a [dear imgui](https://github.com/ocornut/imgui)

```Shell

    $ git clone --recurse-submodules https://github.com/urddru/imgui-glfw.git


    # The default generator is Ninja
    $ b

    # or if you don't have '.' in your PATH env var

    $ ./b

    # Then build using your generator

    $ cd build; ninja

```

## Features

* GLFW and Dear Imgui only - (no boost, etc.)
  * They are git submodules
* Based on Dear Imgui opengl-glfw sample
* Minimal CMake for build generation - builds Ninja, Xcode, Makefiles, etc.
* OpenGL 3
* Tested on Mac and Linux (might work Windows)


## Options

Edit the 'b' file to switch CMake generators or change other options.


## Todos

1. Simple spinning cube

## Credits

This project was inspired by a nicely done similar project that has more batteries included: [asap](https://github.com/abdes/asap) by [@abdes](https://github.com/abdes)
