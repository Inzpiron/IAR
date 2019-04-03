#ifndef __AC_H_INCLUDED__
#define __AC_H_INCLUDED__

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>

namespace ac {
    struct Window {
        int pixel_i;
        int pixel_j;
        int size_i;
        int size_j;
        double rect_i;
        double rect_j;

        Window(int i, int j, int ii, int jj);
        Window();
        sf::Vector2f real_position(int i, int j);
    };

    class Item {
    public:
        static int count;
        int id;
        int group;
        sf::Vector2i * pos;
        sf::RectangleShape rec;

        Item();
        Item(sf::Vector2i* pos, int group, sf::Color cor);
        void refresh();
    };

    class Agent {
    public:
        sf::Vector2i pos;
        sf::Vector2i bounds;
        int item_carrying;

        sf::RectangleShape rec;
        int id;
        int step_count;

        static int ** vision;
        static int length;

        Agent(sf::Vector2i bounds, int id);
        Agent();
        void start_worker();
        void step(sf::Vector2i pos);
    };

    namespace rand {
        int roulette(std::vector<double> row);
    }

     namespace rand {
        namespace {
            std::random_device rd;
            std::mt19937 gen;
            std::uniform_real_distribution<> r_dist;
            std::uniform_int_distribution<> i_dist;
        }

        int roulette(std::vector<double> row);
        void reset();
        int integer(int i, int j);
        double real(double i, double j);
        bool boolean();
    }

    extern std::vector<std::vector<int>> mapa;
    extern std::vector<Item> item; //lista de itens
    extern std::vector<Agent> agent;

    extern int size_pop;
    extern int size_itens;
    extern int size_group;
    extern Window window;

    void init(Window _window, int pop_size, int vision, int groups, int items);
    int ** make_vision(int n);
    void play();
}

#endif