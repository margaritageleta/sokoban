#include "Action.h"
#include "State.h"

using namespace std;
typedef pair<int, int> coord2D;

vector<State> Action:: getNextStates(State state) {
    vector <State> states;
    states.push_back(getState(state,*moveRight));
    states.push_back(getState(state,*moveLeft));
    states.push_back(getState(state,*moveUp));
    states.push_back(getState(state,*moveDown));
    return states;
}

State Action::getState(State state, coord2D (*move)(coord2D coord)){
    coord2D agentPosition = state.player;
    coord2D temptativePosition = move(agentPosition);
    if (state.isWall(temptativePosition)){
        return state;
    } else if (state.isBox(temptativePosition)){
        coord2D temptativeBoxPosition = move(temptativePosition);
        if (state.isWall(temptativeBoxPosition) || state.isBox(temptativeBoxPosition)){
            return state;
        } else {
            state.moveBox(temptativePosition, temptativeBoxPosition);
            state.movePlayer(agentPosition,temptativePosition);
            return state;
        }
    } else {
        state.movePlayer(agentPosition,temptativePosition);
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
