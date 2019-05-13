#include <bits/stdc++.h>
#include "random.hpp"
#include "source.hpp"

using namespace std;
constexpr double const_pi() { return std::atan(1.0)*4.0; }

int main(int argc, char ** argv) {
    int n1, n2;

    cin >> n1 >> n2;
    ia::init(n1, n2);

    int a1, a2, a3, a4;
    while(cin >> a1 >> a2 >> a3 >> a4) {
        std::pair<int, bool> * p = new std::pair<int, bool>[3];
        p[0] = {abs(a1), (a1 < 0) ? false : true};
        p[1] = {abs(a2), (a2 < 0) ? false : true};
        p[2] = {abs(a3), (a3 < 0) ? false : true};
        ia::add_triple(p);
    }
    
    ia::run_rs();
    cout << endl;
    ia::run_sa(ia::Sa_params(200, 90, 1e-10), [](ia::Sa_params &p){
        return (0.5 * (p.ti - p.tn) * (1 + cos((p.i * const_pi()) / (double) p.sa_max))) + p.tn;
        //return p.ti - p.i*(p.ti - p.tn)/double(p.sa_max);
    });

    return 0;
}