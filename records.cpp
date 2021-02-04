// u6669461

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "case.h"
#include "hash_table.h"

using namespace std;
int main(int argc, char *argv[]) {
        if (argc < 2) {
        std::cout << "No file given" << endl;
    }
    else { 
		// Read input
		ifstream inFile(argv[1]);
		int n_elements, amount, steps, x, y, n_i;
        string key, str_start, str_end;
        // Case data also stored, needs to have coordinates, dates, and amount
		inFile >> n_elements;
        // Make record data pair of key and value, do not know how data will be stored yet
		vector<pair<string, Case>> record_data;
		for (int i = 0; i < n_elements; i++) {
            vector<int> xs, ys;
			inFile  >> key >> amount >> steps >> str_start >> str_end >> n_i;
            for (int j = 0; j < n_i; j++)
            {
                inFile >> x >> y;
                xs.push_back(x);
                ys.push_back(y);
            }
            Date start_date, end_date;
            start_date.from_string(str_start);
            end_date.from_string(str_end);
            Case c = Case(xs, ys, start_date, end_date, amount, steps);
            record_data.push_back(make_pair(key, c));
		}
        
        inFile.close();  
        auto start_time = chrono::high_resolution_clock::now();		
        Hash_table<Case> the_table = Hash_table<Case>(1000000, record_data);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time); 
        std::cout << "Table size: " << the_table.get_size() << endl;
        if (n_elements != the_table.get_size()) {
            std::cout << "Some duplicate keys in input" << endl;
        } else {
            std::cout << "All keys unique" << endl;
        }
        std::cout << "Time to build hash table: " << duration.count() << " milliseconds " << endl; 

        while (true){        
            // Read new prompt
            vector<string> argv;
            string arg_line;
            std::cout << "Choose next operation:" << endl;
            std::cout << "Insert (i), Remove (r), Get (g), Quit (q)" << endl;
            getline(cin, arg_line);
            while (arg_line.size() > 0)
            {
                int before_space = arg_line.find(' ');
                if (before_space > 0)
                {
                    string sub = arg_line.substr(0, before_space);   
                    arg_line = arg_line.substr(before_space + 1);
                    argv.push_back(sub);
                } else {
                    argv.push_back(arg_line);
                    arg_line = "";
                }
            }

            string operation = argv[0];

            if (operation == "i") {
                if (argv.size() < 3) {
                    std::cout << "Not enough arguments given" << endl;
                } else {
                    // Read record data from file
                    // Inserting cases directly from terminal inefficient since need separate
                    // argument for each coordinate, makes error prone
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
                    Case c = Case(xs, ys, start, end, amount, steps);
                    string key_c = argv[2];

                    auto start_time = chrono::high_resolution_clock::now();
                    the_table.put(key_c, c);
                    auto end_time = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time); 
                    std::cout << "Inserted into hash table in: " << duration.count() << " microseconds " << endl;   
                }        
            }
            
            else if (operation == "r") {
                if (argv.size() < 2) {
                    std::cout << "No key given" << endl;
                } else {
                    auto start_time = chrono::high_resolution_clock::now();
                    the_table.remove(argv[1]);
                    auto end_time = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);  
                    std::cout << "Removed from hash table in: " << duration.count() << " microseconds" << endl;  
                }  

            }
            else if (operation == "g") {
                if (argv.size() < 2) {
                    std::cout << "No key given" << endl;
                } else {
                    string key = argv[1];
                    auto start_time = chrono::high_resolution_clock::now();
                    Case g = the_table.get(key);
                    auto end_time = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);  
                    if (g.get_reward() > 0) {
                        std::cout << "Found case in: " << duration.count() << " microseconds " << endl;  
                        std::cout << "Case reward: " << g.get_reward() << endl;
                        std::cout << "Case start: " << g.get_start().to_string() << endl;
                        std::cout << "Case end: " << g.get_end().to_string() << endl;
                    }
                }  
            }

            else if (operation == "q") {
                std::cout << "Ending" << endl;
                break;
            }        

            // Invalid input
            else {
                std::cout << "No valid opperation given" << endl;
                std::cout << endl;
            } 
        }
    }

    return 0;
}
