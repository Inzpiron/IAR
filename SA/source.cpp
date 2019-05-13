#include "source.hpp"
#include "random.hpp"

using namespace std;

namespace ia { // inteligencia artificial
    namespace {
        class Triple { 
        public:
            std::pair<int, bool> a;
            std::pair<int, bool> b; 
            std::pair<int, bool> c;

            Triple() {
                this->a = {-1, false};
                this->b = {-1, false};
                this->c = {-1, false};
            }

            Triple(std::pair<int, bool> * p){
                this->a = p[0];
                this->b = p[1];
                this->c = p[2];
            }
        };
        
        struct log {
            vector<int> result;
            int best;
            log(){}
        };

        int n_vars;
        int n_sets;
        bool * vars;
        log log_sa;
        log log_random;
        std::vector< Triple > mapa;

        double obj_function(bool * vet) {
            int sum = 0;
            for(auto item : mapa) {
                if(vet[item.a.first] == item.a.second ||
                   vet[item.b.first] == item.b.second ||
                   vet[item.c.first] == item.c.second)
                    sum++;
            }

            return sum/(double) n_sets;
        }

        void fazer(bool * vet) {
            for(int i = 0; i < ceil(n_vars * 0.05); i++) {
                int pos = bugrand::integer(0, n_vars);
                vet[pos] = !vet[pos];
            }
        }
    }

    Sa_params::Sa_params() {}
    Sa_params::Sa_params(int sa_max, double ti, double tn) {
        this->sa_max = sa_max;
        this->ti = ti;
        this->tn = tn;
        this->i  = 0;
    }

    void init(int n1, int n2) {
        bugrand::reset();
        n_vars = n1;
        n_sets = n2;
        vars = bugrand::vector_bool(n1);
    }

    void add_triple(std::pair<int, bool> * p) {
        mapa.push_back(Triple(p));
    }

    void run_rs() { //random search
        double sum = obj_function(vars);
        bool * _vars = new bool[n_vars];
        std::memcpy(_vars, vars, sizeof(bool) * n_vars);
        log_random.result.push_back(sum);
        cout << sum << endl;

        for(int i = 0; i < 100000; i++) {
            bool * tmp_vet = bugrand::vector_bool(n_vars);
            double tmp_sum = obj_function(tmp_vet);
            log_random.result.push_back(tmp_sum);
            if(tmp_sum > sum) {
                cout << tmp_sum << endl; 
                sum = tmp_sum;
                log_random.best = tmp_sum;
            }
        }
    }
    
    void run_sa(Sa_params params, std::function<double(Sa_params&)> func) { //simulated annealing
        double sol = obj_function(vars);
        bool * _vars = new bool[n_vars];
        bool * __vars = new bool[n_vars];
        std::memcpy(_vars, vars, sizeof(bool) * n_vars);
        cout << params.ti << endl;
        double temp = params.ti;
        while(temp > params.tn) {
            for(int i = 0; i < 200; i++) {
                std::memcpy(__vars, _vars, sizeof(bool) * n_vars);
                fazer(__vars);
                double _pont = obj_function(_vars);
                double __pont = obj_function(__vars);
                
                if(__pont > _pont) {
                    std::memcpy(_vars, __vars, sizeof(bool) * n_vars);
                    if(__pont > sol) { 
                        sol = __pont;
                        cout << sol << endl;
                    }
                } else {
                    double perc = bugrand::real(0, 1);
                    double delta = _pont - __pont;
                    if (perc < std::exp(delta/params.ti)) {
                        std::memcpy(_vars, __vars, sizeof(bool) * n_vars);
                    }
                }
            }
            params.i++;
            temp = func(params);
            cout << "temp " << temp << endl;
            //printf("queda temperatura -> %.8lf\n", temp);
        }

        cout << sol << endl;
    }
}