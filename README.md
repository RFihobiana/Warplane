
# Warplane Game

A 2D warplane game developed in C++ using the SFML (Simple and Fast Multimedia Library) framework.

| Intro | Menu | Game | Pause |
| :---: | :---: | :---: | :---: |
| ![Intro Preview][intro_screen_asset] | ![Menu Preview][menu_screen_asset] | ![Game Preview][game_screen_asset] | ![Pause Preview][pause_screen_asset] |

## Overview

This project demonstrates a simple state-driven game architecture with:

- Intro screen, menu, gameplay, and pause states
- Custom GUI components for buttons and labels
- Command pattern support for decoupled input handling
- Resource management for textures and fonts
- SFML-based rendering, event handling, and window management

## Features

- Player-controlled warplane movement
- Menu navigation with selectable buttons
- Pause and resume support
- Frame-rate display and debugging info
- Modular state stack implementation

## Requirements

- C++20 or later
- SFML 2.5 or newer
- Meson build system

## Building

```bash
meson setup build
meson compile -C build
```

## Running

```bash
./build/warplane
```

## Controls

- **WASD / Arrow keys**: Move the player plane in gameplay
- **P**: Show player position
- **ESC**: Quit the game
- **Up / Down / W / S**: Navigate menu options
- **Enter / Space / E**: Select a menu button

## Project Structure

```txt
.
├── assets
│   ├── data
│   ├── fonts
│   └── images
│       └── preview
├── include
│   ├── command
│   ├── entity
│   ├── GUI
│   ├── resources
│   └── states
└── src
    ├── command
    ├── entity
    ├── GUI
    └── states
```

## Notes

- The game uses a state stack so states can be pushed, popped, and replaced cleanly.
- GUI selection state is preserved while the menu is active.

[game_screen_asset]: ./assets/images/preview/game_screen.png
[intro_screen_asset]: ./assets/images/preview/intro.png
[menu_screen_asset]: ./assets/images/preview/menu.png
[pause_screen_asset]: ./assets/images/preview/pause.png