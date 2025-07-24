#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib> // For rand() and srand()
using namespace std;
class Food
{
public:
    vector<int> food;
    bool onSnake = false;

    vector<int> handleCollision(vector<vector<int>>& snakeBody, int width, int height)
    {
        do {
            onSnake = false; // reset for next time
            food = {rand() % width, rand() % height}; // Generate random food position
            for(int i = 0; i < snakeBody.size(); i++) // Check if the food position collides with the snake body
            {
                if(food[0] == snakeBody[i][0] && food[1] == snakeBody[i][1])
                {
                    onSnake = true;
                    break;
                }
            }
        }while(onSnake);
        return food;
    }
};