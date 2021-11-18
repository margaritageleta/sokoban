#ifndef STATE_H
#define STATE_H

#include "Grid.h"
#include "State.h"

class State: public Grid{
    public:
    State *parent;
    int cost;

    static State create(State state, State *parent);

    int getH();

    int getCost();

    int getG();

    bool equals(State state);

    bool isGoal(); 

};
#endif