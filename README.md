# Title project: Snake-Game
We held a meeting, where we learned about the project and the parts of the program, and then we thought about a suitable project structure for this program in terms of elements and functions.

However, in the end, after facing technical problems and errors, we arrived at the following structure:
# Classes

## Snake

### Variables

    - body (a vector for the snake, stores the snake head and tail's positions)

### Functions

    - move (a function for movement, it takes two arguments,
    one for input and one for a Boolean named ate_food)

#### moving functions

Moves the snake to whatever direction, the movement is achieved by pop_back the last tail in the snake, and insert a new body (which will be the head) at the beginning of the body (the snake) vector with the new position it gets from movement.

    
## Food

### Variables

    - food (a vector store the position of the food)
    - onSnake (a Boolean to avoid the food get a random position on the snake)

### Functions

    - handleCollision 

#### handle collision

It moves the food to a location inside the grid with no snake in it.
It receives the snake head and tail's locations as a parameter.

## Game Control

### Variables

    - gameOver (a Boolean to check whether the game is over or not.)
    - gamePaused (a Boolean to track the game state, is it paused or not.)
    - width (the width of the game border.)
    - height (the height of the game border.)
    - score (an integer track score)
    - gameLevel (an integer to track Game difficulty\level)
    - gameSpeed (an integer to use it in the Sleep() to delay the game, and every
    gameLevel the delay will decrease so the game will speed up)
    - lastInput (a char to track the last input, so the snake moves until the user
    change the direction of the snake.)
    - snake (an instance from the Snake class, makes a snake object.)
    - food (an instance from the Food class, makes a Food object.)
    - obstaclesX (an integer stores the obstacles X axis)
    - obstaclesY (an integer stores the obstacles Y axis)
    - obstacles (a vector stores the obstacle's positions)
    
### Functions

    - gameDraw
    - gameLogic
    - startGame
    - main

#### gameDraw

It handles everything about displaying the game  border, all the way to the obstacles.

#### gameLogic

It handles everything about the game logic, from input to Collision to game over.

#### startGame

It starts the game by containing the game loop and using the gameDraw and gameLogic functions.

#### main

It starts the game.