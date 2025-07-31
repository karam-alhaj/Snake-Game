#include <iostream>
#include <vector>
#include "Food.cpp"
#include <cstdlib>
#include <thread>
#include <termio.h>
#include <unistd.h>
#include <fcntl.h>
#include "Snake.cpp"
using namespace std;
#include <conio.h>






class GameControl{

    public:
    GameControl(){
        
    }
        void startGame() {
    
            Food* food = new Food({{0, 0}}, 9, 19); // Example snake body with one segment at (0, 0)
            Snake* snake = new Snake(2);
            while (true){
                               for (int i = 0; i <= 10; i++){
                    for (int j = 0; j <= 20; j++)
                    {
                        for(int k=0;k<snake->body.size();k++){
                            if (snake->body[k][0] == i && snake->body[k][1] == j){
                                cout<<'#';
                            }
                        }

                        if (i==0 || i==10 || j==0 || j==20){
                            cout<<'*';
                        }

                        else if (food->food[0] == i && food->food[1] == j) {
                            cout << 'o'; // Print food
                        } 
                        

                        else {
                            cout << ' '; // Print empty space
                        }
                    }
                    cout <<endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
               char pressed = getch();
               cout<<pressed;
                bool collision = snake->body[0]==food->food;
                if(collision){
                   food->handleCollision(snake->body,10,10);
                }
               snake->move(pressed,collision);
               
                system("cls");
            }
        }

};

int main(){

    GameControl* game = new GameControl();
    game->startGame();
    return 0;
}