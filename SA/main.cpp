#include <bits/stdc++.h>
#include "random.hpp"
#include "source.hpp"

using namespace std;

int main(int argc, char ** argv) {
    int n1, n2;
    cin >> n1 >> n2;
    ia::init(n1, n2);

    int a1, a2, a3, a4;
    while(cin >> a1 >> a2 >> a3 >> a4) {
        std::pair<int, bool> * p = new std::pair<int, bool>[3];
        p[0] = {a1, (a1 < 0)? false : true};
        p[1] = {a2, (a2 < 0)? false : true};
        p[2] = {a3, (a3 < 0)? false : true};
        ia::add_triple(p);
    }

    return 0;
}