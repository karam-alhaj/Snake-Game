#include <iostream>
#include <string>
#include <vector>
#include <random>
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
            food = {rand() % width, rand() % height};
            for(int i = 0; i < snakeBody.size(); i++)
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