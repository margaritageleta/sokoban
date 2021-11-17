#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <list>
#include "State.h"

using namespace std;
typedef pair<int, int> coord2D;

class Action{
    public:
    static list<State> getNextStates(State state);
    private:
    static State getState(State state, coord2D (*move)(coord2D coord));
    static coord2D moveRight(coord2D coord);
    static coord2D moveLeft(coord2D coord);
    static coord2D moveUp(coord2D coord);
    static coord2D moveDown(coord2D coord);
};

#endif