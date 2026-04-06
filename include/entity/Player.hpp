#pragma once

#include "command/CommandQueue.hpp"
#include <SFML/Window/Event.hpp>
class Player {
    /* This class give an order to player's aircraft */
    public:
        Player();
        void handle_event(const sf::Event& event, CommandQueue& commands);
        void handle_realtime_event(CommandQueue& commands);
};
