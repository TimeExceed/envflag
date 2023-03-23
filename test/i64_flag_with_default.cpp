#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_I64_FLAG(i64_flag_with_default);

using namespace std;

int main() {
    auto x = i64_flag_with_default();
    if (x) {
        cout << *x;
        return 0;
    } else {
        return 1;
    }
}
