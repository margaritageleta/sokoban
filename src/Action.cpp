#include "Action.h"

vector<State*> Action:: getNextStates(State* state) {
    vector <State*> states;
    const vector<coord2D (*)(coord2D coord)> actions = {moveRight,moveLeft,moveUp,moveDown};
    State* nextMove;
    for(auto action: actions){
        nextMove = new State(state);
        nextMove->setParent(state);
        states.push_back(getState(nextMove,action));
    }

    return states;
}

State* Action::getState(State* state, coord2D (*move)(coord2D coord)){
    state->movedBox = false;
    coord2D agentPosition = state->player;
    coord2D temptativePosition = move(agentPosition);
    if (state->isWall(temptativePosition)){
        return state;
    } else if (state->isBox(temptativePosition)){
        coord2D temptativeBoxPosition = move(temptativePosition);
        if (state->isWall(temptativeBoxPosition) || state->isBox(temptativeBoxPosition)){
            return state;
        } else {
            state->moveBox(temptativePosition, temptativeBoxPosition);
            state->movePlayer(agentPosition,temptativePosition);
            return state;
        }
    } else {
        state->movePlayer(agentPosition,temptativePosition);
        return state;
    }
}

coord2D Action::moveRight(coord2D coord){
    return make_pair(coord.first,coord.second+1);
}
coord2D Action::moveLeft(coord2D coord){
    return make_pair(coord.first,coord.second-1);
}
coord2D Action::moveUp(coord2D coord){
    return make_pair(coord.first - 1,coord.second);
}
coord2D Action::moveDown(coord2D coord){
    return make_pair(coord.first + 1,coord.second);
}

Action::Action(Move move){
    this->move = move;
    switch(move){
        case UP: this->action = moveUp; break;
        case DOWN: this->action = moveDown; break;
        case RIGHT: this->action = moveRight; break;
        case LEFT: this->action = moveLeft; break;
    }
}

string Action::getId(){
    switch(this->move){
        case UP: return "U";
        case DOWN: return "D";
        case RIGHT: return "R";
        case LEFT: return "L";
    }
}

State* Action::getState(State * state){
    State* nextMove = new State(state);
    return Action::getState(nextMove,this->action);
}