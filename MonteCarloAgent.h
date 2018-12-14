#pragma once
#include "Agent.h"

class MonteCarloAgent: public Agent {
public:
    MonteCarloAgent() ;
    Move getNextMove(Board * board) ;
    size_t chooseRandomMove(size_t ceil) ;
    BOARD_STATE randomGame(Board * board) ;
    double gettime() ;
    void resettime() {mtime = 0;};
protected:
    int games_per_move ;
    std::default_random_engine generator ;
    int mtime ;
    // std::uniform_int_distribution distributions[8] ;
} ;
 

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