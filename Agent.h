#pragma once
#include "Board.h"
#include <random>

class Agent {
public:
    Agent();
    ~Agent() ;
    virtual Move getNextMove(Board * board) = 0;
protected:

};

class RandomAgent: public Agent 
{
public:
    RandomAgent();
    Move getNextMove(Board * board);
private:
    std::default_random_engine generator ;
};
