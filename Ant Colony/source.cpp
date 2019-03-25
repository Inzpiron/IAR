#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "source.hpp"
using namespace std;
namespace ac {
    std::vector<std::vector<char>> mapa;
    std::vector<std::vector<Item>> item;
    std::vector<Agent> agent;
    int size_pop;
    int size_itens;
    int size_group;
    int size_i;
    int size_j;

    Agent::Agent() {}
    Agent::Agent(sf::Vector2i bounds) {
        this->bounds = bounds;
        do {
            this->pos.x = std::rand()% (this->bounds.x-1);
            this->pos.y = std::rand()% (this->bounds.y-1);
        } while(ac::mapa[this->pos.y][this->pos.x] != '.');

        ac::mapa[this->pos.y][this->pos.x] = '@';
        this->item_carrying = -1;
        this->rec = sf::RectangleShape(sf::Vector2f(720.0/size_j, 720.0/size_i));
        this->rec.setPosition(this->pos.x * (720.0/size_j), this->pos.y * (720.0/size_i));
        this->rec.setFillColor(sf::Color::Red);
    }

    Item::Item(){}
    Item::Item(sf::Vector2i pos, sf::Color cor) {
        this->pos = pos;
        this->rec = sf::CircleShape(720.0/size_j/2);

        this->rec.setFillColor(cor);
        this->rec.setPosition(pos.x * 720.0/size_j, pos.y * 720.0/size_i);
    }

    void init(int i_len, int j_len, int pop_size, int groups, int items) {
        std::srand(std::time(nullptr));
        size_i = i_len;
        size_j = j_len;
        size_pop = pop_size;
        size_group = groups;
        size_itens = items;

        item = std::vector<std::vector<Item>> (size_group, std::vector<Item>(items));
        mapa = std::vector< std::vector<char> > (i_len, std::vector<char>(j_len, '.'));


        agent = std::vector<Agent>(pop_size);
        for(int i = 0; i < pop_size; i++) {
            agent[i] = Agent(sf::Vector2i(i_len, j_len));
        }

        for(int gr = 0; gr < item.size(); gr++) {
            sf::Color cor(std::rand()%255, std::rand()%255, std::rand()%255);
            for(int it = 0; it < item[gr].size(); it++) {
                int i, j;
                i = j = -1;
                do{
                    i = std::rand()% (i_len-1);
                    j = std::rand()% (j_len-1);
                } while(mapa[i][j] != '.' || (i == j == -1));
                item[gr][it] = Item(sf::Vector2i(j, i), cor);
                mapa[i][j] = (char) 'a' + gr;
            }
        }
    }
}




