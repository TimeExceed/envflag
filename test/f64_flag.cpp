#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_F64_FLAG(f64_flag);

using namespace std;

int main() {
    auto x = f64_flag();
    if (x) {
        cout << *x;
        return 0;
    } else {
        return 1;
    }
}
