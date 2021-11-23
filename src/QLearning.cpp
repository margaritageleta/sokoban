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
        if (Heuristic::getValue(state,2,1) > Heuristic::getValue(nextState,2,1)) return 1.0;
        if (Heuristic::getNBoxes(state) > Heuristic::getNBoxes(nextState)) return 2.0;
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
    double probablity = rand() / double(RAND_MAX);
    if (probablity < epsilon) return validActions[rand() % validActions.size()];
    else return chooseActionWithPolicy(state, validActions);
}

State* QLearning::takeAction(State* state){
    Action* action = getAction(state, epsilon);
    double reward = getReward(state, action);
    
    State* nextState = action->getState(state);
    double nextMaxQ = getNextMaxQ(nextState);
    
    QState* qstate = new QState(state,action);
    string id = qstate->getId();
    
    qtable[id] = qtable[id] + alpha * (reward + epsilon * nextMaxQ - qtable[id]);
    
    if (qtable[id] > normalizer) normalizer = qtable[id];
    
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

bool QLearning::executeEpisode(State* initialState){
    State* currentState = initialState;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(true){
        currentState = takeAction(currentState);
        if (currentState->isGoal()) return true;
        chrono::steady_clock::time_point now= chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(now - begin).count()>=100){
            //currentState->printGrid();
            return false;
        }
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

void QLearning::train(int nEpisodes){
    bool found = false;
    for(int i=0;i<nEpisodes;i++){
        cout << "RUNNING EPISODE " << i << endl;
        found = executeEpisode(initialState);
        cout << "SOLUTION FOUND " << found << endl;
        if (nEpisodes % 10 == 0) normalizeQ();
    }
}


