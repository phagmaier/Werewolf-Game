# WERWOLF GAME

## DESCRIPTION
Simple GUI for the game [werewolf](https://en.wikipedia.org/wiki/Mafia_(party_game)) that I 
made in c++ and raylib. My family plays it a lot over the holidays 
and people complain about the "narrator" of the game not making 
truly random decisions. They also wanted something graphical to display
the choices to make it easier and being the good son I am i made this crappy
project to make the game a little easier. 



## File Table

| File | Descripton |
| --------- | --------------------- |
| [Player.h](src/Player.h) | header file for Player class |
| [Selector.h](src/Selector.h) | header file for class that randomly selects and displays players |
| [Player.cpp](src/Player.cpp) | Contains logic for adding players at the beggining of the game |
| [main.cpp](src/main.cpp) | main logic  |
| [Selector.cpp](src/Selector.cpp) | logic for the Selector class that randomly assigns rolls to players |


## How to run
create a build directory in the root of the project cd into it and run cmake .. && make . && ./runme


