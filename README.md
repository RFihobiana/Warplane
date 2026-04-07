
# Warplane Game

A 2D warplane game developed with SFML (Simple and Fast Multimedia Library) in C++.

| Intro | Game |
| :---: | :---: |
| ![Intro Screen][intro_screen_asset] | ![Game Screen][game_screen_asset] |

## Features

- Player-controlled warplane
- Frame Rate Per Seconds tracking
- Seperate command so we can give order to anyone at anytime
- Divide game into states

## Requirements

- C++11 or later
- SFML 2.5+
- Meson

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

- **WASD Keys**: Move
- **P**: Show player position
- **ESC**: Quit

## Project Structure

```txt
warplane/
├── src/
│   ├── main.cpp
│   ├── game.cpp
│   └── player.cpp
├── include/
│   ├── game.h
│   └── player.h
└── CMakeLists.txt
```

[game_screen_asset]: ./assets/images/preview/game_screen.png
[intro_screen_asset]: ./assets/images/preview/intro.png