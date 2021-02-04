// u6669461

#pragma once
#include <string>

using namespace std;
class Date {
    public:
        Date();

        Date(int d, int m, int y);

        void set(int d, int m, int y) {
            day = d;
            month = m;
            year = y;
        };

        // Compares two dates and returns 1 if comp is earlier than this date
        // -1 if comp is after this date, and 0 if they are equal
        virtual int compare(Date comp);

        // Creates string with format dd/mm/yyyy
        virtual string to_string();

        void from_string(string s);

    protected:
        int day;
        int month;
        int year;
};