#include "random.hpp"

void bugrand::reset() {
    gen = std::mt19937(rd());
}

int bugrand::integer(int i, int j){
    i_dist = std::uniform_int_distribution<>(i, j);
    return i_dist(gen);
}

double bugrand::real(double i, double j){
    r_dist = std::uniform_real_distribution<>(i, j);
    return r_dist(gen);
}

bool bugrand::boolean() {
    return integer(0, 1);
}

bool * bugrand::vector_bool(int n) {
    bool * vet = new bool[n];
    for(int i = 0; i < n; i++)
        vet[i] = bugrand::boolean();

    return vet;
}