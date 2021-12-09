#ifndef QSTATE_H
#define QSTATE_H

#include "Grid.h"
#include "State.h"
#include "Action.h"

#include <string>

using namespace std;
class Action;
class QState: public State{
    public:
    Action* action;
    
    QState(State* state, Action* action);
    QState()=default;

    string getId() override;
    

};
#endif