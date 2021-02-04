// u6669461

#include <iostream>
#include <fstream>
#include <vector>
#include "case.h"

using namespace std;
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No file given" << endl;
    }
    else { 
		// Read input
		ifstream inFile(argv[1]);
		int n, x, y, amount, steps;
		string str_start, str_end;
		Date start, end;
		inFile >> str_start >> str_end;
		start.from_string(str_start);
		end.from_string(str_end);
		inFile >> amount >> steps;
		inFile >> n;
		vector<int> xs = {};
		vector<int> ys = {};
		for (int i = 0; i < n; i++) {
			inFile  >> x >> y;
			// Store x and y data
			xs.push_back(x);
			ys.push_back(y);
		}
		inFile.close();  		

		// Find bounded area
		// Choose to find path by input
		// Print bounded area, targets, and path (if selected) to console
		// Area boundary printed with B
		// Target tiles printed with O
		// Starting tile printed with X
		// Path printed with .
		// All other tiles empty

		Case c = Case(xs, ys, start, end, amount, steps);
		Matrix m = c.get_matrix();

		vector<int> best_path = c.get_path();
		std::cout << "Path: ";
		for (int i = 0; i < best_path.size(); i++)
		{
			std::cout << best_path[i] << ' ';
		}
		std::cout << endl;

		std::cout << "Priority: " << c.get_priority() << endl;
		c.show();
	}

    return 0;
}
