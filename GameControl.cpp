#include <iostream>
#include <vector>
#include "Food.cpp"
#include <ctime>
#include <cstdlib>
#include <cstdlib>
#include <thread>
#include <windows.h>
#include <fcntl.h>
#include "Snake.cpp"
using namespace std;
#include <conio.h>

class GameControl
{
    public:
    bool gameOver = false;
    bool gamePaused = false;
    int width = 13;
    int height = 25;
    int score = 0;
    int gameSpeed = 100; // Speed of the game in milliseconds
    int gameLevel = 1; // Initial game level
    enum eDirection {ESC, STOP, UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd'};
    eDirection dir;
    eDirection lastDir = RIGHT; // Default direction is right
    Snake* snake = new Snake(2);
    Food* food = new Food(snake->body, width, height);
    int obstaclesX = rand() % width;
    int obstaclesY = rand() % height;
    vector<vector<int>> obstacles = {{obstaclesX, obstaclesY}, {obstaclesX + 1, obstaclesY}, {obstaclesX + 2, obstaclesY}}; // Initialize with three obstacles
    GameControl(){}

    // Add this above your GameControl class
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    void setColor(int color) {
        SetConsoleTextAttribute(hConsole, color);
    }
    void resetColor() {
        SetConsoleTextAttribute(hConsole, 15); // Reset to white on black
    }

    void input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
                case 'w':
                    dir = UP;
                    break;
                case 's':
                    dir = DOWN;
                    break;
                case 'a':
                    dir = LEFT;
                    break;
                case 'd':
                    dir = RIGHT;
                    break;
                case 'p':
                    dir = STOP; // Pause the game
                    break;
                case 'q':
                    dir = ESC; // Quit the game
                    break;
            }
        }
    }

    void gameDraw()
    {
        system("cls"); // Clear the console for the next frame
        for (int i = 0; i <= width; i++)
        {
            for (int j = 0; j <= height; j++)
            {
                bool filledSpace = false;
                if (i == snake->body[0][0] && j == snake->body[0][1])
                {
                    setColor(2); // Set color for snake head
                    cout << '0'; // Print snake head
                    filledSpace = true; // Mark that a space is filled
                    resetColor(); // Reset color after printing
                }
                if (gameLevel > 1 )
                {
                    for (const auto& obstacle : obstacles)
                    {
                        if (obstacle[0] == i && obstacle[1] == j)
                        {
                            setColor(13); // Set color for obstacles
                            cout << 'X'; // Print obstacle
                            filledSpace = true; // Mark that a space is filled
                            resetColor(); // Reset color after printing
                        }
                    }
                }
                for (int k = 1; k < snake->body.size(); k++)
                {
                    if (snake->body[k][0] == i && snake->body[k][1] == j)
                    {
                        setColor(2); // Set color for snake body
                        cout << 'o'; // Print snake body
                        filledSpace = true;
                        resetColor(); // Reset color after printing
                    }
                }
                if (i == 0 || i == width || j == 0 || j == height)
                {
                    setColor(8); // Set color for walls
                    cout << '#';
                    filledSpace = true; // Mark that a space is filled
                    resetColor(); // Reset color after printing
                }

                else if (food->food[0] == i && food->food[1] == j)
                {
                    setColor(12); // Set color for food
                    cout << 'A'; // Print food
                    filledSpace = true;
                    resetColor(); // Reset color after printing
                }
                else
                {
                    if (!filledSpace)
                    {
                        cout << ' '; // Print empty space
                    }
                }
            }
            cout << endl;
        }
        cout << "===========\n Level: " << gameLevel << " \n===========" << endl;
        cout << "Score: " << score << endl;
        cout << "Press 'w', 'a', 's', 'd' to move the snake." << endl;
        cout << "Press 'q' to quit." << endl;
        if (gamePaused)
        {
            cout << "====================\n The game is paused. Press 'p' to resume.\n====================" << endl;
        }
        else
        {
            cout << "Press 'p' to pause the game." << endl;
        }
    }
    void gameLogic(eDirection dir)
    {
        if (dir == ESC)
        {
            gameOver = true; // Quit the game
            return;
        }
        bool collision = snake->body[0] == food->food;
        if (collision)
        {
            food->handleCollision(snake->body, width, height);
            score += 10;
            if (score % 30 == 0 && gameSpeed > 20) // Increase speed every 30 points, but not below 20 ms
            {
                gameSpeed -= 20; // Increase game speed
                gameLevel++; // Increase game level
                if (gameLevel > 2)
                {
                    int o = rand() % width;
                    int c = rand() % height;
                    obstacles.push_back({o, c}); // Add new obstacle
                    obstacles.push_back({o + 1, c}); // Add another obstacle at the same position
                    obstacles.push_back({o + 2, c}); // Add another obstacle at the same position
                }
            }
        }
        snake->move(dir, collision);
        if (snake->body[0][0] <= 0)
        {
            snake->body[0][0] = width - 1; // Wrap around to the other side
        }
        else if (snake->body[0][0] >= width)
        {
            snake->body[0][0] = 1; // Wrap around to the other side
        }
        if (snake->body[0][1] <= 0)
        {
            snake->body[0][1] = height - 1; // Wrap around to the other side
        }
        else if (snake->body[0][1] >= height)
        {
            snake->body[0][1] = 1; // Wrap around to the other side
        }
        if (gameLevel > 1)
        {
            for (int i = 0; i < obstacles.size(); i++)
            {
                if (snake->body[0] == obstacles[i])
                {
                    gameOver = true; // Game over if snake collides with an obstacle
                }
            }
        }
        for (int i = 1; i < snake->body.size(); i++)
        {
            if (snake->body[0] == snake->body[i])
            {
                gameOver = true; // Game over if snake collides with itself
            }
        }
    }
    void startGame()
    {
        while (!gameOver)
        {
            gameDraw();
            Sleep(gameSpeed); // Sleep for the specified game speed
            if (_kbhit()) // Check if a key is pressed
            {
                input(); // Get the input from the user

                // Handle pause toggle immediately
                if (dir == STOP)
                {
                    gamePaused = !gamePaused;
                }
                else if (!gamePaused)  // Only update movement if not paused
                {
                    if (dir == UP && lastDir == DOWN ||
                        dir == DOWN && lastDir == UP ||
                        dir == LEFT && lastDir == RIGHT ||
                        dir == RIGHT && lastDir == LEFT)
                    {
                        // Prevent the snake from moving in the opposite direction
                        continue; // Skip the game logic if the direction is opposite
                    }
                    else
                    {
                        gameLogic(dir); // Call game logic with the pressed key
                    }
                    lastDir = dir; // Update last input
                }
            }
            else if (!gamePaused)  // Only use last input if not paused
            {
                gameLogic(lastDir); // Use the last input if no new input is given
            }

            // Game over handling
            if (gameOver)
            {
                cout << "===========\n Game Over! \n===========" << endl;
                cout << "Your score is: " << score << endl;
            }
        }
    }
};

int main(){
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    GameControl* game = new GameControl();
    game->startGame();
    return 0;
}
