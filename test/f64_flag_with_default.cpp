#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_F64_FLAG_WITH_DEFAULT(f64_flag_with_default);

using namespace std;

int main() {
    auto x = f64_flag_with_default();
    cout << x;
    return 0;
}
