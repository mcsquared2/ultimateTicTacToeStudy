#include <ctime>
#include <iostream>
#include <random>
#include "Board.h"


void test_generic_applyMove() {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            Board b;
            Move m;
            m.board = y;
            m.cell = x;
            b.ApplyMove(m);
            std::cout << "Applied move " << y << ", " << x << "\n";
            std::cout << b.DisplayString();
        }
    }
}

void test_state_in_constructor() {

    Board b;
    std::vector<Move> moves = b.GetCurrentMoves();
    for (int i = 0; i < 60; i++) {
        // std::cout << (size_t)rand() % moves.size();
        b.ApplyMove(moves[rand() % moves.size()]);
        std::string expected_state = b.DisplayString();
        Board b2(expected_state);
        std::string actual_state = b2.DisplayString();
        if (expected_state == actual_state) {
            std::cout << "Test case " << i << " passed!\n";
        } else {
            std::cout << "Test case " << i << " failed\n";
            std::cout << "expected: \n" << expected_state << "\ngot: \n" << actual_state;
        }
    }

}

int main() {
    // srand(time(0));
    // test_generic_apply_move();
    test_state_in_constructor();
    return 0;
}
