//
//  exceptions.hpp
//  Penzalg_1
//
//  Created by Foltányi Kolos on 2019. 09. 17..
//  Copyright © 2019. Foltányi Kolos. All rights reserved.
//

#ifndef exceptions_hpp
#define exceptions_hpp

#include <stdio.h>

using namespace std;

class invalid_multiplication_operand: public exception {
    virtual const char* what() const throw() {
        return "Invalid multiplication operand! (You can only multiply an n x m matrix with an m x n matrix.)";
    }
};

class invalid_addition_operand: public exception {
    virtual const char* what() const throw() {
        return "Invalid addition operand! (You can only add an n x m matrix to an n x m matrix.)";
    }
};

class invalid_row_length: public exception {
    virtual const char* what() const throw() {
        return "Invalid row length!";
    }
};

class invalid_column_length: public exception {
    virtual const char* what() const throw() {
        return "Invalid column length!";
    }
};

#endif /* exceptions_hpp */
