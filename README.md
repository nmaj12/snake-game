# Snake Game in C++

A simple console-based Snake game written in C++ using basic libraries and Windows console input handling.

## Features

- Classic snake gameplay in terminal
- Keyboard controls (WASD)
- Food spawning system
- Score tracking
- Tail growth mechanic
- Collision detection (walls + self)

---

## Controls

| Key | Action |
|-----|--------|
| W   | Move up |
| A   | Move left |
| S   | Move down |
| D   | Move right |
| X   | Exit game |

---

## How to Run

### Requirements
- Windows OS (uses `<windows.h>` and `_kbhit()`)
- C++ compiler (e.g. g++, MSVC)

### Compile & run (g++ example)
```bash
g++ snake.cpp -o snake
snake.exe
