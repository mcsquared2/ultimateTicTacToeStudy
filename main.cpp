#include <iostream>
#include "Board.h"

int main() {

    Board b;
    std::cout << b.DisplayString();
    // for (int i = 0; i < 9; i++) {
    //     int arr[9];
    //     b.GetLocalBoardIndices(i, arr);
    //     std::cout << i << ": ";
    //     for (int j = 0; j < 9; j++) {
    //         std::cout << arr[j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}