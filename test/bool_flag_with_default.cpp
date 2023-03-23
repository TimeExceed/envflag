#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_BOOL_FLAG(bool_flag_with_default);

using namespace std;

int main() {
    auto x = bool_flag_with_default();
    if (x) {
        cout << boolalpha << *x;
        return 0;
    } else {
        return 1;
    }
}
