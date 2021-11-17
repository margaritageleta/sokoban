#ifndef ACTION_H
#define ACTION_H

#include <list>
#include "State.h"

class Action{
    public:
    static list<State> getNextStates(State state);
    private:
    static State getRightState(State state);
    static State getUpState(State state);
    static State getDownState(State state);
};

#endif