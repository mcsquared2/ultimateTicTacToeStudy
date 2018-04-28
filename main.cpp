#include <ctime>
#include <iostream>
#include <random>
#include "Board.h"
#include "Agent.h"
#include "HueristicAgent.h"


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

void playGame(Agent *p1, Agent *p2, int &p1_wins, int &p2_wins, int &ties) {
    Board board;
    while ( board.CheckGlobalBoardForWin() == UNFILLED ) {
        // std::cout << board.DisplayString() << std::endl;
        Move nextMove;
        if ( board.GetTurn() % 2 == 1 ) {
            nextMove = p1->getNextMove(&board);
        } else {
            nextMove = p2->getNextMove(&board);
        }
        board.ApplyMove(nextMove);
    }
    // std::cout << board.DisplayString();
    // std::cout << "The winner is " << board.CheckGlobalBoardForWin() << "\n";
    // std::cout << "The winner is " << board_state_char[board.CheckGlobalBoardForWin()] << "\n";
    switch (board.CheckGlobalBoardForWin()) {
        case X:
            p1_wins ++;
            break;
        case O:
            p2_wins++;
            break;
        case TIE:
            ties++;
            break;
        default:
            std::cout << "Somewhere something went wrong. We got an invalid win state when checking.";
    }
}

void test_random() {
    RandomAgent p1;
    RandomAgent p2;
    // playGame(&p1, &p2);
}

