#include "envflag/envflag.hpp"
#include <iostream>

IMPORT_STR_FLAG_WITH_DEFAULT(str_flag_with_default);

using namespace std;

int main() {
    auto x = str_flag_with_default();
    cout << x;
    return 0;
}
