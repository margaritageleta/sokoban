#include "QStar.h"

initializer_list<QSMove> allQSMoves = { QUP, QDOWN, QRIGHT, QLEFT, ASTAR};

QStar::QStar(State* initialState, double alpha, double gamma, double epsilon, double decayFactor){
    this->initialState = initialState;
    this->alpha = alpha;
    this->gamma = gamma;
    this->epsilon = epsilon;
    this->decayFactor = decayFactor;
    this->random = Random();
}

double QStar::getReward(State* state, Action* action){
    State* nextState =  action->getQSState(state);
    if((!nextState->equals(state))){
        if(nextState->isAnyBoxInDeadlock()) return 0.0;
        if (nextState->isGoal()) return 100.0;
        if (Heuristic::getNBoxes(state) > Heuristic::getNBoxes(nextState)) return 20.0;
        //if(nextState->movedBox && state->movedBox) return 10.0;
        if(nextState->movedBox) return 5.0;
        //if (Heuristic::getValue(state,2,1) > Heuristic::getValue(nextState,2,1)) return 10.0; // this does not guarantee pushing a box
        return 0.0;
    }
    return -1.0;
}

vector<Action*> QStar::getValidActions(State* state){
    vector<Action*> validActions;
    for (QSMove move: allQSMoves){
        Action* a = new Action(move);
        if (getReward(state,a) != -1.0) {
            validActions.push_back(a);
        }
    }
    return validActions;
}

Action* QStar::chooseActionWithPolicy(State* state, vector<Action*> actions){
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

Action* QStar::getAction(State* state, double epsilon, double decayFactor){
    vector<Action*> validActions = getValidActions(state);
    double probablity = random.getProbablity();
    double greedy = epsilon * pow(decayFactor, epoch);
    if (probablity < greedy){
        int index = random.getBetweenRange(0,validActions.size()-1);
        return validActions[index];
    }

    return chooseActionWithPolicy(state, validActions);
}

State* QStar::takeAction(State* state){
    Action* action = getAction(state,epsilon,decayFactor);
    double reward = getReward(state, action);
    
    if (reward == 0.0) inactiveCounter++;
    else inactiveCounter = 0;
    State* nextState = action->getQSState(state);
    double nextMaxQ = getNextMaxQ(nextState);
    
    QState* qstate = new QState(state,action);
    string id = qstate->getId();
    qtable[id] = qtable[id] + alpha * (reward + gamma * nextMaxQ - qtable[id]);
    
    if (qtable[id] > normalizer) normalizer = qtable[id];
    
    return nextState;
}

State* QStar::takeSuboptimalAction(State* state){
    vector<Action*> validActions = getValidActions(state);
    Action* action = chooseActionWithPolicy(state, validActions);
    State* nextState = action->getQSState(state);
    return nextState;
}

double QStar::getNextMaxQ(State* nextState){
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

bool QStar::executeEpisode(State* initialState, int nMaxMoves){
    State* currentState = initialState;
    int moves = 0; 
    inactiveCounter = 0;
    while((!currentState->isGoal()) && (moves < nMaxMoves)){
        currentState = takeAction(currentState);
        if (currentState->isAnyBoxInDeadlock()) {
            break;
        }
        moves ++;
    }
    //currentState->printGrid();

    return currentState->isGoal();
}

void QStar::normalizeQ(){
    for (pair<string,double> qpair: qtable){
        qtable[qpair.first] = qpair.second / normalizer;
    }
}

void QStar::train(int nEpochs, int nMaxSteps){
    bool found = false;
    for (int i = 0; i < nEpochs; i++){
        found = executeEpisode(initialState, nMaxSteps);
        if (found){
            this->epoch = this->epoch+1;
            cout << "EPISODE " << i << ": I WON" << endl;
            if(thereIsASolution(100)) break;
        }
        if ((i % 100 == 0)){
            cout << "EPISODE " << i << endl;
        }
    }
    //normalizeQ();
}

bool QStar::thereIsASolution(int nMaxSteps){
    State* currentStep = initialState;
    int steps = 0;
    while(!currentStep->isGoal()){
        currentStep = takeSuboptimalAction(currentStep);
        steps++;
        if (steps > nMaxSteps) return false;
    }
    return true;
}


