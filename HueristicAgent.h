#pragma once
#include "Agent.h"
#include <time.h>

class HueristicAgent: public Agent {
public:
    HueristicAgent(int player, int depth, double global_win_weight, double global_partial_weight, double local_partial_weight);
    Move getNextMove(Board * board);
    Move alpha_beta_search(Board *board, int player);
    double max_value(Board & board, int player, int depth, double alpha, double beta, Move & move_delta );
    double min_value(Board & board, int player, int depth, double alpha, double beta);
    double utility(const Board & board, int player);
    bool terminal_test(const Board & board, int player);
    double getTime() {return mTime;};
    void resetTime() { mTime=0;}
private:
    int mPlayer, mDepth;
    int mGlobal_win_weight,
        mGlobal_partial_weight,
        mLocal_partial_weight;
    double mTime;
};