void test_hueristic() {
    HueristicAgent p1(0, 11, .3, .5, .2), p2(1, 11, .2, .7, .1);

    // playGame(&p1, &p2);
}
void test_moves_when_board_is_filled() {
    Board b;
    Move m, om;
    m.board = 0;
    m.cell = 4;
    b.ApplyMove(m);
    om.board=4;
    om.cell = 0;
    b.ApplyMove(om);
    m.cell = 5;
    b.ApplyMove(m);
    om.board = 5;
    b.ApplyMove(om);
    m.cell = 3;
    b.ApplyMove(m);
    om.board = 3;
    b.ApplyMove(om);
    std::vector<Move> moves = b.GetCurrentMoves();
    for (size_t i = 0; i < moves.size(); i++) {
        std::cout << moves[i].board << " " << moves[i].cell << "\n";
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));
    // test_generic_apply_move();
    // test_random();
    // test_hueristic();
    // test_moves_when_board_is_filled();
    int a1_depth = 5, a2_depth = 5;
    int a1_gpw = 90, a1_gww = 20, a1_lpw = 3, a2_gpw = 90, a2_gww = 20, a2_lpw = 3;
    Agent * a1;
    Agent * a2;
    bool display = false, a1isH = false, a2isH = false;
    int games = 1;
    for (int i = 0; i < argc; i++) {
        std::string a(argv[i]);
        if ( a == "-a1" ) {
            if (i < argc) {
                i++;
                a1_gww = atoi(argv[i]);
                i++;
                a1_gpw = atoi(argv[i]);
                i++;
                a1_lpw = atoi(argv[i]);
                i++;
                a1_depth = atoi(argv[i]);
            }
            a1isH = true;
        }
        else if ( a == "-a2" ) {
            if (i < argc) {
                i++;
                a2_gww = atof(argv[i]);
                i++;
                a2_gpw = atof(argv[i]);
                i++;
                a2_lpw = atof(argv[i]);
                i++;
                a2_depth = atoi(argv[i]);
            }
            a2isH = true;
        } else if ( a == "-a12") {
            if (i < argc) {
                i++;
                a1_gww = atof(argv[i]);
                a2_gww = atof(argv[i]);
                i++;
                a2_gpw = atof(argv[i]);
                a1_gpw = atof(argv[i]);
                i++;
                a1_lpw = atof(argv[i]);
                a2_lpw = atof(argv[i]);
                i++;
                a1_depth = atoi(argv[i]);
                a2_depth = atoi(argv[i]);
            }
            a1isH = true;
            a2isH = true;

        } else if ( a == "-g" ) {
            i++;
            games = atoi(argv[i]);
        }
    }
    // std::cout << "a1isH: " << a1isH << " a1_gww: " << a1_gww << " a1_gpw " << a1_gpw << " a1_lpw " << a1_lpw << " a1 depth: " << a1_depth << std::endl;
    // std::cout << "a2isH: " << a2isH << " a2_gww: " << a2_gww << " a2_gpw " << a2_gpw << " a2_lpw " << a2_lpw << " a2 depth: " << a2_depth <<std::endl;
    // std::cout << "Games: " << games << std::endl;
    if ( a1isH ) {
        a1 = new HueristicAgent(0, a1_depth, a1_gww, a1_gpw, a1_lpw);
    } else {
        a1 = new RandomAgent();
    }
    if ( a1isH ) {
        a2 = new HueristicAgent(1, a2_depth, a2_gww, a2_gpw, a2_lpw);
    } else {
        a2 = new RandomAgent();
    }
    int p1_wins = 0, p2_wins = 0, ties = 0;
    double p1_time_total = 0, p2_time_total = 0;
    for (int i = 0; i < games; i++) {
        playGame(a1, a2, p1_wins, p2_wins, ties);
        if (a1isH) {
            HueristicAgent * ha = dynamic_cast<HueristicAgent *>(a1);
            p1_time_total += ha->getTime();
            ha->resetTime();
        }
        if (a2isH) {
            HueristicAgent * ha = dynamic_cast<HueristicAgent *>(a2);
            p2_time_total += ha->getTime();
            ha->resetTime();
        }
    }

    std::cout << "Total games: " << games << std::endl;
    std::cout << "Ties: " << ties << std::endl;
    std::cout << "Player 1 data\n";
    if (a1isH) {
        std::cout << "depth: " << a1_depth << "\nlocal board win weight: " << a1_gww <<
            "\nglobal board partial weight: " << a1_gpw << "\nlocal board partial weight " << a1_lpw << std::endl;
    } else {
        std::cout << "Player 1 is random!\n";
    }
    std::cout << "Average time for player 1: " << p1_time_total / games << std::endl;
    std::cout << "Player 1 win percentage: " << (double)(p1_wins) / games * 100 << "%\n";

    std::cout << "Player 2 data\n";
    if (a2isH) {
        std::cout << "depth: " << a2_depth << "\nlocal board win weight: " << a2_gww <<
            "\nglobal board partial weight: " << a2_gpw << "\nlocal board partial weight " << a2_lpw << std::endl;
    } else {
        std::cout << "Player 2 is random!\n";
    }
    std::cout << "Average time for player 2: " << p2_time_total / games << std::endl;
    std::cout << "Player 2 win percentage: " << (double)(p2_wins) / games * 100 << "%\n";

    p1_wins = 0;
    p2_wins = 0;
    ties = 0;
    p1_time_total = 0;
    p2_time_total = 0;
    for (int i = 0; i < games; i++) {
        playGame(a2, a1, p1_wins, p2_wins, ties);
        if (a1isH) {
            HueristicAgent * ha = dynamic_cast<HueristicAgent *>(a1);
            p1_time_total += ha->getTime();
            ha->resetTime();
        }
        if (a2isH) {
            HueristicAgent * ha = dynamic_cast<HueristicAgent *>(a2);
            p2_time_total += ha->getTime();
            ha->resetTime();
        }
    }

    std::cout << "Total games: " << games << std::endl;
    std::cout << "Ties: " << ties << std::endl;
    std::cout << "Player 1 data\n";
    if (a1isH) {
        std::cout << "depth: " << a1_depth << "\nlocal board win weight: " << a1_gww <<
            "\nglobal board partial weight: " << a1_gpw << "\nlocal board partial weight " << a1_lpw << std::endl;
    } else {
        std::cout << "Player 1 is random!\n";
    }
    std::cout << "Average time for player 1: " << p1_time_total / games << std::endl;
    std::cout << "Player 1 win percentage: " << (double)(p1_wins) / games * 100 << "%\n";

    std::cout << "Player 2 data\n";
    if (a2isH) {
        std::cout << "depth: " << a2_depth << "\nlocal board win weight: " << a2_gww <<
            "\nglobal board partial weight: " << a2_gpw << "\nlocal board partial weight " << a2_lpw << std::endl;
    } else {
        std::cout << "Player 2 is random!\n";
    }
    std::cout << "Average time for player 2: " << p2_time_total / games << std::endl;
    std::cout << "Player 2 win percentage: " << (double)(p2_wins) / games * 100 << "%\n";



    delete a1;
    delete a2;
    return 0;
}
