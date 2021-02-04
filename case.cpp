// u6669461

#include <cmath>
#include <chrono>
#include "case.h"

using namespace std;

Case::Case() {
}

void Case::make_matrix() {
    vector<vector<int>> m;
    for (int i = 0; i < coordinate_names.size(); i++)
    {
        int x_i = x_coordinates[i];
        int y_i = y_coordinates[i];
        vector<int> row_i;
        for (int j = 0; j < coordinate_names.size(); j++)
        {
            if (i == j) {
                row_i.push_back(999);
            } else {
                int x_j = x_coordinates[j];
                int y_j = y_coordinates[j];
                int dist = abs(x_i - x_j) + abs(y_i - y_j);
                row_i.push_back(dist);
            }
        }
        m.push_back(row_i);
    }
    adjacency_matrix = Matrix(m);
}

Case::Case(vector<int> xs, vector<int> ys, Date start, Date end, int rwd, int steps) {
    x_coordinates = xs;
    y_coordinates = ys;
    int n = xs.size();
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = i;
    }
    coordinate_names = v;
    start_date = start;
    end_date = end;
    reward = rwd;
    max_steps = steps;
    make_matrix();
    vector<int> empty;
    greedy_path = empty;
}

// quick_hull implementation taken from solution by Dennehy (2018) at
// https://www.youtube.com/watch?v=2EKIZrimeuk
vector<int> Case::quick_hull() {
    if ((coordinate_names).size() < 3) {
        return coordinate_names;
    }

    vector<int> running_boundary;
    
    // Find starting points as left and rightmost points
    int x_min = x_coordinates[0];
    int min_index = 0;
    int x_max = x_coordinates[0];
    int max_index = 0;
    for (int i = 1; i < x_coordinates.size(); i++)
    {
        if (x_coordinates[i] > x_max)
        {
            x_max = x_coordinates[i];
            max_index = i;
        } else if (x_coordinates[i] < x_min)
        {
            x_min = x_coordinates[i];
            min_index = i;
        }
    }

    running_boundary.push_back(min_index);
    running_boundary.push_back(max_index);

    pair<vector<int>, vector<int>> parts = partition(min_index, max_index, coordinate_names);
    vector<int> points_above = parts.first;
    vector<int> points_below = parts.second;

    vector<int> hull_above = recurse_hull(min_index, max_index, points_above, true);
    vector<int> hull_below = recurse_hull(min_index, max_index, points_below, false);
    
    for (int i = 0; i < hull_above.size(); i++)
    {
        running_boundary.push_back(hull_above[i]);
    }
    for (int i = 0; i < hull_below.size(); i++)
    {
        running_boundary.push_back(hull_below[i]);
    }   

    return running_boundary;
}

// recurse_hull taken from solution for quick hull by Dennehy (2018)
vector<int> Case::recurse_hull(int start_index, int end_index, vector<int> points, bool is_above) {
    vector<int> hull_points;
    if (points.size() == 0) {
        return hull_points;
    }

    int furthest_index = 0;
    int furthest_point = points[0];
    double furthest_distance = dist_from_line(start_index, end_index, furthest_point);
    for (int i = 1; i < points.size(); i++)
    {
        double i_dist = dist_from_line(start_index, end_index, points[i]);
        if (i_dist > furthest_distance) {
            furthest_distance = i_dist;
            furthest_point = points[i];
            furthest_index = i;
        }
    }

    // Further point from line must be on hull
    hull_points.push_back(furthest_point);
    points.erase(points.begin() + furthest_index);

    // Create triangle between furthest point, and start and end points
    // For edge between start and furthest point, and edge between end and furthest point,
    // any points beyond those might be part of the hull, i.e. outside triangle bound

    pair<vector<int>, vector<int>> start_part = partition(start_index, furthest_point, points);
    pair<vector<int>, vector<int>> end_part = partition(end_index, furthest_point, points);

    if (is_above) {
        vector<int> start_above = recurse_hull(start_index, furthest_point, start_part.first, true);
        vector<int> end_above = recurse_hull(furthest_point, end_index, end_part.first, true);
        for (int i = 0; i < start_above.size(); i++)
        {
            hull_points.push_back(start_above[i]);
        }
        for (int i = 0; i < end_above.size(); i++)
        {
            hull_points.push_back(end_above[i]);
        }        

    } else {
        vector<int> start_below = recurse_hull(start_index, furthest_point, start_part.second, false);
        vector<int> end_below = recurse_hull(furthest_point, end_index, end_part.second, false); 
        for (int i = 0; i < start_below.size(); i++)
        {
            hull_points.push_back(start_below[i]);
        }
        for (int i = 0; i < end_below.size(); i++)
        {
            hull_points.push_back(end_below[i]);
        }                  
    }
    
    return  hull_points;
}

