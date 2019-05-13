#include <bits/stdc++.h>

namespace ia { // inteligencia artificial
    struct Sa_params {
        int sa_max;
        double ti;
        double tn;
        int i;

        Sa_params();
        Sa_params(int sa_max, double ti, double tn);
    };
    void init(int n1, int n2);
    void add_triple(std::pair<int, bool> * p);
    void run_rs(); //random search
    void run_sa(Sa_params, std::function<double(Sa_params&)>); //simulated annealing
}