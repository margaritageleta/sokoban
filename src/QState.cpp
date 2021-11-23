#include "QState.h"

QState::QState(State* state, Action* action):State(state){
    this->action = action;
}

string QState::getId(){
    string id = "";
    id = id + to_string(player.first) + to_string(player.second);
    for (coord2D & box : nBoxes){
            id = id + to_string(box.first) + to_string(box.second);
    }
    id = id + action->getId();
    return id;
}