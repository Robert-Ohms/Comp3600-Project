// u6669461

#pragma once
#include <vector>
#include "date.h"
#include "matrix.h"

using namespace std;
class Info {
    public:
        Info();

        Info(string k, Date d);

        void set(string k, Date d) {
            key = k;
            end_date = d;
        }

        string get_key() {return key;}

        Date get_end_date() {return end_date;}

    protected:
        string key;
        Date end_date;
};