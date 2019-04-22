#include <bits/stdc++.h>

namespace bugrand {
    namespace {
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<> r_dist;
        std::uniform_int_distribution<> i_dist;
    }    

    void reset();
    int integer(int i, int j);
    double real(double i, double j);
    bool boolean();
}