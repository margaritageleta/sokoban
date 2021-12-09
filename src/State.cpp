#include "State.h"


void State::setParent(State* parent){
        this->parent = parent;
        this->cost = 1;
        this->G = parent->G + this->cost;
}

string State::getId(){
    string id = "";
    id = id + to_string(player.first) + to_string(player.second);
    for (coord2D & box : nBoxes){
            id = id + to_string(box.first) + to_string(box.second);
    }
    return id;
}

State::State(State* s1):Grid(s1){
    parent = s1->parent;
    cost = s1->cost;
    G = s1->G;
}

int State::getH(){
    return Heuristic::getValue(this, 2,200);
}

int State::getCost(){
    if (isInitialState()) return 0;
    return cost;
}

bool State::equals(State* state){
    if ((player.first != state->player.first) || (player.second != state->player.second)){
        return false;
    }
    for( int i = 0; i < nBoxes.size(); i++){
        bool found = false;
        for( int j = 0; j < nBoxes.size(); j++){
            if ((nBoxes[i].first == state->nBoxes[j].first) && (nBoxes[i].second == state->nBoxes[j].second)){
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool State::isGoal(){
    for (coord2D box : nBoxes){
        if(!isBoxInStorage(box)) return false;
    }
    return true;
}

bool State::isSubGoal(int currentBoxes){
    if (this->isGoal()) return true;
    if(!this->parent) return false;
    return Heuristic::getNBoxes(this) < currentBoxes;
}

bool State::isInitialState(){
    return !parent;
}


