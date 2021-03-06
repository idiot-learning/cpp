# CPPND: Capstone Snake Game

This is a repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

## Final Output

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * For Linux: `sudo apt-get install libsdl2-dev` and `sudo apt-get install libsdl2-ttf-dev`
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Tested on
* Ubuntu 18.04 LTS

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

# Introduction

This is a basic snake game. It starts with asking username and then game window will pop-up with a food and snake as a dot on GUI. The user can use keyboard arrow keys to move the snake around and catch the food. As snake reaches to the food, its length start increasing and score as well. After that, another food (square dot) will pop-up at some random location on fixed sized window. Now, if snake somehow hits its body, then the game is over. The player has to terminate/close the window and check score on terminal or list of all users score in the `user_scores.txt` (inside build/). 

>Note: New score from the same user will overwrite the previous data.

## Code structure

The code is organized in modules:

- controller
- game
- gameMenu
- user
- renderer
- snake

| Class name | Purpose  |
|------------|----------|
| Controller | Interact with users, let users use keyboard to control the snake in the game. |
| Game       | Game class stores the state in the game, running in loops til end. |
| GameMenu   | Game Menu class handles command line player I/O. |
| User       | Basic information about the user and storing the the score. |
| Render     | Render the game to the screen. |
| Snake      | Contains attributes to keep track of the Snake speed, size, and location. |

## Rubric Points

### Loops, Functions, I/O

- The project demonstrates an understanding of C++ functions and control structures. I used a lot of control structures and loops throut the code. In the `user.cpp` for example, in the [`User::saveScore()`](https://github.com/kvnptl/Cpp-Nanodegree/blob/a465c24f7665106d99c14995d80626e50d8b14aa/Project_5_Sname_Game/src/user.cpp#L36) method, I used if-statements to check if the `user_scores.txt` file exists, if not, then the program will create one. A while-loop to write the player data to the file.

- The project accepts user input and processes the input. The *GameMenu* class is defined to accept user input and process the input. In `gameMenu.cpp` [`GameMenu::displayPlayerNamePrompt()`](https://github.com/kvnptl/Cpp-Nanodegree/blob/a465c24f7665106d99c14995d80626e50d8b14aa/Project_5_Sname_Game/src/gameMenu.cpp#L3), will let the user enter his player name to be used in the `user_scores.txt` file.

### Object Oriented Programming

- The project uses Object Oriented Programming techniques. The [*GameMenu*](https://github.com/kvnptl/Cpp-Nanodegree/blob/main/Project_5_Sname_Game/src/gameMenu.cpp) class and [*User*](https://github.com/kvnptl/Cpp-Nanodegree/blob/main/Project_5_Sname_Game/src/user.cpp) class are defined to improve the structure of the program. Classes use appropriate access specifiers for class members and utilize member initialization lists.

### Memory Management

- Modify the `Game` contructor to use `GameMenu` reference in the [`Game::Game(std::size_t grid_width, std::size_t grid_height, GameMenu &gm)`](https://github.com/kvnptl/Cpp-Nanodegree/blob/a465c24f7665106d99c14995d80626e50d8b14aa/Project_5_Sname_Game/src/game.cpp#L5) line.
