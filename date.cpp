// u6669461

#include "date.h"

using namespace std;
Date::Date() {
    set(1, 1, 1900);
}

Date::Date(int d, int m, int y) {
    set(d, m, y);
}

int Date::compare(Date comp) {
    if (year > comp.year) { return 1;}
    else if (year < comp.year) {return -1;}

    if (month > comp.month) { return 1;}
    else if (month < comp.month) {return -1;}

    if (day > comp.day) { return 1;}
    else if (day < comp.day) {return -1;}   
    
    return 0;
}

string Date::to_string() {
    string ret = "";
    if (day < 10) {
        ret += '0';
    }
    ret += std::to_string(day);
    ret += '/';
    if (month < 10) {
        ret += '0';
    }
    ret += std::to_string(month);
    ret += '/';
    ret += std::to_string(year);
    return ret;
}

// Take string of form dd/mm/yyyy
void Date::from_string(string s) {
    day = stoi(s.substr(0, 2));
    month = stoi(s.substr(3, 2));
    year = stoi(s.substr(6, 4));
}
