#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_STR_FLAG(str_flag);

using namespace std;

int main() {
    auto x = str_flag();
    if (x) {
        cout << *x;
        return 0;
    } else {
        return 1;
    }
}
