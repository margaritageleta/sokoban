#include "Algorithms.h"

State* Algorithms::AStar(State* state){

    if (state->isGoal()) return state;
    
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;
    frontier.push(state);

    while (!frontier.empty()){
        State* currentState = frontier.pop();
        visited.insert(currentState->getId());
        
        if (currentState->isGoal()) return currentState;
        vector<State*> children = Action::getNextStates(currentState);
        for (int i=0; i<children.size();i++){
            State* child = children[i];
        
            if ((visited.count(child->getId()) == 0) && (!child->equals(currentState)) && (!child->isAnyBoxInDeadlock())){
                frontier.push(child);
            }
        }

    }
    return nullptr;

}

State* Algorithms::AStarSubRoutine(State* state){
    if (state->isGoal()) return state;
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;

    frontier.push(state);
    int currentBoxes = Heuristic::getNBoxes(state);

    while (!frontier.empty()){
        State* currentState = frontier.pop();
        visited.insert(currentState->getId());
        
        if (currentState->isSubGoal(currentBoxes)){
            return currentState;
        }
        vector<State*> children = Action::getNextStates(currentState);
        for (int i=0; i<children.size();i++){
            State* child = children[i];
        
            if ((visited.count(child->getId()) == 0) && (!child->equals(currentState)) && (!child->isAnyBoxInDeadlock())){
                frontier.push(child);
            }
        }

    }
    return nullptr;
}

QLearning* Algorithms::QLearningAlg(State* state){
    double alpha = 1.0; double gamma = 0.6; double epsilon = 0.9; double decayFactor = 0.999;
    QLearning* ql = new QLearning(state, alpha, gamma, epsilon, decayFactor);
    int iterations = 0;
    while(!ql->thereIsASolution(100) && iterations < 1000){
        cout << "NO SOLUTION YET" << endl;
        ql->train(1000,1000);
        iterations += 1;
    }
    
    return ql;
}

QStar* Algorithms::QStarAlg(State* state){
    double alpha = 1.0; double gamma = 0.6; double epsilon = 0.9; double decayFactor = 0.999;
    QStar* qs = new QStar(state, alpha, gamma, epsilon, decayFactor);
    int iterations = 0;
    while(!qs->thereIsASolution(100) && iterations < 1000){
        cout << "NO SOLUTION YET" << endl;
        qs->train(100,1000);
        iterations += 1;
    }
    
    return qs;
}
