#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "source.hpp"

using namespace std;

int main()
{
    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(720, 720), "Particles", sf::Style::Default, settings);


    ac::init(ac::Window(720, 720, 720, 720), 100, 1, 10, 720*3);
    std::thread play (ac::play); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        for(int i = 0; i < ac::mapa.size(); i++) {
            for(int j = 0; j < ac::mapa[i].size(); j++) {
                if(ac::mapa[i][j] != -1) {
                    //ac::item[ac::mapa[i][j]].refresh();
                    //window.draw(ac::item[ac::mapa[i][j]].rec);
                }
            }
        }

        for(int i = 0; i < ac::agent.size(); i++)
            //window.draw(ac::agent[i].rec);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    play.join();

    return 0;
}
