#ifndef STATE_H
#define STATE_H

#include "string"
#include "Grid.h"
#include "Heuristic.h"


using namespace std;

class State: public Grid{
    public:
    State* parent=nullptr;
    int cost = 0;
    
    int G = 0;

    State(Grid* grid):Grid(grid){};
    State()=default;
    State(State* s1);
    void setParent(State* parent);

    virtual string getId();

    int getH();

    int getCost();

    bool equals(State* state);

    bool isGoal();
    bool isSubGoal(int currentBoxes);

    bool isInitialState();

};
#endif