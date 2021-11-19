#ifndef STATE_H
#define STATE_H

#include "Grid.h"
#include "State.h"
#include "string"


using namespace std;

class State: public Grid{
    public:
    State *parent;
    int cost;
    

    int G;

    static State create(State state, State *parent);
    string getId();

    int getH();

    int getCost();

    bool equals(State state);

    bool isGoal(); 

    bool isInitialState();

};
#endif