# ZeldaINF

**INF01202 - Algoritmos e Programação - UFRGS - 2023/1**

## About
A simple 2D adventure game, inspired by the classic "The Legend of Zelda", developed in C with the Raylib graphics library. The goal of the game is to guide the hero through multiple levels, defeating all the monsters.

## Features

* **Character Movement:** Control the hero on a 2D grid-based map, with obstacle collision detection.

* **Multiple Levels:** Dynamic loading of different levels from text files (`level1.txt`, `level2.txt`, etc.).

* **Simple AI Enemies:** Monsters that move randomly around the environment, posing a challenge to the player.

* **Combat System:** Short-range sword attacks to defeat monsters.

* **Life and Scoring System:** The player starts with 3 lives and earns 100 points for each monster defeated.

* **Persistent High Scores:** The top 5 scores are saved in a binary file (`ranking.bin`) and loaded each time the game is played.

* **Interface Screens:** The game has a well-defined screen flow:

  * **Main Menu** with options to start a new game and exit.
  * **Name Entry Screen**, which appears when the player achieves a new record.
  * **Game End Screen** (Victory or Defeat) which displays the final score.

## How to Compile and Run
To compile and run the project, you will need:

* A C compiler, such as GCC.
* The Raylib library configured in your environment.

You must set the correct path to where the Raylib library is installed on your computer. After compiling (`ctrl + shift + B`), an executable named `zinf.exe` will be created.

To run, open a terminal in the project root folder and run the following command:

```bash
.\zinf.exe
```
## Project Structure

The code was organized modularly to facilitate maintenance and understanding, separating responsibilities:

* `main.c`: Entry point and main game loop, responsible for managing the screens.

* `renderer.c`: Module responsible for loading and drawing all the game's textures.

* `player.c` / `monster.c` / `combat.c`: Modules containing the game's main logic (gameplay).

* `level.c`: Responsible for loading maps from text files.

* `scoreboard.c`: Manages reading and writing the high score file.

* `*_screen.c`: Each screen file (such as `menu_screen.c`, `endscreen.c`, `enter_name_screen.c`) manages its own state, logic, and drawing, in an encapsulated manner.

## Gameplay Loop

In the menu screen, the player can either start a new game or exit, closing the application.

<img width="1205" height="895" alt="Captura de tela 2025-07-30 024952" src="https://github.com/user-attachments/assets/2a7baf5e-9435-45ff-9df4-879087ff5619" />

After starting a new game, the player can control the character and start chasing and killing the monsters. If the player gets hit 3 times, the character loses all 3 lives and dies, triggering the "game over" screen.

<img width="1198" height="893" alt="Captura de tela 2025-07-30 025020" src="https://github.com/user-attachments/assets/b3630a40-64ce-4460-b941-b532d30a8711" />

<img width="1200" height="890" alt="Captura de tela 2025-07-30 025059" src="https://github.com/user-attachments/assets/a7cad483-b2e7-4eec-9ba3-83d0403675e5" />

If the player's score is high enough to replace one of the five top scores from the current scoreboard, a screen is called to ask for the player's name.

<img width="1200" height="891" alt="Captura de tela 2025-07-30 025242" src="https://github.com/user-attachments/assets/59ebf812-62b6-43db-b216-0b0c41f0f546" />

The endgame screen contains the current updated scoreboard, a unique message indicating the player's death or win, and the option to play again from the start or to exit the game.

<img width="1200" height="894" alt="Captura de tela 2025-07-30 025314" src="https://github.com/user-attachments/assets/dcbd181b-f51d-4b29-8ace-baf59995b0d1" />

## Video Demo

working on it...

## License

Distributed under the MIT license. See `LICENSE.txt` for more information.

## Contact

Leonardo Santos - <leorsantos2003@gmail.com>
