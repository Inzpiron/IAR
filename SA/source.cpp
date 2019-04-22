#include "source.hpp"

namespace ia { // inteligencia artificial
    namespace {
        class Triple { 
        public:
            std::pair<int, bool> a;
            std::pair<int, bool> b; 
            std::pair<int, bool> c;

            public Triple() {
                this->a = {-1, false};
                this->b = {-1, false};
                this->c = {-1, false};
            }

            public Triple(std::pair<int, bool> * p){
                this->a = p[0];
                this->b = p[1];
                this->c = p[2];
            }
        };
        
        int n_vars;
        int n_sets;

        bool * vars;
        std::map<Triple, bool> mapa;
    }

    void init(int n1, int n2) {
        n_vars = n1;
        n_sets = n2;
        vars = new bool[n_vars];
    }

    void add_triple(std::pair<int, bool> * p) {
        Triple tmp_triple(p);
        mapa[tmp_triple] = false;
    }
}