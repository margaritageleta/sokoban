#include "State.h"
#include "Grid.h"
#include "Heuristic.h"



State State::create(State state, State *parent){
        state.parent = parent;
        state.cost = 1;
        return state;
}

State State::*parent = nullptr;

int State::getH(){
    return Heuristic::getValue(*this, 2);
}

int State::getCost(){
    if (parent) return 0;
    if ((*parent).equals(*this)) cost += 10000000000000000;
    for (coord2D coord : nBoxes){
        if(isBoxInFreeCorner(coord)) cost+=10000000000000000;
    }
    return cost;
}

int State::getG(){

    if (parent) return getCost();
    else return (*parent).getG() + getCost();
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


