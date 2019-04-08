#include "source.hpp"
using namespace std;

namespace ac {
    namespace rand {
        void reset() {
            gen = std::mt19937(rd());
        }

        int integer(int i, int j){
            i_dist = std::uniform_int_distribution<>(i, j);
            return i_dist(gen);
        }

        double real(double i, double j){
            r_dist = std::uniform_real_distribution<>(i, j);
            return r_dist(gen);
        }

        bool boolean() {
            return integer(0, 1);
        }

        int roulette(std::vector<double> row){
            double choosen_by_god = real(0, 1);
            double sum = 0;
            int cont = 0;
            int i;
            for(i = 0; i < row.size(); i++) {
                cont++;
                if(choosen_by_god >= sum && choosen_by_god < sum+row[i]){
                    return i;
                }
                sum += row[i];
            }

            return -1;
        }
    }

    std::vector<std::vector<int>> mapa;
    std::vector<std::vector<int>> agent_map;
    std::vector<Item> item;
    std::vector<Agent> agent;
    int size_pop;
    int size_itens;
    int size_group;
    Window window;
    int Agent::length = 0;
    int** Agent::vision = NULL;
    int Item::count = 0;

    Window::Window(){}
    Window::Window(int i, int j, int ii, int jj) {
        this->pixel_i = i;
        this->pixel_j = j;
        this->size_i = ii;
        this->size_j = jj;
        this->rect_i = ((double)pixel_i)/size_i;
        this->rect_j = ((double)pixel_j)/size_j;
    }

    sf::Vector2f Window::real_position(int j, int i) {
        double x = j * (this->pixel_j/this->size_j);
        double y = i * (this->pixel_i/this->size_i);

        return sf::Vector2f(x, y);
    }

    //AGENT
    Agent::Agent() {}
    Agent::Agent(sf::Vector2i bounds, int id) {
        this->step_count = 0;
        this->id = id;
        this->item_carrying = -1;
        this->bounds = bounds;
        do {
            this->pos.x = std::rand()% (this->bounds.x);
            this->pos.y = std::rand()% (this->bounds.y);
        } while(ac::mapa[this->pos.y][this->pos.x] != -1 && ac::agent_map[this->pos.y][this->pos.x] != 0);

        /*(this->pos.x = 30;
        this->pos.y = 30;*/

        ac::agent_map[this->pos.y][this->pos.x] = 1;
    }
    void Agent::step(sf::Vector2i offset) {
        ac::agent_map[this->pos.y][this->pos.x] = 0;
        this->pos.x += offset.x;
        this->pos.y += offset.y;

        if( this->pos.x < 0) this->pos.x  = this->bounds.y +  this->pos.x;
        if( this->pos.y < 0) this->pos.y  = this->bounds.y + this->pos.y;

        this->pos.x = (this->pos.x%(window.size_i));
        this->pos.y = (this->pos.y%(window.size_j));
        ac::agent_map[this->pos.y][this->pos.x] = 1;
    }

    int Agent::fix_i(int i, int dist) {
        i += dist;
        if(i < 0) i = window.size_i + i;
        i = (i%(window.size_i));
        return i;
    }

    int Agent::fix_j(int j, int dist) {
        j += dist;
        if(j < 0) j = window.size_j + j;
        j = (j%(window.size_j));
        return j;
    }

