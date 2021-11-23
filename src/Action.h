#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <memory>
#include "State.h"

using namespace std;
typedef pair<int, int> coord2D;

enum Move{ UP=0, DOWN=1, RIGHT=2, LEFT=3, Last};

class Action{
    private:
    static State* getState(State* state, coord2D (*move)(coord2D coord));
    static coord2D moveRight(coord2D coord);
    static coord2D moveLeft(coord2D coord);
    static coord2D moveUp(coord2D coord);
    static coord2D moveDown(coord2D coord);
    public:
    static vector<State*> getNextStates(State* state);
    
    coord2D (*action)(coord2D coord);
    Move move;
    Action(Move move);
    string getId();
    State* getState(State* state);
        
};

#endif