// partition taken from solution for quick hull by Dennehy (2018)
pair<vector<int>, vector<int>> Case::partition(int start_index, int end_index, vector<int> points) {  
    vector<int> points_above;
    vector<int> points_below;

    double x_start = x_coordinates[start_index];
    double x_end = x_coordinates[end_index];

    double y_start = y_coordinates[start_index];
    double y_end = y_coordinates[end_index];

    // X coordinates same would create division by zero
    if (x_start == x_end) {
        return make_pair(points_above, points_below);
    } 

    // Find equation of line between start and end points
    double gradient = (y_end - y_start) / (x_end - x_start);
    double intercept = y_start - gradient * x_start;
    // Check whether points are above or below line 
    // compare y coordinate of point to y coordinate of line for that same x value
    for (int i = 0; i < points.size(); i++)
    {
        int p_i = points[i];
        int x_i = x_coordinates[p_i];
        int y_i = y_coordinates[p_i];

        if (y_i > gradient * x_i + intercept) {
            points_above.push_back(p_i);
        } else if (y_i < gradient * x_i + intercept) {
            points_below.push_back(p_i);
        }
    }
    return make_pair(points_above, points_below);
}

// dist_from_line taken from solution for quick hull by Dennehy (2018)
double Case::dist_from_line(int start_index, int end_index, int check_index) {
    int x_start = x_coordinates[start_index];
    int x_end = x_coordinates[end_index];
    int x_check = x_coordinates[check_index];

    int y_start = y_coordinates[start_index];
    int y_end = y_coordinates[end_index];
    int y_check = y_coordinates[check_index];    

    int a = y_start - y_end;
    int b = x_end - x_start;
    int c = x_start * y_end - x_end * y_start;

    return abs(a * x_check + b * y_check + c) / sqrt(a * a + b * b);
}

vector<int> Case::get_path() {
    vector<int> path;
    int start_point = 0;
    path.push_back(start_point);
    int current_point = start_point;
    adjacency_matrix.set_col(start_point, 999);
    int max_dist = max_steps;

    // Only check if there are unvisited points, and there is still room to move
    while (max_dist > 0 && path.size() < coordinate_names.size()) {
        vector<int> check = adjacency_matrix.get_row(current_point);
        int min_jump = check[0];
        int min_neighbour = 0;

        // Find nearest neighbour
        for (int i = 1; i < check.size(); i++)
        {
            if (check[i] < min_jump) {
                min_jump = check[i];
                min_neighbour = i;
            }
        }

        // If enough remaining distance to move to nearest neighbour,
        // move there and repeat, but no longer consider previously travelled to node
        // set the distance to travel to an already visited node from any other node to infinity
        if (min_jump <= max_dist) {
            max_dist -= min_jump;
            path.push_back(min_neighbour);
            adjacency_matrix.set_col(min_neighbour, 999);
            current_point = min_neighbour;
        } else {
            break;
        }
    }
    greedy_path = path;
    return path;
}

float Case::chance_of_success() {
    float ret = greedy_path.size();
    ret /= coordinate_names.size();
    return ret;
}

int Case::get_priority() {
    int prio = reward;
    prio *= chance_of_success();
    return prio;
}

