#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_F64_FLAG(f64_flag_with_default);

using namespace std;

int main() {
    auto x = f64_flag_with_default();
    if (x) {
        cout << *x;
        return 0;
    } else {
        return 1;
    }
}
