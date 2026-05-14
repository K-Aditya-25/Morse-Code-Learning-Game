# Morse Code Learning Game

This project is a Raspberry Pi Pico Morse code learning game created for the
Microprocessor Systems Assignment 2. It teaches Morse code through a sequence of
increasingly difficult levels, using a single GPIO button for dot/dash input and
an RGB LED to show game state and remaining lives.

## Project Overview

When the board starts, the game prints a welcome banner, gameplay instructions,
the group number, and the Morse sequences used to select each level. The RGB LED
starts blue to show that no level has been selected.

Players enter Morse code with the GP21 button:

- Short press: Morse dot (`.`)
- Long press: Morse dash (`-`)
- No input for more than 1 second: Morse space
- No input for more than 2 seconds: current sequence is submitted
- No input for more than 9 seconds: the game times out and must be restarted

Each level requires five correct Morse sequences in a row to advance. The player
starts with three lives, gains a life for a correct answer up to the maximum of
three, and loses a life for an incorrect answer. If all lives are lost, the game
prints a game-over message and player statistics.

## Levels

| Level | Selection Code | Description |
| --- | --- | --- |
| 1 | `.----` | Shows an alphanumeric character and its Morse equivalent. The player repeats the displayed Morse code. |
| 2 | `..---` | Shows an alphanumeric character only. The player must remember and enter its Morse code. |
| 3 | `...--` | Shows a word and its Morse equivalent. The player repeats the displayed Morse code. |
| 4 | `....-` | Shows a word only. The player must enter the full Morse sequence from memory. |

Levels 3 and 4 are the optional advanced levels described in the project report.
Completing all four levels prints a game-complete message and final statistics.

## RGB LED States

| Colour | Meaning |
| --- | --- |
| Blue | Waiting for a level selection |
| Green | Active game with 3 lives |
| Yellow | Active game with 2 lives |
| Orange | Active game with 1 life |
| Red | Game over |

## Hardware

- Raspberry Pi Pico / RP2040 target
- GP21 button input for Morse entry
- WS2812 RGB LED on GPIO 28
- USB or UART serial output for the text interface

## Repository Structure

| File | Purpose |
| --- | --- |
| `assign02.c` | Main C game logic, level selection, answer checking, LED handling, stats output, and Pico startup flow. |
| `assign02.S` | ARM assembly logic for GPIO setup, interrupt handling, button timing, and alarm handling. |
| `morse_code.c` / `morse_code.h` | Morse lookup tables plus encode/decode helpers for alphanumeric characters. |
| `welcome.c` / `welcome.h` | Startup banner, instructions, and level-selection menu. |
| `CMakeLists.txt` | Pico SDK build target configuration. |
| `Project Report.pdf` | Project report used as the source for this README. |

## Build and Run

This project is intended to be built with the Raspberry Pi Pico SDK and CMake.
From a configured Pico SDK environment:

```sh
mkdir -p build
cd build
cmake ..
make
```

After building, flash the generated UF2 file to the Pico. Open the USB or UART
serial console to view the welcome screen, prompts, game feedback, and stats.

## Gameplay Summary

1. Start the board and wait for the welcome screen.
2. Enter the Morse sequence for the level you want to play.
3. Use GP21 to enter dots, dashes, and spaces.
4. Submit each sequence by pausing long enough for the game to complete the
   current answer.
5. Complete five correct answers in a row to progress.
6. Finish all levels to complete the game, or lose all lives to reach game over.

## Development Workflow

The project was developed collaboratively using GitLab branches and merge
requests. Work was divided across project workflow, GitLab management,
documentation, demonstration, and code ownership. Development progressed over
four weeks from repository setup and GPIO/interrupt foundations through Morse
encoding/decoding, RGB LED support, level implementation, UI output, report
completion, and final demonstration.

## Contributors

- Flynn Clyne
- Parker Jack Kavanagh
- Aditya Kharbanda
- Raaghav Sawhney
- Inam Syed
