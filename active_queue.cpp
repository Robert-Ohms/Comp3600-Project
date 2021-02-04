// u6669461

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "date.h"
#include "heap.h"
#include "info.h"

using namespace std;

// Removes any elements in heap which are before the input date
// can't figure out how to keep this function contained within heap.cpp
void rebuild(Heap<Info> &h, Date d) {
    vector<pair<int, Info>> keep;
    vector<pair<int, Info>> heap = h.get_heap();
    for (int i = 0; i < h.get_size(); i++)
    {
        if (d.compare(heap[i].second.get_end_date()) < 0) {
            keep.push_back(heap[i]);
        }
    }
    h.build(keep);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No file given" << endl;
    } else { 
		// Read input
		ifstream inFile(argv[1]);
        int n, prio;
        string key, str_date;
        Date end_date;
        inFile >> n;
        vector<pair<int, Info>> heap_data = {};
        for (int i = 0; i < n; i++) {
            inFile >> prio >> key >> str_date;
            // Store priority, key, and end date for each active case
            end_date.from_string(str_date);
            Info info = Info(key, end_date);
            heap_data.push_back(make_pair(prio, info));
        }
		inFile.close();		

        auto start_time = chrono::high_resolution_clock::now();
        Heap<Info> active_heap = Heap<Info>(heap_data); 
        rebuild(active_heap, Date(1, 1, 1800));
        vector<pair<int, Info>> the_heap = active_heap.get_heap();
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

        std::cout << "Created heap in: " << duration.count() << " milliseconds ";
        std::cout << "for new heap with " << the_heap.size() << " elements" << endl;     

        // std::cout << "Reading from the_heap" << endl;
        // for (int i = 0; i < the_heap.size(); i++)
        // {
        //     std::cout << the_heap[i].first << ' ';
        //     std::cout << the_heap[i].second.get_key() << ' ' << the_heap[i].second.get_end_date().to_string();
        //     std::cout << endl;
        // }
        
        while (true){        
            // Read new prompt
            vector<string> argv;
            string arg_line;
            std::cout << "Choose next operation:" << endl;
            std::cout << "Insert (i), Extract (e), Rebuild (r), Quit (q)" << endl;
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

            // Case when inserting
            if (operation == "i") {
                std::cout << "Attempting to insert" << endl;
                std::cout << endl;
                
                // Check data legality
                if (argv.size() < 4){
                    std::cout << "Not enough arguments given" << endl;
                } else {

                    int prio = stoi(argv[1]);
                    string key = argv[2];
                    Date end_date;
                    end_date.from_string(argv[3]);
                    Info info = Info(key, end_date);

                    auto start_time = chrono::high_resolution_clock::now();
                    active_heap.insert(prio, info);
                    auto end_time = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);

                    // Print
                    vector<pair<int, Info>> the_heap = active_heap.get_heap();
                    // std::cout << "Reading from the_heap" << endl;
                    // for (int i = 0; i < the_heap.size(); i++)
                    // {
                    //     std::cout << the_heap[i].first << ' ';
                    //     std::cout << the_heap[i].second.get_key() << ' ' << the_heap[i].second.get_end_date().to_string();
                    //     std::cout << endl;
                    // }

                    std::cout << "Inserted element in: " << duration.count() << " nanoseconds ";
                    std::cout << "for heap with " << the_heap.size() - 1 << " elements" << endl;
                }

            }
            

            // Case when extracting
            // Do not need additional data
            else if (operation == "e") {
                std::cout << "Attempting to extract" << endl;
                std::cout << endl;

                auto start_time = chrono::high_resolution_clock::now();
                pair<int, Info> p_max = active_heap.extract_max();
                auto end_time = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);

                // Print
                vector<pair<int, Info>> the_heap = active_heap.get_heap();
                // std::cout << "Reading from the_heap" << endl;
                // for (int i = 0; i < the_heap.size(); i++)
                // {
                //     std::cout << the_heap[i].first << ' ';
                //     std::cout << the_heap[i].second.get_key() << ' ' << the_heap[i].second.get_end_date().to_string();
                //     std::cout << endl;
                // }

                std::cout << endl;
                std::cout << "Extracted:" << endl;
                std::cout << p_max.first << ' ' << endl;
                std::cout << p_max.second.get_key() << ' ' << p_max.second.get_end_date().to_string() << endl;
                std::cout << "Extracted element in: " << duration.count() << " nanoseconds ";
                std::cout << "for heap with " << the_heap.size() + 1 << " elements" << endl;
            }

            // Rebuild from an input date
            else if (operation == "r") {
                if (argv.size() < 2) {
                    std::cout << "No date given" << endl;
                } else {
                    Date end_date;
                    end_date.from_string(argv[1]);

                    auto start_time = chrono::high_resolution_clock::now();
                    rebuild(active_heap, end_date);
                    auto end_time = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

                    the_heap = active_heap.get_heap();
                    // std::cout << "Reading from the_heap" << endl;
                    // for (int i = 0; i < the_heap.size(); i++)
                    // {
                    //     std::cout << the_heap[i].first << ' ';
                    //     std::cout << the_heap[i].second.get_key() << ' ' << the_heap[i].second.get_end_date().to_string();
                    //     std::cout << endl;
                    // }    
                    std::cout << "Rebuilt heap in: " << duration.count() << " milliseconds ";
                    std::cout << "for new heap with " << the_heap.size() << " elements" << endl;                    
                }            
            }             

            // End session
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
