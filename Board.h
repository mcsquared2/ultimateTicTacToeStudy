#pragma once

#include <string>

const int LOCAL_BOARD_SIZE = 3;
const int GLOBAL_BOARD_SIZE = 3;
const int TOTAL_BOARD_SIZE = LOCAL_BOARD_SIZE * GLOBAL_BOARD_SIZE;
const int NUMBER_OF_CELLS = TOTAL_BOARD_SIZE * TOTAL_BOARD_SIZE;

enum states {
    X, 
    O, 
    UNMARKED, 
    LAST
};
const char marks[3] = {'X', 'O', '-'};

class Board {
public:
    Board();
    std::string DisplayString();
    bool checkLocalBoardForWin(int local_board_position);
private:
    char global_state[9];
    char local_states[9][9];
};