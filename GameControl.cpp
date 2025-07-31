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



char getch() {
    char buf = 0;
    struct termios old = {0};

    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcsetattr()");

    // Set terminal to raw mode
    old.c_lflag &= ~ICANON; // disable buffering
    old.c_lflag &= ~ECHO;   // disable echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    // Read 1 character
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");

    // Restore old settings
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return buf;// Save old terminal settings
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);

    // Turn off buffering and echo
    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set non-blocking read
    int oldf = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) < 0) {
        ch = 0;  // No key pressed
    }

    // Restore settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}

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
               
                system("clear");
            }
        }

};

int main(){

    GameControl* game = new GameControl();
    game->startGame();
    return 0;
}