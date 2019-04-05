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


    ac::init(ac::Window(720, 720, 100, 100), 10, 1, 1, 1000);
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
                    sf::RectangleShape rec(sf::Vector2f(ac::window.rect_j, ac::window.rect_j));
                    rec.setFillColor(sf::Color::White);
                    rec.setPosition(ac::window.real_position(j, i));
                    window.draw(rec);
                }
            }
        }

        for(int i = 0; i < ac::agent.size(); i++) {
            sf::RectangleShape rec(sf::Vector2f(ac::window.rect_j, ac::window.rect_j));
            
            if(ac::agent[i].item_carrying != -1)
                rec.setFillColor(sf::Color::Green);
            else
                rec.setFillColor(sf::Color::Red);

            rec.setPosition(ac::window.real_position(ac::agent[i].pos.x, ac::agent[i].pos.y));
            window.draw(rec);
        }

        window.display();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    play.join();

    return 0;
}
