# Arcade - Graphical / Game Library usage

### This document will explain how to create your own graphical / game library.

# Introduction

Arcade relies on the use of a core to handle libraries. Those libraries are
loaded dynamically at runtime. This allows you to create your own graphical /
game library by following those steps.

# Implementation

1. Insert your library in the `lib` folder.
2. The library must be named as follows: `lib_arcade_[library_name].so`.
3. This library must either implement `IDisplay` or `IGame`.
4. The library must export two main functions in order to be loaded and
   destroyed when needed:
```c++

// For a graphical library
extern "C"
{
    void *createDisplay() {
        NCurses *lib = new NCurses();

        lib->init();
        return lib;
    }

    void deleteDisplay(void *display) {
        NCurses *lib = reinterpret_cast<NCurses *>(display);

        lib->exit();
        delete lib;
    }
}

// For a game library
extern "C"
{
    Arcade::IGame *createGame() {
        return new Pacman();
    }

    void deleteGame(Arcade::IGame *display) {
        delete dynamic_cast<Pacman *>(display);
    }
}
```
As shown above, it is recommended to implement a `init` and `exit` function to
avoid constructor and destructor call issues.
You also can use `void *` or `<MYLIB> *` as delete function parameter.
It is also preferred not to use unique pointers as they won't be handled as
we expect them to be.

# Assets

**GAME LIBRARY ONLY** <br />
In `ASSETS/[YOUR_GAME_NAME]/[GRAPHICAL_LIBRARY_NAME]`, add your assets.


**GRAPHICAL LIBRARY ONLY** <br />
You might want to implement texture loading as follows:
- All your assets are fetched from the `ASSETS` folder.
- The assets are loaded from the `ASSETS/[GRAPHICAL_LIBRARY_NAME]/[GAME_NAME]`
  folder. (You can get the game name from the `IGame` interface)

# Misc

- Make sure to link all needed libraries in your .so file.
- Arcade core uses C++20 features.