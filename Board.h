#pragma once

#include <string>
#include <vector>
#include <cstdlib>

const int LOCAL_BOARD_SIZE = 3;
const int GLOBAL_BOARD_SIZE = 3;
const int TOTAL_BOARD_SIZE = LOCAL_BOARD_SIZE * GLOBAL_BOARD_SIZE;
const int NUMBER_OF_CELLS = TOTAL_BOARD_SIZE * TOTAL_BOARD_SIZE;

enum BOARD_STATE {
    X,
    O,
    UNFILLED,
    TIE,
    LAST_BOARD_STATE
};

enum CELL_STATE {
    X_MARKED,
    O_MARKED,
    UNMARKED,
    LAST_CELL_STATE
};
const char cell_marks[3] = {'X', 'O', '-'};

struct Move {
    int board, cell;
};

class Board {
public:
    Board();
    Board(std::string& board_state);
    std::string DisplayString();
    BOARD_STATE CheckLocalBoardForWin(int local_board_position);
    BOARD_STATE CheckGlobalBoardForWin();
    std::vector<Move> GetCurrentMoves();
    bool ApplyMove(Move m);
    std::string DisplayAvailableMoves();
    void UpdateGlobalState();
protected:
    BOARD_STATE mGlobal_state[9];
    char mLocal_states[9][9];
    Move mLast_move;
    int mTurn;
    int mCurrentPlayer;

};
