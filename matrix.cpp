// u6669461

#include "matrix.h"

using namespace std;
Matrix::Matrix() {
    vector<vector<int>> empty_matrix;
    the_matrix = empty_matrix;
}

Matrix::Matrix(vector<vector<int>> elems) {
    the_matrix = elems;
}

void Matrix::set(int row, int col, int elem) {
    the_matrix[row][col] = elem;
}

void Matrix::set_col(int col, int elem) {
    int n_row = the_matrix.size();
    for (int i = 0; i < n_row; i++)
    {
        the_matrix[i][col] = elem;
    }
}

int Matrix::get(int row, int col) {
    return the_matrix[row][col];
}

vector<int> Matrix::get_row(int row) {
    return the_matrix[row];
}


void Matrix::show() {
    int n_row = the_matrix.size();
    int n_col = the_matrix[0].size();

    // Print column names
    std::cout << "    ";
    for (int i = 0; i < n_col; i++)
    {
        std::cout << i << ' ';
        if (i < 100) {
            std::cout << ' ';
        }        
        if (i < 10) {
            std::cout << ' ';
        }
    }
    std::cout << endl;
    

    for (int i = 0; i < n_col; i++)
    {
        // Print row names
        std::cout << i << ' ';
        if (i < 100) {
            std::cout << ' ';
        }        
        if (i < 10) {
            std::cout << ' ';
        }

        vector<int> row_i = the_matrix[i];
        for (int j = 0; j < n_col; j++)
        {
            // Print row contents
            std::cout << row_i[j] << ' ';
             if (row_i[j] < 100) {
            std::cout << ' ';
            }
            if (row_i[j] < 10) {
                std::cout << ' ';
            }
        }
        std::cout << endl;
    }
}