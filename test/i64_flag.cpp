#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_I64_FLAG(i64_flag);

using namespace std;

int main() {
    auto x = i64_flag();
    if (x) {
        cout << *x;
        return 0;
    } else {
        return 1;
    }
}
