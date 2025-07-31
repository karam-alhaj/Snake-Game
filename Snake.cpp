#include <iostream>
#include <vector>

using namespace std;
class Snake{

    public:
    vector<vector<int>> body;
    

    void move(char input,bool ate_food){
        vector<int> head = this->body[0];

        switch (input)
        {
        case 'w':
            head[0] -= 1;
            break;
        case 'a':
            head[1] -= 1;
            break;
        case 'd':
            head[1] += 1;
            break;
        case 's':
            head[0] += 1;
            break;
        default:
            break;
        }
       if (!(head == this->body[0])){
           this->body.insert(body.begin(),head);    
       }
       else{
        this->body.pop_back();
       }

        if (!ate_food){
            this->body.pop_back();
        }

    }
    
    Snake(int len){
           for (int i=0;i<len;i++){
            this->body.push_back({i+5,5});
           }
    }
        

};