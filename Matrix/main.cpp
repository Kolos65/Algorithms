//
//  main.cpp
//  Penzalg_1
//
//  Created by Foltányi Kolos on 2019. 09. 16..
//  Copyright © 2019. Foltányi Kolos. All rights reserved.
//
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "matrix.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Matrix A = Matrix({ {1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9},
                        {1, 2, 3} });


    Matrix B = Matrix({ {1, 2, 3, 4},
                        {4, 5, 6, 7},
                        {7, 8, 9, 10} });

    Matrix C = A * B;

    C.print();
    cout << endl;
    
    Matrix D = Matrix({ {1, 1, 1},
                        {1, 1, 1},
                        {2, 2, 3} });


    Matrix E = Matrix({ {2, 2, 2},
                        {2, 2, 2},
                        {1, 1, 0} });


    Matrix F = D + E;
    
    cout << F << endl;
    
    Matrix G = Matrix({ {1, 1, 1},
                        {1, 1, 1},
                        {1, 1, 1} });
    
    G.addRow({2, 2, 2});
    
    cout << G << endl;
    
    G.addColumn({4, 4, 4, 4});
    
    cout << G << endl;
    
    try {
        G.addRow({1, 2});
    } catch(const exception& e) {
        cout << e.what() << endl;
    }
    
    return 0;
}
