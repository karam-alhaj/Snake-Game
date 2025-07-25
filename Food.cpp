#include <iostream>
#include <vector>
using namespace std;
class Food
{
public:
    vector<int> food;
    bool onSnake = false;
    vector<int> handleCollision(const vector<vector<int>>& snakeBody, int width, int height)
    {
        int maxAttempts = width * height;
        int attempts = 0;
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
            attempts++;
            if (attempts >= maxAttempts) {
                return {-1, -1}; // No space left for food, return an invalid position
            }
        }while(onSnake);
        return food;
    }
    Food(const vector<vector<int>>& snakeBody, int width, int height)
    {
        food = handleCollision(snakeBody, width, height);
    }
};