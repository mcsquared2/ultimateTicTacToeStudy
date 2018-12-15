#pragma once
#include "MonteCarloAgent.h"

class MonteCarloParallelAgent: public MonteCarloAgent {
public:
    MonteCarloParallelAgent(int rank, int size) ;
    Move getNextMove(Board * board) ;
protected:
    int mrank, msize ;
    // moveDataBuff is composed of two ints per move, the first is the number of wins and the second is the numebr of ties.
    // Since there can be at most 81 moves available, the buffer is set to 81 * 2
    int moveDataBuff[81*2] ;
} ;