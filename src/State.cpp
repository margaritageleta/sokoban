#include "State.h"
#include "Grid.h"
#include "Heuristic.h"



State State::create(State state, State *parent){
        state.parent = parent;
        state.cost = 1;
        if (parent) (*parent).G + state.cost;
        else state.G = state.cost;
        return state;
}
string State::getId(){
    string id = "";
    id = id + to_string(player.first) + to_string(player.second);
    for (coord2D & box : nBoxes){
            id = id + to_string(box.first) + to_string(box.second);
    }
    return id;
}


State State::*parent = nullptr;

int State::getH(){
    return Heuristic::getValue(*this, 2);
}

int State::getCost(){
    if (isInitialState()) return 0;
    return cost;
}

bool State::equals(State state){
    if ((player.first != state.player.first) || (player.second != state.player.second)){
        return false;
    }
    for( int i = 0; i < nBoxes.size(); i++){
        bool found = false;
        for( int j = 0; j < nBoxes.size(); j++){
            if ((nBoxes[i].first == state.nBoxes[j].first) && (nBoxes[i].second == state.nBoxes[j].second)){
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool State::isGoal(){
    for (coord2D & box : nBoxes){
        if(!isBoxInStorage(box)) return false;
    }
    return true;
}

bool State::isInitialState(){
    if(parent) return false;
    return true;
}


