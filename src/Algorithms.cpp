#include "Algorithms.h"

State* Algorithms::AStar(State* state){
    
    if (state->isGoal()) return state;
    
    PriorityQueue frontier = PriorityQueue();
    set<string> visited;
    frontier.push(state);

    while (!frontier.empty()){
        State* currentState = frontier.pop();
        visited.insert(currentState->getId());
        
        //debug
        //do{} while (cin.get() != '\n');
        //currentState->printGrid();
        if (currentState->isGoal()) return currentState;
        vector<State*> children = Action::getNextStates(currentState);
        for (int i=0; i<children.size();i++){
            State* child = children[i];
        
            if ((visited.count(child->getId()) == 0) && (!child->equals(currentState)) && (!child->isAnyBoxInFreeCorner())){
                frontier.push(child);
            } else {
                //debug
                //if ((visited.count(child.getId()) != 0)) cout << "branch pruned:: already visited" << endl;
                //else if (child.equals(state)) cout << "branch pruned:: not moving" << endl;
                //else if (child.isAnyBoxInFreeCorner())cout << "branch pruned:: box going to corner" << endl;
            }
        }

    }
    return nullptr;

}

State* Algorithms::QLearningAlg(State* state){
    QLearning* ql = new QLearning(state, 1.0, 0.6, 0.6);
    ql->train(1000);
    return nullptr;
}

