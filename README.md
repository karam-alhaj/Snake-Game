# Classes

## Snake

### Variables

    - locations (a list of each snake segment location)
    - velocity
    - length

### Functions

    - move_up
    - move_down
    - move_right
    - move_left
    - handle_collision_with_food

#### moving functions

    moves the snake to whatever direction, the movement is achieved by making the head moving and in the nex frame the segment behind the head will move to the location of the head and the segment behind it will follow it and so on.
    make sure not to allow the movement in the reverse direction (if the snake is moving up you can't move it down)

#### collision with food

    increase the length of the snake
    

## Food

### Functions

    -handle collision 

#### handle collision

it moves the food to a location inside the grid with no snake in it.
it recieves the snake's location as a parameter.

## Game Control

### Variables

    -score 
    
### Functions

    - main
    - draw snake
    - draw food
    - check collision
    - pause
    - end game

#### main

    this is the game loop function it clears the canvas and runs every frame.

#### Draw Functions

    this function draws the snake segments in a specific location.

#### check collision

    it will check if any two objects collide.

#### pause

    it will pause the game by simply skipping all the calculations until it's unpaused.

#### end game

    it will just close the game.
