#include <iostream>

using namespace std;

int main() {
    bool a = true;
    bool b = false;

    bool * aa = &a;
    bool * bb = &b;

    bool c = (*aa) | (*bb);
    cout << c << endl;

    a = false;
    cout << ((*aa) | (*bb)) << endl;

    return 0;
}