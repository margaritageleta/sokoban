#include "Action.h"

vector<State*> Action:: getNextStates(State* state) {
    vector <State*> states;
    const Move moves[] = {UP,DOWN,LEFT,RIGHT};
    State* nextMove;
    for(auto move: moves){
        nextMove = new State(state);
        nextMove->setParent(state);
        states.push_back(getState(nextMove,move));
    }

    return states;
}

State* Action::getState(State* state, Move m){
    coord2D (*move)(coord2D coord);
    switch(m){
        case UP: move = moveUp; break;
        case DOWN: move = moveDown; break;
        case RIGHT: move = moveRight; break;
        case LEFT: move = moveLeft; break;
    }
    state->movedBox = false;
    coord2D agentPosition = state->player;
    coord2D temptativePosition = move(agentPosition);
    if (state->isWall(temptativePosition)){
        return state;
    } else if (state->isBox(temptativePosition)){
        coord2D temptativeBoxPosition = move(temptativePosition);
        if (state->isWall(temptativeBoxPosition) || state->isBox(temptativeBoxPosition)){
            return state;
        } else {
            state->moveBox(temptativePosition, temptativeBoxPosition);
            state->movePlayer(agentPosition,temptativePosition);
            
            agentPosition = state->player;
            temptativePosition = move(agentPosition);
            temptativeBoxPosition = move(temptativePosition);
            while (state->inTunnel(temptativePosition)){
                if (state->isWall(temptativeBoxPosition) || state->isBox(temptativeBoxPosition)) return state;
                state->moveBox(temptativePosition, temptativeBoxPosition);
                state->movePlayer(agentPosition,temptativePosition);
                agentPosition = state->player;
                temptativePosition = move(agentPosition);
                temptativeBoxPosition = move(temptativePosition);
            }
            return state;
        }
    } else {
        state->movePlayer(agentPosition,temptativePosition);
        return state;
    }
}

State* Action::getQSState(State* state, QSMove m){
    if (m == ASTAR){
        State* newState = Algorithms::AStarSubRoutine(state);
        if (!newState) return state;
        return newState;
    }else{
        return getState(state, getQSMove(m));
    }
}


coord2D Action::moveRight(coord2D coord){
    return make_pair(coord.first,coord.second+1);
}
coord2D Action::moveLeft(coord2D coord){
    return make_pair(coord.first,coord.second-1);
}
coord2D Action::moveUp(coord2D coord){
    return make_pair(coord.first - 1,coord.second);
}
coord2D Action::moveDown(coord2D coord){
    return make_pair(coord.first + 1,coord.second);
}

Action::Action(Move move){
    this->move = move;
}

Action::Action(QSMove move){
    this->qsmove = move;
}

Move Action::getQSMove(QSMove move){
    switch(move){
        case QUP: return Move::UP; break;
        case QDOWN: return Move::DOWN; break;
        case QRIGHT: return Move::RIGHT; break;
        case QLEFT: return Move::LEFT; break;
    }
}

string Action::getId(){
    if(this->qsmove != QLast){
        switch(this->qsmove){
            case QUP: return "U";
            case QDOWN: return "D";
            case QRIGHT: return "R";
            case QLEFT: return "L";
            case ASTAR: return "A";
        }
    }else{
        switch(this->move){
            case UP: return "U";
            case DOWN: return "D";
            case RIGHT: return "R";
            case LEFT: return "L";
        }
    }
    
}

State* Action::getState(State* state){
    State* nextMove = new State(state);
    nextMove = Action::getState(nextMove,this->move);
    return nextMove;
}

State* Action::getQSState(State* state){
    State* nextMove = new State(state);
    nextMove = Action::getQSState(nextMove,this->qsmove);
    return nextMove;
}