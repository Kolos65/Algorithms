//
//  matrix.hpp
//  Penzalg_1
//
//  Created by Foltányi Kolos on 2019. 09. 16..
//  Copyright © 2019. Foltányi Kolos. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <vector>
#include<iterator>
#include "exceptions.hpp"

using namespace std;

class Matrix {
    vector<vector<int>> array;
    
public:
    Matrix();
    Matrix(vector<vector<int>> array);
    
    size_t rows = 0;
    size_t cols = 0;
    
    vector<int> operator[](int index);
    
    Matrix operator*(Matrix rval) throw(invalid_multiplication_operand);
    Matrix operator+(Matrix rval) throw(invalid_addition_operand);
    
    void addRow(vector<int> row) throw(invalid_row_length);
    void addColumn(vector<int> col) throw(invalid_column_length);
    
    void print();
    
    string toString() const;
    
    friend ostream& operator<<(ostream& os, const Matrix& m);
};

Matrix::Matrix() {}

Matrix::Matrix(vector<vector<int>> array): array(array) {
    rows = array.size();
    cols = array[0].size();
}


vector<int> Matrix :: operator[](int index) {
    return array[index];
}

Matrix Matrix::operator*(Matrix rval) throw(invalid_multiplication_operand){
    if(this->rows != rval.cols || this->cols != rval.rows) {
        throw invalid_multiplication_operand();
    }
    
    Matrix dest;
    
    for(int k=0;k<rows;k++){
        vector<int> row;
        for(int j=0;j<rval.cols;j++){
            int x = 0;
            for(int i=0;i<cols;i++){
                x += array[k][i] * rval[i][j];
            }
            row.push_back(x);
        }
        dest.addRow(row);
    }
    
    return dest;
}

Matrix Matrix::operator+(Matrix rval) throw(invalid_addition_operand){
    if(this->rows != rval.rows || this->cols != rval.cols) {
        throw invalid_addition_operand();
    }
    
    Matrix dest;
    
    for(int i=0;i<rows;i++) {
        vector<int> row;
        for(int j=0;j<cols;j++) {
            row.push_back(array[i][j]+rval[i][j]);
        }
        dest.addRow(row);
    }
    
    return dest;
}

void Matrix::addRow(vector<int> row) throw(invalid_row_length) {
    if (cols != 0 && row.size() != cols) {
        throw invalid_row_length();
    }
    array.push_back(row);
    rows++;
}

void Matrix::addColumn(vector<int> col) throw(invalid_column_length) {
    if (rows != 0 && col.size() != rows) {
        throw invalid_column_length();
    }
    
    int i = 0;
    for(vector<int>& row: array) {
        row.push_back(col[i]);
        i++;
    }
}

string Matrix::toString() const {
    string description;
    for(vector<int> row: array) {
        for(int element: row) {
            description.append(to_string(element)+" ");
        }
        description.append("\n");
    }
    return description;
}

void Matrix::print() {
    cout<<toString();
}

ostream& operator<<(ostream& os, const Matrix& m) {
    return os << m.toString();
}

#endif /* matrix_hpp */
