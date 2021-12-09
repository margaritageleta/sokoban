#include "Random.h"

Random::Random(){
    random_device dev;
    this->rng = mt19937(dev());
    this->r = uniform_real_distribution<double>(0,1);
}

double Random::getProbablity(){
    return this->r(this->rng);
}

int Random::getBetweenRange(int from, int to){
    uniform_int_distribution<int> i(from,to);
    return i(this->rng);
}
