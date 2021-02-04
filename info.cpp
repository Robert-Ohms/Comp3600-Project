#include "info.h"

using namespace std;

Info::Info() {
    set("", Date());
}

Info::Info(string k, Date d) {
    set(k, d);
}