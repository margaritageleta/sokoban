#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <queue>
#include "State.h"

using namespace std;

class PriorityQueue {
    public:
    struct GreaterCost{
        bool operator()(State* state1, State* state2){
            return (state1->G + state1->getH()) > (state2->G + state2->getH());
        }
    };

    priority_queue<State*, std::vector<State*>, GreaterCost> pq;
    
    PriorityQueue();
    State* pop();
    void push(State* state);
    bool empty();

    private:
    void lazyRemoval(State* state);
};
#endif