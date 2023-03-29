#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_BOOL_FLAG_WITH_DEFAULT(bool_flag_with_default);

using namespace std;

int main() {
    auto x = bool_flag_with_default();
    cout << boolalpha << x;
    return 0;
}
