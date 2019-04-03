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
            double choosen_by_god = rand::real(0, 1);
            double sum = 0;

            for(int i = 0; i < row.size(); i++) {
                if(choosen_by_god >= sum && choosen_by_god < row[i])
                    return i;
                sum += row[i];
            }
        }
    }

    std::vector<std::vector<int>> mapa;
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

    Agent::Agent() {}
    Agent::Agent(sf::Vector2i bounds, int id) {
        this->step_count = 0;
        this->id = id;
        this->item_carrying = -1;
        this->bounds = bounds;
        do {
            this->pos.x = std::rand()% (this->bounds.x-1);
            this->pos.y = std::rand()% (this->bounds.y-1);
        } while(ac::mapa[this->pos.y][this->pos.x] != -1);

        this->rec = sf::RectangleShape(sf::Vector2f(ac::window.rect_j, ac::window.rect_j));
        this->rec.setPosition(ac::window.real_position(this->pos.x, this->pos.y));
        this->rec.setFillColor(sf::Color::Magenta);
    }

    void Agent::step(sf::Vector2i offset) {
        this->pos.x += offset.x;
        this->pos.y += offset.y;

        this->pos.x %= window.size_i;
        this->pos.y %= window.size_j;

        this->rec.setPosition(ac::window.real_position(this->pos.x, this->pos.y));
    }

    void Agent::start_worker() {
        std::cout << std::this_thread::get_id() << endl;
        rand::reset();

        int total = 0;
        while(true) {
            cin.get();

            this->step(sf::Vector2i(1, 0));
            int ii = this->pos.y - length;
            int jj = this->pos.x - length;
            int _ii = this->pos.y + length;
            int _jj = this->pos.x + length;

            double idx[] = {2<<0, 2<<1, 2<<2, 2<<3};
            double pont[4] = {0}; //0 top, 1 right, 2 bottom, 3 left
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
                            for(int i = 0; i < 4; i++) {
                                if(this->vision[_i][_j] & 2<<i) {
                                    if(this->vision[_i][_j] == 2<<i)
                                        pont[i]++;
                                    else 
                                        pont[i] += 0.5;
                                }
                            }
                        }
                    }
                }
            }

            
            if(this->item_carrying != -1 && mapa[this->pos.y][this->pos.x] == -1) {
                double p_drop = (total-items_around)/((double)items_around); //probabilidade de dropar
                int r = rand::roulette({p_drop, 1.0-p_drop});

                if(r == 0) {
                    mapa[this->pos.y][this->pos.x] = item[this->item_carrying].id;
                    this->item_carrying = -1;
                }
            } else if(this->item_carrying == -1 && mapa[this->pos.y][this->pos.x] != -1){
                double p_catch = (total)/((double) items_around);
                cout << p_catch << endl;
                //int r = rand::roulette({p_catch, 1.0-p_catch});

                //if(r == 0) {
                    //this->item_carrying = mapa[this->pos.y][this->pos.x].id;
                    //mapa[this->pos.y][this->pos.x] = Item();
                //}
            }

            std::cout << "top: " << pont[0] << endl;
            std::cout << "right: " << pont[1] << endl;
            std::cout << "down: " << pont[2] << endl;
            std::cout << "left: " << pont[3] << endl;
            std::cout << items_around << " " << total << endl;
            std::cout << endl;
            
        }
    }

    Item::Item(){
        this->id = -1;
    }
    Item::Item(sf::Vector2i* pos, int group,  sf::Color color) {
        this->id = this->count;
        ++this->count;
    
        this->pos = pos;
        this->group = group;
        this->rec = sf::RectangleShape(sf::Vector2f(ac::window.rect_j, ac::window.rect_j));
        this->rec.setPosition(ac::window.real_position(pos->x, pos->y));
        this->rec.setFillColor(color);
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

        agent = std::vector<Agent>(pop_size);

        Agent::vision = make_vision(vision);
        Agent::length = vision;
        for(int i = 0; i < pop_size; i++) {
            agent[i] = Agent(sf::Vector2i(window.size_i, window.size_j), i);
        }

        for(int gr = 0; gr < groups; gr++) {
            int t_cinza = std::rand()%255;
            sf::Color color(t_cinza, t_cinza, t_cinza); //formiga morta = cinza
            for(int it = 0; it < items; it++) {
                int i, j;
                i = j = -1;
                do{
                    i = std::rand()%(window.size_i);
                    j = std::rand()%(window.size_j);
                } while(mapa[i][j] != -1);
                Item _aux = Item(new sf::Vector2i(j,i), gr, color);
                item.push_back(_aux);
                mapa[i][j] = _aux.id;
            }
        }
    }

    void play() {
        #pragma omp parallel for
        for(int i = 0; i < size_pop; i++) {
            agent[i].start_worker();
        }
    }
}




