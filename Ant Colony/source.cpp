#include "source.hpp"
using namespace std;

namespace ac {
    std::vector<std::vector<char>> mapa;
    std::vector<std::vector<Item>> item;
    std::vector<Agent> agent;
    int size_pop;
    int size_itens;
    int size_group;
    Window window;

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
    Agent::Agent(sf::Vector2i bounds) {
        this->bounds = bounds;
        do {
            this->pos.x = std::rand()% (this->bounds.x-1);
            this->pos.y = std::rand()% (this->bounds.y-1);
        } while(ac::mapa[this->pos.y][this->pos.x] != '.');

        ac::mapa[this->pos.y][this->pos.x] = '@';
        this->item_carrying = -1;
        this->rec = sf::RectangleShape(sf::Vector2f(ac::window.rect_j, ac::window.rect_j));
        this->rec.setPosition(ac::window.real_position(this->pos.x, this->pos.y));
        this->rec.setFillColor(sf::Color::Red);
    }

    Item::Item(){}
    Item::Item(sf::Vector2i* pos, sf::Color color) {
        this->pos = pos;

        this->rec = sf::CircleShape(ac::window.rect_i/1.98, 4);
        this->rec.setPosition(ac::window.real_position(pos->x, pos->y));
        this->rec.setFillColor(color);
    }

    void init(Window _window, int pop_size, int groups, int items) {
        std::srand(std::time(nullptr));
        window = _window;
        size_pop = pop_size;
        size_group = groups;
        size_itens = items;

        item = std::vector<std::vector<Item>> (size_group, std::vector<Item>(items));
        mapa = std::vector< std::vector<char> > (window.size_i, std::vector<char>(window.size_j, '.'));


        agent = std::vector<Agent>(pop_size);
        for(int i = 0; i < pop_size; i++) {
            agent[i] = Agent(sf::Vector2i(window.size_i, window.size_j));
        }

        for(int gr = 0; gr < item.size(); gr++) {
            sf::Color color(std::rand()%255, std::rand()%255, std::rand()%255);
            for(int it = 0; it < item[gr].size(); it++) {
                int i, j;
                i = j = -1;
                do{
                    i = std::rand()% (window.size_i-1);
                    j = std::rand()% (window.size_j-1);
                } while(mapa[i][j] != '.' || (i == j == -1));
                item[gr][it] = Item(new sf::Vector2i(j,i), color);
                mapa[i][j] = (char) 'a' + gr;
            }
        }
    }
}




