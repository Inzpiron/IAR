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
    window.setVerticalSyncEnabled(true);


    sf::Clock clock;
    double _time = 0;

    
    ac::init(40, 40, 100, 2, 5);

    for(int i = 0; i < ac::mapa.size(); i++) {
        for(int j = 0; j < ac::mapa[i].size(); j++) {
            cout << ac::mapa[i][j] << " ";
        }
        cout << endl;
    }

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        

        sf::Time elapsed = clock.restart();
        _time += elapsed.asSeconds();
        if(_time >= 0.1) {
            //cout << "FPS: " << 1.0/elapsed.asSeconds() << endl;
            _time = 0;

        }

        // draw it
        window.clear();
        for(int i = 0; i < ac::item.size(); i++)
            for(int j = 0; j < ac::item[i].size(); j++)
                window.draw(ac::item[i][j].rec);

        for(int i = 0; i < ac::agent.size(); i++)
            window.draw(ac::agent[i].rec);
        window.display();
    }

    return 0;
}
