#include "envflag/envflag.hpp"
#include <iostream>

DEFINE_STR_FLAG(str_flag,
    "a str flag for testing");

using namespace std;

int main() {
    auto x = str_flag();
    if (x) {
        cout << *x;
        return 0;
    } else {
        return 1;
    }
}
