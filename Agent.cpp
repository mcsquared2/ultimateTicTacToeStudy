#include <iostream>
#include "Agent.h"

Agent::Agent() {

}

Agent::~Agent() {

}

RandomAgent::RandomAgent(){
    generator = std::default_random_engine(time( 0 )) ;
}

Move RandomAgent::getNextMove( Board  *board ) {
    Board b = *board;
    // Board b; 
    std::vector<Move> moves = b.GetCurrentMoves() ;
    size_t ceil = moves.size() ;
    if (ceil == 0) {
        exit(1) ;
    }
    std::uniform_int_distribution<size_t> distribution(0, ceil - 1) ; 
    return moves[distribution(generator)];
}
