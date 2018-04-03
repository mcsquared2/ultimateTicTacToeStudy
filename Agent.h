#pragma once
#include "Board.h"

class Agent {
public:
    Agent();
    virtual Move getNextMove(Board * board) = 0;
protected:

};

class RandomAgent: public Agent 
{
public:
    RandomAgent();
    Move getNextMove(Board * board);
};
