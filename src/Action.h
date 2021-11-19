#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <memory>
#include "State.h"

using namespace std;
typedef pair<int, int> coord2D;

class Action{
    private:
    static State* getState(State* state, coord2D (*move)(coord2D coord));
    static coord2D moveRight(coord2D coord);
    static coord2D moveLeft(coord2D coord);
    static coord2D moveUp(coord2D coord);
    static coord2D moveDown(coord2D coord);
    public:
    static vector<State*> getNextStates(State* state);
    
    
};

#endif