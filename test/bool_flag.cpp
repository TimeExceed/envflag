#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_BOOL_FLAG(bool_flag);

using namespace std;

int main() {
    auto x = bool_flag();
    if (x) {
        cout << boolalpha << *x;
        return 0;
    } else {
        return 1;
    }
}
