
# Warplane Game

A 2D warplane game developed with SFML (Simple and Fast Multimedia Library) in C++.

![Game Screen](./assets/images/preview/game_screen.png)

## Features

- Player-controlled warplane
- Frame Rate Per Seconds tracking

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

- **Arrow Keys**: Move
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
