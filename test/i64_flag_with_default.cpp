#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_I64_FLAG_WITH_DEFAULT(i64_flag_with_default);

using namespace std;

int main() {
    auto x = i64_flag_with_default();
    cout << x;
    return 0;
}
