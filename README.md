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
* CMake - builds Ninja, Xcode, Makefiles, etc.
* OpenGL 3
* Orthodox C++
* Tested on Mac (should work on Linux and Windows)


## Options

Edit the 'b' file to switch CMake generators.


## Todos

1. Get a few more themes in there
2. Embed the source location so fonts can load from that
3. Demonstrate proportional fonts
4. More fonts
5. Simple spinning cube

## Credits

This project was inspired by a nicely done similar project that has more batteries included: [asap](https://github.com/abdes/asap) by [@abdes](https://github.com/abdes)
