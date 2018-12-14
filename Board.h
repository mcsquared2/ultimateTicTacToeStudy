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

const std::string board_state_char[4] = {"X", "O", "-", "T"};

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
    Board(char arr[]) ;
    Board(Board & b);
    std::string DisplayString();
    BOARD_STATE CheckLocalBoardForWin(int local_board_position);
    BOARD_STATE CheckGlobalBoardForWin() const ;
    std::vector<Move> GetCurrentMoves();
    bool ApplyMove(Move m);
    bool UnMove(Move m);
    std::string DisplayAvailableMoves();
    void UpdateGlobalState();
    int GetTurn();
    int GetCurrentPlayer() ;
    int boardValue(int player, int global_win_weight, int global_partial_weight, int local_partial_weight) const;
    int getBoardArrSize() ;
    void Board2Arr(char arr[]) ;
protected:
    BOARD_STATE mGlobal_state[9];
    char mLocal_states[9][9];
    Move mLast_move;
    Move mSecond_last_move;
    int mTurn;
    int mCurrentPlayer;


};
