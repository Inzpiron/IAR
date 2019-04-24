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
                cout << "nao me fode" << endl;
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

        int n_vars;
        int n_sets;
        bool * vars;
        std::vector< Triple > mapa;

        int obj_function(bool * vet) {
            int sum = 0;
            for(auto item : mapa) {
                if(vet[item.a.first] == item.a.second ||
                   vet[item.b.first] == item.b.second ||
                   vet[item.c.first] == item.c.second)
                    sum++;
            }

            return sum;
        }
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

    void random_search() {
        int sum = obj_function(vars);
        bool * _vars = new bool[n_vars];
        std::memcpy(_vars, vars, sizeof(bool) * n_vars);

        for(int i = 0; i < n_vars; i++) 
            cout << vars[i];
        cout << " - " << sum << endl;
        for(int i = 0; i < 3000; i++) {
            bool * tmp_vet = bugrand::vector_bool(n_vars);
            int tmp_sum = obj_function(tmp_vet);
            if(tmp_sum > sum) { 
                for(int i = 0; i < n_vars; i++) 
                    cout << tmp_vet[i];

                cout << " - " << tmp_sum << endl;
                sum = tmp_sum;
                vars = tmp_vet;
            }
        }
    }
}