#include "MonteCarloParallelAgent.h"
#include <iostream> 
#include <mpi.h>
#include <ctime>
#define MCW MPI_COMM_WORLD

MonteCarloParallelAgent::MonteCarloParallelAgent(int rank, int size) {
    mrank = rank ;
    msize = size ;
}

Move MonteCarloParallelAgent::getNextMove(Board * board) {
    // if (testRank(mrank)) std::cout << "we are sending all data!\n" ;
    
    
    int t0 = std::clock( ) ;
    std::vector<Move> moves = board->GetCurrentMoves() ;
    int moveDataBuffSize = moves.size() * 2 ;
    // if (testRank(mrank)) std::cout << "we have delivered all data!\n" ;

    for (int i = 0; i < moves.size(); i++) {
        int wins, ties = 0 ;
        Board c(*board) ;
        c.ApplyMove(moves[i]) ;
        for (int g = 0; g < games_per_move; g++) {
            BOARD_STATE result = randomGame(&c) ;
            if (result == board->GetCurrentPlayer()) {
                wins++ ;
            } else if (result == TIE) {
                ties++ ;
            }
        }
        moveDataBuff[i*2] = wins ;
        moveDataBuff[i*2 + 1] = ties ;
    }
    // if (testRank(mrank)) std::cout << "we have tested all moves!\n" ;

    int * totalMoveDataBuff = 0 ;
    if (mrank == 0) totalMoveDataBuff = new int[moveDataBuffSize*msize] ;
    MPI_Gather(moveDataBuff, moveDataBuffSize, MPI_INT, totalMoveDataBuff, moveDataBuffSize, MPI_INT, 0, MCW) ;
    // if (testRank(mrank)) std::cout << "we have gathered all data!\n" ;
    
    int best = 0;
    if (mrank == 0) {
        for (int i = moveDataBuffSize; i < moveDataBuffSize*msize; i++) {
            moveDataBuff[i%moveDataBuffSize] += totalMoveDataBuff[i] ;
        }  
        for (int i = 2; i < moveDataBuffSize; i+=2) {
            if (
                // There are more wins
                moveDataBuff[best] < moveDataBuff[i] ||
                // wins for both are the same, but i has more ties.
                ( moveDataBuff[best] == moveDataBuff[i] && moveDataBuff[best+1] < moveDataBuff[i+1] )
            ) {
                best = i / 2 ;
            } 
        }
        delete [] totalMoveDataBuff ;
    }
    // if (testRank(mrank)) std::cout << "we have chosen the best move\n" ;

    
    mtime += std::clock() - t0 ;

    return moves[static_cast<size_t>(best)] ;
}

