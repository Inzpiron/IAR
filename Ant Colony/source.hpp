#ifndef __AC_H_INCLUDED__
#define __AC_H_INCLUDED__

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>

namespace ac {
    class Agent {
    public:
        sf::Vector2i pos;
        sf::Vector2i bounds;
        int item_carrying;
        sf::RectangleShape rec;

        Agent(sf::Vector2i bounds);
        Agent();
    };

    class Item {
    public:
        sf::Vector2i pos;
        sf::CircleShape rec;

        Item();
        Item(sf::Vector2i pos, sf::Color cor);
    };

    extern std::vector<std::vector<char>> mapa;
    extern std::vector<std::vector<Item>> item;
    extern std::vector<Agent> agent;
    
    extern int size_pop;
    extern int size_itens;
    extern int size_group;
    extern int size_i;
    extern int size_j;

    void init(int i_len, int j_len, int pop_size, int itens, int groups);
}

#endif