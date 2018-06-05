Pentris

Pentris is a game heavily inspired by Tetris, the main difference being that it uses pentominos, whereas Tetris uses tetrominos.


I created Petris as an attempt / learning experience in creating a game without relying on a prebuilt engine. 
Pentris makes effective use of SDL library, which creates the game window, and provides an easy way to render the game's images.
Version 1.0 is very basic, but contains a functional core game. I plan on adding more to the game, further familiarising myself with the SDL library. Currently the project is a Visual Studio solution.


Basic gameplay
	A pentomino piece will appear at the top of the game board. the player controls this piece as it falls, until it cannot fall further and it locks itself into place on the board. As one pentomino locks into place, another will appear on the board for the player to control. If the player manages to fill an entire row of the game board, it will disappear, and all rows above will shift down accordingly. If the player manages to stack pieces too high, and there is no space for a new piece to be played, the game will end.

Controls
Left - moves pentomino piece to the left.
right - moves pentomino piece to the right.
down - moves pentomino piece down. This will lock the Pentomino if it cannot move further down.
space - rotates pentomino piece clockwise 90 degrees.
P - pauses the game.



Features I would like to add:
Audio - music and sound effects. SDL has audio functionality within its library.
Menu - Create a title screen, rather than forcing the game upon execution.
Game Over - currently the program exits when the player loses. I would like a proper game over screen, with the ability to play again.
High Score - Keep track of the highest score achieved. I would like to Utilize a "save" file to keep track of the score even when the program is exited.
Colored Tiles - currently all tiles use the same red sprite. I think I would like to make each pentomino type have a corresponding color.

These are the main things I want to add for now. I'm sure I will come up with more as I continue working on it more.