void Case::show() {
    vector<vector<char>> map;
    auto start_time = chrono::high_resolution_clock::now();
    boundary = quick_hull();
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    // Get dimensions of map
    // Can do this using boundary, since max and min x and y must be in hull
    int x_max = x_coordinates[boundary[0]];
    int x_min = x_coordinates[boundary[0]];
    int y_max = y_coordinates[boundary[0]];
    int y_min = y_coordinates[boundary[0]];
    for (int i = 1; i < boundary.size(); i++)
    {
        int x = x_coordinates[boundary[i]];
        x_max = x_max < x ? x : x_max;
        x_min = x_min > x ? x : x_min;

        int y = y_coordinates[boundary[i]];
        y_max = y_max < y ? y : y_max;
        y_min = y_min > y ? y : y_min;        
    }
    
    // Fill map with empty characters
    vector<char> row(x_max - x_min + 1, ' ');
    for (int i = 0; i < y_max - y_min + 1; i++)
    {
        map.push_back(row);
    }

    // Set target points to special characters
    // Since dimensions of map are x_max - x_min by y_max - y_min
    // need to normalise coordinates by x and y mins
    for (int i = 0; i < coordinate_names.size(); i++)
    {
        int x_i = x_coordinates[i] - x_min;
        int y_i = y_coordinates[i] - y_min;
        map[y_i][x_i] = 'O';
    }


    for (int i = 0; i < boundary.size(); i++)
    {
        int p_i = boundary[i];
        int x_i = x_coordinates[p_i] - x_min;
        int y_i = y_coordinates[p_i] - y_min;
        map[y_i][x_i] = 'B';
    }

    // Use special character for starting point
    int start = greedy_path[0];
    map[y_coordinates[start] - y_min][x_coordinates[start] - x_min] = 'X';

    // Set path
    // Find how to travel between each successive point in the path
    // For simplicity, move in x direction, then in y direction
    for (int i = 0; i < greedy_path.size() - 1; i++)
    {
        int p_i = greedy_path[i];
        int p_i_1 = greedy_path[i + 1];

        int x_i = x_coordinates[p_i] - x_min;
        int x_i_1 = x_coordinates[p_i_1] - x_min;
        int y_i = y_coordinates[p_i] - y_min;
        int y_i_1 = y_coordinates[p_i_1] - y_min;

        // Need to know where next point is in relation to current point
        // 4 cases:

        // Case 1:
        // x_i >= x_i_1 && y_i >= y_i_1
        if (x_i >= x_i_1 && y_i >= y_i_1) {
            // Mark all xs along traversal
            for (int x = x_i - 1; x > x_i_1; x--)
            {
                map[y_i][x] = '.';
            }

            // Mark all ys along traversal
            for (int y = y_i - 1; y > y_i_1; y--)
            {
                map[y][x_i_1] = '.';
            }

            if (x_i != x_i_1 && y_i != y_i_1) {
                map[y_i][x_i_1] = '.';
            }
        }

        // Case 2:
        // x_i >= x_i_1 && y_i < y_i_1
        if (x_i >= x_i_1 && y_i < y_i_1) {
            // Mark all xs along traversal
            for (int x = x_i - 1; x > x_i_1; x--)
            {
                map[y_i][x] = '.';
            }

            // Mark all ys along traversal
            for (int y = y_i + 1; y < y_i_1; y++)
            {
                map[y][x_i_1] = '.';
            }

            if (x_i != x_i_1) {
                map[y_i][x_i_1] = '.';
            }
        }        

        // Case 3:
        // x_i < x_i_1 && y_i >= y_i_1  
        if (x_i < x_i_1 && y_i >= y_i_1) {
            // Mark all xs along traversal
            for (int x = x_i + 1; x < x_i_1; x++)
            {
                map[y_i][x] = '.';
            }

            // Mark all ys along traversal
            for (int y = y_i - 1; y > y_i_1; y--)
            {
                map[y][x_i_1] = '.';
            }

            if (y_i != y_i_1) {
                map[y_i][x_i_1] = '.';
            }
        }

        // Case 4:
        // x_i < x_i_1 && y_i < y_i_1  
        if (x_i < x_i_1 && y_i < y_i_1) {
            // Mark all xs along traversal
            for (int x = x_i + 1; x < x_i_1; x++)
            {
                map[y_i][x] = '.';
            }

            // Mark all ys along traversal
            for (int y = y_i + 1; y < y_i_1; y++)
            {
                map[y][x_i_1] = '.';
            }

            map[y_i][x_i_1] = '.';
        }                
    }
    

    // Print the map
    for (int i = map.size() - 1; i >= 0; i--)
    {
        vector<char> row_i = map[i];
        for (int j = 0; j < row_i.size(); j++)
        {
            std::cout << row_i[j];
        }
        std::cout << endl;
    }

    std::cout << "Created boundary for " << coordinate_names.size() << " points in ";
    std::cout <<  duration.count() << " microseconds" << endl;
}

Matrix Case::get_matrix() {
    return adjacency_matrix;
}

int Case::get_reward() {
    return reward;
}

Date Case::get_start() {
    return start_date;
}

Date Case::get_end() {
    return end_date;
}