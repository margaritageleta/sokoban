#include "QLearning.h"

initializer_list<Move> allMoves = { UP, DOWN, RIGHT, LEFT};

QLearning::QLearning(State* initialState, double alpha, double gamma, double epsilon){
    this->initialState = initialState;
    this->alpha = alpha;
    this->gamma = gamma;
    this->epsilon = epsilon;
}

double QLearning::getReward(State* state, Action* action){
    State* nextState =  action->getState(state);
    if((! nextState->equals(state)) && (! nextState->isAnyBoxInDeadlock())){
        if (nextState->isGoal()) return 100.0;
        if (Heuristic::getNBoxes(state) > Heuristic::getNBoxes(nextState)) return 2.0;
        if(state->movedBox) return 1.0;
        return 0.0;
    }
    return -1.0;
}

vector<Action*> QLearning::getValidActions(State* state){
    vector<Action*> validActions;
    for (Move move: allMoves){
        Action* a = new Action(move);
        if (getReward(state,a) != -1.0) {
            validActions.push_back(a);
        }
    }
    return validActions;
}

Action* QLearning::chooseActionWithPolicy(State* state, vector<Action*> actions){
    double maxQ = -100000000;
    Action * next;
    for(Action* a: actions){
        QState* qstate = new QState(state, a);
        string id = qstate->getId();
        if (!qtable.count(id)){
            qtable[id] = 0.0;
        }
        if(qtable[id] > maxQ){
            maxQ = qtable[id];
            next = a;
        }
    }
    return next;
}

Action* QLearning::getAction(State* state, double epsilon){
    vector<Action*> validActions = getValidActions(state);
    double probablity = Random::getProbablity(); 
    if (probablity < epsilon){
        int index = Random::getBetweenRange(0,validActions.size()-1);
        return validActions[index];
    }
    else return chooseActionWithPolicy(state, validActions);
}

State* QLearning::takeAction(State* state){
    Action* action = getAction(state,epsilon);
    double reward = getReward(state, action);
    
    State* nextState = action->getState(state);
    double nextMaxQ = getNextMaxQ(nextState);
    
    QState* qstate = new QState(state,action);
    string id = qstate->getId();
    
    qtable[id] = qtable[id] + alpha * (reward + epsilon * nextMaxQ - qtable[id]);
    
    if (qtable[id] > normalizer) normalizer = qtable[id];
    
    return nextState;
}

State* QLearning::takeSuboptimalAction(State* state){
    
    Action* action = getAction(state, 0);
    State* nextState = action->getState(state);
    
    return nextState;
}

double QLearning::getNextMaxQ(State* nextState){
    double maxQ = -1000000;
    for(Action* a: getValidActions(nextState)){
        QState* qs = new QState(nextState,a);
        string id = qs->getId();
        if (!qtable.count(id)){
            qtable[id] = 0.0;
        }
        if(maxQ < qtable[id]) maxQ = qtable[id];
    }
    return maxQ;
}

bool QLearning::executeEpisode(State* initialState, int nMaxMoves){
    State* currentState = initialState;
    int moves = 0; 
    while(true){
        currentState = takeAction(currentState);
        if (currentState->isGoal()) return true;
        if (moves == nMaxMoves){
            //currentState->printGrid();
            return false;
        }
        moves ++;
        
    }
    return false;
}

void QLearning::normalizeQ(){
    map<string,double> qtable2;
    for (pair<string,double> qpair: qtable){
        if (qtable[qpair.first] != 0.0) qtable2[qpair.first] = qpair.second / normalizer;
    }
    qtable = qtable2;
}

void QLearning::train(){
    bool found = false;
    int timesFound = 0;
    while(true){
        found = executeEpisode(initialState, 1000);
        if (timesFound > 50) break;
        if (found) timesFound++;
    }
}


