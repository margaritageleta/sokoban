#include "QState.h"

QState::QState(State* state, Action* action):State(state){
    this->action = action;
}

string QState::getId(){
    string id = "";
    id = id + to_string(player.first) + to_string(player.second);
    for(int i=0; i < sizeH; i++){
        for(int j=0; j<sizeV; j++){
            if (grid[i][j]==tile["BOX"] or grid[i][j]==tile["BOXNSTG"]){
                id = id + to_string(i) + to_string(j);
            }
        }
    }
    /*for (coord2D & box : nBoxes){
            id = id + to_string(box.first) + to_string(box.second);
    }*/
    id = id + action->getId();
    return id;
}