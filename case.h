// u6669461

#pragma once
#include <vector>
#include "date.h"
#include "matrix.h"

using namespace std;
class Case {
    public:
        Case();

        Case(vector<int> xs, vector<int> ys, Date start, Date end, int rwd, int steps);

        virtual void make_matrix();

        // Creates a convex hull for points, and returns the list of points which
        // are on the hull edge in order
        virtual vector<int> quick_hull();

        virtual vector<int> recurse_hull(int start_index, int end_index, vector<int> points, bool is_above);

        virtual pair<vector<int>, vector<int>> partition(int start_index, int end_index, vector<int> points);

        virtual double dist_from_line(int start_index, int end_index, int check_index);

        // Finds path using nearest neighbour approach
        virtual vector<int> get_path();

        // Find the proportion of target coordinates which can be passed over
        virtual float chance_of_success();

        // Create heuristic which accounts for chance of success and reward
        // and amount of time to complete
        virtual int get_priority();

        // Shows the set of points, and their convex hull bounded area
        // can also choose to show the path followed
        // Prints to console
        virtual void show();

        virtual Matrix get_matrix();

        virtual int get_reward();
        
        virtual Date get_start();

        virtual Date get_end();

    protected:
        vector<int> coordinate_names;
        vector<int> x_coordinates;
        vector<int> y_coordinates;
        vector<int> boundary;      
        vector<int> greedy_path;
        Date start_date;
        Date end_date;
        int reward = -1;
        Matrix adjacency_matrix;
        int max_steps;
};