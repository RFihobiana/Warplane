#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void process_events();
        void update(sf::Time dt);
        void draw();
    
    private:
        sf::RenderWindow m_window;
};