    void Agent::start_worker() {
        int total = 0;
        int ii = this->pos.y - length;
        int jj = this->pos.x - length;
        int _ii = this->pos.y + length;
        int _jj = this->pos.x + length;
        int idx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        int idy[] = {-1,  1,  0, -1, 1, -1, 1, 0};

        //double pont[4] = {0}; //0 top, 1 right, 2 bottom, 3 left
        int items_around = 0;
        
        for(int i = ii, _i = 0;  i <= _ii; i++, _i++) {
            for(int j = jj, _j = 0; j <= _jj; j++, _j++) {
                int pos_i = i%(this->bounds.y);
                int pos_j = j%(this->bounds.x);
                if(pos_i < 0) pos_i = this->bounds.y + pos_i;
                if(pos_j < 0) pos_j = this->bounds.y + pos_j;
                

                if(!(pos_i == this->pos.y && pos_j == this->pos.x)) {
                    total++;
                    if(ac::mapa[pos_i][pos_j] != -1) {
                        items_around++;
                        /*for(int i = 0; i < 4; i++) {
                            if(this->vision[_i][_j] & 2<<i) {
                                if(this->vision[_i][_j] == 2<<i)
                                    pont[i]++;
                                else 
                                    pont[i] += 0.5;
                            }
                        }*/
                    }
                }
            }
        } 

        double _p_drop, _p_catch;
        _p_drop = _p_catch = -1;
        if(this->item_carrying != -1 && mapa[this->pos.y][this->pos.x] == -1 && items_around > 0) { //Formiga carregando e pisa vazio
            double p_drop = items_around/(double)total; //probabilidade de dropar
            double r = rand::real(0.0, 1.0);
            _p_drop = p_drop;
            if(r <= p_drop) {
                mapa[this->pos.y][this->pos.x] = item[this->item_carrying].id;
                item[this->item_carrying].pos = new sf::Vector2i(this->pos);
                this->item_carrying = -1;
            }
        } else if(this->item_carrying == -1 && mapa[this->pos.y][this->pos.x] != -1 && items_around <= 4){ //Formiga não carregando e pisa formiga
            double p_catch = 1.0 - (items_around/(double)total);
            double r = rand::real(0.0, 1.0);
            _p_catch = p_catch;
            if(r <= p_catch) {
                this->item_carrying = mapa[this->pos.y][this->pos.x];
                mapa[this->pos.y][this->pos.x] = -1;
            }
        }
        
        int dir = -1;
        do {
            dir = rand::integer(0, 7);
            ii = this->fix_i(this->pos.y, idy[dir]);
            jj = this->fix_j(this->pos.x, idx[dir]);
        } while(agent_map[ii][jj] != 0);

        this->step(sf::Vector2i(idx[dir], idy[dir]));
    }

    //ITEM
    Item::Item(){
        this->id = -1;
    }
    Item::Item(sf::Vector2i* pos, int group) {
        this->id = this->count;
        ++this->count;
    
        this->pos = pos;
        this->group = group;
    }

    int ** make_vision(int l) {
        int size = l*2 + 1;
        int ** mapa_vision = new int*[size]();
        for(int i = 0; i < size; i++) {
            mapa_vision[i] = new int[size];
            for(int j = 0; j < size; j++) {
                if(!(i == j && i == l)) {
                    if(i == j) {
                        if(i < l)
                            mapa_vision[i][j]= (2<<0)|(2<<3);
                        else 
                            mapa_vision[i][j]= (2<<1)|(2<<2);
                    } else if(i+j == size-1) {
                        if(i < l)
                            mapa_vision[i][j]= (2<<0)|(2<<1);
                        else 
                            mapa_vision[i][j]= (2<<2)|(2<<3);
                    }else if(i < j) {
                        if(i+j < size - 1)
                            mapa_vision[i][j] = 2<<0;
                        else 
                            mapa_vision[i][j] = 2<<1;
                    }else{
                        if(i+j > size -1)
                            mapa_vision[i][j] =  2<<2;
                        else
                            mapa_vision[i][j] = 2<<3;
                    }
                }
            }
        }
        mapa_vision[l][l] = 0;
        
        return mapa_vision;
    }

    void init(Window _window, int pop_size, int vision, int groups, int items) {
        std::srand(std::time(nullptr));
        window = _window;
        size_pop = pop_size;
        size_group = groups;
        size_itens = items;

        mapa = std::vector< std::vector<int> > (window.size_i, std::vector<int>(window.size_j, -1));
        agent_map = std::vector< std::vector<int> > (window.size_i, std::vector<int>(window.size_j, 0));

        agent = std::vector<Agent>(pop_size);

        Agent::vision = make_vision(vision);
        Agent::length = vision;
        for(int i = 0; i < pop_size; i++) {
            agent[i] = Agent(sf::Vector2i(window.size_i, window.size_j), i);
        }

        for(int gr = 0; gr < groups; gr++) {
            for(int it = 0; it < items; it++) {
                int i, j;
                i = j = -1;
                do{
                    i = std::rand()%(window.size_i);
                    j = std::rand()%(window.size_j);
                } while(mapa[i][j] != -1);
                Item _aux = Item(new sf::Vector2i(j,i), gr);
                item.push_back(_aux);
                mapa[i][j] = _aux.id;
            }
        }

        //Quadrado no centro
        /*for(int i = 10; i < mapa.size()-10; i++) {
            for(int j = 10; j < mapa[i].size()-10; j++){
                Item _aux = Item(new sf::Vector2i(j,i), 0);
                item.push_back(_aux);
                mapa[i][j] = _aux.id;
            }
        }*/
    }

    void play() {
        while(true) {
            for(int i = 0; i < size_pop; i++) {
                agent[i].start_worker();
            }
        }
    }
}




