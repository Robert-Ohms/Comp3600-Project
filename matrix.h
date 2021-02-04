// u6669461

#pragma once
#include <vector>
#include <iostream>

using namespace std;
class Matrix {
    public:
        Matrix();

        Matrix(vector<vector<int>> elems);

        // Sets the value in input row, col to input element
        virtual void set(int row, int col, int elem);

        virtual void set_col(int col, int elem);

        // Returns the element at input row, col
        virtual int get(int row, int col);

        virtual vector<int> get_row(int row);

        // Prints to matrix to console
        virtual void show();

    protected:
        vector<vector<int>> the_matrix;
};